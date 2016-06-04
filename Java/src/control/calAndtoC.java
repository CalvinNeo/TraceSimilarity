package control;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import model.CInterfaceExtra;
import model.ParamInterfaceExtra;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;


import model.CInterfaceExtra;
import model.NameAndPoints;
import net.sf.json.JSONArray;

/**
 * Servlet implementation class calAndtoC
 */
@WebServlet("/calAndtoC")
public class calAndtoC extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public calAndtoC() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		response.getWriter().append("Served at: ").append(request.getContextPath());
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
		String nameListString=request.getParameter("name");
		char[] nameListChar=nameListString.toCharArray();
		System.out.println("dddd");
		String fromC= CInterfaceExtra.ci.Request(nameListChar);
		String[] strs = fromC.split("\\:");
		
		
		List<ArrayList<ArrayList<String[]>>> all=new ArrayList<ArrayList<ArrayList<String[]>>>();
		for(int i=0;i<strs.length;i++)
		{
			ArrayList<ArrayList<String[]>> alFilePal=new ArrayList<ArrayList<String[]>>();//文件1  文件2 相似度
			String strSingleFileAndSim[]=strs[i].split("\\*");
			for(int j=0;j<strSingleFileAndSim.length-1;j++)
			{
				String nameAndNum[]=strSingleFileAndSim[j].split("\\&");
				String filePath="C:/datasets/"+nameAndNum[0];
				String file2Num=nameAndNum[1];
				String Num2[]=file2Num.split("\\!");
				int startLine=Integer.parseInt(Num2[0])+2;
				int endLine=Integer.parseInt(Num2[1])+2;
				NameAndPoints nap=new NameAndPoints();
				ArrayList<String[]> alNameAndPoints=nap.getNameAndPoints(filePath,startLine,endLine);
				//该al包含
				alFilePal.add(alNameAndPoints);
			}
			String simNum=strSingleFileAndSim[strSingleFileAndSim.length-1];
			String[] simNum2 = new String[1];
			simNum2[0]=simNum;
			ArrayList<String[]> alSim=new ArrayList<>();
			alSim.add(simNum2);
			alFilePal.add(alSim);//把相似度数值做成String【】做成ArrayList 放在alFilePal最后一个位置
			
			all.add(alFilePal);
		}
		
		JSONArray jsonArray2 = JSONArray.fromObject(all);  
		PrintWriter out= response.getWriter();
		System.out.println(jsonArray2.toString());
        //把java数组转化成转化成json对象   
		out.print(jsonArray2.toString());
		out.flush();
		out.close();
        System.out.println("finish");
	}

}
