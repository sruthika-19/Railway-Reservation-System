#ifndef AVAILABILITY_H
#define AVAILABILITY_H

#include "global.h"
#include <stdio.h>

void checkAvailability();
void cancellation();
void shiftWaitingList(int coachType);
void updateFileAfterCancellation(Passenger p); 

#endif