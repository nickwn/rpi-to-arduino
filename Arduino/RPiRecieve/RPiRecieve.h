#ifndef RPI_RECIEVE_H
#define RPI_RECIEVE_H


void rpiInit();

bool rpiRead();

double rpiGetDistance();
double rpiGetAzimuth();
double rpiGetAltitude();

#endif // RPI_RECIEVE_H
