#include <stdlib.h>
#include <stdio.h>
#include "funciones.h"
#include <string.h>
#include <math.h>
char changeNumbertoLetter(char columnNumber)
{
    char *letters = {"abcdefgh"};
    for (int i = 0; i < 8; i++)
    {
        if (i == columnNumber)
        {
            return letters[i];
        }
    }
}

int isKing(char **board, char *position)
{
    int row = abs((position[1] - '0') - 8);
    int column = letterToPosition(position[0]) - 1;
    if ((*(*board + row) + column) == 'K' || (*(*board + row) + column) == 'k')
    {
        printf("I'm a king\n");
        return 1;
    }
    return 0;
}

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
}

void changePlayer(int *turn, int *numPlays)
{
    if (*turn == 0)
    {
        *turn = 1;
    }
    else
    {
        *turn = 0;
    }
    //++(*numPlays);
    return;
}

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

int checkLastPositionEmpty(char *lastPosition, char **board)
{
    int row = abs((lastPosition[1] - '0') - 8), column = letterToPosition(lastPosition[0]) - 1;
    printf("%c\n", board[row][column]);
    if (board[row][column] == '*')
    {
        printf("Hello here\n");
        return 1;
    }
    return 0;
}