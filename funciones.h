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
    int pawnQuantity;
    char *playQuantity;
    char *color;
} player;

enum letterKey
{
    a = 1,
    b = 2,
    c = 3,
    d = 4,
    e = 5,
    f = 6,
    g = 7,
    h = 8
};
char **boardSpace();
char **fillBoard(char **);
void displayBoard(char **);
player *fillPlayerData();
char **play(player *, int, char **);
char **movementPawn(player *, int, char **, char, int, char, int);
char **movementLeft(player *, int, char **, int, int, int, int);
int letterToPosition(char);
void checkIfLegalMovement(char **, char **, char **);
int checkIfDiagonal(char *, char *, char **, int *, int *);
int moveDown(int, int, char *, char *, char ***);
int moveUp(int, int, char *, char *, char ***);
//int determineDiagonal(char *, char *);
int checkLastPositionEmpty(char *, char **);
int checkIfCrox(char *, char *);

#endif /* !FUNCIONES_H_ */
