#ifndef BOOKING_H
#define BOOKING_H

#include "global.h"
#include <stdio.h>

void booking();
int generatePNR();
void addToWaitingList(int coachType, Passenger p);

#endif