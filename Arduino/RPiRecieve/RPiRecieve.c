#include "RPiRecieve.h"
#include <Arduino.h>

int distance = -1, azimuth = -1, altitude = -1;

void rpiInit()
{
  Serial.begin(9600);
}

bool rpiRead()
{
  if(Serial.available() < 4) return false;

  while ((char)Serial.read() != ';');
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
