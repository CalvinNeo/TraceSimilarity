package model;

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Cinteractive
{
 public String interactiveC(String param) throws Exception
 {
	String s;
	String iwant="ccc";
	int flag=0;
	Process process;
	process = Runtime.getRuntime().exec("C:\\datasets\\TraceSimilarity.exe "+param+"");
	BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(process.getInputStream()));
	while((s=bufferedReader.readLine()) != null)
	{
	    flag++;
	    if(flag==3)
	    {
	     iwant=s;
	    }
	}
	//process.waitFor();

	return iwant;
 }
}
