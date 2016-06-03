// profile-menu点击效果
$(function (){
  $('#profile-menu').click(function (){
    location.href = "./index.html";
  });

  $('#password_field').focusin(function(){
    $('#remember').addClass('active');
  }).focusout(function(){
    $('#remember').removeClass('active');
  });
  $('#remember').click(function (){
    $('#password_field').focus();
  })

  function SmoothlyMenu() {
      if (!$('body').hasClass('mini-navbar')) {
          // Hide menu in order to smoothly turn on when maximize menu
          $('#side-menu').hide();
          // For smoothly turn on menu
          setTimeout(
              function () {
                  $('#side-menu').fadeIn(500);
              }, 100);
      } else {
          // Remove all inline style from jquery fadeIn function to reset menu state
          $('#side-menu').removeAttr('style');
      }
  }

  // 切换按钮动作
  $('.navbar-minimalize').click(function () {
    // 在点击切换按钮时，如果目前是展开状态，就加上效果
    if (!$('body').hasClass('minibar')){
      setAnimateStyle();
    }
    $("body").toggleClass("mini-navbar");
    SmoothlyMenu();
    // 存储导航栏状态
    if (localStorage) {
      if($('body').hasClass('mini-navbar')){
        localStorage.setItem('navbar-status', 'mini')
      }else {
        localStorage.setItem('navbar-status', 'full')
      }
    }
  });

  // 根据存储的导航栏状态更改当前样式
  if (localStorage) {
    var navbar_status = localStorage.getItem('navbar-status')
    if(navbar_status == 'mini'){
      $("body").addClass("mini-navbar");
    }else {
      // 侧边栏展开状态，直接使用效果
      setAnimateStyle();
    }
  }
  // 这个函数用于给边栏切换加上动画效果，但是由于在加载时就使用会导致不必要的动画，所以必须在侧边栏展开状态下使用。
  function setAnimateStyle(){
    var animateStyle = $('<style>body.mini-navbar #page-wrapper {animation: 0.5s slideLeft;}</style>')
    $('head').append(animateStyle)
  }


  $('#stat_table_toggle_button').click(function (){
    $('#stat_table').toggleClass('expand')
  })
});
