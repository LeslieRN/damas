#include <stdlib.h>
#include <stdio.h>
#include "funciones.c"

int main()
{

    char **boardMain;
    char **boardDisplay;
    boardMain = boardSpace();
    boardDisplay = fillBoard(boardMain);
    //printf("Okay");
    displayBoard(boardDisplay);
    int turn = 0, temp = 1, column = 0, row = 0;
    player *p1 = fillPlayerData();
    //play(p1, turn, boardDisplay);
    int playerChoice = 0, numberCurrent = 0, numberNew = 0;
    do
    {
        fflush(stdin);
        char *letterCurrent, *letterNew;
        printf("Turn # %d Player: %s Color: %s\n", turn + 1, p1[turn].name, p1[turn].color);
        printf("1) Play 2) Give up 3) Ask for table\n");
        scanf("%d", &playerChoice);
        switch (playerChoice)
        {
        case 1:
            checkIfLegalMovement(&letterCurrent, &letterNew, boardDisplay);
            //make the movement
            printf("In main\n");
            if (checkIfDiagonal(letterCurrent, letterNew, boardDisplay, &column, &row))
            {
                moveUp(column, row, letterCurrent, letterNew, &boardDisplay);
                displayBoard(boardDisplay);
            }
            else
            {
                moveDown(column, row, letterCurrent, letterNew, &boardDisplay);
                displayBoard(boardDisplay);
            }
            break;
        case 2:
            printf("Sorry you wan to leave :(\n");
            //add the winner
            break;
        case 3:
            displayBoard(boardDisplay);
            break;
        default:
            printf("Incorrrect option. Try Again\n");
            break;
        }
        if (turn == 0)
        {
            turn = 1;
        }
        else
        {
            turn = 0;
            temp = 0;
        }
    } while (playerChoice != 2);
    /*
    do
    {
        printf("Player name: %s, quantity of pawns: %d, color: %s\n", p1[turn].name, p1[turn].pawnQuantity, p1[turn].color);
        if (turn == 0)
        {
            turn = 1;
        }
        else
        {
            turn = 0;
            temp = 0;
        }
    } while (temp == 1);

    printf("Player name: %s, quantity of pawns: %d, color: %s\n", p1[0].name, p1[0].pawnQuantity, p1[0].color);
    printf("Player name: %s, quantity of pawns: %d, color: %s\n", p1[1].name, p1[1].pawnQuantity, p1[1].color);*/
    return 0;
}