#include <VirtualWire.h>
const int rightSwitchPin = 4;
 const int leftSwitchPin = 6;
int switchState; // Variable to store the switch state
int switchState2;
void setup() {
  // Set the toggle switch pin as an input
  pinMode(rightSwitchPin, INPUT);
   pinMode(leftSwitchPin, INPUT);
  Serial.begin(9600);
  vw_setup(2000); 
  vw_set_tx_pin(12); 
}

void loop() {
   const char *msg;
  switchState = digitalRead(rightSwitchPin);
  switchState2 = digitalRead(leftSwitchPin);

  if (switchState == HIGH && switchState2 == HIGH) {
    Serial.println("Switch A & B is ON");
    msg = "1";
  }
  else if (switchState == HIGH && switchState2 == LOW)//right cutter on
  {
    Serial.println("Switch A is ON");
   msg = "2";
  }

  else if(switchState == LOW && switchState2 == HIGH) { // left cutter on
    Serial.println("Switch B is ON");
    msg = "3";
  }
  else if (switchState == LOW && switchState2 == LOW){
    Serial.println("Switch A & B is OFF");
   msg = "4";
  }
  Serial.println(msg);
 vw_send((uint8_t *)msg, strlen(msg));
   vw_wait_tx(); 
   delay(10);
}

//the will be another toggleswitch for the second motor, the codes are the starred one
//just the 3&4 will be separately used for the second motor
//there might be an issue with using two switch, to be sorted later
