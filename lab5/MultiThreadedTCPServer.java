import java.

public class MultiThreadedTCPServer{
	public static void main(String[] args) throws IOException{
		int portNumber = 8000;
		ServerSocket serverSocket = new ServerSocket(portNumber);
		System.out.println("MyTCPServer is running at port" +serverSocket.getLocalPort());
		while(true){
		Socket clientSocket = serverSocket.accept();
		new TCPServerThread(clientSocket).start();



class	TCPServerThread extends Thread{
	private Socket clientSocket= null;
	TCPServerThread(Socket clientSocket){
		super("TCPServerThread");
		this.clientSocket= clientSocket;
	}
	public void run(){
		clientSocket.close();
	}
}
