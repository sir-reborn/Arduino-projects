#include <SoftwareSerial.h>
const int rxPin= 10; //for bluetooth communication
const int txPin=12;
char incoming; // stores command from the bluetooth
int motorSpeed; //the speed at which the motor moves
int minSpeed=130; // minimum speed 
int maxSpeed=255; //max speed
#define ENA 7
#define ENB 6

// motor 2 control pins
// motor 2 is rightside of the chasis
#define IN4 5
#define IN3 4
//motor 1 is leftside of the chasis
//motor 1 control pins
#define IN2 3
#define IN1 2

//.....................................................................................................
SoftwareSerial bluetooth (rxPin, txPin);
void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
//set pins for PWM of motor
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);

   //set output for motor 1 related pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  //set output for motor 2 related pins
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  if (bluetooth.isListening()) // if the bluetooth is working
  {
    Serial.println("bluetooth is listening");
  }
    motorSpeed=minSpeed;
    analogWrite(ENA, motorSpeed);
     analogWrite(ENB, motorSpeed);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void loop() {
  if (bluetooth.available())
  {
   incoming= bluetooth.read(); // read incoming command
  Serial.print("Received:");
  Serial.println(incoming);
  }
  Speed(); // function for speed
  
  //Serial.println(motorSpeed);
 switch (incoming) {
    case '1': forward(); break;
    case '2': backward(); break;
    case '3': leftward(); break;
    case '4': rightward(); break;
    case 'M': halt(); break;
  }
  
}
  //*******************************************************************************************
void forward() {
  // motor 1 run AntiClockwise (leftside)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // motor 2 run clockwise (rightside)
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
   

}

void backward() {
  // motor 1 run clock wise
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // motor 2 run AntiClockwise
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void rightward() {
  // motor 1 run anticlockwise
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // motor 2 run anticlockwise
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void leftward() {
  // motor 1 runs anticlockwise
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // motor 2 run clockwise
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void halt() {
  // motor 1 runs anticlockwise
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  // motor 2 run clockwise
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void Speed(){ // the shape buttons are set to various speed
  
switch (incoming) {
    case 'r': motorSpeed = minSpeed; break;
    case 's': motorSpeed = 172; break;
    case 't': motorSpeed = 214; break;
    case 'u': motorSpeed = maxSpeed; break;
  }
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
  }
