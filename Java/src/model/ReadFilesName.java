package model;

import java.io.File;
import java.util.ArrayList;

public class ReadFilesName
{
	public ArrayList<String> getFileList(String path) { 
		ArrayList<String> list = new ArrayList<String>(); 
		  try { 
		   File file = new File(path); 
		   String[] filelist = file.list(); 
		   for (int i = 0; i < filelist.length; i++) { 
		    list.add(filelist[i]); 
		   } 
		  } catch (Exception e) { 
		   e.printStackTrace(); 
		  } 
		  return list; 
		} 

}
