/*
*This is a GUI program to showing Serial Data and showing correspondig graph upto 4 seconds where one inspiration and expiration be completed
*It just need to add to collect serial data from Arduino.This program using Graph_page class to create three Graph inside of main window.
*
*
*
*
*
*
*Java Version - 11.0.6
*Processing Version -3.5.4
*Version - 5.0.0
*Writer : Bapon Kar
Contact : baponkar600@gmail.com
*Last Updated : 18/05/2020 @10:16 PM
*/




import processing.serial.*;
Serial myPort;
byte [] inBuffer = new byte[7];
String myString;
String [] list;
String [] serialData = new String[12];


Graph graph1;
Graph graph2;
Graph graph3;
int w = 1000;//window width
int h = 700;//window height
float pw = w/2+200;//each seagment width
float ph = h/3- 100;//each seagment height

//Storing incoming serial data into this arryas
float [] pressureData = new float[60];
float [] flowData = new float[60];
float [] tidalVolumeData = new float[60];
float [] temperatureData = new float[60];
float [] humidityData = new float[60];
float [] peepData = new float[60];
float [] maxPressureData = new float[60];
float [] flowRateData = new float [60];



float pressure = 0,flowRate = 0,tidalVolume = 0,temperature,humidity,inspTime,maxPressure;
int modeState,alarmState,breathingNo,peep;

//measuring time measurements
int time =0;
int second= second();
int minute = minute();
int hour = hour();
int milli = millis();
int second1= second();
int minute1 = minute();
int hour1 = hour();
int milli1 = millis();
int second2=0,minute2=0,hour2=0;




PFont font;


void setup(){
  
  size(1200,700);
  frameRate(15);//4 cycle in a minute
  
  //creating port
  //You may change the portName as your device wise if this script not works
  String portName = Serial.list()[0];//the first active open port
  print(portName);
  myPort = new Serial(this,portName,115200);
  
  for(int i=0;i<60;i++){//initialise to zero of all serial array
   pressureData[i] =0;
   flowData[i] = 0;
   tidalVolumeData[i] = 0;
   temperatureData[i] = 0;
   humidityData[i] = 0;
   peepData[i] = 0;
   maxPressureData[i] = 0;
   flowRateData[i] = 0;
   tidalVolumeData[i] = 0;
  }
  
   for (int i =0;i<12;i++){
      serialData[i] =str( 0);
    }
    
    
  font = createFont(PFont.list()[50],10);//Creating a font label
  
  graph1 = new Graph(60,40,pw,ph,40,10,color(155,0,0),0,6,40,0);//making first graph page for pressure showing
  graph2 = new Graph(60,ph+130,pw,ph,40,10,color(17,150,89),0,6,150,0);//making second graph page for flow rate showing
  graph3 = new Graph(60,ph+350,pw,ph,40,10,color(78,55,9),0,6,500,-500);//making third graph page for tidal volume showing
  background(0);
}

void draw(){
  
  //To track the time
  second= second();
  minute = minute();
  hour = hour();
  milli = millis();
  second2= second();
  if(second2 == 59){
  minute2+=1;
  }
  if(minute2 == 59){
  hour2++;
 }
  
  //refreshing background in after each 15 seconds
 
 
  if(time >= 59){
  background(0);
  }
  
  
  //Receiving Serial data from serial port
  while(myPort.available() > 0) {
    inBuffer = myPort.readBytes();
    myPort.readBytes(inBuffer);
    
    if(inBuffer != null){
      myString = new String (inBuffer);
      list = split(myString, ',');
    //  println(list.length);
      delay(10);
  }
  
  if(list.length == 12){
    for (int i =0;i<12;i++){
      serialData[i] = list[i];
      // println(i,":",serialData[i]);
    }
  }
  //println("length:",list.length);
  if(list.length == 12){
   modeState = int(trim(serialData[1]));
   alarmState = int(trim(serialData[2]));
   breathingNo = int(trim(list[3]));
   inspTime = float(trim(serialData[4]));
   temperature = float(trim(serialData[5]));
   pressure = float(trim(serialData[6]));
   humidity = float(trim(serialData[7]));
   peep = int(trim(serialData[8]));
   maxPressure = float(trim(serialData[9]));
   flowRate = float(trim(serialData[10]));
   tidalVolume = float(trim(serialData[11]));
  }
  
  /*//For testing purpose
  pressure = random(0,40);
  flowRate = random (50,150);
  tidalVolume = random(0,10);*/
   
  //pressure = random(0,40);//creating pressure value in between 0 and 40
  //flowRate = random(50,150);//creating flowrate random value
  //tidalVolume = random(0,10);//creating tidal Volume random value
  //breathingNo = int(random(12,28)); //Creating breathing no random values
  
  graph1.display("Time in S","Pressure in cm H\u2082O");//Making x and y label of pressure graph
  graph2.display("Time in S","Flow Rate in L/minute");//Making x and y label of flow rate graph
  graph3.display("Time in S","Tidal Volume in mL");//Making x and y label of tidal volume graph
 
  
  dataDraw();
  valueShow();
  
 }
}

//-----------------------------------------------------------------------------------------------------

void valueShow(){
  
  textSize(20);
  fill(0);
  stroke(0);
  rect(60+pw+150-130,35,300,30); //Pressure background rectangle
  rect(60+pw+150-130,ph+135,300,30);//Flow rate background rectangle
  rect(60+pw+150-130,ph+355,300,30);//Tidal Volume background rectangle
  rect(20,h-30,500,50);//Contact background rectangle
  
  rect(15,ph+70,230,20);//Current Time background
  rect(w-220,3*ph-50,400,80);//Breathing No background
  rect(15,5,300,20);//Start time backgroud rectangle
  rect(30,ph*3+20,200,50);//Run Time background rectangle
  
  rect(60+pw+20,ph+360,400,400);//background rectangle of temperature,humidity,peep and max Pressure
  rect(430,5,230,20);//making background rectangle of mode
  
  fill(255);
  text("Pressure: " + nf(pressure,2,3)+"  cm H\u2082O",60+pw+170,60);
  text("Flow Rate: " + nf(flowRate,2,3)+" L/minute",60+pw+170,ph+130+30);
  text("Tidal Volume: " + nf(tidalVolume,2,3)+" mL",60+pw+170,ph+350+30);
 // println("FlowRate:",flowRate);
  
  
  text("Temperature  : "+nf(temperature,2,3)+" \u00B0 C",60+pw+170,ph+360+60);
  text("Humidity : "+nf(humidity,2,3)+" %",60+pw+170,ph+360+90);
  text("PEEP : "+nf(peep,2) + "  cm H\u2082O",60+pw+170,ph+360+120);
  text("Max Pressure : "+nf(maxPressure,2,0) + "  cm H\u2082O",60+pw+170,ph+360+140);
  
  text("Current Time "+hour+":"+minute+":"+second,130,ph+87);
  text("Start Time "+hour1+":"+minute1+":"+second1,120,22);
  text("Run Time: "+str(hour2)+":"+str(minute2)+":"+str(second2),120,ph*3+50);
  
  if(modeState == 0){
  text("Mode State :"+"PC-CMV",540,22);
  
  }
  if(modeState == 1){
    text("Mode State :" + "CSV-PS",540,22);
  }
  
  textSize(45);
  text(breathingNo,w+100,3*ph+5);
  textSize(20);
  text("Breathing No per minute",w-100,3*ph);
  
  textSize(20);
  fill(255);
  text("Contact "+"\u00A9"+"baponkar600@gmail.com", 200,h-10);
  textSize(10);
  stroke(78,55,9);
  fill(0);
}




void dataDraw(){
  //Track the time
   if(time >= 59){
    time =0;
  }
   else {
    time++;
   }
  
  //Due to absence of serial Data I am using this values
 // pressureData[time] = random(40,40+ph);  //For testing display in absence of serial Data
  pressureData[time] = map(pressure,0,40,40+ph,40);
  
  //flowData[time] = random(ph+130,2*ph+130);  //For testing display in absence of serial Data
  flowData[time] = map(flowRate,50,150,2*ph+85,ph+130); 
  
  //tidalVolumeData[time] = random(ph+350,2*ph+350);   //For testing display in absence of serial Data
  tidalVolumeData[time] = map(tidalVolume,-500,500,2*ph+350,ph+350);
  
  //The following values printing only
 // temperatureData[time] = random(15,45);//for testing purpose   //For testing display in absence of serial Data
  temperatureData[time] = temperature;
  
  //humidityData[time] = random(0,100);  //For testing display in absence of serial Data
   humidityData[time] = humidity;
  
  //peepData[time] = random(0,15);//for testing purpose
  peepData[time] = peep;
  
 // maxPressureData[time] = random(5,15);//for testing purpose
   maxPressureData[time] = maxPressure;

  
  float x = map(time,0,59,60,60+pw);//converting from time into graph x axis range
  //1 unit time = pw/59 units in the desired x axis
  fill(255);
  
  
  //Drawing three dots
  ellipse(x,pressureData[time],5,5);//for pressure
  ellipse(x,flowData[time],5,5);//forflow rate
  ellipse(x,tidalVolumeData[time],5,5);//for tidal volume
  
  
  //drawing curve
  int time1 = time-1;
  if(time1 < 0){
    time1 = 0;
  }
  
  stroke(255);
  strokeWeight(2);
  strokeJoin(ROUND);
  line(x-pw/59,pressureData[time1],x,pressureData[time]);//For drawing pressure graph
  line(x-pw/59,flowData[time1],x,flowData[time]);//For drawing Volume rate
  line(x-pw/59,tidalVolumeData[time1],x,tidalVolumeData[time]);//For drawing tidal volume 
}
