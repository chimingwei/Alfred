$(function(){
function doSwap() {
  $("#nav li").each(function() {
    if ($(this).hasClass("active")) {
      swap($(this));
    }
    else {
      swapBack($(this));
    }
  });
}
doSwap();
function clear(o) {
  $("#nav li").each(function() {
    $(this).removeClass("active");
  });
}
$("#nav li").click(function() {
  clear();
  $(this).addClass("active");
  doSwap();
  rotate('.dial',$(this));
                     
});

function rotate(m,o) {
  var id = "#" + $(o).attr("id");
  var menu = $(m);
  
  menu.removeClass('r0 lr1 lr2 rr1 rr2');
  
  if (id == "#email") {
    menu.addClass("lr2");
  }
  if (id == "#skype") {
    menu.addClass('lr1');
    
  }
  if (id == "#cloud") {
    menu.addClass('r0');
  }
  if (id == "#portfolio") {
    menu.addClass('rr1');
  }
  if (id == "#settings") {
    menu.addClass('rr2');
  }
      
  
}

function swap(o) {
  var id = "#" + $(o).attr("id");
  var cimg = new String;
  var burl = "http://grantcr.com/files/",
      ext = ".png"
  cimg = id + " img";
  console.log($(cimg).attr("src"));
  
  if (id == "#email") {
    var nimg = burl + "iemailh" + ext;
    $(cimg).attr("src",nimg);
  }
  if (id == "#skype") {
    var nimg = burl + "photosh" + ext;
    $(cimg).attr("src",nimg);
  }
  if (id == "#cloud") {
    var nimg = burl + "icloudh" + ext;
    $(cimg).attr("src",nimg);
  }
  if (id == "#portfolio") {
    var nimg = burl + "portfolioh" + ext;
    $(cimg).attr("src",nimg);
  }
  if (id == "#settings") {
    var nimg = burl + "settingsh" + ext;
    $(cimg).attr("src",nimg);
  }
  
}

function swapBack(o) {
  var id = "#" + $(o).attr("id");
  var cimg = new String;
  var burl = "http://grantcr.com/files/",
      ext = ".png"
  cimg = id + " img";
  console.log($(cimg).attr("src"));
  
  if (id == "#email") {
    var nimg = burl + "iemail" + ext;
    $(cimg).attr("src",nimg);
  }
  if (id == "#skype") {
    var nimg = burl + "iphoto" + ext;
    $(cimg).attr("src",nimg);
  }
  if (id == "#cloud") {
    var nimg = burl + "icloud" + ext;
    $(cimg).attr("src",nimg);
  }
  if (id == "#portfolio") {
    var nimg = burl + "portfolio" + ext;
    $(cimg).attr("src",nimg);
  }
  if (id == "#settings") {
    var nimg = burl + "settings" + ext;
    $(cimg).attr("src",nimg);
  }
  
}
});


//card flip

$(function(){
document.querySelector("#email").onclick = function(e) {

   e.preventDefault();
   document.querySelector('.cards').classList.toggle('flip');
}
});

$(function(){
document.querySelector("#skype").onclick = function(e) {

   e.preventDefault();
   document.querySelector('.cards2').classList.toggle('flip2');
}
});

$(function(){
document.querySelector('#cloud').onclick = function(e) {

   e.preventDefault();
   document.querySelector('.cards3').classList.toggle('flip3');
}
});

$(function(){
document.querySelector("#portfolio").onclick = function(e) {

   e.preventDefault();
   document.querySelector('.cards4').classList.toggle('flip4');
}
});

$(function(){
document.querySelector("#settings").onclick = function(e) {

   e.preventDefault();
   document.querySelector('.cards4').classList.toggle('flip4');
}
});



