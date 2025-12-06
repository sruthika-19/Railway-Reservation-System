#include "booking.h"
#include <ctype.h>
#include "passenger.h"
#include <stdlib.h>

void booking()
{
    Passenger p;
    int ticketCnt, cnt = 0;
    printf("Enter Number of Tickets to be Booked(1 - 3): ");
    scanf("%d", &ticketCnt);
    while (cnt < ticketCnt)
    {
        printf("\nEnter Passenger %d detail:", cnt + 1);

        printf("\nEnter Name: ");
        scanf(" %[^\n]", p.name);

        printf("\nEnter Age: ");
        scanf("%d", &p.age);

        int gen;
        printf("\nEnter Gender(MALE = 1 or FEMALE = 0): ");
        scanf("%d", &gen);
        if (gen == 1)
            p.gender = MALE;
        else
            p.gender = FEMALE;
        
        printf("\nEnter Couch Type:\n");
        printf("\n\t1. AC Couch.");
        printf("\n\t2. NON-AC Couch.");
        printf("\n\t3. SEATER Couch.");
        scanf("%d", &p.couchType);

        generatePNR(&p);

        int seatAllocated = 0;

        if (p.couchType == 1 && acCount < MAX_AC_SEAT)
        {
            p.seatNo = acCount + 1;
            acCouch[acCount++] = p;
            seatAllocated = 1;
            saveToFile(p, p.seatNo, "CONFIRMED");
        }
        else if (p.couchType == 2 && nonAcCount < MAX_NONAC_SEAT)
        {
            p.seatNo = nonAcCount + 1;
            nonAcCouch[nonAcCount++] = p;
            seatAllocated = 1;
            saveToFile(p, p.seatNo, "CONFIRMED");
        }
        else if (p.couchType == 3 && seaterCount < MAX_SEATER_SEAT)
        {
            p.seatNo = seaterCount + 1;
            seaterCouch[seaterCount++] = p;
            seatAllocated = 1;
            saveToFile(p, p.seatNo, "CONFIRMED");
        }

        if (!seatAllocated)
        {
            if (wlCount < MAX_WAITING_LIST)
            {
                addToWaitingList(p.couchType, p);
                saveToFile(p, -1, "WAITING");
                printf("\nAdded to Waiting List.");
                printf("\nWaiting List Number : %d\n", wlCount + 1);
            }

            else
            {
                int available = 0;
                printf("No Seats Available...\n");
                if (acCount < MAX_AC_SEAT)
                {
                    printf("Seats Available in AC Couch\n");
                    available = 1;
                }

                if (nonAcCount < MAX_NONAC_SEAT)
                {
                    printf("Seats Available in NON-AC Couch\n");
                    available = 1;
                }
                    
                if (seaterCount < MAX_SEATER_SEAT)
                {
                    printf("Seats Available in SEATER Couch\n");
                    available = 1;
                }

                if (available == 1)
                    printf("Please Try Booking in Other Couches\n");
                else
                    printf("Sorry... All Seats are Booked\n");

            }
        }
        cnt++;
    }
}

void generatePNR(Passenger * p)
{
    char initials[3] = {"\0"};
    char ageStr[5];
    char couchStr[2];
    char seatStr[5];

    initials[0] = toupper(p->name[0]);
    initials[1] = toupper(p->name[1]);

    itoa(p->age, ageStr, 10);        
    itoa(p->couchType, couchStr, 10); 
    itoa(p->seatNo, seatStr, 10);

    strcpy(p->pnr, initials);
    strcat(p->pnr, ageStr);
    strcat(p->pnr, couchStr);
    strcat(p->pnr, "-");
    strcat(p->pnr, seatStr);  
}

void addToWaitingList(int coachType, Passenger p)
{

}

void saveToFile(Passenger p, int seatNumber, char status[])
{

}

void loadFromFile()
{

}

void updateFileAfterShift(Passenger p, int newSeat)
{

}