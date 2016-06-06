package test;

import java.util.ArrayList;

import model.Cinteractive;
import model.NameAndPoints;
import model.ReadFilesName;

public class Test
{

	public static void main(String[] args)
	{
		// TODO Auto-generated method stub
//		ReadFilesName rfp=new ReadFilesName();
//       ArrayList<String> al=rfp.getFileList("C:\\Users\\yxz\\Desktop\\软件杯\\数据集demo");
//       for(int i=0;i<al.size();i++)
//       {
//    	   System.out.println(al.get(i));
//       }
//		ArrayList<String[]> al2=new ArrayList<>();
//		NameAndPoints nap=new NameAndPoints();
//		ArrayList<String[]> al=nap.getNameAndPoints("C:\\datasets\\1.csv",-1, -1);
//		for(int i=0;i<al.size();i++)
//		{
//			String[] s=al.get(i);
//			for(int j=0;j<s.length;j++)
//			{
//				System.out.println("i"+i+"j"+j+s[j]);
//			}
//		}
		
//		String s="jiejfeh.csv&3!7*yuriwe.csv&8!12*相似度值";
//		String[] strs = s.split("\\:");
//		for(int i=0;i<strs.length;i++)
//		{
//			System.out.println(strs[i]);
//			System.out.println(strs.length);
//		}
		
		Cinteractive ci=new Cinteractive();
		String param="2.csv*3.csv";
		try
		{
			String ss=ci.interactiveC(param);
			System.out.println(ss);
		} catch (Exception e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
