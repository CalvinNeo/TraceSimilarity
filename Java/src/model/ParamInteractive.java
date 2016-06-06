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
		BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(process.getInputStream()));
		while((s=bufferedReader.readLine()) != null)
		{
		   iwant=iwant+"?"+s;//?来分割每一行
		}
		//process.waitFor();

		return iwant;
	 }
}
