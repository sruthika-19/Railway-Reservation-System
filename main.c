#include "availability.h"
#include "booking.h"
#include "global.h"
#include "passenger.h"
#include "system-setup.h"
#include <stdio.h>

int acCount = 0;
int nonAcCount = 0;
int seaterCount = 0;

int acWLCount = 0;
int nonAcWLCount = 0;
int seaterWLCount = 0;

Passenger acCoach[MAX_AC_SEAT];
Passenger nonAcCoach[MAX_NONAC_SEAT];
Passenger seaterCoach[MAX_SEATER_SEAT];

Passenger acWaitingList[MAX_WAITING_LIST];
Passenger nonAcWaitingList[MAX_WAITING_LIST];
Passenger seaterWaitingList[MAX_WAITING_LIST];

int main()
{
    initializeSystem();
    int choice;
    do 
    {
        displayMenu();
        printf("Enter Choice (1 - 5): ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            booking();
            break;

        case 2:
            checkAvailability();
            break;

        case 3:
            cancellation();
            break;

        case 4:
            prepareChart();
            break;
        
        case 5:
            printf("Exiting System...\n");
            break;
        
        default:
            printf("Invalid Entry....Try Again!\n");
            break;
        }
    } while (choice != 5);

    return 0;
}