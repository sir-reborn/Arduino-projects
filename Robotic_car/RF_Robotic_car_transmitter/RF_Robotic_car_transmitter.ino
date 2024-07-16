#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;
const int xPin = A0; // Joystick X-axis
const int yPin = A1; // Joystick Y-axis

void setup() {
 Serial.begin(9600);
  if (!driver.init())
         Serial.println("init failed");
}

void loop() {
  int xval = analogRead(xPin);
  int yval= analogRead(yPin);
  const char *msg;
  
 if(xval<=261&&xval>=0)
  {msg = "a";//send a to the receiver
  }
  else if(xval<=1023&&xval>=782)
  {
   msg = "b";
  }
  else if(yval<=261&&yval>=0)
  {
   msg = "c";
  }
  else if(yval<=1023&&yval>=782)
  {
 msg = "d";
  }
  else 
  {
msg = "e";
  }
 driver.send((uint8_t *)msg, strlen(msg));
   driver.waitPacketSent();
   
  Serial.print("xValue:");
  Serial.println(xval);
  Serial.print("yValue:");
  Serial.println(yval);
//  Serial.println("a");
//  Serial.println("b");
//  Serial.println("c");
//  Serial.println("d");
//  Serial.println("e");

  
}
