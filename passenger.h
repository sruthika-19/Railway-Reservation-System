#ifndef PASSENGER_H
#define PASSENGER_H

typedef enum { MALE, FEMALE } Gender;

typedef struct 
{
    char name[20];
    int age;
    Gender gender;
    int couchType;
    int seatNo;
    char pnr[20];

} Passenger;

#endif