<%@page import="java.util.ArrayList"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@page import="model.ReadFilesName" %>
<%@page import="model.NameAndPoints" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<meta name="viewport" content="initial-scale=1.0, user-scalable=no" />
<style type="text/css">
body, html,#allmap {width: 100%;height: 100%;overflow: hidden;margin:0;font-family:"微软雅黑";}
</style>
<link href="css/buttons.css" rel="stylesheet">
<link href="css/mydemo.css" rel="stylesheet">
<title>地图展示</title>
</head>
<body>

<nav  class="leftbkg">
</nav>

<nav  class="leftop" >

<div id="ShowFileName" >
	
	    
<div name="title">
  <img src="img/logo.png" class="logo-img" alt="" width="55" height="55">
  <h2 class="title">软件杯</h2>
  <h3 class="title2">路径文件选择：</h3>
</div>
          
<div class="setFile">
	<ul >
	<%
	ReadFilesName rfn  = new ReadFilesName();
	ArrayList<String> al= rfn.getFileList("C:\\datasets\\");//获取文件名
	for(int i=0;i<al.size();i++)
	   {
	String name=al.get(i);
	%>
		<li>
		<nobr>
		<input type="checkbox" name="checkbox" class="checkbox" value="<%=name %>">
		<%=name %>
		<nobr>
		</li>
	<% 
	} 
	%>
	</ul>
</div>

<div class="setbutton2">
      <button onclick="selectAll()" class="button button-large button-plain button-border button-box">全选</button>
</div>
<div class="setbutton3">
      <button onclick="unselectAll()" class="button button-large button-plain button-border button-box">反选</button>
</div>
<div class="setbuttonshow">      
<button onclick="getCheckName()" class="button button-glow button-rounded button-raised button-primary setbuttonshow">显示路径</button>
</div>

<div class="setbuttoncal">
<button onclick="doNameCheckAndCal()" class="button button-glow button-rounded button-raised button-primary">相似计算</button>
</div>


<div class="subtitle">
    <h3 >初始化参数设置：</h3>
</div>

<div class="textline">
    <input type="text" name="textString" class="textstring"/>
    <button onclick="param()" class="button button-primary button-box button-small gobutton">GO</button>
</div>


<div class="tabletitle" >
  <h3>计算结果显示：</h3>
</div>
<div id="table">  
</div>


</nav>

<div id="allmap"></div>





<script src="/SimR/d3/d3.js" type="text/javascript" charset="UTF-8"></script>
<script src="/SimR/lib/jquery.js" type="text/javascript" charset="UTF-8"></script>
<script src="/SimR/js/demo.js" type="text/javascript" charset="UTF-8"></script>
<script type="text/javascript" src="http://api.map.baidu.com/api?v=2.0&ak=y1uzGLRhvAt0sm7TeZzn09FFsEfpcsNd"></script>
<script>  
  window.onload = initialize;  //dom加载完毕后执行loadBaiduJs，可以加载百度api的相关js类库。
</script>

<!-- 第三方JS库 -->
<script src="js/bower_components/jquery/dist/jquery.min.js"></script>
<script src="js/bower_components/bootstrap/dist/js/bootstrap.min.js"></script>
<script src="js/bower_components/slimscroll/jquery.slimscroll.min.js"></script>

<!-- AMchart相关 -->
<script src="js/bower_components/amcharts3/amcharts/amcharts.js"></script>
<script src="js/bower_components/amcharts3/amcharts/plugins/dataloader/dataloader.min.js"></script>
<script src="js/bower_components/amcharts3/amcharts/plugins/export/export.min.js"></script>
<script src="js/bower_components/amcharts3/amcharts/serial.js"></script>
<script src="js/vendor/amchart-lang.js"></script>
	
<!-- 项目相关JS文件 -->
<script src="js/pages/common.js"></script>

</body>
</html>