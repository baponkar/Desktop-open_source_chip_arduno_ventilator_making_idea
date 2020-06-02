
/**************************************************************************************************************
********************Arduino Ventilator Circuit's Code************************************************************
   ----------------------------------------------------------------------------------------------------------

   Pressere control and patient control mode code for Arduino Uno.
   Due to lack of Ventilator in this current situation due to COVID-19 pandemic it may help to people.
   This instrument could only use in last .This istrument not suggest to use first as the medical ventilator
   containg much more sensor and property.The basic principle of this simple ventilator is pressure control
   of a ambu bag by a rotating actuator attached on a servo motor. It has Pressure Control and patient Controll
   mode .In this project It can measure breathing number,peep,pressure,temperature
   ,humidity,flow rate,tidal volume.The values are showing in
   LCD display as well as PC serial monitor.

   Components :
                1. High torqe servo(Water proof high torque metal geared servo motor) - 1pc
                2. BMP280 pressure Sensor - 3pcs
                3. buzzer - 1pcs
                4. Potentiometer(10K)(breath,peep,press,LCD Brightness Control) - 5 pcs
                5. Swipe Button - 1pc
                6. Jumping Wires.
                7. Resistor(560 Ohoms, 100 Ohom)
                8. 20X4 LCD Display - 1pc
                9. I2C module
                10. Sensor shield v-5 - 1pc
                11.Servo Bracket -1pc
                12.Arduino UNO R3 - 1pc
                13.Actuator -1pc
                14.Ambu Bag - 1pc
                15.Breathing Circuit
                16. Aeduino program loading data cable. - 1 pc

               # In this Circuit I am using two BME280 Pressure Sensor to using rate of air flow and
                other one BME280 is using for measuring pressure,temperature and Humidity.The other two BMP280 Sensor
                to measure the flow rate and tidal volume.
                To connect three BME280 Sensor in a single Arduino Board SPI Hardware connection.
                LCD 20x4 Display

   Connection :


  ---------------------------------Analog Pins-------------------------------------------------------------------

               Breath Pot(10K) : Midddile Pin --> A0, +Ve, -Ve.
               Pressure Control Pot(10K) : Middle Pin --> A1,+Ve,-Ve.
               PEEP Pot(10K)   : Middle Pin --> A2,+Ve,-Ve.

  -------------------------------------Digital Pins--------------------------------------------------------------
               Buzzer : +Ve--> D4. through 100 Ohom resistance,-Ve-->GND.
               Mode Swipe Button : --> D7.
               Red LEd : --> D2(through 220 ohm to GND)
               Green LED : --> D8(through 220 ohm to GND)
               Yellow LED : --> D10
               
               Servo : Yellow --> D9, Red--> +6V ,Black--> GND.(External Source)
               
               [Water proof High Torque Digital Servo motor with metal Gears]
 *             *servo operating voltage : 6-8.4 volt
 *             *Required Pulse : 3-5 Volt peak to peak square wave
 *             *15.5 kg/cm to 17kg/cm torque

               #Servo should powered have different power source


  -------------------------------|LCD DISPLAY Connection|--------------------------------------------------------

  --------------------------------I2C Module Connection -------------------------------------------------------
            

            connect LCD Display to I2C Module
            SDA --> A4
            SCL --> A5
            
            In general without IC2 Module Connection of LCD Display---
            1-    VSS --> GND
            2-    VDD/VCC --> +5 V
            3-    VEE --> ADJUST PIN TO CONNECT 10K POT
            4-    RS PIN --> D12,
            5-    RW PIN -- GND
            6-    E PIN --> D11,
            7-    D0
            8-    D1
            9-    D2
            10-   D3
            11-   DB4 PIN --> D8,
            12-   DB5 PIN --> D2,
            13-   DB6 PIN --> D1,
            14-   DB7 PIN --> D0,
            15-   LED+ --> EITHER CONNECT TO 3.3V OR CONNECT 5V THROUGH 560 OHM
            16-   LED- --> GND


  ------------------------------BMP-280 Sensor Connections-------------------------------------------------------
               Connect the VCC pin from all three sensors to either the 5 V or the 3.3 V output from your Arduino.
               Connect the GND pin from all three sensors to the GND on the Arduino.
               Connect the SDA/SDI pin from all three sensors to the MOSI pin on the ICSP header from the Arduino.
               Connect the SCL/SCK pin from all three sensors to the SCK pin on the ICSP header from the Arduino.
               Connect the SDO pin from all three sensors to the MISO pin on the ICSP header from the Arduino.
               Conect first Sensor CSB pin to D3,Connect second sensor's CSB to D5,Connect third sensor's CSB Pin to D6.

               
                MISO->SD0
                MOSI->SDA/SDI

                The ICSP Header looks like this:
                  ICSP
              MISO |x  x| VCC
               SCK |x  x| MOSI
             RESET |x  x| GND

  ---------------------------------------------------------------------------------------------------------------

               # Used Digital pins ==>     D2,D3,D4,D5,D6,D7,D8,D9,D10
               # Unused Digital Pins ==>  0[RX0],1[TX1],11[MOSI11],12[MISO12], SCK13
               # Used Analog Pins ==>    A0, A1, A2
               # Unused Analog Pins ==>  A3, A4 ,A5


    Used Library : <Wire.h>,<LiquidCrystal.h>,<Servo.h>,<avr/wdt.h>,<BlueDot_BME280.h>,<BMP280_DEV>.......
    Download Link : 1) <avr/wdt.h>  http://www.nongnu.org/avr-libc/user-manual/group__avr__watchdog.html
                    2) <BlueDot_BME280>  https://www.bluedot.space/tutorials/connect-multiple-bme280-on-spi/
                    3) Other library could supplied by arduino IDE manage library section
                    4) <BMP280_DEV> https://github.com/MartinL1/BMP280_DEV
    Version - v-5.0
    Writter - Bapon Kar
    Contact - baponkar600@gmail.com
    Last Update Time - 02/06/2020 ; 09:32:01 PM.

   ---------------------------------------------------------------------------------------------------------
*/

#include<Wire.h>
unsigned long cTime;//current time to calculate printing message
unsigned long pTime;//previous time calculate to printing serial message
int printInterval = 100;//Printing Serial message time interval


//Settting LCD Display
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);

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
float pressure2 = 0;
float pressure3 = 0;
float temperature1 = 0;
float temperature2 = 0;
float temperature3 = 0;

float pressureDifference = 0;
boolean inspState;
boolean expState;
int redLedPin = 2;
int greenLedPin = 8;
int alarmLedPin = 10;


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
int inspSpeed, expSpeed;




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


unsigned  long pTime1,pTime2;
unsigned  long lastUpdate1;
unsigned  long lastUpdate2;


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

    void update(int mDeg, int mxDeg, int interval)
    {
    
      unsigned long currentTime = millis();

      minDegree = mDeg;
      maxDegree = mxDeg;
      midDegree = (mDeg + mxDeg) / 2;
      updateInterval = interval;
      if (increment > 0 && updateInterval == interval) {
        updateInterval = 2 * interval;
      }
      if (increment < 0 && updateInterval == 2 * interval) {
        updateInterval = interval;
      }

      if(pos > mxDeg && increment > 0){
        increment = - increment;
        pos += increment;
      }
      if(pos <mDeg && increment <0){
        increment = -increment;
        pos += increment;
      }

      if ((currentTime - lastUpdate) > updateInterval)
      {
        lastUpdate = currentTime;
        pos += increment;
        servo.write(pos);

        if ((pos > maxDegree) || (pos < minDegree))
        {
          increment = -increment;
          servo.write(pos);
        }
      }
      servo.write(pos);
    }
};

Sweeper sweeper;        //creating a new sweeper object

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

  void Update(long on, long off)
  {
    // check to see if it's time to change the state of the LED
     OnTime = on;
    OffTime = off;
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

class Flasher2
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
  Flasher2(int pin)
  {
  ledPin = pin;
  pinMode(ledPin, OUTPUT);     
  ledState = LOW; 
  previousMillis = 0;
  }

  void Update(long on, long off)
  {
    // check to see if it's time to change the state of the LED
     OnTime = on;
    OffTime = off;
    unsigned long currentMillis = millis();
     
    if((ledState == HIGH) && (currentMillis - previousMillis >= OffTime))
    {
      ledState = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(ledPin, !ledState);  // Update the actual LED
    }
    else if ((ledState == LOW) && (currentMillis - previousMillis >= OnTime))
    {
      ledState = HIGH;  // turn it on
      previousMillis = currentMillis;   // Remember the time
      digitalWrite(ledPin, !ledState);   // Update the actual LED
    }
  }
};


Flasher1 redLed(redLedPin);//Flashing during expiratory time
Flasher2 greenLed(greenLedPin);//Flashing during inspiratory time

void setup()
{

  lcd.begin();  // initializes the 20x4 LCD,first number represent column and second number represent row
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Breath No. : ");
  lcd.setCursor(0, 1);
  lcd.print("Pres :");
  lcd.setCursor(0, 2);
  lcd.print("Flow Rate :");
  lcd.setCursor(0, 3);
  lcd.print("Tidal Vol.: ");

  bmp280_1.begin();                                 // Default initialisation, place the BMP280 into SLEEP_MODE
  bmp280_1.setTimeStandby(TIME_STANDBY_62MS);     // Set the standby time to 5 milli seconds
  bmp280_1.startNormalConversion();                 // Start BMP280 continuous conversion in NORMAL_MODE
  bmp280_2.begin();                                 // Default initialisation, place the BMP280 into SLEEP_MODE
  bmp280_2.setTimeStandby(TIME_STANDBY_62MS);     // Set the standby time to 5 milli seconds
  bmp280_2.startNormalConversion();                 // Start BMP280 continuous conversion in NORMAL_MODE
  bmp280_3.begin();                                 // Default initialisation, place the BMP280 into SLEEP_MODE
  bmp280_3.setTimeStandby(TIME_STANDBY_125MS);     // Set the standby time to 5 milli seconds
  bmp280_3.startNormalConversion();                 // Start BMP280 continuous conversion in NORMAL_MODE


  //pinMode(redLedPin,OUTPUT);
  //pinMode(greenLedPin,OUTPUT);
  pinMode(alarmLedPin,OUTPUT);

  sweeper.Attach(servoPin);
  pinMode(buzzPin, OUTPUT);
  pinMode(breathPotPin, INPUT);
  pinMode(peepPotPin, INPUT);
  pinMode(pressContPotPin, INPUT);
  pinMode(modeButtonPin, INPUT);
  pinMode(servoPin, OUTPUT);
  Serial.begin(115200);


}


void bmp280Read() {
  if (bmp280_1.getPressure(temp_p))    // Check if the measurement is complete
  {

    pressure1 = temp_p;

  }
  if (bmp280_2.getPressure( temp_p))    // Check if the measurement is complete
  {

    pressure2 = temp_p;

  }

  if (bmp280_3.getTempPres( temp_t,  temp_p))    // Check if the measurement is complete
  {
    temperature3 = temp_t;
    //pressure3 = temp_p;

    //Converting Pa to cm H2O
    pressure3 = temp_p * 0.0102;

  }
}

void flowRate() {
  bmp280Read();
  breathCount();
  

  if (pressure2 > pressure1) {
    pressureDifference = 100 * (pressure2 - pressure1); //if pressure2>pressure1 and changing into Pa
  }
  else if (pressure2 < pressure1) {
    pressureDifference = 100 * (pressure1 - pressure2); //if pressure1>pressure2 and changing into Pa
  }
  //[By using this formula dP=(by using formula (W^2)/2rho)*(1/A2^2−1/A1^2)]

  massFlow = 1000 * sqrt(((pressureDifference) * 2 * rho) / (((1 / pow(area_2, 2))) - (1 / pow(area_1, 2)))); //mass in Kg
  volFlow = 60*massFlow / rho; //volume of air flow in L/minute

  cTime = millis();
  if(cTime - pTime > inspTime){
    pTime = cTime;
    volume = 0.0;
  }
  else{
  volume = ((volFlow/60 )* dt + volume); //total volume in milliLitre during inspiration
  }
  
  dt = 0.001;
  delay(1);//I using this delay to find the volume flow in this time
}



void modeSelect() {
  modeState = digitalRead(modeButtonPin);//Digital read of mode either preesure control or patient control
  modeState = int(modeState);
}

void pressureControl() {

  pressPotVal = analogRead(pressContPotPin);//control by potentiometer attach at A1
  pressVal = map(pressPotVal, 0, 1023, 50, 180); //taking arbitary value
  pressVal = 120;
  //it should change in actual condition with checking bmp280 result
}

void peepControl() {
  peepPotVal = analogRead(peepPotPin);
  if (peepPotVal >= 0 && peepPotVal <= 341) { //My pot have problem as it showing maximum value 60 instead of 1023 so i use  this values
    peepVal = 5;
  }
  else if (peepPotVal > 341 && peepPotVal <= 682) {
    peepVal = 10;
  }
  else {
    peepVal = 15;
  }
}

void breathCount() {
  breathPotVal = analogRead(breathPotPin);//select by potentiometer
  //breathNo = 10+breathPotVal*20/1023;
  breathNo = map(breathPotVal, 0, 1023, 10, 30); //No of breath per minute
  breathTime = (60000.0 / breathNo); //one breath time in milliseconds
  inspTime = breathTime / 3; //Inspiration time in milliseconds
  expTime = 2.0 * inspTime; //Expiration time in milliseconds
  //motor rotation time for 1 degree rotation during inspiration
}


void state() {
  breathCount();
  cTime = millis();
 
  lastUpdate1 = inspTime;
  lastUpdate2 = expTime;

  expState = !inspState;
  if(cTime-pTime1 > lastUpdate1){
    pTime1 = cTime;
    inspState = !inspState;

  }
  if(cTime-pTime2 > lastUpdate2){
    pTime2 = cTime;
    expState = !expState;
  }

  
}

void alarm() {
  digitalWrite(alarmLedPin,alarmState);//Flashing Yellow LED in Alarming situation
  if ((pressure < peepVal) || (pressure > maxPressure) || (breathNo < 12) || (breathNo > 28) || (breathTime > 5000) || (breathTime < 2143)) {
    alarmState = HIGH;
    tone(buzzPin, 1000); //Setting 1000KHz sound alarm
  }
  else {
    alarmState = LOW;
  }
}

void pressureControlMode() {
  pressureControl();
  peepControl();
  breathCount();

  minPos = peepVal;
  maxPos = pressVal;

  //Servo Control for inspiraton and expiration
  //Here pepVal and servo initial value is calibrae after experiment
  sweeper.update(minPos, maxPos, 10);

}

void patientControlMode() {

  maxPressure = pressVal;
  long time1, time2;
  //minPos = peepVal;
  //maxPos = maxPressure;

  //Time interval select by pressure sensor
  if (pressure <= peepVal) {
    time1 = millis();//initial time to start increase pressure
  }
  else if (pressure >= maxPressure) {
    time2 = millis();//the final time to reach saturation pressure
  }
  inspTime = time2 - time1;
  sweeper.update(minPos, maxPos, 10);

}


void lcdDisplay() {
  // Print a message to the LCD.
  lcd.setCursor(13, 0);
  lcd.print(breathNo);
  lcd.setCursor(6, 1);
  lcd.print(pressure3);
  lcd.setCursor(12,1);
  lcd.print("PEEP:");
  lcd.setCursor(18,1);
  lcd.print(peepVal);
  lcd.setCursor(13, 2);
  lcd.print(volFlow);
  lcd.setCursor(13, 3);
  lcd.print(volume);

}


void printMessage() {
  cTime = millis();
  if (cTime - pTime > printInterval) {
    pTime = cTime;
    Serial.println("");
    Serial.print(" , ");     //just omit this comma
    Serial.print(modeState); //mode State either patient controll or pressure control
    Serial.print(" , ");
    Serial.print(alarmState); //Alarm state
    Serial.print(" , ");
    Serial.print(breathNo); //breathing number per minute
    Serial.print(" , ");
    Serial.print(inspTime); //inspiratory time in milli second
    Serial.print(" , ");
    Serial.print(temperature3); //temperature in degree C
    Serial.print(" , ");
    Serial.print(pressure3); //pressure in cm H2O
    Serial.print(" ,");
    Serial.print(humidity);//humidty in %
    Serial.print(" , ");
    Serial.print(peepVal);//peep value in cm H2O
    Serial.print(" , ");
    Serial.print(pressVal);//pressure value
    Serial.print(" , ");
    Serial.print(volFlow);//flow rate in Litre/second
    Serial.print(" , ");
    Serial.print(volume);//tidal volume in Litre
    Serial.print("\n");
  }
}

void loop() {
  state();
  modeSelect();
  bmp280Read();
  flowRate();
  pressureControl();
  peepControl();
  breathCount();
  //alarm();
  lcdDisplay();
  printMessage();
  /*
  Serial.print(int(inspState));
  Serial.print(" , ");
  Serial.print(int(expState));
  Serial.print("\n");
  */
  

  greenLed.Update(inspTime,expTime);
  redLed.Update(expTime,inspTime);

  minPos = peepVal;
  maxPos = pressVal;

  int difPos = maxPos - minPos;

  if (maxPos - minPos == 0) { //to safe unnecessary stop of motor
    difPos = 85;
  }
  inspSpeed = inspTime / (maxPos - minPos);
  expSpeed = 2.0 * inspSpeed; //motor rotation time for 1 degree rotation during expiration
  
 
  
  if (modeState == 0)
  {
 

    if (peepVal == 5) {
      sweeper.update(5, maxPos, int(inspSpeed));
    }

    if (peepVal == 10) {
      sweeper.update(10, maxPos, int(inspSpeed));
    }

    if (peepVal == 15) {
      sweeper.update(15, maxPos, int(inspSpeed));
    }
  }
  if (modeState == 1)
  {
    patientControlMode();
  }
}
