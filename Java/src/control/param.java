package control;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import model.CInterfaceExtra;
import model.ParamInterfaceExtra;
import net.sf.json.JSONArray;

/**
 * Servlet implementation class param
 */
@WebServlet("/param")
public class param extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public param() {
        super();
        ParamInterfaceExtra.pi.dummy();
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
		String paramString=request.getParameter("name");
		char[] paramChar=paramString.toCharArray();
		
		String returnparam=ParamInterfaceExtra.pi.Request(paramChar);
		
		JSONArray jsonArray2 = JSONArray.fromObject(returnparam);  
		PrintWriter out= response.getWriter();
		System.out.println(jsonArray2.toString());
        //把java数组转化成转化成json对象   
		out.print(jsonArray2.toString());
		out.flush();
		out.close();
        System.out.println("param sevlet finish");
	}

}
