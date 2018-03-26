#define SENSORPINX A4 // x axis
#define SENSORPINY A3 // y axis
#define BUTTONPIN 2 // reset button
#define FSRPIN A2 // fsr sensor
 //TODO: define other sensor inputs

unsigned long targetTime=0;
const unsigned long interval=100; //TODO: How fast should we read
const String reset = "rst";
const String width = "lnw";
unsigned long startPress = 0;

void setup(){
// TODO: begin the serial connection with a baudrate of 115200
  Serial.begin(115200);
  pinMode(BUTTONPIN, INPUT);
  pinMode(FSRPIN, INPUT);
}


void loop(){
	if(millis()>=targetTime){
		targetTime= millis()+interval;

		 //TODO: Add other sensor read outs
     //TODO: convert values into a string https://www.arduino.cc/en/Tutorial/StringConstructors
		 //TODO: combine them into a string that can be understood by server.js
		 //TODO: send the string over serial
     int PositionX = analogRead(SENSORPINX);
     int PositionY = analogRead(SENSORPINY);
     String data = String(PositionX) + "," + String(PositionY);
     Serial.println(data.c_str());
	}

  // Require a 1.5 second long press on the button to trigger a reset
  int buttonState = digitalRead(BUTTONPIN);
  if (buttonState == HIGH && !startPress) {
    // TODO: Detect if you want to reset the screen(shake the etch-a-sketch)
    // TODO: write the reset message(see server.js) to the serial port
    startPress = millis();
  }
  if (buttonState == LOW && startPress) {
    if ((millis() - startPress) >= 1500) {
      Serial.println(reset.c_str());
    }
    startPress = 0;
  }
  
  int sensorValue = analogRead(FSRPIN);
  if (sensorValue >= 100) {
    Serial.println(width + "," + String(sensorValue));
  }
}
