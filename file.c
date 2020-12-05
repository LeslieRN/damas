#include <stdlib.h>
#include <stdio.h>
#include "funciones.h"
#include <string.h>
#include <math.h>

void insert_data(char *file_name, player *playerInfo)
{
    FILE *file = open_file(file_name, "a+");
    fwrite(playerInfo, sizeof(player) * 2, 1, file);
    close_file(file);
}

void insert_Moves(char *file_name, gameHistory game)
{
    FILE *file = open_file(file_name, "a+");
    fwrite(&game, sizeof(gameHistory), 1, file);
    close_file(file);
}
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

void close_file(FILE *name_file)
{
    //close the file
    int close = fclose(name_file);
    close == 0 ?: printf("Error, file not close");
}

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
int quantity_of_players(char *file_name)
{
    FILE *file = open_file(file_name, "r");
    fseek(file, 0L, SEEK_END);
    long quantity = ftell(file);
    int quantity_of_players = quantity / sizeof(player);
    close_file(file);
    return quantity_of_players;
}