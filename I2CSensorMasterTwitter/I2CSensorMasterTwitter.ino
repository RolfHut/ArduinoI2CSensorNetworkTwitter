/* 
This program is used to finalize the "streaming water" workshop, given at Delft 
University of Technology. This master program tweets the name of the students,
the measurement type, value and unit of all the connected slave Arduinos

This program cycles through channels of the I2C bus. When it finds 
a life slave connected to an address it sends a code-word to the slave
The slave repsons depends on the code-word.  The code words are:
name - the slave returns the name of the students working with that slave arduino
var - the slave returns the type of measurement, ie. "voltage" or "rainfall"
data - the slave returns the actual measurement. this is send as a string!
unit - the slave returns the unit of the measurement, ie "volts" or "mm/h"

The master compiles a tweet, based on the answers of the slave, which is tweeted
using the Tweet Library for Arduino.

Connecting to twitter is done over wifi: the master arduino must be equiped 
with a wifi shield and the settings below must be adjusted to log into the correct 
network. Note that the standard twitter library is written for use with the arduino 
ethernet shield and here we use the wifi shield. Therefore, we have to use the 
twitterWifi library, which is also provided in the same repository as this code. 
Add the twitterWifi library to your libraries folder and restart the arduino soft-
ware for this to work.

the following parameters should be changed below:
line 57: ssid - this is the ssid (ie. name) of the wifi network to login to.
line 58: pass - this is the password (wpa / wpa2) or the key (WEP) to log into the wifi
  network. If no pwd is needed, comment-out line 58.

In line 66, the twitter token associated with the twitter account should be added
You can get it from http://arduino-tweet.appspot.com/

In line 97, the construction of the tweet should be changed to represent the 
wording that you want. Make sure the total tweet length can never succeed 140
character.

The master should be connected to the slaves using an I2C bus, ie. pin SDA off 
master and all slaves should be connected to each other, as well as SCL. When using 
the Arduino Uno (as most people will be doing), keep in mind that the SDA and SCL pins
are shared with the A4 and A5 analog pins. They can not be used!

For correct communication it is paramount that the master and all slaves share 
the same ground. This is done by disconnecting the slaves from an external 
power source and than connecting all gnd pins in a bus as well as all 
5V pins. This means that the master has to supply the power for all the slaves
which will work up to about 20 slaves (depending on individual power consumption)

*/

#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>
#include <TwitterWifi.h>

#define MAXCHANNEL 40

char ssid[] = "YOUR WIFI SSID HERE";   //  your network SSID (name) 
char pass[] = "YOUR WIFI PASSWORD HERE";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS; // status of the wifi connection

char tweet[140];

// Your Token to Tweet (get it from http://arduino-tweet.appspot.com/)
Twitter twitter("YOUR TOKEN HERE");



void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  
  WiFi.begin(ssid, pass);
  //WiFi.begin(ssid);
  delay(5000);  
  // you're connected now, so print out the status:
  
  printWifiStatus();  

}

void loop()
{
  for(int address=0;address<MAXCHANNEL;address++){
    Wire.beginTransmission(address); 
    Wire.write("");
    byte check = Wire.endTransmission();
    if(check==0){
      
      String name = pullSlave(address,"name");
      String var = pullSlave(address,"var");
      String data = pullSlave(address,"data");
      String unit = pullSlave(address,"unit");
      
      ("a sensor made by " + name + " measures " + var + ": " + data + " " + unit + " and tweets using software by @RolfHut").toCharArray(tweet,140);
      
      Serial.println("connecting to twitter...");
      if (twitter.post(tweet)) {
        // Specify &Serial to output received response to Serial.
        // If no output is required, you can just omit the argument, e.g.
        // int status = twitter.wait();
        int status = twitter.wait(&Serial);
        if (status == 200) {
          Serial.println("OK.");
        } else {
          Serial.print("failed : code ");
          Serial.println(status);
        }
      } else {
        Serial.println("connection failed.");
      }

     
    }delay(0);
    
  }
   delay(30000);
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
  Wire.requestFrom(address, 28);    // request 6 bytes from slave device #2
  while(Wire.available()){
    msg[n++]=Wire.read();
  }
  String msgStr=String(msg);
  msgStr.trim();
  return msgStr;
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

