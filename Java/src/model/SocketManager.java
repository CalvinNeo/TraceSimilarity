package model;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.Reader;
import java.io.Writer;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

 public class SocketManager implements Runnable{
	public int port;
	public static int MAX_BUFFER = 8196;
	public ServerSocket server;
	static List<Socket> socketList = new ArrayList<Socket>();
	Runnable runnable;
	
	public SocketManager(int iport, Runnable r){
		port = iport;
		runnable = r;
	}
	
	@Override
	public void run(){
		try {
			server = new ServerSocket(port);
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} 
		try {  
			while (true) {
				Socket client = server.accept();
				socketList.add(client);
				new Thread(new MessageLoop(client, socketList, runnable)).start();
			}
		} catch (IOException e) {
			e.printStackTrace();
		}  
	}
	
	public String Request(char SendBuffer[]){
		Reader reader;
		Writer writer;  
		try {
			for(Socket socket : socketList){
				reader = new InputStreamReader(socket.getInputStream());
				writer = new OutputStreamWriter(socket.getOutputStream()); 
				char ReceiveBuffer[] = new char[MAX_BUFFER]; 
				int bytes = 0;
				writer.write(SendBuffer);
				writer.flush();
				if((bytes=reader.read(ReceiveBuffer)) != -1){
					return new String(ReceiveBuffer, 0, bytes);
				}
			}
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}     
		return ""; 
	}
	
	public static void init(String[] args) {
		SocketManager manager = new SocketManager(15777);
		new Thread(manager).start();
	}
}
