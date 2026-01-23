import java.io.*;
import java.net.*;
import java.util.Scanner;

public class CalculatorClient
{
    private static final String SERVER_ADDRESS = "localhost";
    private static final int SERVER_PORT = 1308;

    public static void main(String[] args)
    {
        try
                (
                Socket s = new Socket(SERVER_ADDRESS, SERVER_PORT);
                BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));
                PrintWriter out = new PrintWriter(s.getOutputStream(), true);
                Scanner scanner = new Scanner(System.in)
        ) {
            System.out.println("Connected to server");
            System.out.println("Write operation:");

            while (true)
            {
                System.out.print("> ");
                String userInput = scanner.nextLine();

                if ("exit".equalsIgnoreCase(userInput))
                {
                    out.println("exit");
                    break;
                }

                out.println(userInput);

                String response = in.readLine();
                if (response == null)
                {
                    System.out.println("Cutting the connection");
                    break;
                }

                System.out.println("Result: " + response);
            }

        } catch (IOException e)
        {
            System.err.println("Could not connect to server: " + e.getMessage());
        }
    }
}