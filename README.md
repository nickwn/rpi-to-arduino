# rpi-to-arduino
### A 2-part library that allows Option 16's CV code to communicate with an arduino

## Arduino side
### Methods:
```c
void rpiInit()
```
Call this in the ```setup()``` function of your arduino program. It must be called before any other functions from this library are.
```c
bool rpiRead()
```
Call this in the ```loop()``` method before any other ```get``` functions from this library are called. It updates the values for distance, azimuth, and altitude. It returns false if there was a failure in the process, and true otherwise.
```c
double rpiGetDistance()
```
Returns the distance to the target in inches. 
```c
double rpiGetAzimuth()
```
Returns the azimuth to the target in degrees. Azimuth is the horizontal angle to the target, with 0 degrees being straight ahead. A negative angle is to the left, while a positive angle is to the right.
```c
double rpiGetAltitude()
```
Returns the altitude to the target in degrees. Altitude is the vertical angle to the target, with 0 degrees pointing straight ahead and 90 degrees pointing straight up.

Here is a sample program in Arduino that continuously updates variables containing the distance, azimuth, and altitude to the target.
```c
#include "RPiRecieve.h"

double distance;
double azimuth;
double altitude;

void setup()
{
    rpiInit(); // Initializes the library. More specifically, it sets up the serial at a 9600 baud rate.
}

void loop()
{
    rpiRead(); // reads and updates values for distance, azimuth, and altitude
    
    distance = rpiGetDistance(); // gets the distance
    azimuth = rpiGetAzimuth(); // gets the azimuth
    altitude = rpiGetAltitude(); // gets the altitude
}
```
## Raspberry Pi side
The Raspberry Pi side is much easier. 


In order to communicate with the RoboRIO, WPILib has created a NetworkTables library in java. However, CV's targeting code is in C++. In order to get around this, CV has the C++ targeting code and the Java NetworkTables code communicate through a server-socket connection. Note: the server-socket connection is different from the NetworkTable. The server-socket connection allows the C++ targeting code and Java code to communicate (albeit on the same device, the Raspberry Pi). The NetworkTables code allows the Java code and the RoboRIO to communicate.


The code in RPi side of this repository acts as a network client. Instead of having the targeting code communicate with the Java client, the targeting code can communicate with this client, which will send the information to the Arduino. All you have to do is run the targeting server, then run the client:


```./SerialCommClient --host <host> --port <port> --serial <serial num>```


```--host``` The host server for the client to connect to. This would normally be an ip address, but since the client and server are on the same device, we can use the shortcut ```localhost```.


```--port`` The port to connect to. This is normally port 3341 (get it?)


```--serial``` The serial port number the Arduino is at. To figure this out, open the Arduino IDE and find the serial port. It should look something like /dev/tty123 on linux or COM123 on windows. Then go to http://www.teuniz.net/RS-232/ and scroll to the part where a list of all serial ports is given. Find the number matching your serial port and type it in for this argument.


A sample usage would be:


```./SerialCommClient --host localhost --port 3341 --serial 16```


This would connect to ```localhost``` on port 3341 and connect to serial port ```/dev/ttyUSB0``` (16).
