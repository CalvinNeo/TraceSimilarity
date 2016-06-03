// 这个函数仅仅在测试的时候有用，实际的生产服务器请不要用这种方式，应该将其修改为Ajax请求，从服务器获取当前所有的应用列表
function getAppList(){
  var app_list = localStorage.getItem('app_list');
  var default_list = [
    {id: 1, name: '强震系统', icon: 'bullseye', color: '#ed5565'},
    {id: 2, name: 'GNSS', icon: 'globe', color: '#1c84c6'},
    {id: 3, name: '数据汇集', icon: 'pie-chart', color: '#1ab394'},
    {id: 4, name: '巡检系统', icon: 'search', color: '#f8ac59'},
    {id: 5, name: '废弃系统', icon: 'trash', color: '#CCCCCC'}
  ];
  // 如果存在已经保存的app列表，就用保存的
  if (app_list) {
    return JSON.parse(app_list)
  } else {
    localStorage.setItem('app_list', JSON.stringify(default_list))
    return default_list;
  }
}

// Vue组件初始化不需要放到$(function(){})里
var app_manage = new Vue({
  el: 'body',
  data: {
    apps: [],
    owned: [1],
    saved: [1]
  },
  computed: {
    // 待选列表
    unselected_apps: function (){
      return this.extract(this.apps, this.owned, true);
    },
    // 已选列表
    selected_apps: function (){
      return this.extract(this.apps, this.owned);
    },
    // 保存后正式显示的列表
    saved_apps: function (){
      return this.extract(this.apps, this.saved);
    }
  },
  ready: function (){
    this.apps = getAppList();
    var saved_apps = localStorage.getItem('apps');
    if (saved_apps){
      var apps = JSON.parse(saved_apps);
      this.owned = apps;
      this.saved = _.clone(apps)
    }
  },
  methods: {
    add: function (id, pos){
      if (!Number.isNaN(id)){
        if (this.owned.indexOf(id) > -1){
          this.owned.splice(this.owned.indexOf(id), 1)
        }
        this.owned.push(id)
      }

      console.log(this.owned)
    },
    delete: function (id, pos){
      var index = this.owned.indexOf(id);
      if (index >= 0) this.owned.splice(index, 1)
    },
    extract: function (all, part, rev){
      if (rev){
        return _.filter(all, function (e){
          return part.indexOf(e.id) < 0
        })
      } else {
        // 排除不存在的应用
        return _.filter(
          // 对part中的元素，逐一查询全应用数组，获取相应的数据
          _.map(part, function(e) {
            return _.find(all, function (a){
              return a.id == e;
            })
          })
        );
      }

    },
    saveStat: function (){
      this.saved = _.clone(this.owned);
      localStorage.setItem('apps', JSON.stringify(this.saved));
      $('#app_modal').modal('hide')
    },
    darken: function (value, percent){
      if (value.length == 7 && value[0] == '#'){
        var color, p, result, newColor;
        color = {
          r: parseInt(value.substr(1,2), 16),
          g: parseInt(value.substr(3,2), 16),
          b: parseInt(value.substr(5,2), 16)
        }
        p = 1-percent;
        newColor = {
          r: Math.floor(p*color.r),
          g: Math.floor(p*color.g),
          b: Math.floor(p*color.b)
        };
        result = '#' + newColor.r.toString(16) + newColor.g.toString(16) + newColor.b.toString(16);
        return result;
      }else {
        console.warn(value + '不是一个合法的hex颜色值')
        return '#EEEEEE';
      }
    }

  }

})



$(function () {


  // ------   实时水情  ------
  // 生成图表的设置
  var chartOption = {
    // 时间顺序的表格
    "type": "serial",
    "theme": "light",
    "language": "zh",
    "mouseWheelZoomEnabled": true,
    "chartScrollbar": {
      "autoGridCount": true,
      "graph": "v1",
      "scrollbarHeight": 40
    },
    "legend": {
      "useGraphSettings": true
    },
    // 从服务器获取数据
    "dataLoader": {
      "url": "/data/realtime_water_pos.json",
      "format": "json"
    },
    // 坐标轴设定
    "valueAxes": [{
      "id":"v1",
      "axisColor": "#1C84C6",
      "axisThickness": 2,
      "gridAlpha": 0,
      "axisAlpha": 1,
      "position": "left"
    }, {
      "id":"v2",
      "axisColor": "#1AB394",
      "axisThickness": 2,
      "gridAlpha": 0,
      "axisAlpha": 1,
      "position": "right"
    }],
    // 折线图设定
    "graphs": [{
      "valueAxis": "v1",
      "lineColor": "#1C84C6",
      "bullet": "round",
      "bulletBorderThickness": 1,
      "hideBulletsCount": 30,
      "title": "坝上水位",
      "valueField": "up",
  		"fillAlphas": 0
    }, {
      "valueAxis": "v2",
      "lineColor": "#1AB394",
      "bullet": "square",
      "bulletBorderThickness": 1,
      "hideBulletsCount": 30,
      "title": "坝下水位",
      "valueField": "down",
  		"fillAlphas": 0
    }],
    // 鼠标移上去时候的反馈
    "chartCursor": {
      "cursorPosition": "mouse",
      "categoryBalloonDateFormat": 'MM-DD JJ:NN'
    },
    // 用于表示日期的字段
    "categoryField": "date",
    "categoryAxis": {
      "parseDates": true,
      "axisColor": "#DADADA",
      "minorGridEnabled": true,
      "dateFormats": [
        {period:'fff',format:'JJ:NN:SS'},
        {period:'ss',format:'JJ:NN:SS'},
        {period:'mm',format:'JJ:NN'},
        {period:'hh',format:'JJ:NN'},
        {period:'DD',format:'MM-DD'},
        {period:'WW',format:'MM-DD'},
        {period:'MM',format:'MM'},
        {period:'YYYY',format:'YYYY'}
      ]
    },
    // 导出功能
    "export": {
    	"enabled": true,
      "position": "bottom-right"
    }
  }

  // 从服务器获取数据并渲染图标
  var chart = AmCharts.makeChart("chartdiv", chartOption);
  chart.addListener("dataUpdated", function (){
    // 默认缩放显示最新的20条记录
    if (chart.dataProvider){
      chart.zoomToIndexes(chart.dataProvider.length - 20, chart.dataProvider.length - 1);
    }
  });



  // -------  应用管理功能  ---------
  // 设置应用元素的拖拽开始事件。由于元素会动态变化，因此必须使用delegate
  $('#app_modal').delegate('.drag-box', 'dragstart', function (e){
    var target = $(e.target)
    var id = target.data('id');
    e.originalEvent.dataTransfer.dropEffect = "move";
    e.originalEvent.dataTransfer.setData('text/plain', target.find('p.dim-description').text());
    e.originalEvent.dataTransfer.setData('application/appid', id);
  })
  $('#myApp, #unselected_apps').on('dragover', function (e){
    // console.log(e)
    e.preventDefault();
    e.originalEvent.dataTransfer.dropEffect = "move"
  })
  $('#myApp, #unselected_apps').on('drop', function (e){
    e.preventDefault();
    var data = e.originalEvent.dataTransfer.getData("application/appid");
    if (e.target.id == 'myApp'){
      app_manage.add(Number(data));
    }else if($(e.target).parent().attr('id') == 'unselected_apps') {
      app_manage.delete(Number(data));
    }else {
      console.log(e.target)
    }
  })


});
