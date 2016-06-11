package model;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Cinteractive
{
 public String interactiveC(String param) throws Exception
 {
	String s;
	String iwant="ccc";
	int flag=0;
	Runtime rnn=Runtime.getRuntime();
	Process process = rnn.exec("C:\\datasets\\TraceSimilarity.exe "+param+"");
	BufferedInputStream in = new BufferedInputStream(process.getInputStream());
	BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(in));
	 if (process.waitFor() != 0) {  
         if (process.exitValue() == 1)//p.exitValue()==0表示正常结束，1：非正常结束  
             System.err.println("命令执行失败!");  
     }
	while((s=bufferedReader.readLine()) != null)
	{ //System.out.println(s);
	    flag++;
	    if(flag==2)
	    {
	     iwant=s;
	    }
	}
	  bufferedReader.close();  
      in.close(); 
	//bufferedReader.close();
	//process.waitFor();
	//process.destroy();
	return iwant;
 }
}
