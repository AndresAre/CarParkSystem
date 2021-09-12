//String ServerIP = "192.168.1.38"; //Paul Asus  MAC: 40:E2:30:CC:1E:8D
//String ServerIP = "192.168.1.88"; //Darren PC MAC: CC:B0:DA:CA:EA:D1

var ServerIP = '192.168.1.38';
var SENSITIVITY = 0.1;   //Higher means more sensitive, range from 0.0 to 1.0
var PASSWORD = 'iot999'; 

var isCal = 0;  //to keep track of calibration state
var myTimer;
var lightColors;

function getInfo() {
  var navigator = document.getElementById('adminNavigator');
  data = { data: { title: 'IOT Carpark' }, animation: 'slide' };
  navigator.pushPage('info.html', data);
}

function getAdminInfo() {
  var navigator = document.getElementById('adminNavigator');
  data = { data: { title: 'IOT Carpark' }, animation: 'slide' };
  navigator.pushPage('info.html', data);
}

function startTimer() {
  $('#status').html('it worksaaa');
  myTimer = setInterval(function() {
    fetchDataFromServer();
  }, 100);
  document.getElementById("light-img").src="images/green.png";
}

function stopTimer() {
  clearInterval(myTimer);
  document.getElementById("light-img").src="images/red.png";

}


function calibrateOnOff() {
  if(isCal === 0){
    startCalibrate();
    document.getElementById('calbutton').innerHTML = 'Calibrate Off';
  } else if (isCal === 1) {
    stopCalibrate();
    document.getElementById('calbutton').innerHTML = 'Calibrate On';
  }
}

function startCalibrate() {
 
  var url = 'http://' + ServerIP + '/parking/setcmd.php?cmd=1';

  $.ajax(url)
    .done(function(data) {
      $('#status').html('Calibrating...');
    })

    .fail(function() {
      $('#status').html('error not found!');
    });
}

function stopCalibrate() {
 
  var url = 'http://' + ServerIP + '/parking/setcmd.php?cmd=0';
  $.ajax(url)
    .done(function(data) {
      $('#status').html('');
      ons.notification.toast({
        message: 'Calibrate Off',
        timeout: 2000
      });
    })

    .fail(function() {
      $('#status').html('error not found!');
    });
}

function fetchDataFromServer() {
 
  var url = 'http://' + ServerIP + '/parking/getdata.php';
  $.ajax(url)
    .done(function(data) {
      lightColors = JSON.parse(data);

      $('#status-a').html('a: ' + lightColors[0].a);
      $('#status-b').html('b: ' + lightColors[0].b);
      $('#status-c').html('c: ' + lightColors[0].c);
      $('#status-d').html('d: ' + lightColors[0].d);
      $('#status-e').html('e: ' + lightColors[0].e);
      $('#status-f').html('f: ' + lightColors[0].f);
      $('#status-g').html('g: ' + lightColors[0].g);
      $('#status-h').html('h: ' + lightColors[0].h);
      if(lightColors[0].cmd == 0) {
        $('#status-cmd').html('cal: off');
        isCal = 0;
      }
      else {
        $('#status-cmd').html('cal: ON');
        isCal = 1;
      }
      $('#status-sens').html('sens: ' + SENSITIVITY);
  
      setColors();
      
    })

    .fail(function() {
      $('#status').html('error not found!');
    });
}

var green = '#90EE90';
var red = '#FDD5B1';
function setColors() {
  if (lightColors[0].a < SENSITIVITY)
    document.getElementById('a').style.backgroundColor = red;
  else document.getElementById('a').style.backgroundColor = green;

  if (lightColors[0].b < SENSITIVITY)
    document.getElementById('b').style.backgroundColor = red;
  else document.getElementById('b').style.backgroundColor = green;

  if (lightColors[0].c < SENSITIVITY)
    document.getElementById('c').style.backgroundColor = red;
  else document.getElementById('c').style.backgroundColor = green;

  if (lightColors[0].d < SENSITIVITY)
    document.getElementById('d').style.backgroundColor = red;
  else document.getElementById('d').style.backgroundColor = green;

  if (lightColors[0].e < SENSITIVITY)
    document.getElementById('e').style.backgroundColor = red;
  else document.getElementById('e').style.backgroundColor = green;

  if (lightColors[0].f < SENSITIVITY)
    document.getElementById('f').style.backgroundColor = red;
  else document.getElementById('f').style.backgroundColor = green;

  if (lightColors[0].g < SENSITIVITY)
    document.getElementById('g').style.backgroundColor = red;
  else document.getElementById('g').style.backgroundColor = green;

  if (lightColors[0].h < SENSITIVITY) {
    document.getElementById('h').style.backgroundColor = red;
  } else document.getElementById('h').style.backgroundColor = green;
}


var password = '';  //temp password
function doLoginLogoff(){

  //-- logout ---
  if(password === PASSWORD) {
    password = '';
    // document.getElementById('passworddiv').style.visibility = 'visible';
    document.getElementById('passworddiv').style.display = 'block';
 
    //--- make control buttons hidden
    var cb = document.getElementsByClassName('controlbutton');
    for(var i = 0; i < cb.length; i++) {
      cb[i].style.visibility = 'hidden';
    }
    document.getElementById('loginbutton').innerHTML = 'Login';

    //--- make status text hidden
    var st = document.getElementsByClassName('statustext');
    for(var i = 0; i < st.length; i++) {
      st[i].style.visibility = 'hidden';
    }
    return;
  }

  //-- login ---
  password = document.getElementById('passwordinput').value;
  if(password === PASSWORD) {
    document.getElementById('passwordinput').value = '';
    //document.getElementById('passworddiv').style.visibility = 'hidden';
    document.getElementById('passworddiv').style.display = 'none';
    //--- make control buttons visible
    var cb = document.getElementsByClassName('controlbutton');
    for(var i = 0; i < cb.length; i++) {
      cb[i].style.visibility = 'visible';
    }
    document.getElementById('loginbutton').innerHTML = 'Logout';

    //--- make status text visible
    var st = document.getElementsByClassName('statustext');
    for(var i = 0; i < st.length; i++) {
      st[i].style.visibility = 'visible';
    }
  } else {
    alert('wrong password');
  }
}