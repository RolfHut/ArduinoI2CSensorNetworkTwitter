# ArduinoI2CSensorNetworkTwitter
==============================

connect multiple arduino slaves to a single master. The slaves do measurements, the master collects them and sends them to twitter.

This repo contains the software code and hardware schemes needed to run a workshop in which students, after making their own sensor, connect all sensors together and send a message to twitter with their measurement values.

==============================
## The Grand workshop Finale: connecting to twitter.

In this section, I will explain how to connect different arduinos from students to one master-arduino run by a workshop leader and how to tweet the measurements values from the students.I will assume that:

* There are a number of student teams, each with their own sensor and each with their own arduino. 
* There is a master arduino, which is controlled by the workshop leader. This arduino is equipped with a wifi shield.
* The workshop leader has access to internet via wifi (ie. he has the SSID & password). The local wifi should not be shielded by a proxy, or any other fancy redirects. When the master arduino connects to the wifi, it should have direct internet access.

Per student team, we assumed that at the end of the workshop they have accomplished the following:
* students have build a sensor that can measure an environmental variable, for example temperature.
* students have connected this sensor to an arduino and are able to display sensor values on screen when the arduino is connected to a computer. The easiest way to do this, is to use an analog sensor, for example a tmp35 temperature sensor, or simply a potentiometer and use the "analog read voltage" example from the arduino examples. More complex solutions are, of course, encouraged.
* students have changed the arduino code such that their measurement value is available as a float, called "measurement". 

When the above 3 points are completed by a student team, they should be given the "I2CSensorSlaveTemplate" code and the should be given an unique address by the workshop leader. The address is a unique number per team. The maximum address allowed is 40. They should copy-paste this code under their own code and change a few lines in the new code. This is all explained in the comments of the "I2CSensorSlaveTemplate" code.

When the students have added the "I2CSensorSlaveTemplate" to their code, they should connect their arduino to the master arduino (controlled by the workshop leader). See the pdf in the hardware folder on how to connect the different arduinos. Basically: connect all SDA pins to each other and all SCL pins to each other. Remember that on the arduino UNO the SDA and the SCL pins are shared with pins A4 and A5, which can not be used by the students!

When a new team connects their sensor to the master, the workshop leader should run the "I2CSensorMasterSerial" on the master arduino and open a serial monitor on his computer to see if the connection is ok. 

The workshop leader should adept the "I2CSensorMasterTwitter" code to include information on the local wifi, and to include a token which allows him to send tweets. All this is explained in the comments of the "I2CSensorMasterTwitter" code.

When all teams have connected their sensor to the master, the workshop leader should upload the "I2CSensorMasterTwitter" on the master arduino, than disconnect the master from the computer and power it through a 5V adapter. If everything works ok, the master arduino connects to the internet, start querying the slave arduinos for measurements and will post those measurements on twitter.


==============================
## Broader Picture: Sensor Design Workshops

The code provided here is used in the final moments of a workshop in which students make their own sensor. How students make their sensor is dependent on their starting level. I have run this workshop successfully with 
<<<<<<< HEAD
<<<<<<< HEAD
- high school kids (age 16-18) for the JuniorDelft program (junior.tudelft.nl, dutch only)
=======
- high school kids (age 16-18) for the JuniorDelft program (http://junior.tudelft.nl, dutch only)
>>>>>>> dev
- undergrad students (http://ocw.tudelft.nl/courses/bachelor-civiele-techniek/meten-aan-water/course-home/, dutch only)
- international students and researchers in Africa (www.tahmo.org)
=======
* high school kids (age 16-18) for the JuniorDelft program (http://junior.tudelft.nl, dutch only)
* undergrad students (http://ocw.tudelft.nl/courses/bachelor-civiele-techniek/meten-aan-water/course-home/, dutch only)
* international students and researchers in Africa (www.tahmo.org)
>>>>>>> dev

Information on how to run the first part of the workshop, in which students make their own sensor, will be posted on different websites in the future. Links will be provided here when this information becomes available.

==============================
## Acknowledgements

<<<<<<< HEAD
All code in this project is written by Rolf Hut (@RolfHut) of Delft University of Technology, but borrows heavily on earlier code written by Adam Gleave of Cambridge University. Parts of the code develop for this workshop was first written for the TAHMO sensor design competition, see tahmo.org. Cleaning up of the code was done for the "Junior Delft Streaming Water" workshop, see junior.tudelft.nl (in dutch)
=======
All code in this project is written by Rolf Hut (http://twitter.com/@RolfHut) of Delft University of Technology, but borrows heavily on earlier code written by Adam Gleave of Cambridge University. Parts of the code developed for this workshop was first written for the TAHMO sensor design competition, see www.tahmo.org. Cleaning up of the code was done for the "Junior Delft Streaming Water" workshop, see http://junior.tudelft.nl (in dutch)
>>>>>>> dev

==============================
## Using and Citing this work.

This code is published under the GNL2 license, see the license file. When using this work, or when citing this work as an example, use the following citation:
[![DOI](https://zenodo.org/badge/doi/10.5281/zenodo.11240.png)](http://dx.doi.org/10.5281/zenodo.11240)

 
