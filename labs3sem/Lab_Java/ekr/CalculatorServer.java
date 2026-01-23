import java.io.*;
import java.net.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class CalculatorServer
{

    public static void main(String[] args)
    {
        int port = 1308;

        try (ServerSocket serverSocket = new ServerSocket(port))
        {
            log("Server started on port " + port);

            while (true)
            {
                Socket clientSocket = serverSocket.accept();
                log("New connection: " + clientSocket.getInetAddress());

                new Thread(new ClientHandler(clientSocket)).start();
            }
        } catch (IOException e)
        {
            log("Server error: " + e.getMessage());
        }
    }

    private static void log(String message)
    {
        String time = LocalDateTime.now().format(DateTimeFormatter.ofPattern("HH:mm:ss"));
        System.out.println("[" + time + "] " + message);
    }

    private static class ClientHandler implements Runnable
    {
        private final Socket clientSocket;
        private final String clientIP;

        public ClientHandler(Socket socket)
        {
            this.clientSocket = socket;
            this.clientIP = socket.getInetAddress().toString();
        }

        @Override
        public void run()
        {
            try (
                    BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                    PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true)
            ) {
                String inputLine;
                while ((inputLine = in.readLine()) != null) {
                    if ("exit".equalsIgnoreCase(inputLine.trim())) break;

                    log("Request from " + clientIP + ": " + inputLine);

                    try
                    {
                        String result = calculate(inputLine);
                        out.println(result);
                        log("Result for " + clientIP + ": " + result);
                    } catch (Exception e)
                    {
                        out.println("Error: " + e.getMessage());
                        log("Error for " + clientIP + ": " + e.getMessage());
                    }
                }
            } catch (IOException e) {
                log("Connection with " + clientIP + " lost");
            } finally {
                try {
                    clientSocket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                log("Client " + clientIP + " disconnected");
            }
        }

        private String calculate(String expr) throws Exception
        {
            String finexpr = expr.replaceAll("\\s+", "");
            char operator = 0;
            int ind = -1;
            char[] ops = {'+', '-', '*', '/'};

            for (char op : ops)
            {
                int idx = finexpr.indexOf(op);
                if (idx > 0) {
                    operator = op;
                    ind = idx;
                    break;
                }
            }

            if (ind == -1) throw new Exception("Invalid format");
            double num1 = Double.parseDouble(finexpr.substring(0, ind));
            double num2 = Double.parseDouble(finexpr.substring(ind + 1));
            double result = 0;
            switch (operator)
            {
                case '+': result = num1 + num2; break;
                case '-': result = num1 - num2; break;
                case '*': result = num1 * num2; break;
                case '/':
                    if (num2 == 0) throw new Exception("Division by zero");
                    result = num1 / num2;
                    break;
            }
            return String.valueOf(result);
        }
    }
}