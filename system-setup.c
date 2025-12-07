#include "global.h"
#include "booking.h"
#include "availability.h"
#include "passenger.h"
#include "system-setup.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void displayMenu()
{
    printf("\n--- RAILWAY RESERVATION MENU ---\n");
    printf("\t1. Booking\n");
    printf("\t2. Check Availability\n");
    printf("\t3. Cancellation\n");
    printf("\t4. Prepare Chart\n");
    printf("\t5. Exit\n");

}

v
void prepareChart()
{
    int i;
    char *genderText;

    printf("\nTotal AC Tickets Booked: %d\n", acCount);
    printf("Total Non-AC Tickets Booked: %d\n", nonAcCount);
    printf("Total Seater Tickets Booked: %d\n", seaterCount);
    printf("Total AC Waiting List Tickets: %d\n", acWLCount);
    printf("Total Non-AC Waiting List Tickets: %d\n", nonAcWLCount);
    printf("Total Seater Waiting List Tickets: %d\n", seaterWLCount);

    printf("\nAC COACH RESERVATIONS\n");
    for (i = 0; i < acCount; i++)
    {
        genderText = (acCoach[i].gender == MALE) ? "Male" : "Female";
        printf("Name: %-30s\t, Gender: %-8s\t, Seat No: %-4d\t, Coach: AC\t, PNR: %-10s\n", acCoach[i].name, genderText, acCoach[i].seatNo, acCoach[i].pnr);
    }

    printf("\nNON-AC COACH RESERVATIONS\n");
    for (i = 0; i < nonAcCount; i++)
    {
        genderText = (nonAcCoach[i].gender == MALE) ? "Male" : "Female";
        printf("Name: %-30s\t, Gender: %-8s\t, Seat No: %-4d\t, Coach: Non-AC\t, PNR: %-10s\n", nonAcCoach[i].name, genderText, nonAcCoach[i].seatNo, nonAcCoach[i].pnr);
    }

    printf("\nSEATER COACH RESERVATION\n");
    for (i = 0; i < seaterCount; i++)
    {
        genderText = (seaterCoach[i].gender==MALE) ? "Male" : "Female";
        printf("Name: %-30s\t, Gender: %-8s\t, Seat No: %-4d\t, Coach: Seater\t, PNR: %-10s\n", seaterCoach[i].name, genderText, seaterCoach[i].seatNo, seaterCoach[i].pnr);
    }

    printf("\nAC COACH WAITING LIST\n");
    for (i = 0; i < acWLCount; i++)
    {
        genderText = (acWaitingList[i].gender==MALE) ? "Male" : "Female";
        printf("Name: %-30s\t, Gender: %-8s\t, Status: Waiting\t, PNR: %-10s\n", acWaitingList[i].name, genderText, acWaitingList[i].pnr);
    }

    printf("\nNON-AC COACH WAITING LIST\n");
    for (i = 0; i < nonAcWLCount; i++)
    {
        
        genderText = (nonAcWaitingList[i].gender==MALE) ? "Male" : "Female";
        printf("Name: %-30s\t, Gender: %-8s\t, Status: Waiting\t, PNR: %-10s\n", nonAcWaitingList[i].name, genderText, nonAcWaitingList[i].pnr);
    }

    printf("\nSEATER COACH WAITING LIST\n");
    for (i = 0; i < seaterWLCount; i++)
    {
        genderText = (seaterWaitingList[i].gender==MALE) ? "Male" : "Female";
        printf("Name: %-30s\t, Gender: %-8s\t, Status: Waiting\t, PNR: %-10s\n", seaterWaitingList[i].name, genderText, seaterWaitingList[i].pnr);
    }
    printf("\n=================================================\n");
}

void initializeSystem()
{
    loadFromFile();
    loadSystemData();
    printf("System initialized.\n");
}

void saveChartToFile()
{
    FILE *fp = fopen("reservation.txt", "w");
    if (fp == NULL) 
        return;

    fprintf(fp, "AC Waiting List:\n");
    for (int i = 0; i < acWLCount; i++)
        fprintf(fp, "%d, %s\n", i+1, acWaitingList[i].name);

    fprintf(fp, "\nNon-AC Waiting List:\n");
    for (int i = 0; i < nonAcWLCount; i++)
        fprintf(fp, "%d, %s\n", i+1, nonAcWaitingList[i].name);

    fprintf(fp, "\nSeater Waiting List:\n");
    for (int i = 0; i < seaterWLCount; i++)
        fprintf(fp, "%d, %s\n", i+1, seaterWaitingList[i].name);

    fclose(fp);
}

void loadSystemData()
{
    FILE *fp = fopen("system.dat", "rb"); 

    if (fp == NULL)
        return;

    fread(&acCount, sizeof(int), 1, fp);
    fread(&nonAcCount, sizeof(int), 1, fp);
    fread(&seaterCount, sizeof(int), 1, fp);
    fread(&acWLCount, sizeof(int), 1, fp);
    fread(&nonAcWLCount, sizeof(int), 1, fp);
    fread(&seaterWLCount, sizeof(int), 1, fp);
    fread(&serialNo, sizeof(int), 1, fp);

    fread(acCoach, sizeof(Passenger), acCount, fp);
    fread(nonAcCoach, sizeof(Passenger), nonAcCount, fp);
    fread(seaterCoach, sizeof(Passenger), seaterCount, fp);
    fread(acWaitingList, sizeof(Passenger), acWLCount, fp);
    fread(nonAcWaitingList, sizeof(Passenger), nonAcWLCount, fp);
    fread(seaterWaitingList, sizeof(Passenger), seaterWLCount, fp);

    fclose(fp);
}


void saveSystemData()
{
    FILE *fp = fopen("system.dat", "wb");
    if (fp == NULL) 
        return;

    fwrite(&acCount, sizeof(int), 1, fp);
    fwrite(&nonAcCount, sizeof(int), 1, fp);
    fwrite(&seaterCount, sizeof(int), 1, fp);
    fwrite(&acWLCount, sizeof(int), 1, fp);
    fwrite(&nonAcWLCount, sizeof(int), 1, fp);
    fwrite(&seaterWLCount, sizeof(int), 1, fp);
    fwrite(&serialNo, sizeof(int), 1, fp);

    fwrite(acCoach, sizeof(Passenger), acCount, fp);
    fwrite(nonAcCoach, sizeof(Passenger), nonAcCount, fp);
    fwrite(seaterCoach, sizeof(Passenger), seaterCount, fp);
    fwrite(acWaitingList, sizeof(Passenger), acWLCount, fp);
    fwrite(nonAcWaitingList, sizeof(Passenger), nonAcWLCount, fp);
    fwrite(seaterWaitingList, sizeof(Passenger), seaterWLCount, fp);

    fclose(fp);
}