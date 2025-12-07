#include "availability.h"
#include "booking.h"
#include "system-setup.h"   
#include "passenger.h"
#include "global.h"

#include <stdio.h>
#include <string.h>

void checkAvailability()
{
    printf("\n------ SEAT AVAILABILITY ------");
    printf("\n AC SEATS            : %d available", MAX_AC_SEAT - acCount);
    printf("\n NON AC SEATS        : %d available", MAX_NONAC_SEAT - nonAcCount);
    printf("\n SEATER SEATS        : %d available", MAX_SEATER_SEAT - seaterCount);
    printf("\n AC WAITING LIST     : %d available", MAX_WAITING_LIST - acWLCount);
    printf("\n NON-AC WAITING LIST : %d available", MAX_WAITING_LIST - nonAcWLCount);
    printf("\n SEATER WAITING LIST : %d available", MAX_WAITING_LIST - seaterWLCount);
}

void cancellation()
{
    char pnr[20];
    int found = 0;

    printf("\nEnter PNR to cancel: ");
    if (scanf("%19s", pnr) != 1 || strlen(pnr) == 0)
    {
        printf("Invalid input!\n");
        return;
    }

    for (int i = 0; i < acCount && !found; i++)
    {
        if (strcmp(acCoach[i].pnr, pnr) == 0)
        {
            Passenger p = acCoach[i];

            for (int j = i; j < acCount - 1; j++)
                acCoach[j] = acCoach[j + 1];

            acCount--;

            updateFileAfterCancellation(p);
            shiftWaitingList(1);
            printf("Cancelled AC seat!\n");

            found = 1;
        }
    }
    
    for (int i = 0; i < nonAcCount && !found; i++)
    {
        if (strcmp(nonAcCoach[i].pnr, pnr) == 0)
        {
            Passenger p = nonAcCoach[i];

            for (int j = i; j < nonAcCount - 1; j++)
                nonAcCoach[j] = nonAcCoach[j + 1];

            nonAcCount--;

            updateFileAfterCancellation(p);
            shiftWaitingList(2);
            printf("Cancelled Non-AC seat!\n");

            found = 1;
        }
    }
    
    for (int i = 0; i < seaterCount && !found; i++)
    {
        if (strcmp(seaterCoach[i].pnr, pnr) == 0)
        {
            Passenger p = seaterCoach[i];

            for (int j = i; j < seaterCount - 1; j++)
                seaterCoach[j] = seaterCoach[j + 1];

            seaterCount--;

            updateFileAfterCancellation(p);
            shiftWaitingList(3);
            printf("Cancelled Seater seat!\n");

            found = 1;
        }
    }

    if (!found)
        printf("PNR not found!\n");
}


void shiftWaitingList(int coachType)
{
    Passenger p;

    if (coachType == 1)
    {
        if (acWLCount == 0 || acCount >= MAX_AC_SEAT) return;

        p = acWaitingList[0];

        for (int i = 0; i < acWLCount - 1; i++)
            acWaitingList[i] = acWaitingList[i + 1];

        acWLCount--;
        p.seatNo = acCount + 1;
        acCoach[acCount++] = p;

        updateFileAfterShift(p, p.seatNo);
    }
    else if (coachType == 2)
    {
        if (nonAcWLCount == 0 || nonAcCount >= MAX_NONAC_SEAT) return;

        p = nonAcWaitingList[0];

        for (int i = 0; i < nonAcWLCount - 1; i++)
            nonAcWaitingList[i] = nonAcWaitingList[i + 1];

        nonAcWLCount--;
        p.seatNo = nonAcCount + 1;
        nonAcCoach[nonAcCount++] = p;

        updateFileAfterShift(p, p.seatNo);
    }
    else if (coachType == 3)
    {
        if (seaterWLCount == 0 || seaterCount >= MAX_SEATER_SEAT) return;

        p = seaterWaitingList[0];

        for (int i = 0; i < seaterWLCount - 1; i++)
            seaterWaitingList[i] = seaterWaitingList[i + 1];

        seaterWLCount--;
        p.seatNo = seaterCount + 1;
        seaterCoach[seaterCount++] = p;

        updateFileAfterShift(p, p.seatNo);
    }
    else
    {
        return;
    }

    printf("\nWaiting-list passenger %s Promoted to confirmed seat.\n", p.name);
    saveSystemData();
}

void updateFileAfterCancellation(Passenger p)
{
    FILE *fp = fopen("reservation.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    char line[256];
    int lineNo = 0;

    while(fgets(line, sizeof(line), fp))
    {
        if(lineNo++ == 0) 
        { 
            fputs(line, temp); 
            continue;
        } 

        char pnr[20], name[50], gender[10], status[20];
        int age, coach, seat;

        if(sscanf(line,"%s\t%49[^\t]\t%d\t%s\t%d\t%d\t%s", pnr, name, &age, gender, &coach, &seat, status)==7)
        {
            if(strcmp(pnr, p.pnr)==0)
                strcpy(status, "CANCELLED");

            fprintf(temp, "%-10s\t%-50s\t%-4d\t%-8s\t%-5d\t%-5d\t%-10s\n", pnr, name, age, gender, coach, seat, status);
        }
    }
    fclose(fp); fclose(temp);
    remove("reservation.txt");
    rename("temp.txt","reservation.txt");
}
