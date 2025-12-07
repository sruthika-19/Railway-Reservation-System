#include "booking.h"
#include <ctype.h>
#include "passenger.h"
#include <stdlib.h>
#include <string.h>

int serialNo = 100;

void booking()
{
    int ticketCnt, cnt = 0, gen;

    do 
    {
        printf("Enter Number of Tickets to be Booked(1 - 3): ");
        
        if (scanf("%d", &ticketCnt) != 1) 
        {
            printf("Invalid input. Try again.\n");
            while(getchar() != '\n');

            ticketCnt = 0;
            continue;
        }

    } while (ticketCnt < 1 || ticketCnt > 3);
    
    while (cnt < ticketCnt)
    {
        Passenger p = {0};
        do 
        {
            printf("Enter Name: ");
            scanf(" %49[^\n]", p.name);

            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);

        } while (strlen(p.name) == 0);

        do {
            printf("Enter Age: ");
            if (scanf("%d", &p.age) != 1) 
            {
                printf("Invalid input. Try again.\n");

                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);

                p.age = 0;
                continue;
            }

            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
            
        } while (p.age <= 0 || p.age > 120);

        do 
        {
            printf("Enter Gender (MALE = 1, FEMALE = 0): ");
            if (scanf("%d", &gen) != 1)
            {
                printf("Invalid input. Try again.\n");

                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);

                gen = -1;
                continue;
            }

            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);

        } while (gen != 0 && gen != 1);

        p.gender = (gen == 1) ? MALE : FEMALE;

        do 
        {
            printf("Enter Coach Type:\n");
            printf("\t1. AC Coach\n");
            printf("\t2. NON-AC Coach\n");
            printf("\t3. SEATER Coach\n");

            if (scanf("%d", &p.coachType) != 1)
            {
                printf("Invalid input. Try again.\n");

                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF);

                p.coachType = 0;
                continue;
            }

            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);

        } while (p.coachType < 1 || p.coachType > 3);

        int seatAllocated = 0;

        if (p.coachType == 1 && acCount < MAX_AC_SEAT)
        {
            p.seatNo = acCount + 1;
            generatePNR(&p);
            acCoach[acCount++] = p;
            saveToFile(p, p.seatNo, "CONFIRMED");
            seatAllocated = 1;
        }
        else if (p.coachType == 2 && nonAcCount < MAX_NONAC_SEAT)
        {
            p.seatNo = nonAcCount + 1;
            generatePNR(&p);
            nonAcCoach[nonAcCount++] = p;
            saveToFile(p, p.seatNo, "CONFIRMED");
            seatAllocated = 1;
        }
        else if (p.coachType == 3 && seaterCount < MAX_SEATER_SEAT)
        {
            p.seatNo = seaterCount + 1;
            generatePNR(&p);
            seaterCoach[seaterCount++] = p;
            saveToFile(p, p.seatNo, "CONFIRMED");
            seatAllocated = 1;
        }

        if (!seatAllocated)
        {           
            if ((p.coachType == 1 && acWLCount < MAX_WAITING_LIST) ||
               (p.coachType == 2 && nonAcWLCount < MAX_WAITING_LIST) ||
               (p.coachType == 3 && seaterWLCount < MAX_WAITING_LIST))
            {
                p.seatNo = -1;
                generatePNR(&p);

                addToWaitingList(p.coachType, &p);
                saveToFile(p, -1, "WAITING");

                printf("Added to Waiting List.\n");
            }

            else
            {
                int available = 0;
                printf("No Seats Available in Selected coach...\n");
                
                if (acCount < MAX_AC_SEAT)
                {
                    printf("Seats Available in AC Coach\n");
                    available = 1;
                }

                if (nonAcCount < MAX_NONAC_SEAT)
                {
                    printf("Seats Available in NON-AC Coach\n");
                    available = 1;
                }
                    
                if (seaterCount < MAX_SEATER_SEAT)
                {
                    printf("Seats Available in Seater Coach\n");
                    available = 1;
                }

                if (available)
                {
                    printf("Please Try Booking in Other Coaches\n");
                    cnt--;
                    continue;
                }
                    else
                    printf("Sorry... All Seats are Booked\n");

            }
        }
        cnt++;
    }
    saveSystemData();
}

void generatePNR(Passenger * p)
{
    char first = toupper(p->name[0]);
    char second = (strlen(p->name) > 1) ? toupper(p->name[1]) : 'X';

   snprintf(p->pnr, sizeof(p->pnr), "%c%c%d%d-%d",
        first,
        second,
        p->age,
        p->coachType,
        serialNo++); 
}

void addToWaitingList(int coachType, Passenger * p)
{
    if (coachType == 1 && acWLCount < MAX_WAITING_LIST)
    {
        acWaitingList[acWLCount++] = *p;
        printf("\nWaiting List Number: %d", acWLCount);
    }
    else if (coachType == 2 && nonAcWLCount < MAX_WAITING_LIST)
    {
        nonAcWaitingList[nonAcWLCount++] = *p;
        printf("\nWaiting List Number: %d", nonAcWLCount);
    }
    else if (coachType == 3 && seaterWLCount < MAX_WAITING_LIST)
    {
        seaterWaitingList[seaterWLCount++] = *p;
        printf("\nWaiting List Number: %d", seaterWLCount);
    }
}

void saveToFile(Passenger p, int seatNumber, char status[])
{
    FILE *fp = fopen("reservation.txt", "a+");
    
    if (fp == NULL)
    {
        fp = fopen("reservation.txt", "w");
        if (fp == NULL)
        {
            printf("\nError Opening File!");
            return;
        }
    }

    fseek(fp, 0, SEEK_END);
    if (ftell(fp)== 0)
    {
        fprintf(fp, "%-10s\t%-50s\t%-4s\t%-8s\t%-5s\t%-5s\t%-10s\n",
        "PNR", "NAME", "AGE", "GENDER", "COACH", "SEAT", "STATUS");
    }

   fprintf(fp, "%-10s\t%-50s\t%-4d\t%-8s\t%-5d\t%-5d\t%-10s\n",
        p.pnr,
        p.name,
        p.age,
        (p.gender == MALE ? "MALE" : "FEMALE"),
        p.coachType,
        seatNumber,
        status);

    fclose(fp);
}

void loadFromFile()
{
    FILE *fp = fopen("reservation.txt", "r");
    if (!fp) 
        return;

    char line[256];
    int lineNo = 0;

    while (fgets(line, sizeof(line), fp))
    {
        lineNo++;
        if (lineNo == 1) 
            continue; 

        Passenger p;
        char genderStr[10], status[20];
        int seat, coach;

        if (sscanf(line, "%s\t%49[^\t]\t%d\t%s\t%d\t%d\t%s",
                p.pnr, p.name, &p.age, genderStr, &coach, &seat, status) == 7)
        {
            p.gender = strcmp(genderStr, "MALE") == 0 ? MALE : FEMALE;
            p.coachType = coach;
            p.seatNo = seat;

            if (strcmp(status, "CONFIRMED") == 0)
            {
                if (p.coachType == 1 && acCount < MAX_AC_SEAT) 
                    acCoach[acCount++] = p;
                else if (p.coachType == 2 && nonAcCount < MAX_NONAC_SEAT) 
                    nonAcCoach[nonAcCount++] = p;
                else if (p.coachType == 3 && seaterCount < MAX_SEATER_SEAT) 
                    seaterCoach[seaterCount++] = p;
            }
            else if (strcmp(status, "WAITING") == 0)
            {
                addToWaitingList(p.coachType, &p);
            }
        }
    }

    fclose(fp);
}

void updateFileAfterShift(Passenger p, int newSeat)
{
    FILE *fp = fopen("reservation.txt", "r");
    if (!fp) 
        return;

    FILE *temp = fopen("temp.txt", "w");
    if (!temp)
    {
        fclose(fp);
        return;
    }

    char line[256];
    int lineNo = 0;

    while (fgets(line, sizeof(line), fp))
    {
        lineNo++;
        if (lineNo == 1)
        {
            fputs(line, temp);
            continue;
        }

        char pnr[20], name[50], genderStr[10], status[20];
        int age, seat, coach;

        if (sscanf(line, "%s\t%49[^\t]\t%d\t%s\t%d\t%d\t%s",
           pnr, name, &age, genderStr, &coach, &seat, status) == 7)
        {
            if (strcmp(pnr, p.pnr) == 0)
            {
                seat = newSeat;
                strcpy(status, "CONFIRMED");
            }

            fprintf(temp, "%-10s\t%-50s\t%-4d\t%-8s\t%-5d\t%-5d\t%-10s\n",
            pnr, name, age, genderStr, coach, seat, status);

        }
    }

    fclose(fp);
    fclose(temp);
    remove("reservation.txt");
    rename("temp.txt", "reservation.txt");
}
