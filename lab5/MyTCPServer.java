import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.io.*;
import java.util.Date;

public class MyTCPServer {
public static void main(String[] args) throws IOException {
	System.out.println("MyTCPServer");
	int portNumber =8000;
	ServerSocket serverSocket = new ServerSocket(portNumber);	
	System.out.println("MyTCPServer is running at port "+serverSocket.getLocalPort()); //serversocket: creates socket,bind,listen
	
	//three handshake process: ServerSocket----accept---> Socket
	//create a socket: 
	while(true){
	
	Socket clientSocket = serverSocket.accept(); //socket used to connect to the client
		//client already connected, if no error
	System.out.println("Client is already connected");
	System.out.println("A client is connected from IP: "+clientSocket.getInetAddress().getHostAddress());
PrintWriter outputStream =new PrintWriter(clientSocket.getOutputStream(), true);
                outputStream.write("helloworld");
	//TCPServerThread th= new TCPServerThread(clientSocket);	
	//th.start();
	}


	//BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
	
	
	}
		
}

class TCPServerThread extends Thread{
	private Socket clientSocket= null;
	TCPServerThread(Socket clientSocket){
		super("TCPServerThread");
		this.clientSocket= clientSocket;
	}
	public void run(){

		try{	/*
			BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
			String inputLine=in.readLine();
		String receivedData = inputLine;
		while((inputLine!=null) && !inputLine.isEmpty()){
		
			inputLine=in.readLine();
			receivedData += inputLine + "\n";
			}
		System.out.println("Data received from client: "+receivedData);	
	
	*/
		//String response = "MyTCPServer\n" +(new Date()).toString() + "\n" +"You have sent: "+receivedData;
		//clientSocket.getOutputStream().write(response.getBytes("UTF-8"));
		PrintWriter outputStream =new PrintWriter(clientSocket.getOutputStream(), true);
                outputStream.write("helloworld");
		
		//clientSocket.getOutputStream().write("Hi");
	
			//clientSocket.close();
	} catch(IOException io){
		System.err.println("Exception is "+io.getMessage());
	}
	}
}












