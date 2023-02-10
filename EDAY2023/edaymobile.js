var select = document.getElementById("motorSelect");
var motor = select.options[select.selectedIndex].value;
var message_out = 'M1000100010001000';
var m1='0000';
var m2='0000';
var m3='0000';
var m4='0000';

function val()
{
	select = document.getElementById("motorSelect");
	motor = (select.options[select.selectedIndex].value);
}

/* TODO add websocket communication stuff for each of the buttons*/
function forward() {
	if(motor=="1"){
		m1='1100';
		m2='0000';
		m3='0000';
		m4='0000';
	}
	else if(motor=="2"){
		m1='0000';
		m2='1100';
		m3='0000';
		m4='0000';
	}
	else if(motor=="3"){
		m1='0000';
		m2='0000';
		m3='0100';
		m4='0000';
	}
	else if(motor=="4"){
		m1='0000';
		m2='0000';
		m3='0000';
		m4='0100';
	}
}
function stop() {
	if(motor=="1"){
		m1='2000';
		m2='0000';
		m3='0000';
		m4='0000';
	}
	else if(motor=="2"){
		m2='2000';
		m1='0000';
		m3='0000';
		m4='0000';
	}
	else if(motor=="3"){
		m3='2000';
		m1='0000';
		m2='0000';
		m4='0000';
	}
	else if(motor=="4"){
		m4='2000';
		m1='0000';
		m2='0000';
		m3='0000';
	}
	
}
function reverse(){
	if(motor=="1"){
		m1='0100';
		m2='0000';
		m3='0000';
		m4='0000';
	}
	else if(motor=="2"){
		m2='0100';
		m1='0000';
		m3='0000';
		m4='0000';
	}
	else if(motor=="3"){
		m3='1100';
		m1='0000';
		m2='0000';
		m4='0000';
	}
	else if(motor=="4"){
		m4='1100';
		m1='0000';
		m2='0000';
		m3='0000';
	}
}

function updateMsg(){
		console.log(motor);
		message_out = 'M' + m1 + m2 + m3 + m4 + '\n';
		console.log(message_out);
		ws.send(message_out);
}

function connect() {
  console.log("connecting");
  if ("WebSocket" in window) {
  var socketURL = location.origin.replace(/^http/, 'ws') + ':1234';
  
               // Let us open a web socket
               ws = new WebSocket(socketURL);
				//ws = new WebSocket(url);	
				
               ws.onopen = function() {
				console.log("opened websocket");
                  // Web Socket is connected, send data using send()
                  ws.send("publish motors");
		  document.getElementById("cbutton").innerText = "Connected";
               };
				
               ws.onmessage = function (evt) { 
                  var received_msg = evt.data;
                  console.log(received_msg);
               };
				
               ws.onclose = function() { 
                  
                  // websocket is closed.
                 console.log("websocket connection closed!!");
               };
            } else {
              
               // The browser doesn't support WebSocket
               alert("WebSocket NOT supported by your Browser!");
            }
}

function disconnect() {
	ws.close();
	console.log("user inititated disconnection");
	document.getElementById("cbutton").innerText = "Connect";
}