#include <stdlib.h>
#include <stdio.h>
#include "funciones.c"
#include <string.h>
#include "boardUser.c"
#include "winner.c"
#include "file.c"
int main()
{

    char **boardMain, **boardDisplay, *record = "playRecord.txt", *moves = "movesRecord.txt", *tempPlay, continuePlay;

    int turn = 0, temp = 0, column = 0, row = 0, numberPlay = 0, option = 0, numberGames = 0, tie = 0;
    gameHistory game;
    tempPlay = (char *)malloc(sizeof(char));
    strcpy(tempPlay, "\0");
    int playerChoice = 0, numberCurrent = 0, numberNew = 0;
    do
    {
        option = mainMenu();
        if (option == 1)
        {
            player *p1 = fillPlayerData();
            boardPositions *position = secondBoard();
            boardMain = boardSpace();
            boardDisplay = fillBoard(boardMain, p1);
            //displayBoard(boardDisplay);
            strcpy(game.name, p1[0].name);
            strcat(game.name, p1[1].name);
            strcat(game.name, "\0");
            do
            {
                do
                {
                    numberPlay++;

                    fflush(stdin);
                    displayBoard(boardDisplay);
                    char *letterCurrent, *letterNew;
                    printf("Turn # %d Player: %s Color: %s\n", turn + 1, p1[turn].name, p1[turn].color);
                    printf("1) Play 2) Give up 3) Ask for table\n");
                    scanf("%d", &playerChoice);
                    //do
                    //{

                    switch (playerChoice)
                    {
                    case 1:

                        checkIfLegalMovement(&letterCurrent, &letterNew, position, boardDisplay, turn, p1);
                        coordinates(letterCurrent, letterNew, boardDisplay, &column, &row, p1);
                        //printf("Hello?\n");
                        changePlayer(&turn, &numberPlay);
                        p1[turn].pawnQuantity -= move(column, row, letterCurrent, letterNew, &boardDisplay, p1);
                        changePlayer(&turn, &numberPlay);
                        //displayBoard(boardDisplay);
                        printf("Hello?\n");
                        tempPlay = (char *)realloc(tempPlay, (sizeof(char) * 14) * numberPlay);
                        strcat(tempPlay, p1[turn].color);
                        strcat(tempPlay, " ");
                        strcat(tempPlay, letterCurrent);
                        strcat(tempPlay, " ");
                        strcat(tempPlay, letterNew);
                        strcat(tempPlay, "\0");
                        strcat(tempPlay, "\n");
                        break;
                    case 2:
                        printf("Sorry you want to leave :(\n");
                        changePlayer(&turn, &numberPlay);
                        p1[turn].win++;
                        //add the winner
                        break;
                    case 3:
                        if (askForTable())
                        {
                            p1[0].tie++;
                            p1[1].tie++;
                            printf("The game it's a tie!!!\n");
                        }
                        else
                        {
                            playerChoice = 1;
                        }
                        break;
                    default:
                        printf("Incorrrect option. Try Again!!\n");
                        break;
                    }
                    changePlayer(&turn, &numberPlay);
                    temp = 1;
                } while (playerChoice != 2 && playerChoice != 3 && determineWinner(&p1) == 1);

                strcpy(game.moves, tempPlay);
                insert_Moves(moves, game);
                p1[0].quantityGames++;
                p1[1].quantityGames++;
                fflush(stdin);
                printf("Do you want to continue playing? (y)es or (n)o\n");
                continuePlay = getchar();
                if (continuePlay == 'y')
                {
                    p1[0].pawnQuantity = 12;
                    p1[1].pawnQuantity = 12;
                    temp = 0;
                }
            } while (continuePlay == 'y');
            //
            insert_data(record, p1);
        }
        else if (option == 2)
        {
            show_file_data(record);
            printf("\n");
            //option = mainMenu();
        }
        else if (option == 3)
        {
            //notacion algebraica
            show_history_data(moves);
            printf("\n");
        }
        else
        {
            exit(0);
        }
    } while (option != 4);
    return 0;
}