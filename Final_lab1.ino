/*
  ESP8266 Blink by Simon Peter
  Blink the blue LED on the ESP-01 module
  This example code is in the public domain

  The blue LED on the ESP-01 module is connected to GPIO1
  (which is also the TXD pin; so we cannot use Serial.print() at the same time)

  Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/
int s1 = 4;
int s2 = 0;
int Rled = 16;
int Gled = 5;
int check1;
int check2;



//red
int buttonState = LOW; 
int ledState = -1; 

long lastDebounceTime = 0;  
long debounceDelay = 50; 

//green
int buttonState1 = LOW; 
int ledState1 = -1; 

long lastDebounceTime1 = 0;  
long debounceDelay1 = 100; 

void setup() {
  pinMode(Rled, OUTPUT);
  pinMode(Gled, OUTPUT);
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
}


void loop() {
 

//red
  
  buttonState = digitalRead(s1);
 
  //filter out any noise by setting a time buffer
  if ( (millis() - lastDebounceTime) > debounceDelay) {
 
    //if the button has been pressed, change
    if ( (buttonState == HIGH) && (ledState < 0) ) {
 
      digitalWrite(Rled, HIGH); //turn LED on
      ledState = -ledState; //now the LED is on, we need to change the state
      lastDebounceTime = millis(); //set the current time
    }
    else if ( (buttonState == HIGH) && (ledState > 0) ) {
 
      digitalWrite(Rled, LOW); //turn LED off
      ledState = -ledState; //now the LED is off
      lastDebounceTime = millis(); //set the current time
    }
 
  }


//green

 buttonState1 = digitalRead(s2);
 
  //filter out any noise by setting a time buffer
  if ( (millis() - lastDebounceTime1) > debounceDelay1) {
 
    //if the button has been pressed, change
    if ( (buttonState1 == HIGH) && (ledState1 < 0) ) {
 
      digitalWrite(Gled, HIGH); //turn LED on
      ledState1 = -ledState1; //now the LED is on, we need to change the state
      lastDebounceTime1 = millis(); //set the current time
    }
    else if ( (buttonState1 == HIGH) && (ledState1 > 0) ) {
 
      digitalWrite(Gled, LOW); //turn LED off
      ledState1 = -ledState1; //now the LED is off
      lastDebounceTime1 = millis(); //set the current time
    }
 
  }












  //check1 = digitalRead(s1);
  //digitalWrite(Rled, check1);
  
  //check2 = digitalRead(s2);
  //digitalWrite(Gled, check2);
  
 
}
