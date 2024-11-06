//DHT INITIALIZATION
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>
int DhtPin = 2; //pin 2
#define DHTTYPE DHT11
DHT DhtSensor(DhtPin, DHTTYPE);
float humidity, temp,tempF;
//************************************************************************************
//RTC INITIALIZATION
#include <RTClib.h>
#include <Wire.h>
RTC_DS3231 myClock;
const char* daysOfTheWeek[]= {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
//**************************************************************************************
//MQ-135 INITIALIZATION
const int SmokePin = A0; //analogin 0
int state, rating;
//********************************************************************************

#define ledPin 6
//ST7735 INITIALIZATION
#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_ST77xx.h>

#include <Adafruit_GFX.h>
#include <SPI.h>

//TFT screen
int CS=10;
int RST=9;
int DC=8;
Adafruit_ST7735 screen = Adafruit_ST7735(CS, DC, RST);

unsigned int BLACK; //= 0x0000;
unsigned int BLUE;// = 0x001F;
unsigned int RED;// = 0xF800;
unsigned int GREEN;// = 0x07E0;
unsigned int CYAN;// = 0x07FF; // HEX codes for colors
unsigned int MAGENTA ;//= 0xF81F;
unsigned int YELLOW ;//= 0xFFE0;
unsigned int WHITE ;//= 0xFFFF;
unsigned int GREY ;//= 0xC618;
unsigned int NAVY_BLUE;//= 0x000080;
unsigned int PURPLE1;//=0X6d59b6;
unsigned int PURPLE2;//=0X9b59b6;
unsigned int COLOUR2;//=0x45b3f7;
unsigned int PURPLE3;//=0xb659a3;
unsigned int DARK_GREY;//=0x333333;


unsigned int color[] = {BLACK, BLUE, RED, GREEN, CYAN, MAGENTA, YELLOW, WHITE, GREY};
//**************************************************************************************
void setup(void) {
 Serial.begin(9600);
 pinMode(SmokePin, INPUT);
 pinMode(DhtPin, INPUT); 
  DhtSensor.begin();
  Wire.begin();
    myClock.begin();
//************************************************************************************
 screen.initR(INITR_BLACKTAB); 
screen.fillScreen(BLACK);
WelcomeDisplayDesign(color[2]); //RED
screen.drawRect(1,1,126,158,WHITE);
screen.drawRect(3,3,122,154,BLUE);
CoverPage();
preparingData();
dataLayout();
initialView("TEMPERATURE",40);
initialView("HUMIDITY",85);
initialView("AIR PURITY",127);
//*****************************************************************************************
SmokeSensor();
 delay(1000);
 TempAndHumidity();
 delay(1000);
//************************************************************************************
   
  if(myClock.lostPower()){
     myClock.adjust(DateTime(F(__DATE__),F(__TIME__)));
 }

 }


//************************************************************************************

DateTime now;
void loop() {
  ledState();
  TimeSmokeDisplay();
//************************************************************************************

  unsigned long PreviousMillis = 0; //--> will store last time updated
const long Interval = 1000;
  unsigned long CurrentMillis = millis();
  if (CurrentMillis - PreviousMillis >= Interval) {
    // Save the last time you updated the display
    PreviousMillis = CurrentMillis;
    now = myClock.now();
  }

 if (!myClock.begin()){
  screen.setTextColor(BLACK,COLOUR2);
  screen.setCursor(20,15);
  screen.print("TIME & DATE N/A");
 }
 else{
  // Update the display

  screen.setTextSize(1, 1);
  screen.setTextColor(BLACK, COLOUR2);
  screen.setCursor(17, 10);
  
//Print day of the week
  screen.print(daysOfTheWeek[now.dayOfTheWeek()]);
  screen.print(", ");
  
 // Print day with leading zero if necessary
  if (now.day() < 10) screen.print('0');
  screen.print(now.day(), DEC);
  screen.print(" ");

//Print month in word
   screen.print(months[now.month() - 1]); 
   screen.print(" ");
   
  // Print year
  screen.print(now.year(), DEC);

  
  screen.setTextSize(1, 2);
  screen.setTextColor(BLACK, COLOUR2);
  screen.setCursor(36, 20);

  // Print hours with leading zero if necessary
  if (now.hour() < 10) screen.print('0');
  screen.print(now.hour(), DEC);
  screen.print(":");

  // Print minutes with leading zero if necessary
  if (now.minute() < 10) screen.print('0');
  screen.print(now.minute(), DEC);
  screen.print(":");

  // Print seconds with leading zero if necessary
  if (now.second() < 10) screen.print('0');
  screen.print(now.second(), DEC);
 
 }
  
  
}


 

void CoverPage(){
  screen.setCursor(17,7);
  screen.setTextSize(2);
screen.setTextColor(BLUE);
screen.print("ECOWATCH");
screen.setCursor(30,40);
  screen.setTextSize(1);
screen.setTextColor(GREY);
screen.print("project by");
screen.setCursor(17,60);
  screen.setTextSize(2);
screen.setTextColor(BLUE);
screen.print("ELECTRON" );
screen.setCursor(5,80);
screen.print("NEXUS TEAM" );
screen.setCursor(5,110);
  screen.setTextSize(1);
screen.setTextColor(GREY);
screen.print("under supervision of");
screen.setCursor(10,135);
  screen.setTextSize(2);
screen.setTextColor(BLUE);
screen.print("SMART LAB" );
delay(5000);
screen.fillScreen(BLACK);
}


void WelcomeDisplayDesign(int color) {
  screen.fillScreen(BLACK);
  for (int16_t y=screen.height(); y > 0; y-=6) {
    screen.drawLine(screen.width()/2,screen.height()/2, 0,y, color);
    delay(10);
  }
  for (int16_t x=0; x < screen.width(); x+=6) {
     screen.drawLine(screen.width()/2,screen.height()/2, x,0, color);
    delay(10);
  }
  for (int16_t y=0; y <screen.height(); y+=6) {
    screen.drawLine(screen.width()/2,screen.height()/2, screen.width(),y, color);
    delay(10);
  }
  for (int16_t x=screen.width(); x >0; x-=6) {
     screen.drawLine(screen.width()/2,screen.height()/2, x,screen.height(), color);
    delay(10);
  }
  delay(500);
  screen.fillScreen(BLACK);
  delay(500);
  }


  void preparingData(){
screen.fillScreen(BLACK);
screen.drawRect(3,3,122,154,BLUE);
screen.fillRoundRect(5, screen.height()/2-20, 118, 30, 5, BLUE);
screen.setCursor(34,screen.height()/2-15);
screen.setTextSize(1);
screen.setTextColor(GREY);
screen.print("PREPARING " );
screen.setCursor(10,screen.height()/2-3);
screen.print("ATMOSPHERIC DATA...");
delay(4000);
screen.fillScreen(BLACK);
}

void dataLayout(){ //the background colours
screen.drawRect(1,1,126,158,GREY);
screen.drawRect(3,3,122,154,COLOUR2);
screen.fillRect(5, 5, 118, 39,  COLOUR2);
screen.fillRoundRect(5, 5, 118, 35, 5, COLOUR2);
screen.fillRect(5, 42, 118, 43,  PURPLE1);
screen.fillRoundRect(5, 38, 118, 40, 5, PURPLE1);
screen.fillRect(5,86, 118, 42,  COLOUR2);
screen.fillRoundRect(5, 81, 118, 40, 5, COLOUR2);
screen.fillRoundRect(5, 122,118, 34, 5, PURPLE1);
}

void initialView(char *text,int y) {// to display the type of data we are displaying
   int16_t x1, y1,w,h,W,x;
   screen.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  W= screen.width();
  x=(W-w)/2;
  screen.setTextSize(1);
  screen.setTextColor(WHITE);
  screen.setCursor(x,y);
  screen.print(text);
}

//**********************************************************************************************************************************************************************************

void TimeSmokeDisplay(){
  
  unsigned long previousMillis = 0; //--> will store last time updated
const long interval = 2000;
 unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    TempAndHumidity();
  SmokeSensor();
  }

   if (isnan(humidity) && isnan(temp)){
    //FOR TEMPERATURE
    
     screen.setTextSize(2,2);
screen.setTextColor(BLACK,PURPLE1);
  screen.setCursor(50,55);
    screen.print("N/A");
    
    //FOR HUMIDITY
    screen.setTextColor(BLACK,COLOUR2);
  screen.setCursor(50,100);
  screen.print("N/A");
   }
   else{
  //celcius temperature value
  screen.setTextSize(1,2);
screen.setTextColor(BLACK,PURPLE1);
  screen.setCursor(15,55);
  screen.print(temp);
  screen.print((char)247);
  screen.println("C");

  
// farhenheit temperature value

  screen.setCursor(75,55);
  screen.print(tempF);
  screen.print((char)247);
  screen.println("F");

  //humidity value
  screen.setTextColor(BLACK,COLOUR2);
  screen.setCursor(40,100);
  screen.print(humidity);
  screen.print(" %");
   }

  //air purity
  screen.setTextSize(1,2);
  screen.setTextColor(BLACK,PURPLE1);
  screen.setCursor(40,140);
   switch (rating) {
    case 0:
    case 1:
    case 2:
      screen.print("EXCELLENT");
      break;
    case 3:
      screen.print("GOOD");
      break;
    case 4:
    case 5:
      screen.print("FAIR");
      break;
    case 6:
    case 7:
      screen.print("POOR");
      break;
    case 8:
    case 9:
    case 10:
     screen.print("HAZARDOUS");
      break;
  }

}


//**********************************************************************************************************************************************************************************

void TempAndHumidity(){
  
  humidity = DhtSensor.readHumidity();
  temp = DhtSensor.readTemperature();
  tempF = DhtSensor.readTemperature(true);
  if (isnan(humidity) || isnan(temp) || isnan(tempF)) {
    
    return;
  }
 
} 



//**********************************************************************************************************************************************************************************

void SmokeSensor(){
state= analogRead(SmokePin);
int rating = map(state, 0, 1023, 0, 10);
}
//**********************************************************************************************************************************************************************************
void ledState(){
  digitalWrite(ledPin,HIGH);
  delay(5000);
  
  if (!myClock.begin()&& isnan(humidity) && isnan(temp)){
    digitalWrite(ledPin,LOW);
  }
  
    else{
      digitalWrite(ledPin,HIGH);
      delay(2000);
      digitalWrite(ledPin,LOW);
      delay(2000);
    }
    
 }


//display when either of the component is disconnected
//make rtc save time
