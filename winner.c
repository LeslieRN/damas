#include <stdlib.h>
#include <stdio.h>
#include "funciones.h"
#include <string.h>
int askForTable()
{
    char option;
    int total = 0, counter = 0;
    do
    {
        fflush(stdin);
        printf("Do you want to give up? (y)es or (n)o\n");
        option = getchar();
        if (option == 'y')
        {
            total += 1;
        }
        counter++;
    } while (counter <= 1);
    if (total == 2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int determineWinner(player **playerInfo)
{
    /*printf("Pwn value %s\n", (*(playerInfo))->color);
    printf("This is the pawn q %d\n", (*(playerInfo))->pawnQuantity);
    printf("This is the pawn q %d\n", (*(playerInfo))->pawnQuantity++);*/
    printf("This is the pawn q %d\n", (*(playerInfo))->pawnQuantity);
    //printf("This is the pawn 2 %d\n", (*(playerInfo + 1))->pawnQuantity);
    if ((*(playerInfo))->pawnQuantity == 0)
    {
        (*(playerInfo + 1))->win++;
        return 0;
    }
    else if ((*(playerInfo + 1))->pawnQuantity == 0)
    {
        (*(playerInfo))->win++;
        return 0;
    }
    return 1;
}