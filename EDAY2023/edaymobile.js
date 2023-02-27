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

	imgPath = "../Images/car-icon-motor" + motor + ".png";
	document.getElementById("car-icon").src = imgPath;
}

/* TODO add websocket communication stuff for each of the buttons*/
function forward() {
	if(motor=="1"){
		m1='1200';
		m2='9000';
		m3='9000';
		m4='9000';
	}
	else if(motor=="2"){
		m1='9000';
		m2='1200';
		m3='9000';
		m4='9000';
	}
	else if(motor=="3"){
		m1='9000';
		m2='9000';
		m3='0200';
		m4='9000';
	}
	else if(motor=="4"){
		m1='9000';
		m2='9000';
		m3='9000';
		m4='0200';
	}
}
function stop() {
	if(motor=="1"){
		m1='0000';
		m2='9000';
		m3='9000';
		m4='9000';
	}
	else if(motor=="2"){
		m2='0000';
		m1='9000';
		m3='9000';
		m4='9000';
	}
	else if(motor=="3"){
		m3='0000';
		m1='9000';
		m2='9000';
		m4='9000';
	}
	else if(motor=="4"){
		m4='0000';
		m1='9000';
		m2='9000';
		m3='9000';
	}
	
}
function reverse(){
	if(motor=="1"){
		m1='0200';
		m2='9000';
		m3='9000';
		m4='9000';
	}
	else if(motor=="2"){
		m2='0200';
		m1='9000';
		m3='9000';
		m4='9000';
	}
	else if(motor=="3"){
		m3='1200';
		m1='9000';
		m2='9000';
		m4='9000';
	}
	else if(motor=="4"){
		m4='1200';
		m1='9000';
		m2='9000';
		m3='9000';
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
					button = document.getElementById("cbutton");
		  			button.innerText = "Disconnect";
					button.onclick = disconnect;
					button.style.backgroundColor = "#f44336"; // same colors in hex and rgba (red)
					button.style.boxShadow = "1px 5px 20px rgba(244,67,54,0.75)";
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

	button = document.getElementById("cbutton");
	button.innerText = "Connect";
	button.onclick = connect;
	button.style.backgroundColor = "#4CAF50"; // same colors in hex and rgba (green)
	button.style.boxShadow = "1px 5px 20px rgba(76,175,80,0.75)";
}

function styleButton(element) {
	element.style.boxShadow = "inset 0 0 40px rgba(44, 155, 186, 0.75)";
}

function removeStyleButton(element) {
	element.style.boxShadow = "none";
}
