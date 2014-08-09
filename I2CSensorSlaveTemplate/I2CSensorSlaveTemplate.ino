/*
 I2CSensorSlaveTemplate

This piece of code is copy pasted below the individual codes of the students
Arduinos. This allows the student arduino to communicate as a slave with the 
master arduino, which has a wifi shield on it. In this way all the measurements
from all the student arduinos are tweeted from the master arduino.

After copy pasting the code below their own code, the students have to make a 
simple addition to their electric scheme, and the have to add some meta-data below.

These steps below have to be done in the correct order!

- make sure that the student code has a global variable called "measurement" that 
is of type "float". This variable should contain the actual measurement value.

- copy-paste this code underneath the students own code.

- change the variables ADDRESS, NAME, VARIABLE and UNIT below. 
- The address is given to the students by the teachter and should be unique and 
  lower than 40
- The name contains the name of the students like "John and Lea". Students can
  use their twitter name in stead of their real name, for example "@john and @lea"
- The variable is the type of measurement, for example "rain" or "temperature"
- The unit is the unit of the measurement, for example "mm per hour" or "degrees C"

- finally change the "void setup{" line in the student code to "void user_setup{"
  and change the "void loop{" line in the student code to "void user_loop{"

- compile and upload the student-code to the arduino. 

- disconnect the arduino from the computer

- connect the Gnd pin of the slave to the bus that is also connected to the Gnd pin
  of the master
- connect pin SDA of the slave to the bus that is also connected to SDA of the master
- connect pin SCL of the slave to the bus that is also connected to SCL of the master
- connect the 5V pin of the slave to the bus that is also connected to the 5V pin
  of the master

 This example code is in the public domain. The code is written by Rolf Hut (@RolfHut)
 but borrows heavily on earlier code written by Adam Gleave of Cambridge University.
 */


/***************************************** GENERAL CODE ****************************/


#define ADDRESS XX //change the XX into the adres number assigend to this arduino.
#define NAME "STUDENT NAME" 
#define VARIABLE "VARIABLE THAT IS MEASURED" //ie. temperature, or rainfall
#define UNIT "UNIT THAT IS MEASURED"  //ie. degrees C, or mm per hour



#define SPACE "                                "
#include <Wire.h>
#include <stdbool.h>


char msgVal0[8];
char buf[8];
int posRead = 0;
int posWrite = 0;
char * msgout;
char tweet[32];


/* This function SHOULD be modified */
void requestEvent()
{
  if (strcmp(buf, "?") == 0)
  {
    msgout = "HELLO";
  } else if (strcmp(buf, "name") == 0) {
    msgout = NAME;
  } else if (strcmp(buf, "var") == 0) {
    msgout = VARIABLE;
  } else if (strcmp(buf, "unit") == 0) {
    msgout = UNIT;
  } else if (strcmp(buf, "data") == 0) {
    dtostrf(measurement,2,5,msgVal0); //this line converts the students variable measurement to a string
    msgout = msgVal0;
  } else {
    msgout = "ERR";
  }

  //Serial.print("Received ");
  //Serial.println(buf);
  posRead = 0;
  buf[0] = 0;
  (String(msgout)+String(SPACE)).toCharArray(tweet,32);
  Wire.write(tweet);
  //Serial.print("Send: ");
  //Serial.println(tweet);
}

void setup()
{
  //Serial.begin(9600);
  Wire.begin(ADDRESS);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);

  //Serial.println("Starting");
  user_setup();
}

void loop()
{
  user_loop();
}

void receiveEvent(int howMany)
{
    while (howMany > 0)
  {
    if (posRead < sizeof(buf)-1) 
    {
      buf[posRead++] = Wire.read();
      buf[posRead] = 0; // maintain it as a string by NIL-terminating
    }
    else {
      //Serial.println("WARNING: Read too many bytes before receiving a request.");
    }
    howMany--;
  }
  //Serial.println(buf);
}


