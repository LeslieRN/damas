#include <stdlib.h>
#include <stdio.h>
#include "funciones.h"
#include <string.h>
#include <math.h>

/**
 * Funtion that set the memory space for the board
*/
char **boardSpace()
{
    char **pointerBoard = (char **)malloc(sizeof(char *) * 8);
    for (int i = 0; i < 8; i++)
    {
        *(pointerBoard + i) = (char *)malloc(sizeof(char *) * 8);
    }

    return pointerBoard;
}
/**
 * This funtions fill each line of the board
*/
char **fillBoard(char **pointerBoard, player *playerP)
{
    int squareBoard = 1;
    char symbolsBoard = '.';
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (j % 2 == ((i + 1) % 2))
            {
                if (i < 3)
                {
                    symbolsBoard = playerP[0].pawn;
                }
                else if (i > 4)
                {
                    symbolsBoard = playerP[1].pawn;
                }
                else
                {
                    symbolsBoard = '*';
                }
            }
            else
            {
                symbolsBoard = '.';
            }
            *(*(pointerBoard + i) + j) = symbolsBoard;
        }
    }
    return pointerBoard;
}

boardPositions *secondBoard()
{
    boardPositions *position = (boardPositions *)malloc(sizeof(boardPositions) * 64);
    char symbolsBoard = '.';
    int counter = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (j % 2 == ((i + 1) % 2))
            {

                symbolsBoard = '*';
            }
            else
            {
                symbolsBoard = '.';
            }
            position[counter].row = i;
            position[counter].column = j;
            position[counter].value = symbolsBoard;
            counter++;
        }
    }
    return position;
}

void displayBoard(char **pointerBoard)
{
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", abs(i - 8));
        for (int j = 0; j < 8; j++)
        {
            printf(" %c ", pointerBoard[i][j]);
        }
        printf(" %d", abs(i - 8));
        printf("\n");
    }
    printf("   a  b  c  d  e  f  g  h \n");
    return;
}

player *fillPlayerData()
{
    int counter = 0;
    player *p1 = (player *)malloc(sizeof(player) * 2);
    char temp_name[100];
    do
    {
        fflush(stdin);
        printf("Insert the name of player %d\n", counter + 1);
        fgets(temp_name, sizeof temp_name, stdin);
        strcpy(p1[counter].name, temp_name);
        p1[counter].pawnQuantity = 12;
        p1[counter].quantityGames = 0;
        p1[counter].tie = 0;
        p1[counter].win = 0;
        counter++;
    } while (counter <= 1);
    strcpy(p1[0].color, "Black");
    strcpy(p1[1].color, "White");

    p1[0].king = 'K';
    p1[1].king = 'k';
    p1[0].pawn = 'P';
    p1[1].pawn = 'p';
    return p1;
}