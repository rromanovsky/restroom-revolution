var SerialPort = require("serialport");
var request = require('request');

var port = new SerialPort("/dev/ttyACM0", {
  baudRate: 9600,
  parser: SerialPort.parsers.readline('\n')
});

port.on('data', function (data) {
  console.log('Data: ' + !!parseInt(data, 10));
  request.post(
    'https://restroom-5a8ee.firebaseio.com/data.json',
    { json: {"thing" : "restroom1", "isBusy" : !!parseInt(data, 10) } },
    function (error, response, body) {
        if (!error && response.statusCode == 200) {
            console.log(body)
        }
    }
  );
});
