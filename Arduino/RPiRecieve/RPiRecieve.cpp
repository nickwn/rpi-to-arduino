#include "RPiRecieve.h"
#include "Arduino.h"

double distance = -1, azimuth = -1, altitude = -1;

void rpiInit()
{
  Serial.begin(9600);
}

bool rpiRead()
{
  while ((char)Serial.read() != ';')
  {
	  if(Serial.available() <= 0)
		  return false;
  }
  if(Serial.available() <3) return false;

  distance = Serial.read();
  azimuth = Serial.read();
  altitude = Serial.read();

#ifdef DEBUG
  Serial.println("distance: " + distance ", azimuth: " + azimuth ", altitude: " + altitude);
#endif

  return true;
}

double rpiGetDistance()
{
  return distance;
}

double rpiGetAzimuth()
{
  return azimuth;
}

double rpiGetAltitude()
{
  return altitude;
}
