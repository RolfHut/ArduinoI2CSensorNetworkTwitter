/* 
Part of the "streaming water workshop given at Delft University of Technology

This program is used to test the communication between the student slave arduinos
and the master arduino. IF this is succesful, the final program to run on the 
master arduino should be I2CSensorMasterTwitter, which tweets the measurements.

This program cycles through channels of the I2C bus. When it finds 
a life slave connected to an address it sends a code-word to the slave
The slave repsons depends on the code-word.  The code words are:
name - the slave returns the name of the students working with that slave arduino
var - the slave returns the type of measurement, ie. "voltage" or "rainfall"
data - the slave returns the actual measurement. this is send as a string!
unit - the slave returns the unit of the measurement, ie "volts" or "mm/h"

These values are than printen on the Serial com line, for easy debugging.

The master should be connected to the slaves using an I2C bus, ie. pin A4 off 
master and all slaves should be connected to each other, as well as pinA5.

For correct communication it is paramount that the master and all slaves share 
the same ground. This is done by disconnecting the slaves from an external 
power source and than connecting all gnd pins in a bus as well as all 
5V pins. This means that the master has to supply the power for all the slaves
which will work up to about 20 slaves (depending on individual power consumption)


*/

#include <Wire.h>

#define MAXCHANNEL 40

char tweet[140];

void setup()
{
  delay(10000);
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  Serial.println("starting");
}

void loop()
{
  for(int address=2;address<MAXCHANNEL;address++){
    Serial.println(address);
    Wire.beginTransmission(address); 
    Wire.write("");
    byte check = Wire.endTransmission();
    //Serial.println(check);
    if(check==0){
      
      String name = pullSlave(address,"name");
      String var = pullSlave(address,"var");
      String data = pullSlave(address,"data");
      String unit = pullSlave(address,"unit");
      
      ("testmeasurement " + name + " " + var + ": " + data + " " + unit).toCharArray(tweet,140);
      Serial.print(address);
      Serial.print(" ");
      Serial.println(tweet);

      delay(1000);
    }
  }
  delay(5000);
}

String pullSlave(int address, char command[]){
  char msg[30];
  int n=0;
  
  //send command to slave  
  Wire.beginTransmission(address); 
  Wire.write(command);
  Wire.endTransmission();
  
  //give slave time to construct msg
  delay(100);
  
  //demand msg from slave
  Wire.requestFrom(address, 28);    // request 28 bytes from slave device #2
  while(Wire.available()){
    msg[n++]=Wire.read();
  }
  String msgStr=String(msg);
  msgStr.trim();
  return msgStr;
}


