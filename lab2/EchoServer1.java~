

import java.net.*;
import java.io.*;

public class EchoServer {
    public static void main(String[] args) throws IOException {
       
        if (args.length != 1) {
            System.err.println("Usage: java EchoServer <port number>");
            System.exit(1);
        }
       
        int portNumber = Integer.parseInt(args[0]);
	// create thread

       
        try {
            ServerSocket serverSocket =
                new ServerSocket(Integer.parseInt(args[0]));
            System.out.println("EchoServer is running at port " + Integer.parseInt(args[0]));
            Socket clientSocket = serverSocket.accept();
            System.out.println("A client is connected ");   
            PrintWriter out =
                new PrintWriter(clientSocket.getOutputStream(), true);                  
            BufferedReader in = new BufferedReader(
                new InputStreamReader(clientSocket.getInputStream()));
   		while(true){
            String inputLine=in.readLine();
            while ((inputLine = in.readLine()) != null) {
                System.out.println("received from client: " + inputLine);
                System.out.println("Echo back");
		inputLine=in.readLine();
                System.out.println(inputLine);
            }
        } catch (IOException e) {
            System.out.println("Exception caught when trying to listen on port "
                + portNumber + " or listening for a connection");
		e.printStackTrace();
            System.out.println(e.getMessage());
        }
    }
}

class TCPClientThread extends Thread{
private Socket clientSocket = null;
TCPClientThread(Socket clientSocket){
super("TCPClientThread");
this.clientSocket=clientSocket;
}
public void run(){
clientSocket.close();
}
}

