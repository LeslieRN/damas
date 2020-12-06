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

//Estructura player que guarda informacion relevante como: color, cantidad de piezas, cantidad de juegos...
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

//Estructura que guarda las posiciones blancas y negras del tablero
typedef struct
{
    int row;
    int column;
    char value;
} boardPositions;

//Estructura que guarda el historial del juego
typedef struct
{
    char name[150];
    char moves[1000];
} gameHistory;

//funciones de tabla
char **boardSpace();
char **fillBoard(char **, player *);
boardPositions *secondBoard();
void displayBoard(char **);
player *fillPlayerData();
//void showPositions(boardPositions *);

//funcion del menu principal
int mainMenu();

//funciones de validacion y coordinadas
int letterToPosition(char);
char positionToLetter(int);
void checkIfLegalMovement(char **, char **, boardPositions *, char **boardPlay, int, player *);
int checkOverflow(boardPositions *, char *);
int coordinates(char *, char *, char **, int *, int *, player *);
char *possibleMoves(char *, char **);
char *possibleForceMove(int, player *, char **);

//funcione de movimiento
int move(int, int, char *, char *, char ***, player *);

//funciones de validacion y forzar movimiento
int checkLastPositionEmpty(char *, char **);
int checkIfForceMove(int, player *, char *, char **);
int checkIfPossibleMove(char *, char *, char **);
int isKing(char);
int askForTable();
void changePlayer(int *);
void returnMovement(char *, int, int);

//funciones de jugador
//char changeNumbertoLetter(char);
int determineWinner(player **);

/*FILE FUNCTIONS*/
FILE *open_file(char *, char *);
void close_file(FILE *);
void show_file_data(char *);
void show_history_data(char *);
//void printStruct(FILE *fout, player temp);
int quantity_of_players(char *file_name);
void insert_data(char *file_name, player *);
void insert_Moves(char *file_name, gameHistory);

#endif /* !FUNCIONES_H_ */