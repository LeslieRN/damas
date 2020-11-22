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
    printf("Okay\n");

    return pointerBoard;
}
/**
 * This funtions fill each line of the board
*/
char **fillBoard(char **pointerBoard)
{
    int squareBoard = 1;
    char symbolsBoard = '.';
    printf("Okay\n");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (i != 3 && i != 4)
            {
                //SHORT THIS!!!!
                if (squareBoard % 2 == 0)
                {
                    symbolsBoard = 'P';
                }
                else
                {
                    symbolsBoard = '.';
                }
            }
            else
            {
                if (squareBoard % 2 == 0)
                {
                    symbolsBoard = '*';
                }
                else
                {
                    symbolsBoard = '.';
                }
            }
            *(*(pointerBoard + i) + j) = symbolsBoard;
            squareBoard++;
        }
        squareBoard++;
    }
    return pointerBoard;
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

/**
 * Name: fillPlayerData
 * Funtion: insert the information of the playes in the playes structure
 * return: (player)
*/

player *fillPlayerData()
{
    int counter = 0;
    player *p1 = (player *)malloc(sizeof(player) * 2);
    do
    {
        fflush(stdin);
        printf("Insert the name of player %d\n", counter + 1);
        scanf("%s", p1[counter].name);
        p1[counter].pawnQuantity = 12;
        counter++;
    } while (counter <= 1);
    printf("The end of the fillPlayerData\n");
    p1[0].color = (char *)malloc(sizeof(char) * 5);
    p1[1].color = (char *)malloc(sizeof(char) * 5);
    strcpy(p1[0].color, "White");
    strcpy(p1[1].color, "Black");
    printf("The end of the fillPlayerData\n");
    return p1;
}

/**
 * Name: play
 * Funtion: it's the function in charge of the movements and changes on the board
 * return: (char**) -> the board with it's changes
*/
char **play(player *playersMain, int turn, char **boardMain)
{
    fflush(stdin);
    int playerChoice = 0, numberCurrent = 0, numberNew = 0;
    char *letterCurrent, *letterNew;
    printf("Turn # %d Player: %s Color: %s\n", turn + 1, playersMain[turn].name, playersMain[turn].color);
    printf("1) Play 2) Give up 3) Ask for table\n");
    scanf("%d", &playerChoice);
    switch (playerChoice)
    {
    case 1:
        checkIfLegalMovement(&letterCurrent, &letterNew, boardMain);
        break;

    default:
        printf("Incorrrect option. Try Again\n");
        break;
    }
}

void checkIfLegalMovement(char **currentLetter, char **newLetter, char **boardPlay)
{
    int tempN1 = 0, temp2 = 0;
    char *message = "No data found, Try Again!!";
    char temp1[6];
    char *token;
    *currentLetter = (char *)malloc(sizeof(char) * 3);
    *newLetter = (char *)malloc(sizeof(char) * 3);
    int correctMove;
    do
    {
        fflush(stdin);
        correctMove = 0;
        printf("Insert the current and the new position separated by semicolon\n");
        fgets(temp1, sizeof temp1, stdin);
        token = strtok(temp1, ":");
        strcpy(*currentLetter, token);
        //printf("This is current %c\n", *(*(currentLetter) + 1));
        token = strtok(NULL, "\0");
        strcpy(*newLetter, token);
        tempN1 = *(*(currentLetter) + 1) - '0';
        temp2 = *(*(newLetter) + 1) - '0';
        if (letterToPosition(*currentLetter[0]) > 8 || letterToPosition(*currentLetter[0]) < 1)
        {
            printf("%s Overfload!!\n", message);
            correctMove = 1;
        }

        if (letterToPosition(*newLetter[0]) > 8 || letterToPosition(*newLetter[0]) < 1)
        {
            printf("%s Overfload\n", message);
            correctMove = 1;
        }
        if (tempN1 > 8 || tempN1 < 1)
        {
            printf("%s Number OverFload\n", message);
            correctMove = 1;
        }

        if (temp2 > 8 || temp2 < 1)
        {
            printf("%s Number OverFload\n", message);
            correctMove = 1;
        }
        if (checkLastPositionEmpty(*newLetter, boardPlay))
        {
            printf("%s, Last position empty\n", message);
            correctMove = 1;
        }
        /*
        if (checkIfCrox(*currentLetter, *newLetter))
        {
            printf("%s\n", message);
            correctMove = 1;
        }*/

    } while (correctMove == 1);
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

int checkLastPositionEmpty(char *lastPosition, char **board)
{
    int row = abs((lastPosition[1] - '0') - 8), column = letterToPosition(lastPosition[0]);
    if (board[row][column - 1] != '*')
    {
        return 1;
    }
    return 0;
}

int checkIfCrox(char *firstPosition, char *lastPosition)
{
    int firstRow = (firstPosition[1] - '0'), lastRow = (lastPosition[1] - '0');
    int columnFirst = letterToPosition(firstPosition[0]), columnLast = letterToPosition(lastPosition[0]);
    if (columnFirst == columnLast)
    {
        return 1;
    }
    else if (columnFirst > columnLast && firstRow == lastRow)
    {
        return 1;
    }
    else if (columnFirst < columnLast && firstRow == lastRow)
    {
        return 1;
    }
    else if (columnFirst == columnLast && firstRow > lastRow)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    return 0;
}

int checkIfDiagonal(char *firstPosition, char *lastPosition, char **board, int *x, int *y)
{
    /*int firstRow = (firstPosition[1] - '0') - 1, lastRow = (lastPosition[1] - '0') - 1, movement = 0;
    int columnFirst = letterToPosition(firstPosition[0]) - 1, columnLast = letterToPosition(lastPosition[0]) - 1;*/
    int firstRow = abs((firstPosition[1] - '0') - 8), lastRow = abs((lastPosition[1] - '0') - 8), movement = 1;
    int columnFirst = letterToPosition(firstPosition[0]) - 1, columnLast = letterToPosition(lastPosition[0]) - 1;
    *x = 0;
    *y = 0;
    if (firstRow > lastRow && columnLast > columnFirst) //+- up left
    {
        *x = 1;
        *y = -1;
    }
    else if (firstRow > lastRow && columnFirst > columnLast) //-- up right
    {

        *x = -1;
        *y = -1;
    }
    else if (firstRow < lastRow && columnFirst > columnLast) //-+ down left
    {
        *x = -1;
        *y = 1;
        movement = 0;
    }
    else //++ down right
    {
        *x = 1;
        *y = 1;
        movement = 0;
    }
    return movement;
    ///
    /*int firstRow = (firstPosition[1] - '0') - 1, lastRow = (lastPosition[1] - '0') - 1;
    int columnFirst = letterToPosition(firstPosition[0]) - 1, columnLast = letterToPosition(lastPosition[0]) - 1;
    int x = 0, y = 0;
    if (determineDiagonal(firstPosition, lastPosition) == 1) //--
    {
        x = -1;
        y = -1;
    }
    else if (determineDiagonal(firstPosition, lastPosition) == 2) //+-
    {
        x = 1;
        y = -1;
    }
    else if (determineDiagonal(firstPosition, lastPosition) == 3) //++
    {
        x = 1;
        y = 1;
    }
    else if (determineDiagonal(firstPosition, lastPosition) == 4) //-+
    {
        x = -1;
        y = 1;
    }
    for (int i = firstRow; i <= lastRow; i += x)
    {
        if (board[i][columnFirst] == board[lastRow][columnLast])
        {
            return 1;
        }
        columnFirst += y;
    }*/
}

int moveDown(int column, int row, char *firstPosition, char *lastPosition, char ***board)
{
    int firstRow = abs((firstPosition[1] - '0') - 8), lastRow = abs((lastPosition[1] - '0') - 8), movement = 0;
    int columnFirst = letterToPosition(firstPosition[0]) - 1, columnLast = letterToPosition(lastPosition[0]) - 1;
    int eaten = 0;
    printf("Inside move up variables\n");
    printf("Inside move up variables Row: %d\n", row);
    printf("Inside move up variables Column: %d\n", column);
    printf("Inside move up variables firstRow: %d\n", firstRow);
    printf("Inside move up variables firstRow: %d\n", lastRow);
    printf("Inside move up variables columnFirst: %d\n", columnFirst);
    //*(*(arreglo_dimension + i) + j)
    //printf("Inside move up variables firstRow: %s\n", *(*board[firstRow][columnFirst]);
    char temp = *(*(*board + firstRow) + columnFirst);
    printf("Inside move up variables firstRow: %c\n", temp);
    for (int i = firstRow; i < lastRow; i += row)
    {
        //*(*(arreglo_dimension + i) + j)
        // printf("Inside move up variables firstRow: %d\n", firstRow);
        //printf("Inside move up variables columnFirst: %d\ns", columnFirst);
        //printf("Inside move up variables firstRow: %c\n", *(*(*board + i) + columnFirst));
        if (*(*(*board + i) + columnFirst) == 'P')
        {
            *(*(*board + i) + columnFirst) = '*';
            eaten++;
        }
        columnFirst += column;
    }
    *(*(*board + lastRow) + columnLast) = temp;
    printf("Inside move up variables firstRow: %d\n", firstRow);
    printf("Inside move up variables firstRow: %d\n", firstRow);

    return eaten;
}
int moveUp(int column, int row, char *firstPosition, char *lastPosition, char ***board)
{
    int firstRow = abs((firstPosition[1] - '0') - 8), lastRow = abs((lastPosition[1] - '0') - 8), movement = 0;
    int columnFirst = letterToPosition(firstPosition[0]) - 1, columnLast = letterToPosition(lastPosition[0]) - 1;
    int eaten = 0;
    printf("Inside move up variables columnLast %d\n", columnLast);
    printf("Inside move up variables Row: %d\n", row);
    printf("Inside move up variables Column: %d\n", column);
    printf("Inside move up variables firstRow: %d\n", firstRow);
    printf("Inside move up variables lastRow: %d\n", lastRow);
    printf("Inside move up variables columnFirst: %d\n", columnFirst);
    //*(*(arreglo_dimension + i) + j)
    //printf("Inside move up variables firstRow: %s\n", *(*board[firstRow][columnFirst]);
    char temp = *(*(*board + firstRow) + columnFirst);
    printf("Inside move up variables firstRow: %c\n", temp);
    for (int i = firstRow; i > lastRow; i += row)
    {
        //*(*(arreglo_dimension + i) + j)
        // printf("Inside move up variables firstRow: %d\n", firstRow);
        //printf("Inside move up variables columnFirst: %d\ns", columnFirst);
        //printf("Inside move up variables firstRow: %c\n", *(*(*board + i) + columnFirst));
        if (*(*(*board + i) + columnFirst) == 'P')
        {
            *(*(*board + i) + columnFirst) = '*';
            eaten++;
        }
        columnFirst += column;
    }
    *(*(*board + lastRow) + columnLast) = temp;
    //*(*(*board + firstRow) + columnFirst) = '*';
    printf("Inside move up variables firstRow: %d\n", firstRow);
    printf("Inside move up variables firstRow: %d\n", firstRow);

    return eaten;
}