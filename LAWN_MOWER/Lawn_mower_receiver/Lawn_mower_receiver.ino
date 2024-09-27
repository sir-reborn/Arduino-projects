
#include <ServoTimer2.h>
#include <VirtualWire.h>
ServoTimer2 ESC;     // create servo object to control the ESC
ServoTimer2 ESC2; 
char* val;
int R_cutter=9;
int L_cutter=6;
void setup() {
  Serial.begin(9600); 
    Serial.println("setup");
    ESC.attach( R_cutter); // (pin, min pulse width, max pulse width in microseconds)
    ESC2.attach(L_cutter); 
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
        case '1': ESC.write(1035); break;
        case '2': ESC.write(0); break;
       // case '3': ESC2.write(90);
       // case '4': ESC2.write(0);
    }  
}
 }
}
