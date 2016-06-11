package model;

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ParamInteractive
{
	 public String interactiveC(String param) throws Exception
	 {
		String s;
		String iwant="";
	
		Process process;
		process = Runtime.getRuntime().exec("C:\\datasets\\ParamOptimizer.exe "+param+"");
		
		InputStreamReader isr=new InputStreamReader(process.getInputStream());
		BufferedReader bufferedReader = new BufferedReader(isr);
		
		while((s=bufferedReader.readLine()) != null)
		{
			//System.out.println(".........");
		   iwant=iwant+"?"+s;//?来分割每一行
		}
		//process.waitFor();
		bufferedReader.close();
		isr.close();
		return iwant;
	 }
}
