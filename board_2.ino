//http://forum.arduino.cc/index.php?topic=396450 Help from this website!
int error = 0;
int Rled = 0;
int Gled = 16;
const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;
static byte ndx = 0;
char endMarker = '\n';
char holder;
void setup() {
  // Begin the Serial at 9600 Baud
  pinMode(Rled, OUTPUT);
  pinMode(Gled, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  if (Serial.available() > 0) {

    holder = Serial.read();
    //Serial.println(holder); //Print data on Ser-2ial Monitor


    if (holder != endMarker) {
      receivedChars[ndx] = holder;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }


    if (newData == true ) {
      newData = false;
    }



    if (holder == 'L')
    {
      digitalWrite(Gled, LOW); //turn LED off
      Serial.write("H");
    }
    if (holder == 'H')
    {
      digitalWrite(Gled, HIGH); //turn LED off
      Serial.write("H");
    }

    if (strcmp(receivedChars, "Turn green LED 2 off") == 0)
    {
      digitalWrite(Gled, LOW); //turn LED off
      Serial.write("H");
    }
    if (strcmp(receivedChars, "Turn green LED 2 on") == 0)
    {
      digitalWrite(Gled, HIGH); //turn LED off
      Serial.write("H");
    }
    
    if (strcmp(receivedChars, "Turn green LED 2 on") != 0 && strcmp(receivedChars, "Turn green LED 2 off") != 0)
    {
     

      if (holder == 'H')
      {

        error = 0;
      }
      if (holder == 'L')
      {
        error = 0;
      }
       error = 1;
    }

   /* if (error == 1 )
    { digitalWrite(Rled, HIGH); //turn LED off
      delay(300);
      digitalWrite(Rled, LOW); //turn LED off
      error = 0;
    }*/
    error = 0;
  }
}
