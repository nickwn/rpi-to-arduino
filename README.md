# rpi-to-arduino
### A 2-part library that allows Option 16's CV code to communicate with an arduino

## Arduino side
### Methods:
```c
void rpiInit()
```
Call this in the ```setup()``` loop of your arduino program. It must be called before any other functions from this library are.
```c
bool rpiRead()
```
Call this in the ```loop()``` method before any other ```get``` functions from this library are called. It updates the values for distance, azimuth, and altitude.
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
