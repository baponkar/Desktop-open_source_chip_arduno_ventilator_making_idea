/*----------------------------------------------------------------------------------------------------------
 *Pressere control and patient control mode code for Arduino Uno.
 * Due to lack of Ventilator in this current situation due to COVID-19 pandemic it may help to people.
 * This instrument could only use in last .This istrument not suggest to use first as the medical ventilator
 * contai g much more sensor and property.
 * This code is  not included tidal flow rate calculation.I am working on it.
 * Components : High torqe servo(MG-996 metal geared),BME280 pressure Sensor,buzzer,Potentiometer(10K)
 *              (breath,peep,press),Swipe Button,Jumping Wires.
 * Connection :
 *             
 *---------------------------------Analog Pins-------------------------------------------------------------------           
 *             BME280 : SCL--> D17,SDA-->16,Vin-->5V,GND-->GND.
 *             Breath Pot(10K) : Midddile Pin --> A0, +Ve, -Ve.
 *             Pressure Control Pot(10K) : Middle Pin --> A1,+Ve,-Ve.
 *             PEEP Pot(10K)   : Middle Pin --> A2,+Ve,-Ve.
 *             
 *-------------------------------------Digital Pins--------------------------------------------------------------
 *             Green LED : --> D3. Showing inspiration
 *             Buzzer : +Ve--> D4. through 100 Ohom resistance,-Ve-->GND.
 *             Yellow LED : --> D5. Showing Expiration.
 *             Mode Swipe Button : --> D7.
 *             Servo : Yellow --> D9, Red--> +6V ,Black--> GND.(External Source)
 *             Alarm Red LED : --> D6. Showing alarming Situation.
 *             
 *             Note ---> I am disable the bme280 sensor in this code.
 *             
 *  Version - v-4.0
 *  Writter - Bapon Kar           
 *  Contact - baponkar600@gmail.com
 *  Last Update Time - 03/05/2020 ; 01:03:01 PM.
 *  
 * ---------------------------------------------------------------------------------------------------------
 */
long cTime = 0;//current time to calculate printing message
long pTime = 0;//previous time calculate to printing serial message
int printInterval = 100;//Printing Serial message time interval

#include<stdio.h>
#include<Servo.h>

//Setting BME280 pressure sensor
//SCL-->17 and SDA--> 16 if not working SCL-->A5 and SDA--A4
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;
int temperature = 0;
int pressure = 0;
int maxPressure = 0;
int humidity = 0;

// char data[10];
//Setting alarm
int const buzzPin = 4;//attach a buzzer in D4 pin
boolean alarmState = 0;
int const alarmPin = 6;//Attaching a red LED pin for showing alarming situation

//Setting breathing rate
const int breathPotPin = A0;//Attach a pot to control breathing rate per minute
int breathPotVal;
int breathNo;
float breathTime;
float inspTime;
float expTime;
int inspSpeed,expSpeed;

//peep pot setting
int const peepPotPin = A2;//attach a 10K pot in this pin
int peepPotVal;
int peepVal;

//Pressure Control
const int pressContPotPin = A1;//attaching 10k pot
int pressPotVal;
int pressVal;

//Setting Servo
#include <Servo.h>

const int servoPin = 9;//attach yelow servo signal pin
int minPos ;
int maxPos ;


//setting mode select button 
const int modeButtonPin = 7;//attaching a swipe button to select mode
boolean modeState = LOW;

//Adding two led for testing purpouse
const int greenLed = 3;
const int yellowLed = 5;
boolean greenLedState = LOW;
boolean yellowLedState = LOW;

class Sweeper
{
  Servo servo;
  int pos = 100;
  int increment;
  int updateInterval;
  int maxDegree;
  int minDegree;
  int midDegree;
  unsigned long lastUpdate;

  public:
  Sweeper()
  {   
    increment = 1;
  }

  void Attach(int pin)
  {
    servo.attach(pin);
    servo.write(100);
    delay(100);
  }
  
  void Detach()
  {
    servo.detach();
  }

  void update(int mDeg, int mxDeg,int interval)
  {
    unsigned long currentTime = millis();

    minDegree = mDeg;
    maxDegree = mxDeg;
    midDegree = (mDeg+mxDeg)/2;
    updateInterval = interval;
      if(increment >0 && updateInterval == interval){
         updateInterval = 2*interval;
       }
      if(increment <0 && updateInterval == 2*interval) {
         updateInterval = interval;
       }

   /*Serial.print(interval);
      Serial.print(" ,");
      Serial.print(pos);
      Serial.print(" ,");
      Serial.println(updateInterval); */
   
    
    if((currentTime - lastUpdate) > updateInterval)
    {
      lastUpdate = currentTime;
      pos += increment;
      servo.write(pos);
     // Serial.println(pos);
     //Serial.print(",");
     //Serial.println(pos);
     /*Serial.print(",");
     Serial.print(maxDegree);
     Serial.print(",");
     Serial.println(minDegree);*/
           
      if((pos >= maxDegree) || (pos <= minDegree))
      {
        increment = -increment;
      }
    }
    servo.write(pos);  
  }
};


class Flasher
{
  // Class Member Variables
  // These are initialized at startup
  int ledPin;      // the number of the LED pin
  long OnTime;     // milliseconds of on-time
  long OffTime;    // milliseconds of off-time

  // These maintain the current state
  int ledState;                 // ledState used to set the LED
  unsigned long previousMillis;   // will store last time LED was updated

  // Constructor - creates a Flasher 
  // and initializes the member variables and state
  public:
  Flasher(int pin)
  {
  ledPin = pin;
  pinMode(ledPin, OUTPUT);     
    
  
  
  ledState = LOW; 
  previousMillis = 0;
  }

  void Update( long on, long off)
  {
    OnTime = on;
    OffTime = off;
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();
     
    if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      ledState = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(ledPin, ledState);  // Update the actual LED
    }
    else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      ledState = HIGH;  // turn it on
      previousMillis = currentMillis;   // Remember the time
      digitalWrite(ledPin, ledState);   // Update the actual LED
    }
  }
};


class Flasher1
{
  // Class Member Variables
  // These are initialized at startup
  int ledPin;      // the number of the LED pin
  long OnTime;     // milliseconds of on-time
  long OffTime;    // milliseconds of off-time

  // These maintain the current state
  int ledState;                 // ledState used to set the LED
  unsigned long previousMillis;   // will store last time LED was updated

  // Constructor - creates a Flasher 
  // and initializes the member variables and state
  public:
  Flasher1(int pin)
  {
  ledPin = pin;
  pinMode(ledPin, OUTPUT);     
    
  
  
  ledState = LOW; 
  previousMillis = 0;
  }

  void Update( long on, long off)
  {
     OnTime = on;
     OffTime = off;
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();
     
    if((ledState == LOW) && (currentMillis - previousMillis >= OnTime))
    {
      ledState = HIGH;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(ledPin, !ledState);  // Update the actual LED
    }
    else if ((ledState == HIGH) && (currentMillis - previousMillis >= OffTime))
    {
      ledState = LOW;  // turn it on
      previousMillis = currentMillis;   // Remember the time
      digitalWrite(ledPin, !ledState);   // Update the actual LED
    }
  }
};

Flasher flasher(greenLed);
Flasher1 flasher1(yellowLed);
Sweeper sweeper;



void setup()
{
  sweeper.Attach(servoPin);
  
  pinMode(buzzPin,OUTPUT);
  pinMode(breathPotPin,INPUT);
  pinMode(peepPotPin,INPUT);
  pinMode(pressContPotPin,INPUT);
  pinMode(modeButtonPin, INPUT);
  pinMode(servoPin,OUTPUT);
  pinMode(alarmPin,OUTPUT);
  //pinMode(greenLed,OUTPUT);
  //pinMode(yellowLed,OUTPUT);
  Serial.begin(115200);
}

void modeSelect(){
  modeState = digitalRead(modeButtonPin);//Digital read of mode either preesure control or patient control  
  modeState = int(modeState);
  /*cTime = millis();

  if(cTime - pTime > test){ 
    pTime = cTime; 
    Serial.print(modeState);
    Serial.print(" , ");
  }*/
}

void pressureControl(){
  
  pressPotVal = analogRead(pressContPotPin);//control by potentiometer attach at A1
  pressVal = map(pressPotVal,0,1023,50,180);//taking arbitary value
  pressVal = 120;
  //it should change in actual condition with checking bmp280 result
  /*cTime = millis();

  if(cTime - pTime > test){ 
    pTime = cTime;
    Serial.print(pressVal);
    Serial.print(" , ");
  }*/
  
  
}


void peepControl(){
  peepPotVal = analogRead(peepPotPin);
  if(peepPotVal >=0 && peepPotVal <= 20){//My pot have problem as it showing maximum value 60 instead of 1023 so i use  this values
    peepVal = 5; 
  }
  else if(peepPotVal >20 && peepPotVal <= 40){
    peepVal = 10;
  }
  else {
    peepVal = 15;
  } 
  /*cTime = millis();

  if(cTime - pTime > test){ 
    pTime = cTime;
  
    Serial.print(peepVal);
    Serial.print(" , ");
  }*/
  
}

void breathCount(){
  
  breathPotVal = analogRead(breathPotPin);//select by potentiometer
  breathNo = map(breathPotVal,0,1023,12,28);//No of breath per minute
  breathTime = (60000.0/breathNo);//one breath time in milliseconds
  inspTime = breathTime/3;//Inspiration time in milliseconds
  expTime = 2.0*inspTime;//Expiration time in milliseconds 
  //motor rotation time for 1 degree rotation during inspiration
  expSpeed = 2.0*inspSpeed;//motor rotation time for 1 degree rotation during expiration
  cTime = millis();

 /* if(cTime - pTime > test){ 
    pTime = cTime;
    Serial.print(breathNo); 
    Serial.print(" , "); 
    Serial.print(inspTime);
    Serial.print(" , ");
  }*/
   
}

void bme280Result(){
  //temperature = bme.readTemperature();//reading temperature by bme280 sensor
  //pressure = bme.readPressure();//reading pressure by bme280 sensor
  //humidity = bme.readHumidity();//reading humidity by bme280 sensor 
  /*cTime = millis();

  if(cTime - pTime > test){ 
    pTime = cTime;
    Serial.print(temperature); 
    Serial.print(" , "); 
    Serial.print(pressure); 
    Serial.print(" ,"); 
    Serial.print(humidity);
    Serial.print(" , "); 
  }*/
}

void alarm(){
  if((pressure < peepVal) || (pressure > maxPressure) || (breathNo < 12) || (breathNo > 28) || (breathTime > 5000) || (breathTime < 2143)){
     alarmState = HIGH;
     tone(buzzPin,1000);//Setting 1000KHz sound alarm
     digitalWrite(alarmPin,HIGH);//ON red alarm LED
     }
  else {
    alarmState = LOW;
    digitalWrite(alarmPin,LOW);//OFF red alarm LED
  } /* 
  cTime = millis();

  if(cTime - pTime > test){ 
    pTime = cTime; 
    Serial.println(alarmState);
  }*/
}

void pressureControlMode(){
   pressureControl();
   peepControl();
   breathCount();
   
   minPos = peepVal;
   maxPos = pressVal;
   
  //Servo Control for inspiraton and expiration
  //Here pepVal and servo initial value is calibrae after experiment

   sweeper.update(minPos,maxPos,10);
   
  } 

void patientControlMode(){

   maxPressure = pressVal;
   long time1,time2;
   //minPos = peepVal;
   //maxPos = maxPressure;
     
  //Time interval select by pressure sensor
  if(pressure <= peepVal){
    time1 = millis();//initial time to start increase pressure
  }
  else if(pressure >= maxPressure) {
    time2 = millis();//the final time to reach saturation pressure
  }
  inspTime = time2 - time1;
  sweeper.update(minPos,maxPos,10);
   
}

void ledControl(int tim){
  long currentTime = millis();
  long previousTime = 0;
  int interval = tim;
  if(currentTime-previousTime > tim && greenLedState == LOW){
    greenLedState = HIGH;
    yellowLedState = LOW;
    previousTime += interval;
  }
  else {
    greenLedState = LOW;
    yellowLedState = HIGH;
  }
  digitalWrite(greenLed,greenLedState);
  digitalWrite(yellowLed,yellowLedState);
}

void printMessage() {
 cTime = millis();

  if(cTime - pTime > printInterval){ 
    pTime = cTime; 
    Serial.println("");
    Serial.print(" , ");
    Serial.print(modeState);
    Serial.print(" , "); 
    Serial.print(alarmState); 
    Serial.print(" , "); 
    Serial.print(breathNo); 
    Serial.print(" , "); 
    Serial.print(inspTime); 
    Serial.print(" , "); 
    Serial.print(temperature); 
    Serial.print(" , "); 
    Serial.print(pressure); 
    Serial.print(" ,"); 
    Serial.print(humidity);
    Serial.print(" , ");
    Serial.print(peepVal);
    Serial.print(" , ");
    Serial.print(pressVal);
    Serial.print("\n");
  }
}

void loop(){
  
 modeSelect();
 bme280Result();
 pressureControl();
 peepControl();
 breathCount();
 alarm();
 printMessage();

 
 flasher.Update(inspTime,2*inspTime);
 flasher1.Update(2*inspTime,inspTime);

 
 minPos = peepVal;
 maxPos = pressVal;
 int difPos = maxPos - minPos;
 if(maxPos-minPos == 0){//to safe unnecessary stop of motor
   difPos= 85;
 }
 inspSpeed = inspTime/(maxPos-minPos);
 if( inspSpeed == 0){//to safe unnecessary stop of servo
  inspSpeed = 3000/(maxPos-minPos);
 }


 if(modeState == 0)
 {
  if(peepVal == 5){
    sweeper.update(5,maxPos,int(inspSpeed));
  }
  if(peepVal == 10){
    sweeper.update(10,maxPos,int(inspSpeed));
  }
  if(peepVal == 15){
    sweeper.update(15,maxPos,int(inspSpeed));
  }
    
 }
 if(modeState == 1)
 {
  patientControlMode();
 }
 //sprintf(data,"\n%d,%d,%d,%d,%d,%d,%d,%d,%d\n",modeState,alarmState,breathNo,inspTime,temperature,pressure,humidity);
 //Serial.write(data);

 // Serial.write(45); // send a byte with the value 45

 // int bytesSent = Serial.write(data);
 
/*
 Serial.print(modeState);
 Serial.print(" , "); 
 Serial.print(alarmState); 
 Serial.print(" , "); 
 Serial.print(breathNo); 
 Serial.print(" , "); 
 Serial.print(inspTime); 
 Serial.print(" , "); 
 Serial.print(temperature); 
 Serial.print(" , "); 
 Serial.print(pressure); 
 Serial.print(" ,"); 
 Serial.print(humidity);
 Serial.print(" , ");
 Serial.print(peepVal);
 Serial.print(" , ");
 Serial.print(pressVal);
 Serial.println("");
 delay(10);*/
 
 
}
