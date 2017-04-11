var wifi = require('Wifi');
var http = require('http');

var info = wifi.getIP();
var deviceId = info.mac;
var host = '192.168.2.1:1880';

var currentState = 0;
var prevState = 1;

(function loop () {
  console.log('Loop');
  currentState = analogRead(D0) > 0.2 ? 1 : 0;

  if (currentState != prevState) {
    console.log('Change ' + currentState);
    prevState = currentState;
    http.get('http://' + host + '/change-state?deviceId=' + deviceId + '&state=' + currentState);
  }

  setTimeout(loop, 1000);
})();
