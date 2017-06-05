
import java.io.*;
import java.net.*;

public class MyTCPClient{
 public static void main(String[] args)throws IOException{
	String hostName=args[0];
	    int portNumber=Integer.parseInt(args[1]);
	try{
	    if(args.length!=2){
		System.err.println("Usage: java MyTCPClient <hostname> <portname>");
	    System.exit(1);
	    }
	   
	    Socket socket= new Socket(hostName,portNumber);
	    System.out.println("Connected to server \'"+hostName +"\' at port"+portNumber);
	   

	    //outputstream to send data

	    PrintWriter out= new PrintWriter(socket.getOutputStream(),true);
	   
	    BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
	    BufferedReader stdln= new BufferedReader(new InputStreamReader(System.in));
	    new TCPClientThread(socket).start();
	
	    String userInput;
	    while((userInput=stdln.readLine())!=null){
		if(userInput.equals("exit")||userInput.equals("Exit")) 
			{
			System.out.println("Connection is disconnected");
			System.exit(0);
			}

		out.println(userInput);
	    }
}
	catch(UnknownHostException e)
	{
	System.err.println("Don't know about host"+hostName);
	System.exit(1);
	}
	catch(IOException e)
	{
	System.err.println("Couldn't get I/O for the connection to "+hostName);
	System.exit(1);
	}

	}
}

class TCPClientThread extends Thread {

	private Socket clientSocket = null;

	TCPClientThread(Socket clientSocket) 
	{

		super("TCPClientThread");

		this.clientSocket = clientSocket;

	}

	public void run() {

	try 
	{

		BufferedReader in = new BufferedReader(

		new InputStreamReader(clientSocket.getInputStream()));
	
		while(true){

		String inputLine=in.readLine();

		while ((inputLine!=null) && !inputLine.isEmpty()) 
		{

			System.out.println("received from server: " + inputLine);

			inputLine=in.readLine();
			
		}

	}

	} 
	catch (IOException e) 
	{

		e.printStackTrace();

	}

	}
}


