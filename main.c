#include "availability.h"
#include "booking.h"
#include "global.h"
#include "passenger.h"
#include "system-setup.h"
#include <stdio.h>

int main()
{
    initializeSystem();
    int choice;
    do 
    {
        displayMenu();
        printf("Enter Choice (1 - 5)\n");
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
            printf("Invalid Entry...! Try Again!\n");
            break;
        }
    } while (choice != 5);

    return 0;
}