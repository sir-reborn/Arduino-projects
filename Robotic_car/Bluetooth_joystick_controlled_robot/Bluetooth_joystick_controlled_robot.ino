#include <SoftwareSerial.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
//RF receiver data pin is connected to pin 11
RH_ASK driver;
int motorSpeed; //the speed at which the motor moves
int joyStickSpeed= 200; //joystick max speed
char* val;
//**************************************************
const int rxPin= 10; //for bluetooth communication
const int txPin=12;
char incoming; // stores command from the bluetooth
int minSpeed=130; // minimum speed 
int maxSpeed=255; //max speed
//***********************************************
#define ENA 7
#define ENB 6
// motor 2 control pins
 //motor 2 is rightside of the chasis
#define IN4 5
#define IN3 4
//motor 1 is leftside of the chasis
//motor 1 control pins
#define IN2 3
#define IN1 2
//********************************
SoftwareSerial bluetooth (rxPin, txPin);

void setup(){
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


   motorSpeed=minSpeed;
    analogWrite(ENA, motorSpeed);
     analogWrite(ENB, motorSpeed);
  if (!driver.init())
    Serial.println("init failed");
}

//**********************************************
void loop() {
  if (bluetooth.available())
  {
   incoming= bluetooth.read(); // read incoming command
  Serial.print("Received:");
  Serial.println(incoming);
  }
//  joystickControl();
//  bluetoothControl();
}

void joystickControl()
{
  //motorSpeed=joyStickSpeed;
//    analogWrite(ENA, motorSpeed);
//     analogWrite(ENB, motorSpeed);
    uint8_t buf[1];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
       int i;
       val= buf;
       Serial.println(val);
       for (i=0;i<buflen;i++)
       {
        
     if (buf[i]=='a'){// when the  the car moves forward
    forward();
     }
      if (buf[i]=='b'){// when the  the car moves forward
    backward();
     }
      if (buf[i]=='c'){// when the  the car moves forward
    rightward();
     }
      if (buf[i]=='d'){// when the  the car moves forward
    leftward();
     }
      if (buf[i]=='e'){// when the  the car moves forward
    halt();
     }
  }

  
    }
}

//*********************************************
void bluetoothControl() {
  
  Speed(); // function for speed
  
  //Serial.println(motorSpeed);
  if (incoming=='1') // when the upward arrow of the app is pressed, the car moves forward
  {
    forward();
  }
  
  else if (incoming=='2') //// when the downward arrow of the app is pressed, the car reverses
  {
    backward();
  }
  
  else if (incoming=='4') // when the right arrow of the app is pressed,the car turns right
  {
    rightward();
  }
  else if (incoming=='3') // when the left arrow of the app is pressed,the car turns left
  {
    leftward();
  }
  else if (incoming=='M')
  {
    halt();
  }
  
}
  //************************************************
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
//****************************************************
void Speed(){ // the shape buttons are set to various speed
  
   if (incoming=='r') //when rectangle shape is pressed, gives minimum speed
  {
    motorSpeed=minSpeed;
     analogWrite(ENA, motorSpeed);
      analogWrite(ENB, motorSpeed);
  }
  else if (incoming== 's') //when triangle shape is pressed, increases speed
  {
    motorSpeed= 172;
     analogWrite(ENB, motorSpeed);
      analogWrite(ENA, motorSpeed);
  }
   else if (incoming=='t') //when X shape is pressed, increases the speed more
  {
    motorSpeed=214;
     analogWrite(ENA, motorSpeed);
      analogWrite(ENB, motorSpeed);
  }
   else if (incoming=='u') //when circle shape is pressed, maximum speed
  {
    motorSpeed=maxSpeed;
     analogWrite(ENA, motorSpeed);
      analogWrite(ENB, motorSpeed);
  }
}
