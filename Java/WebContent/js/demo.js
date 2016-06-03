function readCSV(name) {
	var csv = d3.dsv(',', 'text/csv;charset=gb2312');
	csv(name, function(error, csvdata) {
		if (error) {
			console.log(error);
		} else {
			console.log(csvdata);
			var data = '';
			$.each(csvdata, function(index, ele) {
				data += '(';
				$.each(ele, function(key, val) {
					data += key + ':' + val + ' ';
				})
				data += ")<br>";
			});
			$("#box").html(data);
		}
	});
}
//没有使用

function doNameCheckAndCal()
{
	var flag = 0;
	var NameList = Array();
	for (var i = 0; i < document.getElementsByName("checkbox").length; i++) {
		if (document.getElementsByName("checkbox")[i].checked) {
			var name = document.getElementsByName("checkbox")[i].value;
			flag++;
			NameList.push(name);
		}
	}
	var param=document.getElementById("text").value;
	if(param !== null)
		{
		NameList.push(param);//把参数字符串
		}
	if (flag == 0) 
	{
		alert("没有选择文件！");
	}else if(flag>2)
	{
		alert("文件数超过2！不符合题意！");
	}else
	{
		var param = "";
		for (var i = 0; i < NameList.length; i++) {
			param += NameList[i] + "*";
		}
		$.post('calAndtoC', {name : param },function(data, statu){
			if("success" == statu)
			{
				var aa=data.substring(16);
				var bb=eval(aa);//string转成数组 和servlet定义一致
				drawlineAndSetHTML(bb);
			}else
			{
				alert("Cal error");
			}
		});
	}
}
// 获取点选的文件名并提交到sevlet calAndtoC处理

function param(){
	var paramString=document.getElementsByName("textString").value;
	if(paramString==null)
	{
		alert("内容为空！请输入！")
	}else
	{
		$.post('param', {name :  paramString },function(data, statu){
			if("success" == statu){
				alert(data+"！")
			}else{
				alert("param error");
			}
		});
	}

}
//获取点选的文件名并提交到sevlet param处理 画线

function getCheckName() {
	// document.getElementsByName("checkbox");
	var flag = 0;
	var NameList = Array();
	for (var i = 0; i < document.getElementsByName("checkbox").length; i++) {
		if (document.getElementsByName("checkbox")[i].checked) {
			var name = document.getElementsByName("checkbox")[i].value;
			flag++;
			NameList.push(name);
		}
	}
	if (flag == 0) {
		alert("没有选择文件！");
	} else {
		var param = "";
		for (var i = 0; i < NameList.length; i++) {
			param += NameList[i] + "*";
		}
		$.post('handle', {name :  param },function(data, statu){
			if("success" == statu){
				var aa=data.substring(16);
				var bb=eval(aa);//string转成数组 和servlet定义一致
				drawline(bb);
				//TODO 实现your function 
				//console.log(data);
			}else{
				alert("Show error");
				
			}
		});
		/*$.ajax({
			url : 'handle',
			type : 'post',
			data : {
				name : '[' + param + ']'
			},
			dataType : 'json',
			success : function(json) {
				console.log(json);
			},
			error : function() {
				alert("error");
			}
		});*/
		// var aa="handle?value=www$"
		// window.location.href=aa;
		// var param="";
		// for(var i=0;i<NameList.length;i++)
		// {
		// param += "value="+NameList[i]+"&";
		// }
		// var url ="handle?"+param;
		// window.location.href=url;
		// alert(url);
		// return NameList;
	}
}
// 获取点选的文件名并提交到sevlet handle处理 画线

//function changeHTML(StringID,Stringcontent)
//{
//	var obj;
//	obj=document.getElementById(StringID);
//	obj.innerHTML=Stringcontent;
//}

function drawlineAndSetTable(arr)
{
	var map=initializeMap();
	
	var all=Array();
	all=arr;
	
	var centreX;
	var centreY;
	var firstalFilePal=all[0];
	var firstFile=firstalFilePal[0];
	var firstFilefirstXY=firstFile[1]
	centreX=firstFilefirstXY[0];
	centreY=firstFilefirstXY[1];
	map.centerAndZoom(new BMap.Point(centreX, centreY), 12);
	
	var container=document.getElementById("table");//获取容器div的引用
	
	
	for(k=0;k<all.length;k++)
	{
		 var alFilePal=Array();
		 alFilePal=all[k];
		 var colorFlag=0;
		
		 var alFilePalSim=Array();
		 alSim=alFilePal[alFilePal.length-1];
		 var StringalSim=alSim[0];
		 var StringSim=StringalSim[0];//取出Sim数值
	     var _h4Sim=document.createElement("h4");	//创建表格标题：相似度	
	     _h4Sim.innerHTML=StringSim;//将h4标题设为相似度
	     var _table=document.createElement("table");//创建表格对象
	
		for(var i=0;i<alFilePal.length-1;i++)//取出csv文件 遍历(除了最后一个 里面是相似度)
		{
			var alNameandPoints=Array();
			alNameandPoints=alFilePal[i];//取出一个csv文件
			var pointList=Array();
			
			var tr_1 = document.createElement("tr");
			var td_1 = document.createElement("td");
			var td_2 = document.createElement("td");
			var stringAlFilePath=alNameandPoints[0];
			var stringName=stringAlFilePath[0].substring(12);//干掉路径 保留文件名
			td_1.innerHtml=stringName;
			td_2.innerHtml="文件名：";
			tr_1.appendChild(td_2);
			tr_1.appendChild(td_1);
			_table.appendChild(tr_1);//将文件名写表格第一行
			
			for(var j=1;j<alNameandPoints.length;j++)
			{
			   var arrpoint=alNameandPoints[j];
			   var x=arrpoint[0];
			   var y=arrpoint[1];
			   var point = new BMap.Point(x,y);//创建坐标点
			   pointList.push(point);//画线
			   
			   var  X_Y="("+x+","+y+")";
			   var tr = document.createElement("tr");
			   var td2 = document.createElement("td")
			   var td1 = document.createElement("td")
			   td2.innerHtml="轨迹点"+j+":";
			   td1.innerHtml=X_Y;
			   tr.appendChild(td2);
			   tr.appendChild(td1);//生成轨迹点表格
			}
			var lineColor=color(colorFlag);
			
			_table.appendChild(tr);	//tr加入表格	
			
			var polyline = new BMap.Polyline(pointList, {strokeColor:lineColor, strokeWeight:4, strokeOpacity:2});   //创建折线
			map.addOverlay(polyline);   //增加折线
		}
		colorFlag++;//一对文件路径 使用相同颜色
		
		container.appendChild(_table);//把表格加入进<div>
	}
	

}



function drawline(arr) {
	var map=initializeMap();
	var bb=Array();
	bb=arr;
	var centreX;
	var centreY;
	var centerArray=bb[0];
	var centerArray2=centerArray[1]
	centreX=centerArray2[0];
	centreY=centerArray2[1];
	map.centerAndZoom(new BMap.Point(centreX, centreY), 12);
	var colorFlag=0;
	for(var i=0;i<bb.length;i++)//取出csv文件 遍历
	{
		var arrthis=Array();
		arrthis=bb[i];//取出一个csv文件
		var pointList=Array();
		for(var j=1;j<arrthis.length;j++)
		{
		   var arrpoint=arrthis[j];
		   var x=arrpoint[0];
		   var y=arrpoint[1];
		   var point = new BMap.Point(x,y);//创建坐标点
		   pointList.push(point);
		}
		var lineColor=color(colorFlag);
		colorFlag++;
		var polyline = new BMap.Polyline(pointList, {strokeColor:lineColor, strokeWeight:4, strokeOpacity:2});   //创建折线
		map.addOverlay(polyline);   //增加折线
	}
	return map
}
//调用initializeMap  设置中心点 画折线

function color(Flag)
{
  var flag=Flag%4;
  if(flag==0)
  {
  var Yellow="yellow";
  return Yellow;
  }
  else if(flag==1)
  {
  var Blue="blue";
  return Blue;
  }else if(flag==2)
  {
  var Green="green";
  return Green;
  }else if(flag==3)
  {
  var Red="red"; 
  return Red;
  }else
  {
	alert("color error");  
  }
}

function initializeMap() {
	var map = new BMap.Map("allmap");    // 创建Map实例
	// 初始化地图,设置中心点坐标和地图级别
	map.addControl(new BMap.MapTypeControl());   //添加地图类型控件
	map.addControl(new BMap.ScaleControl());   //比例尺控件，默认位于地图左下方，显示地图的比例关系。
	map.addControl(new BMap.OverviewMapControl());//缩略地图控件，默认位于地图右下方，是一个可折叠的缩略地图
	map.setCurrentCity("南京");          // 设置地图显示的城市 此项是必须设置的
	map.enableScrollWheelZoom(true);     //开启鼠标滚轮缩放
	map.setMapStyle({style:'light'});
	return map;
}
//没有 设置中心点坐标和地图级别

function initialize() {
	var map = new BMap.Map("allmap");    // 创建Map实例
    map.centerAndZoom(new BMap.Point(118.870, 32.030), 12);// 初始化地图,设置中心点坐标和地图级别
	map.addControl(new BMap.MapTypeControl());   //添加地图类型控件
	map.addControl(new BMap.ScaleControl());   //比例尺控件，默认位于地图左下方，显示地图的比例关系。
	map.addControl(new BMap.OverviewMapControl());//缩略地图控件，默认位于地图右下方，是一个可折叠的缩略地图
	map.setCurrentCity("南京");          // 设置地图显示的城市 此项是必须设置的
	map.enableScrollWheelZoom(true);     //开启鼠标滚轮缩放
	map.setMapStyle({style:'light'});
	return map;
}
//创建南京为中心的map

function selectAll(){
	var a = document.getElementsByName("checkbox");
	for(var i = 0;i<a.length;i++){
	if(a[i].type == "checkbox") a[i].checked = true;
	}
	}

function unselectAll(){
	var a = document.getElementsByName("checkbox");
	for(var i = 0;i<a.length;i++){
	if(a[i].type == "checkbox") a[i].checked = false;
	}
	}