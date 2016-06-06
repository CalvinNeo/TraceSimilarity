package control;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;


import model.NameAndPoints;
import net.sf.json.JSONArray;


/**
 * Servlet implementation class handle
 */
@WebServlet("/handle")
public class handle extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public handle() {
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
		String nameList=request.getParameter("name");
		String[] strs = nameList.split("\\*");//只是文件名 不是路径
		List<ArrayList<String[]>> alAll=new ArrayList<ArrayList<String[]>>();
		for(int i=0;i<strs.length;i++)
		{
			String filePath="C:/datasets/"+strs[i];
			NameAndPoints nap=new NameAndPoints();
			ArrayList<String[]> alNameAndPoints=nap.getNameAndPoints(filePath,-1, -1);
			alAll.add(alNameAndPoints);
			//request.getRequestDispatcher("All.jsp").forward(request, response);
			//System.out.println(strs[i]);
		}
		JSONArray jsonArray2 = JSONArray.fromObject(alAll);  
		PrintWriter out= response.getWriter();
		System.out.println(jsonArray2.toString());
        //把java数组转化成转化成json对象   
		out.print(jsonArray2.toString());
		out.flush();
		out.close();
        System.out.println("handle finish");
		//request.setAttribute("alAll", alAll);
	}

}
