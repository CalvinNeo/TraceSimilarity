package model;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.Reader;
import java.io.Writer;
import java.net.ServerSocket;
import java.net.Socket;

public class ParamInterface
{
	public int port = 15778;
	public static int MAX_BUFFER = 8196;
	public Socket socket;
	public ServerSocket server;
	public void dummy(){
		
	}
	public ParamInterface(){
		try {
			server = new ServerSocket(port);
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} 
		try {  
			socket = server.accept();
		} catch (IOException e) {
			e.printStackTrace();
		}  
	}
	public String Request(char SendBuffer[]){
		Reader reader;
		Writer writer;  
		try {
			reader = new InputStreamReader(socket.getInputStream());
			writer = new OutputStreamWriter(socket.getOutputStream()); 
			char ReceiveBuffer[] = new char[MAX_BUFFER]; 
			int bytes = 0;
			writer.write(SendBuffer);
			writer.flush();
			if((bytes=reader.read(ReceiveBuffer)) != -1){
				return new String(ReceiveBuffer, 0, bytes);
			}
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}     
		return ""; 
	}
}
