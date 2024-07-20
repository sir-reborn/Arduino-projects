#include <VirtualWire.h>
const int X_AX = A0;
const int Y_AX = A1;
void setup()
{
  Serial.begin(9600);    
  Serial.println("setup");
  vw_setup(2000); 
  vw_set_tx_pin(12); 
}
void loop()
{
  int xval = analogRead(X_AX);
  int yval = analogRead(Y_AX);
  const char *msg;
  if(xval<=261&&xval>=0)//backward
  {msg = "2"; //send a to the receiver
  }
  else if(xval<=1023&&xval>=782) //forward
  {
   msg = "1";
  }
  else if(yval<=1023&&yval>=782)//right
  {
 msg = "4";
  }
  else if (yval<=261 && yval>=0)//left
  {
  msg = "3";
  }
  else 
  {
msg = "M";
  }
  vw_send((uint8_t *)msg, strlen(msg));
   vw_wait_tx(); 
   delay(10);
   Serial.print("xValue:");
  Serial.println(xval);
  Serial.print("yValue:");
  Serial.println(yval);
}
