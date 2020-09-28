//#include <SoftwareSerial.h>
char incomingByte = 0;   // for incoming serial data
//SoftwareSerial serial1(3, 1);
int Gled = 0;
int s1 = 16;
int check1;
int check2;
//red
int buttonState = LOW;
int ledState = -1;
int holder;

long lastDebounceTime = 0;
long debounceDelay = 100;

const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;
static byte ndx = 0;
char endMarker = '\n';


//green
void setup() {

  pinMode(Gled, OUTPUT);
  pinMode(s1, INPUT);
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop() {
  
  buttonState = digitalRead(s1);
  // send data only when you receive data:
  //filter out any noise by setting a time buffer
  if ( (millis() - lastDebounceTime) > debounceDelay) {

    //if the button has been pressed, change
    if ( (buttonState == HIGH) && (ledState < 0) ) {
      //Change this to the TX pin
      Serial.write("H"); //turn LED on
      //Serial.print("High");
      ledState = -ledState; //now the LED is on, we need to change the state
      lastDebounceTime = millis(); //set the current time
    }
    else if ( (buttonState == HIGH) && (ledState > 0) ) {
      //Change this to the TX pin
      Serial.write("L"); //turn LED off
      // Serial.print("low");
      ledState = -ledState; //now the LED is off
      lastDebounceTime = millis(); //set the current time
    }

  }
  if (Serial.available() > 0) {
    Serial.begin(9600);
    holder = Serial.read();

    
   */ if (holder != 'H')
    {
      //Serial.write("ahhhhhh ahhhhh ahhhh ");
    }*/
    


    if (holder == 'H')
    {
      digitalWrite(Gled, HIGH);
      delay(300);
      digitalWrite(Gled, LOW);
    }


    //filter out any noise by setting a time buffer
    /* if ( (millis() - lastDebounceTime) > debounceDelay) {

       //if the button has been pressed, change
       if ( (buttonState == HIGH) && (ledState < 0) ) {
         //Change this to the TX pin
         Serial.write("H"); //turn LED on
         //Serial.print("High");
         ledState = -ledState; //now the LED is on, we need to change the state
         lastDebounceTime = millis(); //set the current time
       }
       else if ( (buttonState == HIGH) && (ledState > 0) ) {
         //Change this to the TX pin
         Serial.write("L"); //turn LED off
         // Serial.print("low");
         ledState = -ledState; //now the LED is off
         lastDebounceTime = millis(); //set the current time
       }

      }*/
    // say what you got:
    //  Serial.print("I received: ");
    // Serial.println(incomingByte, DEC);
  }
}
