#include <stdlib.h>
#include <stdio.h>
#include "funciones.h"
#include <string.h>

/**
 * Name: askForTable
 * Funtion: registrar si los jugadores se quieren rendir
 * return: (int) retorna 1 si ambos estan de acuerdo y, 0 si no
*/
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

/**
 * Name: determineWinner
 * Funtion: verificar la cantidad de fichas que tiene cada jugador, y encontrar el ganador
 *          Esta funcion revisa si la cantidad de fichas es 0
 * return: (int) retorna 1 si no hay cantidad de fichas 0 y, 0 si existe un jugador con fichas 0
*/
int determineWinner(player **playerInfo)
{
    //printf("This is pawn q %d\n", (*(playerInfo))->pawnQuantity);
    //printf("This is pawn q 2 %d\n", (*(playerInfo) + 1)->pawnQuantity);
    if ((*(playerInfo))->pawnQuantity == 0)
    {
        (*(playerInfo) + 1)->win++;
        return 0;
    }
    else if ((*(playerInfo) + 1)->pawnQuantity == 0)
    {
        (*(playerInfo))->win++;
        return 0;
    }
    return 1;
}