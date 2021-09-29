

/* check elke 2 seconden of het bord nog is verbonden, en geef dit weer op blockly.html */
setInterval(function() {
  var xhttp = new XMLHttpRequest();
  var outputStateM;
  
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      if( this.responseText == 1){ 
        outputStateM = Blockly.Msg.TXT_CONNECTED;

      } else { 
        outputStateM = Blockly.Msg.TXT_DISCONNECTED; //in geval van geen communicatie met ATxmega128A1U?
      }
      document.getElementById("status").innerHTML = outputStateM;
    }
  };
  
  xhttp.ontimeout = function(e){
    outputStateM = Blockly.Msg.TXT_DISCONNECTED; //in geval van geen reactie van ESP32
    document.getElementById("status").innerHTML = outputStateM;
  };
  
  xhttp.open("GET", "/status", true);
  xhttp.timeout = 1000; //ms
  xhttp.send();
}, 2000 );


/* geef start-feedback in de start button in blockly.html */
function getStartFeedback(elem) {
  var prevText;
  if (Blockly.Msg.TXT_START != undefined) {
    prevText = Blockly.Msg.TXT_START;
  } else {
//    prevText = document.getElementById(elem).innerHTML; //pak de tekst wat nu op de button staat
    prevText = "Start";
  }

//  document.getElementById(elem).innerHTML = "<img src=\"images/loading.gif\" height=80%/>";
  document.getElementById(elem).innerHTML = "⏳";
  
  var xhr = new XMLHttpRequest();

  xhr.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      if(this.responseText == 1){						//ATmega is gestart
        document.getElementById(elem).innerHTML = "✔️";
        setTimeout(function() {
          document.getElementById(elem).innerHTML = prevText;
        }, 3000); //3 sec ✔️ laten zien
      } else {											//ATmega is nog niet gestart
        setTimeout(function() {
          getStartFeedback(elem); //check over 1 sec nog een keer
        }, 1000);
      }
    }
  };

  xhr.ontimeout = function(e){                //Timeout
    alert(Blockly.Msg.TXT_ONTIMEOUT);
    document.getElementById(elem).innerHTML = "❌";
    setTimeout(function() {
      document.getElementById(elem).innerHTML = prevText;
    }, 3000); //3 sec ❌ laten zien
  };

  xhr.onerror = function(e){                  //Error
    alert(Blockly.Msg.TXT_ONERROR);
    document.getElementById(elem).innerHTML = "❌";
    setTimeout(function() {
      document.getElementById(elem).innerHTML = prevText;
    }, 3000); //3 sec ❌ laten zien
  };

  setTimeout(function() { //ESP32 moet de kans gehad hebben om de request van runProgram() te ontvangen
    xhr.open("GET", "/startfeedback", true); 
    xhr.timeout = 1000; //ms
    xhr.send();
  }, 100);
}

/* geef start-feedback in de start button in blockly.html */
function getStopFeedback(elem) {
  var prevText1 = "Stop";
  if (Blockly.Msg.TXT_STOP != undefined) {
    prevText1 = Blockly.Msg.TXT_STOP;
  } else {
//    prevText1 = document.getElementById(elem).innerHTML; //pak de tekst wat nu op de button staat
    prevText1 = "Stop";
  }

//  document.getElementById(elem).innerHTML = "<img src=\"images/loading.gif\" height=80%/>";
  document.getElementById(elem).innerHTML = "⏳";
  
  var xhr = new XMLHttpRequest();

  xhr.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      if(this.responseText == 1){						//ATmega is gestop
        document.getElementById(elem).innerHTML = "✔";
        setTimeout(function() {
          document.getElementById(elem).innerHTML = prevText1;
        }, 3000); //3 sec ✔️ laten zien
      } else {											//ATmega is nog niet gestop
        setTimeout(function() {
          getStopFeedback(elem); //check over 1 sec nog een keer
        }, 1000);
      }
    }
  };

  xhr.ontimeout = function(e){                //Timeout
    alert(Blockly.Msg.TXT_ONTIMEOUT);
    document.getElementById(elem).innerHTML = "❌";
    setTimeout(function() {
      document.getElementById(elem).innerHTML = prevText1;
    }, 3000); //3 sec ❌ laten zien
  };

  xhr.onerror = function(e){                  //Error
    alert(Blockly.Msg.TXT_ONERROR);
    document.getElementById(elem).innerHTML = "❌";
    setTimeout(function() {
      document.getElementById(elem).innerHTML = prevText1;
    }, 3000); //3 sec ❌ laten zien
  };

  setTimeout(function() { //ESP32 moet de kans gehad hebben om de request van runProgram() te ontvangen
    xhr.open("GET", "/stopfeedback", true); 
    xhr.timeout = 1000; //ms
    xhr.send();
  }, 100);
}