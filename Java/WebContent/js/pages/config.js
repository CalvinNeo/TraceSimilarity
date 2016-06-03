// Vue组件初始化不需要放到$(function(){})里
var app_manage = new Vue({
  el: 'body',
  data: {
    // 添加新字段的话，必须在这里先写上默认值
    newApp: {
      name: '',
      icon: 'cube',
      color: '#16a765'
    },
    // 用整个字符串表示是为了减少编码复杂度
    icons: "archive area-chart arrows at automobile ban bar-chart bars battery-full bell bell-slash binoculars bicycle book bookmark briefcase bug building bullhorn bullseye bus calculator calendar camera check check-square-o clock-o clone close cloud cloud-download cloud-upload code cogs comment-o comments-o copyright crop cube cubes dashboard desktop download edit envelope-o exchange exclamation-triangle external-link file-word-o file-pdf-o file-picture-o file-zip-o film flask folder-o folder-open-o globe group heartbeat home history laptop lock map-o map-signs microphone music newspaper-o pencil phone pie-chart print qrcode refresh server signal sliders star user wrench wifi file file-text"
  },
  computed: {
    arrIcons: function (){
      return this.icons.split(' ')
    }
  },
  methods: {
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
    },
    addNewapp: function (){
      // 如果要和服务器交互，那就先通过ajax请求把name, icon, color发到服务器，服务器返回一个唯一的id
      // 这里的添加应用功能缺少类别和跳转Url的输入内容，真实的应用场景需要加上
      var id = Math.floor(Math.random() * 1000 + 100)
      // 添加新字段必须在这里把字段写进去
      var item_to_add = {
        id: id, name: this.newApp.name, icon: this.newApp.icon, color: this. newApp.color
      };
      var old_list = localStorage.getItem('app_list');
      var new_list;
      if (old_list){
        new_list = JSON.parse(old_list);
        new_list.push(item_to_add)
      } else {
        new_list = [item_to_add]
      }
      localStorage.setItem('app_list', JSON.stringify(new_list))

      // 这里是还原默认值
      this.newApp.name = '';
      this.newApp.icon = 'cube';
      this.newApp.color = '#16a765'
      alert('添加成功')
    },
    showIconModal: function (){
      $('#icon_modal').modal('show');
    },
    chooseIcon: function (icon){
      this.newApp.icon = icon;
      $('#icon_modal').modal('hide');
    }

  }

})



$(function () {
  // 这段初始化应该放在Vue初始化后面，不然应用不到Vue的变量
  $('select[name="colorpicker"]').simplecolorpicker({picker: true, theme: 'fontawesome'}).on('change', function (e) {
    console.log($(this).val())
    app_manage.newApp.color = $(this).val();
  });
});
