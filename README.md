![GitHub Logp](chip_open_source_arduino_based_ventilator_logo.jpg)
### <p style='color:blue'> OPEN SOURCE CHIP "VENTILATOR" CIRCUIT IDEA & CIRCUIT AND CODES</p>

## <p style='color:green'>Arduino-Ventilator Electronic Configaration</p>
### <p style = 'color:magenta'> Required  electronic components :</p>

[![IMAGE ALT TEXT HERE ](/home/uniteworld/Downloads/Screenshot(8).png)](https://www.youtube.com/watch?v=A6c_zpoSJIw)
- [x] High torqe servo(MG-996 metal geared) -  1pc
- [x] BMP280 pressure Sensor -  3pcs
- [x] buzzer - 1pcs
- [x] Potentiometer(10K)(breath,peep,press,LCD Brightness Control) - 5 pcs
- [x] Potentiometer Knob - 3pcs
- [x] Swipe Button - 1pc
- [x] Jumping Wires.
- [x] SResistor(560 Ohoms, 100 Ohom).
- [x] 16X4 LCD Display - 1pc.
- [x] Sensor shield v-5 - 1pc.
- [x] Servo Bracket -1pc.
- [x] Arduino UNO R3 - 1pc.
- [x] Actuator -1pc.
- [x] Ambu Bag - 1pc.
- [x] Breathing Circuit.
- [x] computer
- [x] Power source - 2 pcs [9v for arduino 6 volt for servo]

 * The Electronic-Circuit Diagram ![GitHub Logp](circuit_diagram.jpg)

 * The Basic Hardware configaration : ![GitHub Logp](hardware_setup.jpg)
 * <p style = 'color:green'>  To see details circuit diagram ,look arduino_code_version-1.0.ino file</p>


<<<<<<< HEAD
![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+)<p style='color:red'>The important message : I did not have  all items as my country is in Lockdown.So I am unable to test all the staff.If you are interested to make this then you need to your own experiment and conclusion .You may find out multiple numbers of bug in this project.I don't know.</p>



=======
>>>>>>> ee6eb521a00fed9d51fa2e951a33715bff94f918

## <p style = 'color:red'>1. Why did I make this?</p>
 ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) We all know world is going through a pandemic situation due to COVID-19.This Corona virus mainly attacking on lungs and making Pnumenia of the patient. So maximum time patient need a ventilaton support .We all know that our system have only limited number ventilator in every country.This virus transmitting very fast and getting infected more and more persion in each day.The original medical ventilator has very important and complex property and it's building time and price both are high.So we need a fast and easy  building machine which also be chip from this idea we need a chip ventilator.It may help if there has no other option.I will recomend not to use in normal situation it should use in extreem situation.

## <p style = 'color:red'> 2. What is actually have in this project ?</p>

 ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) The basic idea of the ambu bag compress VENTILATOR is to controlled compress and release of [Ambu Bag](https://images.app.goo.gl/5exEBuaQRQ4HmXZ7A).So we need a control run of a servo motor what vexactly will do this project.

 ![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) This is not the all !  It has two mode(PC-CMV or pressure Control Mode) and (CSV-PS or Patient Controlled Mode).Which could be control by a swipe switch.Here I take expiratory time as two times of inspiratory time.
1.  * CSV-PS : We can select this mode by placing mode switch at "0".Now we need to slect number of breath per minute by breathing Pot.Now select the minimum pressure selecting by peep pot and select the maximum pressure by pressure pot.Now motor give equal number of forward and backward rotation  which is equal to breathing number per minute.

  * Another BME-280 sensor record pressure,temperature and humidity  and showing on Desktop app
  * <p style ='color:red'> The two BMP-280 sensor measuring air flow rate and supplied tidal volume by spirometry principle and showing intime data as well as graph on desktop application.</p>

2.  * PC-CMV : We can select this mode by placing mode switch on "1".In this mode we can't select breathing number manually.Actual Idea of this mode is The motor run forward when patient need a inspiration and run backward when patient need to expiration.

  * Another BME-280 sensor record pressure,temperature and humidity  and showing on Desktop app.
  * <p style ='color:red'> The two BME-280 sensor measuring air flow rate and supplied tidal volume by spirometry principle and showing intime data as ell as graph on desktop application.</p>

3. I attached a Buzzer .It will make sound if there arise any kind alarming situation like,low or very  high pressure,low or very temperatior,low or very high humidity,motor stopage etc.
* I get this serial output from arduino Serial which is using as  serial input of processing code :
![GitHub Logp](arduino_serial.gif)


* <p style='color:red'>The first value is modeState</p>
* <p style='color:red'>Second value is alarm State </p>
* <p style='color:red'>Third Value is breath no</p>
* <p style='color:red'>fourth value is Inspiratory time</p>
* <p style='color:red'>fifth value is temperature</p>
* <p style='color:red'>sixth value is pressure</p>
* <p style='color:red'>seventh value is humidity</p>
* <p style='color:red'>Eigth value is Peep</p>
* <p style='color:red'>Nineth value is maximum pressure value</p>
* <p style='color:red'>Tenth value is flow rate volume </p>
* <p style='color:red'>eleventh value is tidal volume</p>

4. Let's talk about desktop application.It is showing real time pressure,air flow rate and tidal volume data logging with graph.It is also showing some other imporatant serial data which is obtained from Arduino like breathing no,inspiration time,expiration time,temperature,humidity,runnig time etc.
 ![GitHub Logo](desktop_app.gif)

 * <p style='color:red'>
Desktop output ,Here I did not attached any sensor altough output showing some graph as I included some random value inside of Processing code to showing.</p>


 ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) Reference : I got inspiration to work in this kind project from here-

 * [This MIT Paper](https://web.mit.edu/2.75/projects/DMD_2010_Al_Husseini.pdf)
 * [This Instructable](https://www.instructables.com/id/COVID-19-Rapid-Manufacture-Ventilator-BVM-Ambubag-/)
 * [The ventilator graph analysis](https://youtu.be/KSd1c8koNaA)


 * ### <p style='color:green'>If you would like to use this project :</p>

 * #### Linux :
 You need arduino IDE to upload the arduino code into arduino.
   If you would like to Download this "arduino-IDE" see [this](https://www.arduino.cc/en/main/software) link.

Before install this application you need to install [Java](https://www.java.com/en/) in your computer.

Download this project file which containing the source file To run desktop application If your machine is 64 bit open Terminal and type ,except '$' :

```bash
$cd $HOME cd $HOME/Downloads/open_source_chip_arduno_ventilator_making_idea/processing_desktop_application_1_0/
```


and then run the application by following command

```bash
$./processing_desktop_application_1_0
```
If your machine is 32 bit.

 Before instaall this application you need to install [Java](https://www.java.com/en/) in your computer.
        open Terminal and type
```bash
$cd /$HOME/open_source_chip_arduno_ventilator_making_idea/processing_desktop_application_1_0/application.linux32/
```

and then

```bash
$./processing_desktop_application_1_0
```


 * #### Windows  :
 You need arduino IDE to upload the arduino code into arduino.
   If you would like to Download this "arduino-IDE" see [this](https://www.arduino.cc/en/main/software) link.

   Before instaall this application you need to install [Java](https://www.java.com/en/) in your computer.

   Download this project file which containing the source file.
   Now if your machine is 64 bit then go to downloaded folder and enter  inside of application.windows64 and double click on processing_desktop_application_1_0.exe

   Now if your machine is 32 bit then go to downloaded folder and enter  inside of application.windows 32 and double click on processing_desktop_application_1_0.exe

 * #### Mac :
 Till now I have no Idea.I will try in future to make useable in Mac.

* #### <p style='color:green'>If you would like to develop this project </p>

* Before instaall this application you need to install [Java](https://www.java.com/en/) in your computer :

* ####  Linux :

1. First, update the apt package index with:
```bash
$~ sudo apt update
```
Once the package index is updated install the default Java OpenJDK package with:
```bash
$~ sudo apt install default-jdk
```
Verify the installation, by running the following command which will print the Java version:
```bash
$~ java -version
```
Java 8 is still the most widely-used version of Java. If your application requires Java 8, you can install it by typing the following commands:
```bash
sudo apt update
sudo apt install openjdk-8-jdk
```
Installing Oracle Java

Before installing Oracle Java, make sure you read the Oracle JDK License. The license permits only non-commercial use of the software, such as personal use and development use.

Oracle Java 11 can be installed from the Linux Uprising PPA.

The following steps describe how to install Oracle Java 11 on Ubuntu 18.04:

    Install the dependencies necessary to add a new repository:
```bash
    sudo apt install software-properties-common
```
    Enable the Linux Uprising PPA by running the following commands:
```bash
    sudo add-apt-repository ppa:linuxuprising/java
```
    Once the repository is added, update the packages list and install the oracle-java11-installer package by typing:
```bash
    sudo apt update
    sudo apt install oracle-java11-installer
```
    You will be prompted to accept the Oracle license.

    Verify the installation by running the following command which will print the R version:
```bash
    java -version
```

* ####  Windows :

To install Java please see [this](https://java.com/en/download/help/download_options.xml) link.


  * I have used "arduino-1.8.12-linux64" IDE to write Arduino Code.
    If you would like to Download this "arduino-IDE" see [this](https://www.arduino.cc/en/main/software) link.

  * I have used "processing-3.5.4-linux64" IDE to write desktop application.
    If you would like to Download "processing-IDE" see [this](https://processing.org/download/) link.
