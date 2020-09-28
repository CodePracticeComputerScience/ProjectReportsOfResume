//#include <Adafruit_MCP3008.h>
//
//
//
////Adafruit_MCP3008 adc(D5,D7,D6,D8);
//Adafruit_MCP3008 t;
//
//void setup() {
//  // put your setup code here, to run once:
//Serial.begin(115200);
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
////Serial.println(String(adc.readADC(0)));
//Serial.println(String(t.readADC(0)));
//delay(1000);
//}

//http://domoticx.com/esp8266-wifi-mcp3008-adc-converter/
#include <MCP3008.h>
 
// Pin configuratie
#define CLOCK_PIN 2
#define MISO_PIN 5
#define MOSI_PIN 4
#define CS_PIN 14
 
MCP3008 adc(CLOCK_PIN, MOSI_PIN, MISO_PIN, CS_PIN); // configureer de MCP3008 constructor.
 
void setup() {
  Serial.begin(9600); // open de seriele poort.
}
 
void loop() {
  int val = adc.readADC(7); // lees kanaal 8 van de MCP3008 ADC.
  Serial.println(val); // print de waarde naar de console.
  delay(50); // wacht even
}
