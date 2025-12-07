#ifndef PASSENGER_H
#define PASSENGER_H

typedef enum { MALE, FEMALE } Gender;

typedef struct 
{
    char name[50];
    int age;
    Gender gender;
    int coachType;
    int seatNo;
    char pnr[20];
} Passenger;

#endif