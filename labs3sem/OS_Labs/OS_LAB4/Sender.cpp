#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

const int maxLen = 20;

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        std::cout << "Invalid input" << std::endl;
        return 1;
    }

    const char* filename = argv[1];
    int numRecords = atoi(argv[2]);
    int senderId = atoi(argv[3]);

    HANDLE hConsoleMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"ConsoleMutex");
    if (!hConsoleMutex)
    {
        std::cout << "Open mutex failed." << std::endl;
        std::cout << "Press any key to exit." << std::endl;
        std::cin.get();
        return GetLastError();
    }

    std::fstream file(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!file)
    {
        std::cout << "Open file failed." << std::endl;
        std::cout << "Press any key to exit." << std::endl;
        std::cin.get();
        return GetLastError();
    }

    std::wstring eventName = L"SenderReadyEvent" + std::to_wstring(senderId);
    HANDLE hReadyEvent = OpenEvent(EVENT_MODIFY_STATE, FALSE, eventName.c_str());
    if (!hReadyEvent)
    {
        std::cout << "Open event failed." << std::endl;
        std::cout << "Press any key to exit." << std::endl;
        std::cin.get();
        return GetLastError();
    }

    HANDLE hFileMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"FileAccessMutex");
    if (!hFileMutex)
    {
        std::cout << "Open mutex failed." << std::endl;
        std::cout << "Press any key to exit." << std::endl;
        std::cin.get();
        return GetLastError();
    }
    HANDLE hEnoughSpaceEvent = CreateEvent(NULL, TRUE, TRUE, L"EnoughSpace");
    {
        if (!hEnoughSpaceEvent)
        {
            std::cout << "Open event failed." << std::endl;
            std::cout << "Press any key to exit." << std::endl;
            std::cin.get();
            return GetLastError();
        }
    }
    HANDLE hMsgEvent = OpenEvent(EVENT_MODIFY_STATE, FALSE, L"MsgEvent");
    {
        if (!hMsgEvent)
        {
            std::cout << "Open event failed." << std::endl;
            std::cout << "Press any key to exit." << std::endl;
            std::cin.get();
            return GetLastError();
        }
    }
    SetEvent(hReadyEvent);
    std::string cmd;

    while (true)
    {
        WaitForSingleObject(hConsoleMutex, INFINITE);
        std::cout << "|Sender " << senderId+1 << "| Enter command (send/exit): ";
        ReleaseMutex(hConsoleMutex);

        std::cin >> cmd;

        if (cmd == "exit")
        {
            break;
        }
        else if (cmd == "send")
        {
            std::string message;
            
            WaitForSingleObject(hConsoleMutex, INFINITE);
            std::cout << "Enter message: ";
            std::cin.ignore();
            std::getline(std::cin, message);
            ReleaseMutex(hConsoleMutex); 

            if (message.length() > maxLen)
            {
                message = message.substr(0, maxLen);
                std::cout << "20 symbols maximum!!" << std::endl;
            }

            bool written = false;
            while (!written)
            {
                WaitForSingleObject(hFileMutex, INFINITE);

                bool emptySpace = false;

                for (int i = 0; i < numRecords; i++)
                {
                    int pos = i * maxLen;
                    file.seekg(pos);
                    char buff[maxLen];
                    file.read(buff, maxLen);

                    bool empty = true;
                    for (int j = 0; j < maxLen; j++)
                    {
                        if (buff[j] != '\0')
                        {
                            empty = false;
                            break;
                        }
                    }

                    if (empty)
                    {
                        file.seekp(pos);
                        char msg[maxLen] = { 0 };
                        strncpy_s(msg, message.c_str(), maxLen);
                        file.write(msg, maxLen);
                        file.flush();
                        written = true;

                        SetEvent(hMsgEvent);
                        WaitForSingleObject(hConsoleMutex, INFINITE);
                        std::cout << "Message sent to record " << i+1 << std::endl;
                        ReleaseMutex(hConsoleMutex);
                        emptySpace = true;
                        break;
                    }
                }

                ReleaseMutex(hFileMutex);

                if (!written)
                {   
                    std::cout << "Queue is full." << std::endl;
                    ResetEvent(hEnoughSpaceEvent);
                    WaitForSingleObject(hEnoughSpaceEvent, INFINITE);
                }
            }
          
        }
        else
        {
            WaitForSingleObject(hConsoleMutex, INFINITE);
            std::cout << " Unknown command!" << std::endl;
            ReleaseMutex(hConsoleMutex);
        }
    }

    WaitForSingleObject(hConsoleMutex, INFINITE);
    std::cout << "Sender " << senderId+1 << " stopped." << std::endl;
    ReleaseMutex(hConsoleMutex);
    CloseHandle(hReadyEvent);
    CloseHandle(hFileMutex);
    CloseHandle(hMsgEvent);
    CloseHandle(hEnoughSpaceEvent);
    CloseHandle(hConsoleMutex);
    file.close();
    return 0;
}