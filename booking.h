#ifndef BOOKING_H
#define BOOKING_H

#include "global.h"
#include <stdio.h>

void booking();
int generatePNR();
void addToWaitingList(int coachType, Passenger p);
void saveToFile(Passenger p, int seatNumber, char status[]);
void loadFromFile();                       
void updateFileAfterShift(Passenger p, int newSeat); 

#endif