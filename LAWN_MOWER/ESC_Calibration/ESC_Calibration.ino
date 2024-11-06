#include "ESC.h"
#define LED_PIN (13)              // Pin for the LED 

ESC myESC (9, 1000, 2000, 500);   // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Arm Value)
//ESC myESC2 (6, 1000, 2000, 500);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);       // LED Visual Output (can be removed)
  digitalWrite(LED_BUILTIN, HIGH);    // LED High while signal is High (can be removed)
  myESC.calib();                  // Calibration of the Max and Min value the ESC is expecting
  // myESC2.calib(); 
  myESC.stop();                   // Stop the ESC to avoid damage or injuries
 //   myESC2.stop();
  digitalWrite(LED_BUILTIN, LOW);     // LED Low when the calibration is done (can be removed)
}

void loop() {

}
