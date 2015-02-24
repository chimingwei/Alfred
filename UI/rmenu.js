$(function(){
//radial menu
var items = document.querySelectorAll('.circle a');

for(var i = 0, l = items.length; i < l; i++) {
  items[i].style.left = (50 - 35*Math.cos(-0.5 * Math.PI - 2*(1/l)*i*Math.PI)).toFixed(4) + "%";
  
  items[i].style.top = (50 + 35*Math.sin(-0.5 * Math.PI - 2*(1/l)*i*Math.PI)).toFixed(4) + "%";
}
});

$(function(){
document.querySelector('.menu-button').onclick = function(e) {

   e.preventDefault();
   document.querySelector('.circle').classList.toggle('open');
}
});

//clickable menu
$(function(){
var menu = $('#menu'), but = $('#menu_button');
$(document).on('click', '*', function(evt) {
    evt.stopPropagation(); //<-- stop the event propagating to ancestral elements
    if ($(this).is(but))   //<-- on button click, toggle visibility of menu
        menu.toggle();
    else if (!$(this).closest(menu).length) //<-- on click outside, hide menu
        menu.hide();
});
});

//card flip

$(function(){
$(".cards").click(function(){
    $(this).toggleClass("flip"); 
});
});

$(function(){
$(".cards2").click(function(){
    $(this).toggleClass("flip2"); 
});
});

$(function(){
$(".cards3").click(function(){
    $(this).toggleClass("flip3"); 
});
});

$(function(){
$(".cards4").click(function(){
    $(this).toggleClass("flip4"); 
});
});