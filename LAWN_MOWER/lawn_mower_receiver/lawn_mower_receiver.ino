#include <VirtualWire.h>
int motor1=9; //RIGHT MOTOR
int motor2=2; //LEFT MOTOR
char* val;

void setup() {
 Serial.begin(9600); 
    Serial.println("setup");
  pinMode(LED_BUILTIN, OUTPUT);                               // LED Visual Output
  pinMode(motor1, OUTPUT);
    pinMode(motor2, OUTPUT);
    digitalWrite(motor1,HIGH); digitalWrite(motor2,HIGH); delay(100);
  vw_setup(2000);  
    vw_set_rx_pin(11);    
    vw_rx_start(); 

}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

     if (vw_get_message(buf, &buflen)) 
    {
  int i;
  val=buf;
  Serial.println(val);
   for (i = 0; i < buflen; i++)
  {
   switch (buf[i]) {
case '1':  digitalWrite(motor1,LOW); digitalWrite(motor2,LOW); delay(100); break;
case '2':  digitalWrite(motor1,LOW); digitalWrite(motor2,HIGH); delay(100); break;
case '3': digitalWrite(motor1,HIGH); digitalWrite(motor2,LOW); delay(100); break;
case '4':  digitalWrite(motor1,HIGH); digitalWrite(motor2,HIGH); delay(100); break;
   }  
}
}
}
//testing one cutter with receiving comand
