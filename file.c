#include <stdlib.h>
#include <stdio.h>
#include "funciones.h"
#include <string.h>
#include <math.h>

/**
 * Name: insert_data
 * Funtion: insertar los datos del jugador en un archivo
 * return: (sin retorno)
*/
void insert_data(char *file_name, player *playerInfo)
{
    FILE *file = open_file(file_name, "a+");
    fwrite(playerInfo, sizeof(player) * 2, 1, file);
    close_file(file);
}

/**
 * Name: insert_Moves
 * Funtion: insertar los movimientos que hizo cada jugador
 * return: (sin retorno)
*/
void insert_Moves(char *file_name, gameHistory game)
{
    FILE *file = open_file(file_name, "a+");
    fwrite(&game, sizeof(gameHistory), 1, file);
    close_file(file);
}

/**
 * Name: open_file
 * Funtion: abrir el archivo que se va a editar
 * return: (FILE) retorna el archivo abierto
*/
FILE *open_file(char *name_file, char *mode)
{
    //open the file
    FILE *file = fopen(name_file, mode);
    if (file == NULL)
    {
        fputs("File not open... Please Check", stderr);
        exit(-1);
    }
    return file;
}

/**
 * Name: close_file
 * Funtion: cerrar el archivo que se edito
 * return: (sin retorno)
*/
void close_file(FILE *name_file)
{
    //close the file
    int close = fclose(name_file);
    close == 0 ?: printf("Error, file not close");
}

/**
 * Name: show_file_data
 * Funtion: mostrar el registro de jugadores
 * return: (sin retorno)
*/
void show_file_data(char *file_name)
{
    int total = quantity_of_players(file_name);
    FILE *file = open_file(file_name, "r");
    int counter = 0;
    while (counter < total)
    {
        player temp;
        fread(&temp, sizeof(player), 1, file);
        printf("Name: %sColor: %s ties: %d win: %d total games: %d\n", temp.name, temp.color, temp.tie, temp.win, temp.quantityGames);
        counter++;
    };
    close_file(file);
    return;
}

/**
 * Name: show_history_data
 * Funtion: mostrar el registro de movimientos
 * return: (sin retorno)
*/
void show_history_data(char *file_name)
{
    FILE *file = open_file(file_name, "r");
    gameHistory movesGames;
    while (fread(&movesGames, sizeof(gameHistory), 1, file))
    {
        printf("Name of players %s\n", movesGames.name);
        printf("Moves\n");
        printf("%s", movesGames.moves);
    }
    close_file(file);
}

/**
 * Name: quantity_of_players
 * Funtion: calcular la cantidad de jugadores en el archivo
 * return: (int) retorna la cantidad de jugadores en el archivo
*/
int quantity_of_players(char *file_name)
{
    FILE *file = open_file(file_name, "r");
    fseek(file, 0L, SEEK_END);
    long quantity = ftell(file);
    int quantity_of_players = quantity / sizeof(player);
    close_file(file);
    return quantity_of_players;
}