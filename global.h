#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <string.h>
#include "passenger.h"

#define MAX_AC_SEAT 10
#define MAX_NONAC_SEAT 10
#define MAX_SEATER_SEAT 10
#define MAX_WAITING_LIST 3

extern Passenger acCouch[MAX_AC_SEAT];
extern Passenger nonacCouch[MAX_NONAC_SEAT];
extern Passenger seaterCouch[MAX_SEATER_SEAT];
extern Passenger waitingList[MAX_WAITING_LIST];

extern int acCount;
extern int nonAcCount;
extern int seaterCount;
extern int wlCount;

#endif