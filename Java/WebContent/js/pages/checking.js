'use strict';
var dataTableInstance;
// 用来处理计算最大最小值的类
function MinMax(min, max){
  this.max = max===undefined ? 0 : max;
  this.min = min===undefined ? 0 : min;

}
MinMax.prototype.add = function (val){
  if(this.min > val){
    this.min = val
  }
  if(this.max < val){
    this.max = val
  }
};
MinMax.prototype.test = function (val){

  if (typeof val === 'number'){
    if(val > 500) console.log(val)
    return val <= this.max+0.05 && val >= this.min - 0.05
  } else {
    return val <= this.max && val >= this.min
  }

};

// 这里处理数据的初始化以及控件初始化
$(function (){
  var datePickerOption = {
    "locale": {
      "format": "YYYY-MM-DD",
      "separator": "至",
      "applyLabel": "保存",
      "cancelLabel": "取消",
      "fromLabel": "From",
      "toLabel": "To",
      "customRangeLabel": "Custom",
      "daysOfWeek": [
        "日", "一", "二", "三", "四", "五", "六"
      ],
      "monthNames": [
        "一月", "二月", "三月", "四月", "五月", "六月", "七月", "八月", "九月", "十月", "十一月", "十二月"
      ],
      "firstDay": 1
    }

  };
  $('select').selectpicker({
    style: 'btn-default'
  });


  var dataTableOptions = {
    "scrollX": true,
    "searching": false,
    "pageLength": 30,
    "lengthChange": false,
    fixedHeader: true,
    "language": {
      "sProcessing":   "处理中...",
      "sLengthMenu":   "显示 _MENU_ 项结果",
      "sZeroRecords":  "没有匹配结果",
      "sInfo":         "显示第 _START_ 至 _END_ 项结果，共 _TOTAL_ 项",
      "sInfoEmpty":    "显示第 0 至 0 项结果，共 0 项",
      "sInfoFiltered": "(由 _MAX_ 项结果过滤)",
      "sInfoPostFix":  "",
      "sSearch":       "搜索:",
      "sUrl":          "",
      "sEmptyTable":     "表中数据为空",
      "sLoadingRecords": "载入中...",
      "sInfoThousands":  ",",
      "oPaginate": {
        "sFirst": "首页",
        "sPrevious": "上页",
        "sNext": "下页",
        "sLast": "末页"
      },
      "oAria": {
        "sSortAscending":  ": 以升序排列此列",
        "sSortDescending": ": 以降序排列此列"
      },
    }

  };
  dataTableInstance = $('#check_result').DataTable(dataTableOptions);
  // 这里请求一下table的数据,以便完成上面查询表单的初始化
  $.getJSON('document.json', function (result){
    var now = moment();
    var range = {
      tm: new MinMax(now, now),
      resper: new Set(),
      people: new Set(),
      recorder: new Set(),
      upz: new MinMax(),
      xh: new MinMax(),
      downz: new MinMax(),
      rain: new MinMax()
    };
    var data = result['rows'];
    data.forEach(function (e){
      range.tm.add(moment(e.tm));

      range.resper.add(e.resper);
      e.people.split(',').forEach(function (e2){
        if(e2 !== '') range.people.add(e2);
      });
      range.recorder.add(e.recorder);

      range.upz.add(Number(e.upz));
      range.xh.add(Number(e.xh));
      range.downz.add(Number(e.downz));
      range.rain.add(Number(e.rain));

    });

    // 设置日期范围
    datePickerOption.startDate = range.tm.min;
    datePickerOption.endDate = range.tm.max;
    $('input[type="daterange"]').daterangepicker(datePickerOption);
    // 设置下拉框
    range.resper.forEach(function (e){
      $('#resper').append('<option>' + e + '</option>');
    });
    range.people.forEach(function (e){
      $('#people').append('<option>' + e + '</option>');
    });
    range.recorder.forEach(function (e){
      $('#recorder').append('<option>' + e + '</option>');
    });
    $('select').selectpicker('refresh');
    // 设置滑动条
    $('#upz').data('min', range.upz.min).data('max', range.upz.max);
    $('#xh').data('min', range.xh.min).data('max', range.xh.max);
    $('#downz').data('min', range.downz.min).data('max', range.downz.max);
    $('#rain').data('min', range.rain.min).data('max', range.rain.max);
    $('.rangeslider').ionRangeSlider();
    //console.log(range)
    //console.log(data[0])

  });


});


// 这里是一些操作下的对应处理函数
$(function() {
  var formatRangeDate = function (val){
    var arr = val.split(';');
    return new MinMax(Number(arr[0]), Number(arr[1]))
  };
//  查询按钮
  $('.query_button').click(function (){
    var dateRangeObj = $('#date_range').data('daterangepicker');
    var getRangeData = function (id){
      return formatRangeDate($('#'+id).val());
    };
    var query = {
      dateRange: new MinMax(dateRangeObj.startDate, dateRangeObj.endDate),
      resper: $('#resper').val(),
      people: $('#people').val(),
      recorder: $('#recorder').val(),
      upz: getRangeData('upz'),
      xh: getRangeData('xh'),
      downz: getRangeData('downz'),
      rain: getRangeData('rain')
    };
    // 去除空项目
    for(var i in query){
      if(query.hasOwnProperty(i)){
        if(query[i] === '' || query[i] === null){
          delete query[i]
        }
      }
    }
    getFilteredData(query, function (data){
      var formatted = formatData(data);
      dataTableInstance.clear();
      dataTableInstance.rows.add(formatted).draw();
    });
    console.log('点击查询按钮:', query)
  });

  function getFilteredData(query, cb){
    $.getJSON('document.json', function (result){
      var filtedResult = [];
      result['rows'].forEach(function (e){
        if(!query.dateRange.test(moment(e.tm))) return;
        if(query.resper && query.resper !== e.resper) return;
        if(query.people){
          var people = e.people.split(',');
          var hasOne = false;
          people.forEach(function (e2){
            if(query.people.indexOf(e2) !== -1) hasOne = true;
          });
          if(!hasOne) return;
        }
        if(query.recorder && query.recorder.indexOf(e.recorder) == -1) return;
        if(!query.upz.test(e.upz)) return;
        if(!query.downz.test(e.downz)) return;
        if(!query.xh.test(e.xh)) return;
        if(!query.rain.test(e.rain)) return;
        filtedResult.push(e)
      });

      cb(filtedResult)

    });

  }

// 这里处理用户的查询
  function formatData(data){
    var d = [];
    var j = 0;
    var reflection = ['tm', 'resper', 'people', 'recorder', 'upz', 'xh', 'downz', 'rain', 'locat', 'part', 'brk', 'descipt'];
    for(var i in data){
      if(data.hasOwnProperty(i)){
        d[j] = [];
        reflection.forEach(function (e, index){
          d[j][index] = data[i][e];
        });
        j++;
      }
    }
    return d;
  }


  // 这里是切换隐藏状态的函数
  var listener = {};
  Object.defineProperty(listener, 'tab', {
    get: function (){
      return this._tab;
    },
    set: function (val){
      if (val !== null){
        $('#toggle_query').removeClass('t-open').addClass('t-close')
        $('.tab-pane.active, .nav-tabs .active').removeClass('active')
      } else {
        $('#toggle_query').removeClass('t-close').addClass('t-open')
        $('.nav-tabs li').eq(this._tab).children('a').tab('show');
      }
      this._tab = val
    }
  });

  $('#toggle_query').click(function (){
    if(this.className.indexOf('close') > -1){
      listener.tab = null
    }else {
      listener.tab = $('.tab-pane').index($('.tab-pane.active'))
    }
  });
  $('.nav-tabs li').click(function (){
    listener.tab = null
  })


});
