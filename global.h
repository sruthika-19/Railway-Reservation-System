#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <string.h>
#include "passenger.h"

#define MAX_AC_SEAT 60
#define MAX_NONAC_SEAT 60
#define MAX_SEATER_SEAT 60
#define MAX_WAITING_LIST 10

extern Passenger acCoach[MAX_AC_SEAT];
extern Passenger nonAcCoach[MAX_NONAC_SEAT];
extern Passenger seaterCoach[MAX_SEATER_SEAT];
extern Passenger acWaitingList[MAX_WAITING_LIST];
extern Passenger nonAcWaitingList[MAX_WAITING_LIST];
extern Passenger seaterWaitingList[MAX_WAITING_LIST];

extern int acCount;
extern int nonAcCount;
extern int seaterCount;
extern int acWLCount;
extern int nonAcWLCount;
extern int seaterWLCount;

#endif
