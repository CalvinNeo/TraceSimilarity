package model;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.LineNumberReader;
import java.util.ArrayList;

public class NameAndPoints
{
  //fileName:文件路径    startline：对应csv文件起始2 	 设置startIndex\endIndex=-1为读取所有点
  public ArrayList<String[]> getNameAndPoints(String fileName,int startIndex,int endIndex)
  {
	    ArrayList<String[]> altwoORthree=new ArrayList<String[]>();
	    try {
	    	int startLine=2;
		    int endLine=getTotalLines(fileName);
		    if(startIndex!=-1)
		    {
		    	startLine=startIndex;
		    }
		    if(endIndex!=-1)
		    {
		    	endLine=endIndex;
		    }
		   
		    String[] fileNametoAl = new String[1];
		    fileNametoAl[0]=fileName;
		    altwoORthree.add(fileNametoAl);//将文件路径写入进string数组 放在al第一个位置
            BufferedReader reader = new BufferedReader(new FileReader(fileName));
            //reader.readLine();//第一行信息，为标题信息，不用，如果需要，注释掉
            if (startLine <= 1 || endLine > getTotalLines(fileName) || endLine<startLine) {  
                System.out.println("文件开始和结束行数有问题");  
                System.exit(0);  
            } 
            String line = null;
            int lineFlag=0;
            while(lineFlag!=endLine && (line=reader.readLine())!=null){
            	if(lineFlag>=startLine-1)
            	{
                String item[] = line.split(",");//CSV格式文件为逗号分隔符文件，这里根据逗号切分
                altwoORthree.add(item);
            	}
            	lineFlag++;
            } 
        } catch (Exception e) { 
            e.printStackTrace(); 
        }
	    return altwoORthree;
  }

//文件内容的总行数。  
  static int getTotalLines(String file) throws IOException {  
      FileReader in = new FileReader(file);  
      LineNumberReader reader = new LineNumberReader(in);  
      String s = reader.readLine();  
      int lines = 0;  
      while (s != null) {  
          lines++;  
          s = reader.readLine();  
//          if(lines>=2){  
//              if(s!=null){  
//                  System.out.println(s+"$");  
//              }  
//          }  
      }  
      reader.close();  
      in.close();  
      return lines;  
  }  
}  

