package model;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.List;

public class MessageLoop implements Runnable {
	Socket client;
	List<Socket> socketList;
	Runnable runner;
	public MessageLoop(Socket client, List<Socket> socketList, Runnable r) {
		this.client = client;
		this.socketList = socketList;
		this.runner = r;
	}
	
	@Override
	public void run() {
		BufferedReader input;
		DataOutputStream output;
		try {
			input = new BufferedReader(new InputStreamReader(client.getInputStream()));
			output = new DataOutputStream(client.getOutputStream());
			while (true) {
				// 接受一个连接写入
				String listMsg = input.readLine();
				
				System.out.println("Recive from" + client.getInetAddress() + ":" + listMsg);
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}

