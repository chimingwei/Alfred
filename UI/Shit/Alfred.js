//radial menu
var items = document.querySelectorAll('.circle a');

for(var i = 0, l = items.length; i < l; i++) {
  items[i].style.left = (50 - 35*Math.cos(-0.5 * Math.PI - 2*(1/l)*i*Math.PI)).toFixed(4) + "%";
  
  items[i].style.top = (50 + 35*Math.sin(-0.5 * Math.PI - 2*(1/l)*i*Math.PI)).toFixed(4) + "%";
}

document.querySelector('.menu-button').onclick = function(e) {

   e.preventDefault();
   document.querySelector('.circle').classList.toggle('open');
}

/*
function slideDown( elem )
{
    elem.style.maxHeight = '600px';
    elem.style.opacity   = '1';
}

function slideUp( elem )
{
    elem.style.maxHeight = '0';
    once( 1, function ()
    {
        elem.style.opacity = '0';
    } );    
}

function once( seconds, callback ) 
{
    var counter = 0;
    var time = window.setInterval( function ()
    {
        counter++;
        if ( counter >= seconds )
        {
            callback();
            window.clearInterval( time );
        }
    }, 1000 );
} */
