package net;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.Reader;
import java.io.Writer;
import java.net.ServerSocket;
import java.net.Socket;

public class CInterface {
	public static void socketmain(){
		int port = 15777;
		int MAX_BUFFER = 2048;
		try {
			//定义一个ServerSocket监听在端口8899上  
	      	ServerSocket server = new ServerSocket(port);
			//server尝试接收其他Socket的连接请求，server的accept方法是阻塞式的  
			Socket socket = server.accept();
			Reader reader = new InputStreamReader(socket.getInputStream());    
		    Writer writer = new OutputStreamWriter(socket.getOutputStream());  
			char ReceiveBuffer[] = new char[MAX_BUFFER];  
			char SendBuffer[] = "ffffff".toCharArray();  
			int bytes = 0;  
			StringBuilder sb = new StringBuilder();  
			while (true) {
				if((bytes=reader.read(ReceiveBuffer)) != -1){
					sb.append(new String(ReceiveBuffer, 0, bytes));  
					System.out.println("from client: " + sb); 
				} 
				writer.write(SendBuffer);
				writer.flush(); 
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
//			writer.close();
//			reader.close();
//			socket.close();
//			server.close();
			e.printStackTrace();
		}  
	}
}
