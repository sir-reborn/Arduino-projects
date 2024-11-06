
#include "ESC.h"

#define SPEED_MIN (1000)                                  // Set the Minimum Speed in microseconds
#define SPEED_MAX (2000)                                  // Set the Minimum Speed in microseconds

ESC myESC (9, SPEED_MIN, SPEED_MAX, 500);                 // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)
//ESC myESC2(6, SPEED_MIN, SPEED_MAX, 500); 
int oESC;                                                 // Variable for the speed sent to the ESC


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);                               // LED Visual Output
 digitalWrite(LED_BUILTIN, HIGH);    // LED High while signal is High (can be removed)
  myESC.calib();                  // Calibration of the Max and Min value the ESC is expecting
  myESC.stop();                   // Stop the ESC to avoid damage or injuries
  digitalWrite(LED_BUILTIN, LOW);     // LED Low when the calibration is done (can be removed)                          // LED High Once Armed
  delay(5000);                                            // Wait for a while
}

void loop() {
  for (oESC = SPEED_MIN; oESC <= 1200; oESC += 1) {  // goes from 1000 microseconds to 2000 microseconds
    myESC.speed(oESC);// tell ESC to go to the oESC speed value
    //myESC2.speed(oESC);
    delay(10);                                            // waits 10ms for the ESC to reach speed
  }
  delay(1000);
  for (oESC = 1200; oESC >= SPEED_MIN; oESC -= 1) {  // goes  `from 2000 microseconds to 1000 microseconds
    myESC.speed(oESC);                                    // tell ESC to go to the oESC speed value
    //myESC2.speed(oESC);
    delay(10);                                            // waits 10ms for the ESC to reach speed  
   }
   
  delay(2500);                                            // Wait for a while befor restart
}
