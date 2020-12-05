#include <stdlib.h>
#include <stdio.h>
#include "funciones.h"
#include <string.h>
#include <math.h>
#include "tools.c"
//#include "boardUser.c"
int mainMenu()
{
    int option = 0;
    printf("WELCOME TO CHECKERS GAME!!\n");
    printf("Menu options:\n");
    printf("1. Play\n");
    printf("2. Review History\n");
    printf("3. Game notation\n");
    printf("4. Exit\n");
    scanf("%d", &option);
    return option;
}

/**
 * Name: fillPlayerData
 * Funtion: insert the information of the playes in the playes structure
 * return: (player)
*/

void checkIfLegalMovement(char **currentLetter, char **newLetter, boardPositions *positions, char **boardPlay, int turn, player *playerData)
{
    //int tempN1 = 0, temp2 = 0;
    char *message = "No data found, Try Again!!";
    char temp1[3], temp2[3];
    char *token, key = 'P';
    *currentLetter = (char *)malloc(sizeof(char) * 3);
    *newLetter = (char *)malloc(sizeof(char) * 3);
    int correctMove;
    do
    {
        correctMove = 0;
        if ((strcmp(possibleForceMove(turn, playerData, boardPlay), "") != 0))
        {
            key = 'F';
        }
        do
        {
            correctMove = 0;
            fflush(stdin);
            printf("Insert the first position\n");
            fgets(temp1, sizeof temp1, stdin);
            strcpy(*currentLetter, temp1);
            if (checkOverflow(positions, *currentLetter) == 0)
            {
                printf("%s, position overflow\n", message);
                correctMove = 1;
            }
        } while (correctMove == 1);

        if (key != 'F')
        {
            possibleMoves(*currentLetter, boardPlay);
        }

        do
        {
            correctMove = 0;
            fflush(stdin);
            printf("Insert the value of the last position\n");
            fgets(temp2, sizeof temp2, stdin);
            strcpy(*newLetter, temp2);
            if (checkOverflow(positions, *currentLetter) == 0 && checkLastPositionEmpty(*newLetter, boardPlay))
            {
                printf("%s, position overflow\n", message);
                correctMove = 1;
            }
        } while (correctMove == 1);

        if (key == 'P' && checkIfPossibleMove(*currentLetter, *newLetter, boardPlay))
        {
            printf("%s. Error moving the pieces normally\n", message);
            correctMove = 1;
        }
        if (key == 'F' && checkIfForceMove(turn, playerData, *currentLetter, boardPlay))
        {
            printf("%s. Error forcing movement\n", message);
            correctMove = 1;
        }
        key = 'P';
    } while (correctMove == 1);
}

int checkOverflow(boardPositions *positions, char *userPosition)
{
    int row = abs((userPosition[1] - '0') - 8);
    int column = letterToPosition(userPosition[0]) - 1;
    for (int i = 0; i < 64; i++)
    {
        if (userPosition[1] > 8 || userPosition[1] < 1)
        {

            if (positions->row == row && positions->column == column && positions->value != '.')
            {
                return 1;
            }
        }
        positions++;
    }
    return 0;
}

int checkIfPossibleMove(char *currentPosition, char *lastPosition, char **boardPlay)
{
    char *tempPosition = possibleMoves(currentPosition, boardPlay);
    char *token = strtok(tempPosition, " ");
    int result = 0;
    while (token != NULL)
    {
        if (strcmp(lastPosition, token) == 0)
        {
            return 0;
        }
        token = strtok(NULL, " ");
    }
    return 1;
}

int checkIfForceMove(int turn, player *playerData, char *firstPosition, char **boardPlay)
{
    char *tempPosition = possibleForceMove(turn, playerData, boardPlay);
    char *token = strtok(tempPosition, " ");
    int result = 0;
    while (token != NULL)
    {
        if (strcmp(firstPosition, token) == 0)
        {
            return 0;
        }
        token = strtok(NULL, " ");
    }
    return 1;
}

char *possibleForceMove(int turn, player *playerData, char **boardPlay)
{
    int quantity = 1;
    char *possiblePositions = (char *)malloc(sizeof(char) * 4), tempPosition[4];
    strcpy(possiblePositions, "\0");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (j % 2 == ((i + 1) % 2))
            {
                if (boardPlay[i][j] == playerData[0].pawn || boardPlay[i][j] == 'K' || boardPlay[i][j] == 'k')
                {
                    //{ //white player
                    if (boardPlay[i + 1][j - 1] == 'p' && boardPlay[i - 1][j + 1] == '*')
                    {
                        returnMovement(tempPosition, j - 1, i + 1);
                        possiblePositions = (char *)realloc(possiblePositions, (sizeof(char) * 4) * quantity);
                        strcat(possiblePositions, tempPosition);
                        quantity++;
                    }
                    if (boardPlay[i + 1][j + 1] == 'p' && boardPlay[i - 1][j - 1] == '*')
                    {
                        returnMovement(tempPosition, j + 1, i + 1);
                        possiblePositions = (char *)realloc(possiblePositions, (sizeof(char) * 4) * quantity);
                        strcat(possiblePositions, tempPosition);
                        quantity++;
                    }
                }
                if (boardPlay[i][j] == playerData[1].pawn || boardPlay[i][j] == 'K' || boardPlay[i][j] == 'k')
                { //black player
                    if (boardPlay[i - 1][j - 1] == 'P' && boardPlay[i + 1][j + 1] == '*')
                    {
                        returnMovement(tempPosition, j - 1, i - 1);
                        possiblePositions = (char *)realloc(possiblePositions, (sizeof(char) * 4) * quantity);
                        strcat(possiblePositions, tempPosition);

                        quantity++;
                    }
                    if (boardPlay[i - 1][j + 1] == 'P' && boardPlay[i + 1][j - 1] == '*')
                    {
                        returnMovement(tempPosition, j + 1, i - 1);
                        possiblePositions = (char *)realloc(possiblePositions, (sizeof(char) * 4) * quantity);
                        strcat(possiblePositions, tempPosition);
                        quantity++;
                    }
                }
            }
        }
    }

    printf("Possible Force positions %s\n", possiblePositions);
    return possiblePositions;
}

int coordinates(char *firstPosition, char *lastPosition, char **board, int *x, int *y, player *checkPiece)
{
    int firstRow = abs((firstPosition[1] - '0') - 8), lastRow = abs((lastPosition[1] - '0') - 8);
    int columnFirst = letterToPosition(firstPosition[0]) - 1, columnLast = letterToPosition(lastPosition[0]) - 1;
    *x = 0;
    *y = 0;
    if (firstRow > lastRow && columnLast > columnFirst) //+- down
    {
        *x = 1;
        *y = -1;
        return 1;
    }
    else if (firstRow > lastRow && columnFirst > columnLast) //-- up right
    {

        *x = -1;
        *y = -1;
        return 1;
    }
    else if (firstRow < lastRow && columnFirst > columnLast) //-+ down left
    {
        *x = -1;
        *y = 1;
        return 1;
    }
    else //++ down right
    {
        *x = 1;
        *y = 1;
        return 1;
    }
}

int move(int column, int row, char *firstPosition, char *lastPosition, char ***board, player *p1)
{
    int firstRow = abs((firstPosition[1] - '0') - 8), lastRow = abs((lastPosition[1] - '0') - 8);
    int columnFirst = letterToPosition(firstPosition[0]) - 1, columnLast = letterToPosition(lastPosition[0]) - 1;
    int eaten = 0;
    char temp = *(*(*board + firstRow) + columnFirst);
    if (*(*(*board + (firstRow + row)) + (columnFirst + column)) != '*')
    {
        *(*(*board + (firstRow + row)) + (columnFirst + column)) = '*';
        eaten++;
        row += row;
        column += column;
    }
    if (lastRow == 0 || lastRow == 7)
    {
        if (temp == p1[0].pawn)
        {
            temp = p1[0].king;
        }
        else
        {
            temp = p1[1].king;
        }
    }
    *(*(*board + (firstRow + row)) + (columnFirst + column)) = temp;
    *(*(*board + firstRow) + columnFirst) = '*';
    return eaten;
}

/*
void checkLastDiag(char *lastPosition, char **boardPlay)
{
    int row = abs((lastPosition[1] - '0') - 8);
    int column = letterToPosition(lastPosition[0]) - 1;
    char **possiblePositions = (char **)malloc(sizeof(char *)), tempPosition[2];
    if (boardPlay[row][column] == 'P')
    { //white player
        if (boardPlay[row + 1][column - 1] == '*' || isKing(boardPlay, lastPosition))
        {
            if (boardPlay[row - 1][column - 1] = 'p')
            {
                printf("Possible movement at %c%d\n", positionToLetter(column - 1), row - 1);
                tempPosition[0] = positionToLetter(column - 1);
                tempPosition[1] = (row - 1) + '0';
            }
        }
        else if (boardPlay[row + 1][column + 1] == '*')
        {
            if (boardPlay[row - 1][column + 1] = 'p')
            {
                printf("Possible movement at %c%d\n", positionToLetter(column + 1), row - 1);
            }
        }
    }

    if (boardPlay[row][column] == 'p' || isKing(boardPlay, lastPosition))
    { //black player
        if (boardPlay[row - 1][column - 1] == '*')
        {
            if (boardPlay[row + 1][column + 1] = 'P')
            {
                printf("Possible movement at %c%d\n", positionToLetter(column + 1), row + 1);
            }
        }
        else if (boardPlay[row - 1][column + 1] == '*')
        {
            if (boardPlay[row + 1][column - 1] = 'P')
            {
                printf("Possible movement at %c%d\n", positionToLetter(column - 1), row + 1);
            }
        }
    }
}
*/
char *possibleMoves(char *firstPosition, char **boardPlay)
{
    int row = abs((firstPosition[1] - '0') - 8);
    int column = letterToPosition(firstPosition[0]) - 1, quantity = 1;
    char *possiblePositions = (char *)malloc(sizeof(char) * 4), tempPosition[4];
    strcpy(possiblePositions, "\0");

    if (boardPlay[row][column] == 'P' || boardPlay[row][column] == 'K' || boardPlay[row][column] == 'k')
    { //white player
        if (boardPlay[row + 1][column - 1] == '*')
        {
            returnMovement(tempPosition, column - 1, row + 1);
            possiblePositions = (char *)realloc(possiblePositions, (sizeof(char) * 4) * quantity);
            strcat(possiblePositions, tempPosition);
            quantity++;
        }
        if (boardPlay[row + 1][column + 1] == '*')
        {
            returnMovement(tempPosition, column + 1, row + 1);
            possiblePositions = (char *)realloc(possiblePositions, (sizeof(char) * 4) * quantity);
            strcat(possiblePositions, tempPosition);
            quantity++;
        }
    }

    if (boardPlay[row][column] == 'p' || boardPlay[row][column] == 'K' || boardPlay[row][column] == 'k')
    { //black player
        if (boardPlay[row - 1][column - 1] == '*')
        {
            returnMovement(tempPosition, column - 1, row - 1);
            possiblePositions = (char *)realloc(possiblePositions, (sizeof(char) * 4) * quantity);
            strcat(possiblePositions, tempPosition);
            quantity++;
        }
        if (boardPlay[row - 1][column + 1] == '*')
        {

            returnMovement(tempPosition, column + 1, row - 1);
            possiblePositions = (char *)realloc(possiblePositions, (sizeof(char) * 4) * quantity);
            strcat(possiblePositions, tempPosition);
            quantity++;
        }
    }
    printf("Possible positions %s\n", possiblePositions);
    return possiblePositions;
}

void returnMovement(char *tempPosition, int column, int row)
{
    tempPosition[0] = positionToLetter(column);
    tempPosition[1] = abs((row - 8)) + '0';
    tempPosition[2] = ' ';
    tempPosition[3] = '\0';
}