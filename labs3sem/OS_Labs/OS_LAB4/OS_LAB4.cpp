#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>

const int maxLen = 20;

int main(int argc, char* argv[])
{
    char filename[100];
    int numRecords, numSenders;

    if (argc >= 4) 
    {
        strcpy_s(filename, argv[1]);
        numRecords = std::stoi(argv[2]);
        numSenders = std::stoi(argv[3]);
    }
    else 
    {
        std::cout << "Enter name of the bin file: ";
        std::cin >> filename;
        std::cout << "Enter number of records: ";
        std::cin >> numRecords;
        std::cout << "Enter number of senders: ";
        std::cin >> numSenders;
    }

    std::ofstream outFile(filename, std::ios::binary);
    std::string emptyMsg(maxLen, '\0');
    for (int i = 0; i < numRecords; ++i)
    {
        outFile.write(emptyMsg.c_str(), maxLen);
    }
    outFile.close();

    std::vector<HANDLE> hReadyEvents;
    for (int i = 0; i < numSenders; i++)
    {
        std::wstring eventName = L"SenderReadyEvent" + std::to_wstring(i);
        HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, eventName.c_str());
        if (hEvent == NULL)
        {
            std::cout << "Create event failed" << std::endl;
            return GetLastError();
        }
        hReadyEvents.push_back(hEvent);
    }

    HANDLE hFileMutex = CreateMutex(NULL, FALSE, L"FileAccessMutex");
    if (hFileMutex == NULL)
    {
        std::cout << "Create mutex failed." << std::endl;
        return GetLastError();
    }

    HANDLE hMsgEvent = CreateEvent(NULL, TRUE, FALSE, L"MsgEvent");
    if (hMsgEvent == NULL)
    {
        std::cout << "Create event failed" << std::endl;
        return GetLastError();
    }

    HANDLE hConsoleMutex = CreateMutex(NULL, FALSE, L"ConsoleMutex");
    if (hConsoleMutex == NULL)
    {
        std::cout << "Create console mutex failed." << std::endl;
        return GetLastError();
    }
    HANDLE hEnoughSpaceEvent = CreateEvent(NULL, TRUE, TRUE, L"EnoughSpace");
    if (hEnoughSpaceEvent == NULL)
    {
        std::cout << "Create console mutex failed." << std::endl;
        return GetLastError();
    }

    std::vector<PROCESS_INFORMATION> senderProcesses;

    for (int i = numSenders-1; i >=0; i--)
    {
        STARTUPINFOA si;
        PROCESS_INFORMATION pi;

        ZeroMemory(&si, sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);

        char commandLine[200];
        sprintf_s(commandLine, 200, "Sender.exe \"%s\" %d %d", filename, numRecords, i);

        if (CreateProcessA(
            NULL,
            commandLine,
            NULL,
            NULL,
            FALSE,
            CREATE_NEW_CONSOLE,
            NULL,
            NULL,
            &si,
            &pi))
        {
            std::cout << "Sender process " << i + 1 << " started successfully!" << std::endl;

            senderProcesses.push_back(pi);
        }
        else
        {
            std::cout << "Failed to start Sender process " << i + 1 << std::endl;
        }
    }

    WaitForMultipleObjects(numSenders, hReadyEvents.data(), TRUE, INFINITE);
    std::cout << "All Senders are ready" << std::endl;

    std::fstream file(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!file) 
    {
        std::cout << "Cannot open file" << std::endl;
        return 1;
    }
    std::string cmd;
    int posInd=0;
    while (true)
    {
        WaitForSingleObject(hConsoleMutex, INFINITE);
        std::cout << "|Receiver| Enter command (read/exit): ";
        ReleaseMutex(hConsoleMutex);

        std::cin >> cmd;

        if (cmd == "exit")
        {
            break;
        }
        else if (cmd == "read")
        {
            bool anyMessage = false;

            while (!anyMessage)
            {
                WaitForSingleObject(hFileMutex, INFINITE);


                for (int i = 0; i < numRecords; i++)
                {
                    int Ind = (posInd + i) % numRecords;
                    int pos = Ind * maxLen;
                    file.seekg(pos);
                    char buff[maxLen + 1] = { 0 };
                    file.read(buff, maxLen);

                    bool empty = true;
                    for (int j = 0; j < maxLen; ++j) {
                        if (buff[j] != '\0')
                        {
                            empty = false;
                            break;
                        }
                    }

                    if (!empty)
                    {
                        anyMessage = true;
                        WaitForSingleObject(hConsoleMutex, INFINITE);
                        std::cout << "Message from record " << Ind + 1 << ": " << buff << std::endl;
                        ReleaseMutex(hConsoleMutex);
                        file.seekp(pos);
                        std::string emptyStr(maxLen, '\0');
                        file.write(emptyStr.c_str(), maxLen);
                        file.flush();

                        posInd = (Ind + 1) % numRecords;
                        SetEvent(hEnoughSpaceEvent);
                        break;
                    }
                }
                ReleaseMutex(hFileMutex);

                if (!anyMessage)
                {
                    WaitForSingleObject(hConsoleMutex, INFINITE);
                    std::cout << "No messages. Waiting for new messages..." << std::endl;
                    ReleaseMutex(hConsoleMutex);
                    ResetEvent(hMsgEvent);
                    WaitForSingleObject(hMsgEvent, INFINITE);
                }
            }
      
        }
        else
        {
            WaitForSingleObject(hConsoleMutex, INFINITE);
            std::cout << "Unknown command" << std::endl;
            ReleaseMutex(hConsoleMutex);
        }
    }

    file.close();

    for (auto& pi : senderProcesses)
    {
        TerminateProcess(pi.hProcess, 0);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    }

    for (auto& hEvent : hReadyEvents)
    {
        CloseHandle(hEvent);
    }

    CloseHandle(hFileMutex);
    CloseHandle(hMsgEvent);
    CloseHandle(hEnoughSpaceEvent);
    CloseHandle(hConsoleMutex);

    std::cout << "Receiver stopped." << std::endl;
    return 0;
}