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

  if (id == "#calendar") {
    menu.addClass("lr2");
  }
  if (id == "#skype") {
    menu.addClass('lr1');

  }
  if (id == "#weather") {
    menu.addClass('r0');
  }
  if (id == "#settings") {
    menu.addClass('rr1');
  }
  // if (id == "#settings") {
  //   menu.addClass('rr2');
  // }


}

function swap(o) {
  var id = "#" + $(o).attr("id");
  var cimg = new String;
  var burl = "icons/",
      ext = ".png"
  cimg = id + " img";
  console.log($(cimg).attr("src"));

  if (id == "#calendar") {
    var nimg = burl + "gcalh" + ext;
    $(cimg).attr("src",nimg);
  }
  if (id == "#skype") {
    var nimg = burl + "helph" + ext;
    $(cimg).attr("src",nimg);
  }
  if (id == "#weather") {
    var nimg = burl + "weatherh" + ext;
    $(cimg).attr("src",nimg);
  }
  if (id == "#settings") {
    var nimg = burl + "settingsh" + ext;
    $(cimg).attr("src",nimg);
  }
  // if (id == "#settings") {
  //   var nimg = burl + "weatherh" + ext;
  //   $(cimg).attr("src",nimg);
  // }

}

function swapBack(o) {
  var id = "#" + $(o).attr("id");
  var cimg = new String;
  var burl = "icons/",
      ext = ".png"
  cimg = id + " img";
  console.log($(cimg).attr("src"));

  if (id == "#calendar") {
    var nimg = burl + "gcal"+ ext;
    $(cimg).attr("src",nimg);
  }
  if (id == "#skype") {
    var nimg = burl + "help" + ext;
    $(cimg).attr("src",nimg);
  }
  if (id == "#weather") {
    var nimg = burl + "weather" + ext;
    $(cimg).attr("src",nimg);
  }
  if (id == "#settings") {
    var nimg = burl + "settings" + ext;
    $(cimg).attr("src",nimg);
  }
  // if (id == "#settings") {
  //   var nimg = burl + "weatherb" + ext;
  //   $(cimg).attr("src",nimg);
  // }

}
});


//card flip

$(function(){
document.querySelector("#calendar").onclick = function(e) {

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
document.querySelector('#weather').onclick = function(e) {

   e.preventDefault();
   document.querySelector('.cards3').classList.toggle('flip3');
}
});

$(function(){
document.querySelector("#settings").onclick = function(e) {

   e.preventDefault();
   document.querySelector('.cards4').classList.toggle('flip4');
}
});

// $(function(){
// document.querySelector("#settings").onclick = function(e) {

//    e.preventDefault();
//    document.querySelector('.cards4').classList.toggle('flip4');
// }
// });



