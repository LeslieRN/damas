#include <stdlib.h>
#include <stdio.h>
#include "funciones.h"
#include <string.h>
#include <math.h>

/**
 * Name: changeNumbertoLetter
 * Funtion: cambia el numero de columna a letras (a,b,c,d,e,f,g,h)
 * return: (char) retorna el numero cambiado a letra
*/
/*char changeNumbertoLetter(char columnNumber)
{
    char *letters = {"abcdefgh"};
    for (int i = 0; i < 8; i++)
    {
        if (i == columnNumber)
        {
            return letters[i];
        }
    }
}*/

/**
 * Name: isKing
 * Funtion: verifica si una pieza es reyna(rey)
 * return: (int) retorna 1 si es rey o 0 si no lo es
*/
int isKing(char position)
{
    if (position == 'k' || position == 'K')
    {
        return 1;
    }
    return 0;
}

/*
int isPawn(char **board, char *position)
{
    int row = abs((position[1] - '0') - 8);
    int column = letterToPosition(position[0]) - 1;
    printf("Inside pawn\n");
    if ((*(*board + row) + column) == 'p' || (*(*board + row) + column) == 'P')
    {
        return 1;
    }
    return 0;
}*/
/**
 * Name: changePlayer
 * Funtion: cambia el turno del jugador. Del jugador 0 a 1 y, del jugador 1 al 0
 * return: (sin retorno) los elemntos son pasados por referencia
*/
void changePlayer(int *turn)
{
    if (*turn == 0)
    {
        *turn = 1;
    }
    else
    {
        *turn = 0;
    }
    return;
}

/**
 * Name: letterToPosition
 * Funtion: cambia la letra de la columna a numero
 * return: (int) retorna el numero correspodiente de la posicion de la letra
*/
int letterToPosition(char letterPlay)
{
    char *letters = {"abcdefgh"};
    for (int letter = 0; letter < 8; letter++)
    {
        if (letters[letter] == letterPlay)
        {
            return letter + 1;
        }
    }
}

/**
 * Name: positionToLetter
 * Funtion: cambia el numero de columna a letras (a,b,c,d,e,f,g,h)
 * return: (char) retorna el numero cambiado a letra
*/
char positionToLetter(int numberPosition)
{
    char *letters = {"abcdefgh"};
    for (int number = 0; number < 8; number++)
    {
        if (number == numberPosition)
        {
            return letters[number];
        }
    }
}

/**
 * Name: checkLastPositionEmpty
 * Funtion: revisar si la ultima posicion a mover esta vacia
 * return: (int) retorna 1 si lo esta y, 0 si no
*/
int checkLastPositionEmpty(char *lastPosition, char **board)
{
    int row = abs((lastPosition[1] - '0') - 8), column = letterToPosition(lastPosition[0]) - 1;
    if (board[row][column] == '*')
    {
        return 1;
    }
    return 0;
}