
/**************************************************************************************************************
********************Arduino Ventilator Circuit's Code************************************************************
 * ----------------------------------------------------------------------------------------------------------
 * 
 * Pressere control and patient control mode code for Arduino Uno.
 * Due to lack of Ventilator in this current situation due to COVID-19 pandemic it may help to people.
 * This instrument could only use in last .This istrument not suggest to use first as the medical ventilator
 * containg much more sensor and property.The basic principle of this simple ventilator is pressure control
 * of a ambu bag by a rotating actuator attached on a servo motor. It has Pressure Control and patient Controll mode .In this project IT
 * can measure breathing number,peep,pressure,temperature,humidity,flow rate,tidal volume.The values are showing in 
 * LCD display as well as PC serial monitor.
 * 
 * Components : 
 *              1. High torqe servo(Water proof high torque metal geared servo motor) - 1pc
 *              2. BMP280 pressure Sensor - 3pcs
 *              3. buzzer - 1pcs
 *              4. Potentiometer(10K)(breath,peep,press,LCD Brightness Control) - 5 pcs
 *              5. Swipe Button - 1pc
 *              6. Jumping Wires.
 *              7. Resistor(560 Ohoms, 100 Ohom)
 *              8. 16X4 LCD Display - 1pc
 *              9. Sensor shield v-5 - 1pc
 *              10.Servo Bracket -1pc
 *              11.Arduino UNO R3 - 1pc
 *              12.Actuator -1pc
 *              13.Ambu Bag - 1pc
 *              14.Breathing Circuit
 *              15. Aeduino program loading data cable. - 1 pc
 *              
 *             # In this Circuit I am using two BME280 Pressure Sensor to using rate of air flow and
 *              other one BME280 is using for measuring pressure,temperature and Humidity.The other two BME280 Sensor
 *              to measure the flow rate and tidal volume.
 *              To connect three BME280 Sensor in a single Arduino Board SPI Hardware connection.
 *              LCD 16x4 Display
 *              
 * Connection :
 * 
 *   
 *---------------------------------Analog Pins-------------------------------------------------------------------           
 *            
 *             Breath Pot(10K) : Midddile Pin --> A0, +Ve, -Ve.
 *             Pressure Control Pot(10K) : Middle Pin --> A1,+Ve,-Ve.
 *             PEEP Pot(10K)   : Middle Pin --> A2,+Ve,-Ve.
 *             
 *-------------------------------------Digital Pins--------------------------------------------------------------
 *             Buzzer : +Ve--> D4. through 100 Ohom resistance,-Ve-->GND.
 *             Mode Swipe Button : --> D7.
 *             Servo : Yellow --> D9, Red--> +6V ,Black--> GND.(External Source)
 *             [Water proof High Torque Digital Servo motor with metal Gears]
 *             *servo operating voltage : 6-8.4 volt
 *             *Required Pulse : 3-5 Volt peak to peak square wave
 *             *15.5 kg/cm to 17kg/cm torque
 *             
 *             #Servo should powered have different power source 
 *             
 *             
 *-------------------------------|LCD DISPLAY Connection|--------------------------------------------------------
 *             
 *             VSS --> GND
 *             VDD/VCC --> +5 V
 *             VEE --> ADJUST PIN TO CONNECT 10K POT
 *             RS PIN --> D12,
 *             RW PIN -- GND
 *             E PIN --> D11,
 *             DB4 PIN --> D8,
 *             DB5 PIN --> D2,
 *             DB6 PIN --> D1,
 *             DB7 PIN --> D0,
 *             LED+ --> EITHER CONNECT TO 3.3V OR CONNECT 5V THROUGH 560 OHM
 *             LED- --> GND
 *     
 *             
 *             
 *             
 *------------------------------BMP-280 Sensor Connections-------------------------------------------------------
 *             Connect the VCC pin from all three sensors to either the 5 V or the 3.3 V output from your Arduino.
 *             Connect the GND pin from all three sensors to the GND on the Arduino. 
 *             Connect the SDA/SDI pin from all three sensors to the MOSI pin on the ICSP header from the Arduino.
 *             Connect the SCL/SCK pin from all three sensors to the SCK pin on the ICSP header from the Arduino.
 *             Connect the SDO pin from all three sensors to the MISO pin on the ICSP header from the Arduino.
 *             Conect first Sensor CSB pin to D3,Connect second sensor's CSB to D5,Connect third sensor's CSB Pin to 6.
 *              
 *              The ICSP Header looks like this:
 *                ICSP 
 *            MISO |x  x| VCC
 *             SCK |x  x| MOSI
 *           RESET |x  x| GND
 *             
 *---------------------------------------------------------------------------------------------------------------
 *             
 *             # Used Digital pins ==>   RX0,TX1,INT2,3,4,5,6,7,8,9,11,12  [MOSI11,MISO12]
 *             # Unused Digital Pins ==> SS10, SCK13      
 *             # Used Analog Pins ==>    A0, A1, A2
 *             # Unused Analog Pins ==>  A3, A4 ,A5
 *             
 *             
 *  Used Library : <Wire.h>,<LiquidCrystal.h>,<Servo.h>,<avr/wdt.h>,<BlueDot_BME280.h>,<BMP280_DEV>.......
 *  Download Link : 1) <avr/wdt.h>  http://www.nongnu.org/avr-libc/user-manual/group__avr__watchdog.html
 *                  2) <BlueDot_BME280>  https://www.bluedot.space/tutorials/connect-multiple-bme280-on-spi/
 *                  3) Other library could supplied by arduino IDE manage library section
 *                  4) https://github.com/MartinL1/BMP280_DEV
 *  Version - v-5.0
 *  Writter - Bapon Kar           
 *  Contact - baponkar600@gmail.com
 *  Last Update Time - 19/05/2020 ; 09:32:01 PM.
 *  
 * ---------------------------------------------------------------------------------------------------------
 */

#include<Wire.h>
long cTime = 0;//current time to calculate printing message
long pTime = 0;//previous time calculate to printing serial message
int printInterval = 100;//Printing Serial message time interval


//Settting LCD Display
#include<LiquidCrystal.h>
int RS_PIN = 12;
int E_PIN = 11;

int DB4_PIN = 8;
int DB5_PIN = 2;
int DB6_PIN = 1;
int DB7_PIN = 0;
LiquidCrystal lcd(RS_PIN, E_PIN, DB4_PIN, DB5_PIN, DB6_PIN, DB7_PIN);//making LiquidCrystal object

#include<Servo.h>

#include <BMP280_DEV.h> 

BMP280_DEV bmp280_1(3);                            // Instantiate (create) a BMP280_DEV object and set-up for SPI operation on digital pin D10
BMP280_DEV bmp280_2(5);                             // Instantiate (create) a BMP280_DEV object and set-up for SPI operation on digital pin D9
BMP280_DEV bmp280_3(6);
float temp_t, temp_p ;

int bme1Detected = 0; //Checks if Sensor 1 is available
int bme2Detected = 0; //Checks if Sensor 2 is available
int bme3Detected = 0; //Checks if Sensor 3 is available

float pressure1 = 0;
float pressure2 =0;
float pressure3 = 0;
float temperature1 =0;
float temperature2 = 0;
float temperature3 = 0;

float pressureDifference = 0;


float rho = 1.225;       //Density of air in Kg/m3
float area_1 = 0.000415;  //surface area in m1
float area_2 = 0.0000283;  //surface area in m2
float dt = 0;    //Time Difference
float massFlow;  //in Kg/s
float volFlow;  //in L/s
float volume;  //in Litre

int temperature = 0;
int pressure = 0;
int maxPressure = 0;
int humidity = 0;

//Setting alarm
int const buzzPin = 4;     //attach a buzzer in D4 pin
boolean alarmState = 0;

//Setting breathing rate
const int breathPotPin = A0;   //Attach a pot to control breathing rate per minute
int breathPotVal;
int breathNo;
float breathTime;
float inspTime;
float expTime;
int inspSpeed,expSpeed;

//peep pot setting
int const peepPotPin = A2;    //attach a 10K pot in this pin
int peepPotVal;
int peepVal;

//Pressure Control
const int pressContPotPin = A1;  //attaching 10k pot
int pressPotVal;
int pressVal;

const int servoPin = 9;    //attach yelow servo signal pin
int minPos ;
int maxPos ;

//setting mode select button 
const int modeButtonPin = 7;  //attaching a swipe button to select mode
boolean modeState = LOW;



class Sweeper //Making a servo rotation controlling class
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
   
    if((currentTime - lastUpdate) > updateInterval)
    {
      lastUpdate = currentTime;
      pos += increment;
      servo.write(pos);
           
      if((pos >= maxDegree) || (pos <= minDegree))
      {
        increment = -increment;
      }
    }
    servo.write(pos);  
  }
};

Sweeper sweeper;        //creating a new sweeper object

void setup()
{ 

  lcd.begin(16, 4);  // initializes the 16x4 LCD,first number represent column and second number represent row

  lcd.setCursor(0,0);              //sets the cursor at column 0 row 0 
  lcd.print("Breathing No : ");   // print message 
  
  lcd.setCursor(0,1);             //sets the cursor at column 0 and row 1
  lcd.print("Pressure : ");     //print message
  
  lcd.setCursor(0,2);              //sets the cursor at column 0 and row 2
  lcd.print("Flow Rate : ");    //print message
  
  lcd.setCursor(0,3);             //sets the cursor at column 0 and row 3
  lcd.print("Tidal Volume : "); //print message
    
  bmp280_1.begin();                                 // Default initialisation, place the BMP280 into SLEEP_MODE 
  bmp280_1.setTimeStandby(TIME_STANDBY_05MS);     // Set the standby time to 5 milli seconds
  bmp280_1.startNormalConversion();                 // Start BMP280 continuous conversion in NORMAL_MODE 
  bmp280_2.begin();                                 // Default initialisation, place the BMP280 into SLEEP_MODE 
  bmp280_2.setTimeStandby(TIME_STANDBY_05MS);     // Set the standby time to 5 milli seconds
  bmp280_2.startNormalConversion();                 // Start BMP280 continuous conversion in NORMAL_MODE  
  bmp280_3.begin();                                 // Default initialisation, place the BMP280 into SLEEP_MODE 
  bmp280_3.setTimeStandby(TIME_STANDBY_05MS);     // Set the standby time to 5 milli seconds
  bmp280_3.startNormalConversion();                 // Start BMP280 continuous conversion in NORMAL_MODE  
  
  
  sweeper.Attach(servoPin);  
  pinMode(buzzPin,OUTPUT);
  pinMode(breathPotPin,INPUT);
  pinMode(peepPotPin,INPUT);
  pinMode(pressContPotPin,INPUT);
  pinMode(modeButtonPin, INPUT);
  pinMode(servoPin,OUTPUT);
  Serial.begin(115200);
}


void bmp280Read(){
  if (bmp280_1.getTempPres( temp_t,  temp_p))    // Check if the measurement is complete
  {
    temperature1 = temp_t;
    pressure1 = temp_p;
     
  }
  if (bmp280_2.getTempPres(temp_t, temp_p))    // Check if the measurement is complete
  {
    temperature2 = temp_t;
    pressure2 = temp_p;
     
  }

   if (bmp280_3.getTempPres( temp_t,  temp_p))    // Check if the measurement is complete
  {
    temperature3 = temp_t;
    pressure3 = temp_p;
     
  }
}

void flowRate(){
  bmp280Read();
  pressureDifference = 100*(pressure2 - pressure1);//if temperature2>temperature1 and changing into Pa
  //[By using this formula dP=(by using formula (W^2)/2rho)*(1/A2^2−1/A1^2)]
  
  massFlow = 1000*sqrt((abs(pressureDifference)*2*rho)/((1/pow(area_2,2)))-(1/pow(area_1,2)));//mass in Kg
  volFlow = massFlow/rho;//volume of air flow in L/s
  volume = volFlow*dt + volume;//total volume
  dt = 0.001;
  delay(1);//I using this delay to find the volume flow in this time
}


void modeSelect(){
  modeState = digitalRead(modeButtonPin);//Digital read of mode either preesure control or patient control  
  modeState = int(modeState);
}

void pressureControl(){
  
  pressPotVal = analogRead(pressContPotPin);//control by potentiometer attach at A1
  pressVal = map(pressPotVal,0,1023,50,180);//taking arbitary value
  pressVal = 120;
  //it should change in actual condition with checking bmp280 result
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
}

void breathCount(){
  
  breathPotVal = analogRead(breathPotPin);//select by potentiometer
  breathNo = map(breathPotVal,0,1023,12,28);//No of breath per minute
  breathTime = (60000.0/breathNo);//one breath time in milliseconds
  inspTime = breathTime/3;//Inspiration time in milliseconds
  expTime = 2.0*inspTime;//Expiration time in milliseconds 
  //motor rotation time for 1 degree rotation during inspiration
  expSpeed = 2.0*inspSpeed;//motor rotation time for 1 degree rotation during expiration
}

void alarm(){
  if((pressure < peepVal) || (pressure > maxPressure) || (breathNo < 12) || (breathNo > 28) || (breathTime > 5000) || (breathTime < 2143)){
     alarmState = HIGH;
     tone(buzzPin,1000);//Setting 1000KHz sound alarm
     }
  else {
    alarmState = LOW;
  } 
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

void lcdDisplay(){

  lcd.setCursor( 2,0);
  lcd.print(breathNo);//Printing breathing number at column 2 row 0

  lcd.setCursor(2,1);
  lcd.print(pressure);//Printing pressure value at column 2 row 1


  lcd.setCursor(2,2);
  lcd.print(volFlow);//Printing flowrate at column 2 row 2


  lcd.setCursor(2,3);
  lcd.print(volume);//Printing tidal volume at column 2 row 3
}

void printMessage() {
  cTime = millis();
  if(cTime - pTime > printInterval){ 
    pTime = cTime; 
    Serial.println("");
    Serial.print(" , ");     //just omit this comma
    Serial.print(modeState); //mode State either patient controll or pressure control
    Serial.print(" , "); 
    Serial.print(alarmState); //Alarm state
    Serial.print(" , "); 
    Serial.print(breathNo); //breathing number per minute
    Serial.print(" , "); 
    Serial.print(inspTime); //inspiratory time
    Serial.print(" , "); 
    Serial.print(temperature3); //temperature
    Serial.print(" , "); 
    Serial.print(pressure3); //pressure
    Serial.print(" ,"); 
    Serial.print(humidity);//humidty
    Serial.print(" , ");
    Serial.print(peepVal);//peep value
    Serial.print(" , ");
    Serial.print(pressVal);//pressure value
    Serial.print(" , ");
    Serial.print(volFlow);//flow rate
    Serial.print(" , ");
    Serial.print(volume);//tidal volume
    Serial.print("\n");
  }
}

void loop(){
  
 modeSelect();
 bmp280Read();
 flowRate();
 pressureControl();
 peepControl();
 breathCount();
 alarm();
 lcdDisplay();
 printMessage();
 
 minPos = peepVal;
 maxPos = pressVal;
 
 int difPos = maxPos - minPos;
 
 if(maxPos-minPos == 0){ //to safe unnecessary stop of motor
   difPos= 85;
 }
 inspSpeed = inspTime/(maxPos-minPos);
 if( inspSpeed == 0){  //to safe unnecessary stop of servo
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
}
