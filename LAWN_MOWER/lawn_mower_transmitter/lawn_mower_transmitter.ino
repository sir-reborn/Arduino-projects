#include <VirtualWire.h>
const int toggleSwitchPin = 2;
 const int toggleSwitchPin2 = 3;
int switchState; // Variable to store the switch state
int switchState2;
void setup() {
  // Set the toggle switch pin as an input
  pinMode(toggleSwitchPin, INPUT);
   pinMode(toggleSwitchPin2, INPUT);
  Serial.begin(9600);
  vw_setup(2000); 
  vw_set_tx_pin(12); 
}

void loop() {
   const char *msg;
  switchState = digitalRead(toggleSwitchPin);
  switchState2 = digitalRead(toggleSwitchPin2);

  if (switchState == HIGH) {
    Serial.println("Switch is ON");
    msg = "1";
  }
  else {
    Serial.println("Switch is OFF");
   msg = "2";
  }

//  if (switchState2 == HIGH) {
//    Serial.println("Switch is ON");
//    msg = "3";
//  }
//  else {
//    Serial.println("Switch is OFF");
//   msg = "4";
//  }
  Serial.println(msg);
 vw_send((uint8_t *)msg, strlen(msg));
   vw_wait_tx(); 
   delay(10);
}

//the will be another toggleswitch for the second motor, the codes are the starred one
//just the 3&4 will be separately used for the second motor
//there might be an issue with using two switch, to be sorted later
