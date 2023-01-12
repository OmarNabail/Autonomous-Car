//RS lib
#include <Adafruit_GFX.h>                 //graphix library for drawing
#include <Adafruit_TFTLCD.h>              //LCD library to drive screen
#include "TouchScreen.h"                  //library for tounchscreen
#include <Wire.h>                         //I2C library
#include <TEA5767N.h>
#include <stdint.h>
//end
//fI LIB
#include <Servo.h>
//END
//FI PINS
#define rainDropSensor 39
Servo myservo;
int rainDropValue=0;
#define e 53
#define d 51
#define c 49
#define b 47
#define a 45
#define f 43
#define g 41
#define WaterLevelSensor  A15 
int sensorReading =0;
//END
//pin RS
#define YP A2  
#define XM A3  
#define YM 22   
#define XP 23   
TEA5767N radio = TEA5767N();                                          
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
#define LCD_CS A3                         //LCD Control Pins
#define LCD_CD A2                         //LCD Control Pins
#define LCD_WR A1                         //LCD Control Pins
#define LCD_RD A0                         //LCD Control Pins
#define LCD_RESET A4                       //LCD Control Pins
// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x07FF
#define RED     0xFFE0
#define GREEN   0xF81F
#define CYAN    0x001F
#define MAGENTA 0x07E0
#define YELLOW  0xF800
#define WHITE   0xFFFF                    
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
float station=100.6;                        //var to hold station
int volume = 5;                           //var to hold volume
int horz;                                 //var to hold x touch
int vert;                                 //var to hold y touch
String rdsname="xxxxxxxxxx-_-xxxxxxxxxx";               
String on ="On";
String off="Off";
// end RS

void setup(void) {
 
  Serial.begin(9600);                    //serial comms for debug
  
  //RS setup
  tft.reset();                           //reset the screen
  tft.begin(0x8357);                     //start screen using chip identifier hex 
  Wire.begin();
  tft.setRotation(1);                    //set rotation for wide screen
  tft.fillScreen(BLACK);                 //fill screen with black (ersatz clear)
  tft.setCursor(0, 0); 
  tft.setTextColor(WHITE);               //set text color white
  tft.setTextSize(2);                    //set text size to 2 (1-6)
  tft.println("     Arduino FM Radio");  //print header to screen
   tft.drawRoundRect(10, 20, 300, 200, 6, WHITE); //draw screen outline
   tft.fillRoundRect(20, 30, 160, 50, 6, CYAN);    //draw station box
     tft.fillRoundRect(40, 90,80, 50, 6, GREEN); //draw On BUTTON box
     tft.fillRoundRect(150, 90,80, 50, 6, RED); //draw OFF BUTTON box
   tft.fillRoundRect(20, 150,280, 50, 6, YELLOW); //draw RDS box
   tft.fillRoundRect(190, 30, 50, 50, 6, CYAN);    //draw station up buton
   tft.fillRoundRect(250, 30, 50, 50, 6, CYAN);    //draw station down buton
   tft.fillTriangle(215, 30, 192, 67, 235, 67,WHITE); //draw up triangle for station
   tft.fillTriangle(275, 67, 252, 30, 295, 30,WHITE); //draw down triangle for station
  radio.setFrequency(station);  
  // end setup RS
  //FI START
  pinMode(WaterLevelSensor,INPUT);
pinMode(e,OUTPUT);
  pinMode(b,OUTPUT);
  pinMode(d,OUTPUT);
  pinMode(c,OUTPUT);
  pinMode(g,OUTPUT);
  pinMode(a,OUTPUT);
  pinMode(f,OUTPUT);
  pinMode(g,OUTPUT);
  pinMode(rainDropSensor,INPUT);
  myservo.attach(37);
  // END 
}
// RS function
void think(){    
  //logic for buttons
  if(horz>370 && horz<450){           //station up
    if(vert>270 && vert<320){
      station=station+20;
      tft.fillRoundRect(20, 30, 160, 50, 6, RED);
      radio.selectFrequency(station);
    }
  }
  if(horz>200 && horz<250){           //station down
    if(vert>270 && vert<320){
      station=station-20;
      tft.fillRoundRect(20, 30, 160, 50, 6, RED);
      radio.selectFrequency(station);
    }
  }

  if(horz>=600 && horz<=750){           //on
    if(vert>400 && vert<800){
      Serial.print("on");
    radio.setStandByOff();
    }
  }
    if(horz>=400 && horz<=550){           //off
    if(vert>400 && vert<800){
       Serial.print("off");
  radio.setStandByOn();
    }
  }
}
// RS function END
// FI FUNCTION
//servoMovingFunction
void servo(){
   for (int pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }}
  //rainDropActionFunction
 void rainDrop(){
    rainDropValue=digitalRead(rainDropSensor);
    Serial.println(rainDropValue);
    if(rainDropValue==0){
     servo();
      
    }}
    //to print 0
void zero(){
   //0
  digitalWrite(a,1);
 digitalWrite(b,1);
 digitalWrite(c,1);
 digitalWrite(d,1);
 digitalWrite(e,1);
 digitalWrite(f,1);
 digitalWrite(g,0);   
}
//to print 1
void one(){
   //1
  digitalWrite(a,0);
 digitalWrite(b,1);
 digitalWrite(c,1);
 digitalWrite(d,0);
 digitalWrite(e,0);
 digitalWrite(f,0);
 digitalWrite(g,0);   
}
//to print 2
void two(){
   //2
  digitalWrite(a,1);
 digitalWrite(b,1);
 digitalWrite(c,0);
 digitalWrite(d,1);
 digitalWrite(e,1);
 digitalWrite(f,0);
 digitalWrite(g,1);   
} 
//END
void loop(void) {
     // RS LOOP
 tft.setCursor(22, 40);
 tft.setTextColor(WHITE);
 tft.setTextSize(2);
 tft.print("Station:");
 tft.setTextColor(WHITE);
 tft.print(station);                //write station
 tft.setCursor(50, 160);
 tft.setTextSize(2);
tft.setCursor(22, 170);
 tft.print(rdsname);
tft.setCursor(68, 110);
 tft.print(on);
 tft.setCursor(170, 110);
 tft.print(off);
   digitalWrite(13, HIGH);
   TSPoint p = ts.getPoint();       //get touch
   digitalWrite(13, LOW);
   pinMode(XM, OUTPUT);
   pinMode(YP, OUTPUT);
   if (p.z > ts.pressureThreshhold) { //if touch is above threshold
     
     horz=p.x;                        //send touch values to variables
     vert=p.y;
     Serial.print("X = "); Serial.println(p.x);
     Serial.print("\tY = "); Serial.println(p.y);
     think();                         //call think function
  }
    /// RS END 
    //FI LOOP
     sensorReading=analogRead(WaterLevelSensor);
  if(sensorReading>=650){
   Serial.println(sensorReading);
   Serial.println("full");
   two();  
  }
  else if(sensorReading>=600&&sensorReading<650){
   Serial.println(sensorReading);
   Serial.println("meduim"); 
   one();
  }
  else{
    Serial.println(sensorReading);
   Serial.println("Empty");
   zero();
  }
  rainDrop();

    //END
}
