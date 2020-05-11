# <p style='color:blue'> OPEN SOURCE CHIP "VENTILATOR" CIRCUIT IDEA & CIRCUIT AND CODES</p>

## <p style='color:green'>Arduino-Ventilator Electtronic Configaration</p>
### <p style = 'color:magenta'> Required  electronic components :</p>

- [x] Arduino UNO R3.(1 Pice)
- [x] BME-280 Pressure Sensor Module.(3 Pieces)
- [x] 10K Potentiometer (3 Pieces)
- [x] Arduino Uno Sensor Shield.(1 Pice)
- [x] High Torqe Servo Motor.(1 Pice,May be MG-996 Servo work!)
- [x] Buzzer.(1 Piece)
- [x] Swipe Button. (1 Pice)
- [x] Jumping Wires.
- [x] Power Source.(One for Servo and other for Arduino)
- [x] Computer.


![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+)<p style='color:red'>The important message : I did not have  all items as my country is in Lockdown.So I am unable to test all the staff.If you are interested to make this then you need to your own experiment and conclusion .You may find out multiple numbers of bug in this project.I don't know.</p>


## <p style = 'color:red'>1. Why do I made this?</p>
 ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) We all know world is going through a pandemic situation due to COVID-19.This Corona virus mainly attacking on lungs and making Pnumenia of the patient. So maximum time patient need a ventilaton support .We all know that our system have only limited number ventilator in every country.This virus transmitting very fast and getting infected more and more persion in each day.The original medical ventilator has very important and complex property and it's building time and price both are high.So we need a fast and easy  building machine which also be chip from this idea we need a chip ventilator.It may help if there has no other option.I will recomend not to use in normal situation it should use in extreem situation.

## <p style = 'color:red'> 2. What is actually have in this project ?</p>
 ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) The basic idea of the ambu bag compress VENTILATOR is to controlled compress and release of [Ambu Bag](https://images.app.goo.gl/5exEBuaQRQ4HmXZ7A).So we need a control run of a servo motor what vexactly will do this project.

 ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) This is not the all !  It has two mode(PC-CMV or pressure Control Mode) and (CSV-PS or Patient Controlled Mode).Which could be control by a swipe switch.
1.  * CSV-PS : We can select this mode by placing mode switch at "0".Now we need to slect number of breath per minute by breathing Pot.Now select the minimum pressure selecting by peep pot and select the maximum pressure by pressure pot.Now motor give equal number of forward and backward rotation  which is equal to breathing number per minute.
  * The two BME-280 sensor measuring air flow rate and supplied tidal volume and showing on desktop application.
  * Another BME-280 sensor record pressure,temperature and humidity  and showing on Desktop app.

2.  * PC-CMV : We can select this mode by placing mode switch on "1".In this mode we can't select breathing number manually.Actual Idea of this mode is The motor run forward when patient need a inspiration and run backward when patient need to expiration.
  * The two BME-280 sensor measuring air flow rate and supplied tidal volume and showing on desktop application.
  * Another BME-280 sensor record pressure,temperature and humidity  and showing on Desktop app.

3. I attached a Buzzer .It will make sound if there arise any kind alarming situation like,low or very  high pressure,low or very temperation,low or very high humidity,motor stopage etc.

4. Let's talk about desktop application.It is showing real time pressure,air flow rate and tidal volume data logging with graph.It is also showing some other imporatant serial data which is obtained from Arduino like breathing no,inspiration time,expiration time,temperature,humidity,runnig time etc.

 ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) Reference : I got inspiration to work in this kind project from here-

 * [This MIT Paper](https://web.mit.edu/2.75/projects/DMD_2010_Al_Husseini.pdf)
 * [This Instructable](https://www.instructables.com/id/COVID-19-Rapid-Manufacture-Ventilator-BVM-Ambubag-/)
 * [The ventilator graph analysis](https://youtu.be/KSd1c8koNaA)


 * ### <p style='color:green'>If you would like to use this project :</p>

 * #### Linux :
 You need arduino IDE to upload the arduino code into arduino.
   If you would like to Download this "arduino-IDE" see [this](https://www.arduino.cc/en/main/software) link.

Before install this application you need to install Java in your computer.

       Download this project file which containing the source file
      To run desktop application
      If your machine is 64 bit
       open Terminal and type
       $cd $HOME/Downloads/open_source_chip_arduno_ventilator_making_idea/processing_desktop_application_1_0/application.linux.64
and then
        $./processing_desktop_application_1_0

       If your machine is 32 bit
         Before instaall this application you need to install Java in your computer.
        open Terminal and type
        $cd /$HOME/open_source_chip_arduno_ventilator_making_idea/processing_desktop_application_1_0/application.linux32/processing_desktop_application_1_0
and then
        $./processing_desktop_application_1_0



 * #### Windows  :
 You need arduino IDE to upload the arduino code into arduino.
   If you would like to Download this "arduino-IDE" see [this](https://www.arduino.cc/en/main/software) link.

   Before instaall this application you need to install Java in your computer.

   Download this project file which containing the source file.
   Now if your machine is 64 bit then go to downloaded folder and enter  inside of application.windows64 and double click on processing_desktop_application_1_0.exe

   Now if your machine is 32 bit then go to downloaded folder and enter  inside of application.windows 32 and double click on processing_desktop_application_1_0.exe

 * #### Mac :
 You need arduino IDE to upload the arduino code into arduino.
   If you would like to Download this "arduino-IDE" see [this](https://www.arduino.cc/en/main/software) link.
   Before instaall this application you need to install Java in your computer.
     Download this project file which containing the source file

* #### <p style='color:green'>If you would like to develop this project </p>
  * I have used "arduino-1.8.12-linux64" IDE to write Arduino Code.
    If you would like to Download this "arduino-IDE" see [this](https://www.arduino.cc/en/main/software) link.

  * I have used "processing-3.5.4-linux64" IDE to write desktop application.
    If you would like to Download "processing-IDE" see [this](https://processing.org/download/) link.
