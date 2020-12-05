/*
** EPITECH PROJECT, 2020
**  
** File description:
** funciones
*/
#include <stdlib.h>
#include <stdio.h>
#ifndef FUNCIONES_H_
#define FUNCIONES_H_

typedef struct
{
    char name[100];
    char color[6];
    int pawnQuantity;
    int win;
    int quantityGames;
    int tie;
    char king;
    char pawn;
} player;

typedef struct
{
    int row;
    int column;
    char value;
} boardPositions;

typedef struct
{
    char name[150];
    char moves[500];
} gameHistory;

char **boardSpace();
char **fillBoard(char **, player *);
boardPositions *secondBoard();
void displayBoard(char **);
player *fillPlayerData();
void showPositions(boardPositions *);
int mainMenu();

int letterToPosition(char);
char positionToLetter(int);
void checkIfLegalMovement(char **, char **, boardPositions *, char **boardPlay, int, player *);
int checkOverflow(boardPositions *, char *);
int coordinates(char *, char *, char **, int *, int *, player *);
char *possibleMoves(char *, char **);
char *possibleForceMove(int, player *, char **);
int move(int, int, char *, char *, char ***, player *);
//void checkLastDiag(char *, char **);
//int determineDiagonal(char *, char *);
int checkLastPositionEmpty(char *, char **);
int checkIfForceMove(int, player *, char *, char **);
int checkIfPossibleMove(char *, char *, char **);
//int checkIfCrox(char *, char *);
//void forceMovement(char *, int, player *, char **);
int isKing(char **, char *);
int isPawn(char **, char *);
int askForTable();
//char *checkDiagDown(char *, char **, int, int);
//char *checkDiagUp(char *, char **, int, int);
//int checkRightDown(char *, char **, int, int);
//void showPossibleMoves(char **);
void changePlayer(int *, int *);
void returnMovement(char *, int, int);
char changeNumbertoLetter(char);
int determineWinner(player **);
//int chec
/*FILE FUNCTIONS*/
FILE *open_file(char *, char *);
void close_file(FILE *);
void show_file_data(char *);
void show_history_data(char *);
void printStruct(FILE *fout, player temp);
int quantity_of_players(char *file_name);
void insert_data(char *file_name, player *);
void insert_Moves(char *file_name, gameHistory);

#endif /* !FUNCIONES_H_ */