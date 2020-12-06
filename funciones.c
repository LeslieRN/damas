#include <stdlib.h>
#include <stdio.h>
#include "funciones.h"
#include <string.h>
#include <math.h>
#include "tools.c"

/**
 * Name: mainMenu
 * Funtion: es el menu principal del juego
 * return: (int) retorna la opcion que el usuario desee
*/
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
 * Name: checkIfLegalMovement
 * Funtion: es la funcion que se encarga de revisar si los movimientos estan permitidos
 *          Tambien se encarga de revisar si hay movimiento forzado
 * return: (sin retorno)
*/
void checkIfLegalMovement(char **currentLetter, char **newLetter, boardPositions *positions, char **boardPlay, int turn, player *playerData)
{

    char *message = "No data found, Try Again!!"; //variable que tiene mensaje de alerta
    char temp1[3], temp2[3];                      //variables auxiliares que guardaran la posicion
    char key = 'P';                               //variable que se encarga de determinar el acceso a movimiento normal o forzado

    //se reserva espacio para las variables del main
    *currentLetter = (char *)malloc(sizeof(char) * 3);
    *newLetter = (char *)malloc(sizeof(char) * 3);
    int correctMove;
    do
    {
        correctMove = 0;
        //si existe algun movimiento forzado, esta cambia la clave para que se ejecuten las opciones del movimiento forzado
        if ((strcmp(possibleForceMove(turn, playerData, boardPlay), "") != 0))
        {
            key = 'F';
        }

        do
        {
            correctMove = 0;
            fflush(stdin);
            //insercion de la primera posicion
            printf("Insert the first position\n");
            fgets(temp1, sizeof temp1, stdin);
            strcpy(*currentLetter, temp1);
            // si la posicion no esta dentro del rango o es una posicion blanca
            if (checkOverflow(positions, *currentLetter) == 0)
            {
                //se imprimer el mensaje
                printf("%s, position overflow\n", message);
                correctMove = 1;
            }
            //y continua el ciclo
        } while (correctMove == 1);

        //si la clave es diferente de F, entonces luego de ser insertada la primera posicion
        //esta verifica los posibles movimientos que se pueden hacer
        if (key != 'F')
        {
            possibleMoves(*currentLetter, boardPlay);
        }

        do
        {
            correctMove = 0;
            fflush(stdin);
            //insercion de datos para la segunda posicion
            printf("Insert the value of the last position\n");
            fgets(temp2, sizeof temp2, stdin);
            strcpy(*newLetter, temp2);
            //se verifica si esta dentro del rango y si la posicion esta vacía
            if (checkOverflow(positions, *newLetter) == 0 && checkLastPositionEmpty(*newLetter, boardPlay))
            {
                //en dado caso de que no se cumpla una de las dos, se imprime el mensaje
                printf("%s, position overflow\n", message);
                correctMove = 1;
            }
            //continua el ciclo
        } while (correctMove == 1);

        //se revisa si los movimientos insertados concuerdan con los mostrados al usuario
        if (key == 'P' && checkIfPossibleMove(*currentLetter, *newLetter, boardPlay))
        {
            // en  dado caso de no serlo, este imprime el mensaje, y se repite el ciclo otra vez
            printf("%s. Error moving the pieces normally\n", message);
            correctMove = 1;
        }
        //se revisa si los movimientos insertados concuerdad con los mostrados al usuario (movimiento forzado)
        if (key == 'F' && checkIfForceMove(turn, playerData, *currentLetter, boardPlay))
        {
            // en  dado caso de no serlo, este imprime el mensaje, y se repite el ciclo otra vez
            printf("%s. Error forcing movement\n", message);
            correctMove = 1;
        }
        key = 'P';
    } while (correctMove == 1);
}

/**
 * Name: checkOverflow
 * Funtion: es la funcion que se encarga de revisar si los movimientos estan dentro del rango
 * return: (int) retorna 1 si los movimientos estan bien y 0 si no lo estan
*/
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

/**
 * Name: checkIfPossibleMove
 * Funtion: es la funcion que revisa si se pueden realizar el movimiento de los posibles movimientos mostrados al usuario
 *          esta recorre todos los posibles movimientos mostrados al usuario y los compara con la ultima posicion
 * return: (int) retorna 1 si no hay movimiento que concuerden y, 0 si si los hay
*/
int checkIfPossibleMove(char *currentPosition, char *lastPosition, char **boardPlay)
{
    char *tempPosition = possibleMoves(currentPosition, boardPlay); // se guardan los posibles movientos
    char *token = strtok(tempPosition, " ");
    int result = 0;
    while (token != NULL)
    {
        if (strcmp(lastPosition, token) == 0) // se comparan con la ultima posicion
        {
            return 0;
        }
        token = strtok(NULL, " ");
    }
    return 1;
}

/**
 * Name: checkIfForceMove
 * Funtion: es la funcion que revisa si se pueden realizar el movimiento (forzado) de los posibles movimientos mostrados al usuario
 *          esta recorre todos los posibles movimientos mostrados al usuario y los compara con la ultima posicion
 * return: (int) retorna 1 si no hay movimiento que concuerden y, 0 si si los hay
*/
int checkIfForceMove(int turn, player *playerData, char *firstPosition, char **boardPlay)
{
    char *tempPosition = possibleForceMove(turn, playerData, boardPlay); //se guardan los posibles movientos forzados
    char *token = strtok(tempPosition, " ");
    int result = 0;
    while (token != NULL)
    {
        if (strcmp(firstPosition, token) == 0) //se compara el movimiento forzado con la primera posicion
        {
            return 0;
        }
        token = strtok(NULL, " ");
    }
    return 1;
}

/**
 * Name: possibleForceMove
 * Funtion: es la funcion que revisa el tablero para determinar los posibles movimientos forzados
 *          esta recorre la tabla en busca del turno actual y, dada ciertas condiciones, inserta la opcion de movimiento forzados
 *          esta tiene ciertos limites para evitar que exista un "overflow"
 * return: (char*) retorna los posibles movimientos forzados
*/
char *possibleForceMove(int turn, player *playerData, char **boardPlay)
{
    int quantity = 1;
    // se reserva memoria para los posibles movimientos y, la variable tempPosition guarda temporalmente las posiciones
    char *possiblePositions = (char *)malloc(sizeof(char) * 4), tempPosition[4];
    strcpy(possiblePositions, "\0");

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (j % 2 == ((i + 1) % 2)) // se recorre el ciclo de manera que se va exactamente a las posiciones negras
            {
                //si es turno del jugador blanco
                if (turn == 1)
                {
                    //se revisa que los datos de las tablas sean que los mismo del jugador blanco
                    if (boardPlay[i][j] == playerData[turn].pawn || boardPlay[i][j] == playerData[turn].king)
                    {
                        //si i - 2 es >= 0, es decir si no se produce un overdlow
                        if ((i - 2) >= 0)
                        {
                            //se pregunta si la ficha es reyna
                            if (boardPlay[i][j] == playerData[turn].king)
                            {
                                //si lo es, se verifica que el restarle dos las columnas no sufran overflow
                                if ((j - 2) >= 0)
                                {
                                    //en dado caso de no ser asi se verifica si hay movimiento forzado
                                    if ((boardPlay[i - 1][j - 1] == 'p' || boardPlay[i - 1][j - 1] == 'k') && boardPlay[i - 2][j - 2] == '*')
                                    {
                                        //si lo hay, entonces esta es guardada en la variable possiblePositions
                                        returnMovement(tempPosition, j, i);
                                        possiblePositions = (char *)realloc(possiblePositions, (sizeof(char) * 4) * quantity);
                                        strcat(possiblePositions, tempPosition);

                                        quantity++;
                                    }
                                }
                                //si lo es, se verifica que el sumarle dos las columnas no sufran overflow
                                if ((j + 2) <= 7)
                                {
                                    //en dado caso de no ser asi se verifica si hay movimiento forzado
                                    if ((boardPlay[i - 1][j + 1] == 'p' || boardPlay[i - 1][j + 1] == 'k') && boardPlay[i - 2][j + 2] == '*')
                                    {
                                        //si lo hay, entonces esta es guardada en la variable possiblePositions
                                        returnMovement(tempPosition, j, i);
                                        possiblePositions = (char *)realloc(possiblePositions, (sizeof(char) * 4) * quantity);
                                        strcat(possiblePositions, tempPosition);
                                        quantity++;
                                    }
                                }
                            }
                        }
                        //si no se produce overflow de fila
                        if ((i + 2) <= 7)
                        {
                            // y si no se produce overflow de columna izquierda
                            if ((j - 2) >= 0)
                            {
                                if ((boardPlay[i + 1][j - 1] == 'p' || boardPlay[i + 1][j - 1] == 'k') && boardPlay[i + 2][j - 2] == '*')
                                {
                                    returnMovement(tempPosition, j, i);
                                    //se guardan los datos
                                    possiblePositions = (char *)realloc(possiblePositions, (sizeof(char) * 4) * quantity);
                                    strcat(possiblePositions, tempPosition);
                                    quantity++;
                                }
                            }
                            //y/o si no se produce overflow de la columna izquierda
                            if ((j + 2) <= 7)
                            {
                                if ((boardPlay[i + 1][j + 1] == 'p' || boardPlay[i + 1][j + 1] == 'k') && boardPlay[i + 2][j + 2] == '*')
                                {
                                    returnMovement(tempPosition, j, i);
                                    //se guardan los datos
                                    possiblePositions = (char *)realloc(possiblePositions, (sizeof(char) * 4) * quantity);
                                    strcat(possiblePositions, tempPosition);
                                    quantity++;
                                }
                            }
                        }
                    }
                }

                if (turn == 0)
                {
                    //si es turno del jugador negro
                    if (boardPlay[i][j] == 'p' || boardPlay[i][j] == 'k') // se verifican que los datos de la tabla concuerden con los del turno
                    {                                                     //black player
                                                                          //si no se produce overflow
                        if ((i + 2) <= 7)
                        {
                            if (boardPlay[i][j] == 'k') // si la ficha es dama
                            {
                                //y si la columna izq. no produce overflow
                                if ((j - 2) >= 0)
                                {
                                    //se verifica si hay movimiento forzado
                                    if ((boardPlay[i + 1][j - 1] == 'P' || boardPlay[i + 1][j - 1] == 'K') && boardPlay[i + 2][j - 2] == '*')
                                    {
                                        returnMovement(tempPosition, j, i);
                                        //se guardan los datos en variable possiblePositions
                                        possiblePositions = (char *)realloc(possiblePositions, (sizeof(char) * 4) * quantity);
                                        strcat(possiblePositions, tempPosition);
                                        quantity++;
                                    }
                                }
                                //y/o si la columna derecha no produce overflow
                                if ((j + 2) <= 7)
                                {
                                    //se verifica si hay movimiento forzado
                                    if ((boardPlay[i + 1][j + 1] == 'P' || boardPlay[i + 1][j + 1] == 'K') && boardPlay[i + 2][j + 2] == '*')
                                    {
                                        returnMovement(tempPosition, j, i);
                                        //se guardan los datos en variable possiblePositions
                                        possiblePositions = (char *)realloc(possiblePositions, (sizeof(char) * 4) * quantity);
                                        strcat(possiblePositions, tempPosition);
                                        quantity++;
                                    }
                                }
                            }
                        }
                        // si no hay overflow de fila
                        if ((i - 2) >= 0)
                        {
                            //y si no hay overflow de columna iz.
                            if ((j - 2) >= 0)
                            {
                                //se verifica si hay movimiento forzado
                                if ((boardPlay[i - 1][j - 1] == 'P' || boardPlay[i - 1][j - 1] == 'K') && boardPlay[i - 2][j - 2] == '*')
                                {
                                    returnMovement(tempPosition, j, i);
                                    //se guardan los datos
                                    possiblePositions = (char *)realloc(possiblePositions, (sizeof(char) * 4) * quantity);
                                    strcat(possiblePositions, tempPosition);

                                    quantity++;
                                }
                            }
                            //y /o si no hay overflow de columna derecha
                            if ((j + 2) <= 7)
                            {
                                //se verifica si hay movimiento forzado
                                if ((boardPlay[i - 1][j + 1] == 'P' || boardPlay[i - 1][j + 1] == 'K') && boardPlay[i - 2][j + 2] == '*')
                                {
                                    returnMovement(tempPosition, j, i);
                                    //se guardan los datos
                                    possiblePositions = (char *)realloc(possiblePositions, (sizeof(char) * 4) * quantity);
                                    strcat(possiblePositions, tempPosition);
                                    quantity++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //se muestran las posibles posiciones forzadas
    printf("Possible Force positions %s\n", possiblePositions);
    return possiblePositions;
}

/**
 * Name: coordinates
 * Funtion: es la funcion que determina las coordenadas para realizar el movimiento
 * return: (int) retorna 1 como confirmacion de datos
*/
int coordinates(char *firstPosition, char *lastPosition, char **board, int *x, int *y, player *checkPiece)
{
    // se cambian los datos character a numero de las filas y columnas respectivamente
    int firstRow = abs((firstPosition[1] - '0') - 8), lastRow = abs((lastPosition[1] - '0') - 8);
    int columnFirst = letterToPosition(firstPosition[0]) - 1, columnLast = letterToPosition(lastPosition[0]) - 1;
    //se inicializan las variables x, y (que en el main son las variables column y row)
    *x = 0;
    *y = 0;
    //se determinan las coodernadas dependiendo de la posicion de ambos movimientos
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

/**
 * Name: move
 * Funtion: es la funcion que realiza el movimiento de las piezas
 *          Tambien verifica si hay pieza para comer
 * return: (int) retorna la variable eaten que tiene la candidad de fichas comidas
*/
int move(int column, int row, char *firstPosition, char *lastPosition, char ***board, player *p1)
{
    // se cambian los datos de posiciones a numeros
    int firstRow = abs((firstPosition[1] - '0') - 8), lastRow = abs((lastPosition[1] - '0') - 8);
    int columnFirst = letterToPosition(firstPosition[0]) - 1, columnLast = letterToPosition(lastPosition[0]) - 1;
    int eaten = 0;
    //se guarda el valor de la primera posicion en varible temporal
    char temp = *(*(*board + firstRow) + columnFirst);

    //si la siguiente posicion no es un espacio
    if (*(*(*board + (firstRow + row)) + (columnFirst + column)) != '*')
    {
        //modifica la posicion a espacio en negro
        *(*(*board + (firstRow + row)) + (columnFirst + column)) = '*';
        //ingrementa el valor de piezas comidas y de posiciones
        eaten++;
        row += row;
        column += column;
    }
    //si la ultima fila es 0 o 7
    if (lastRow == 0 || lastRow == 7)
    {
        //se cambia a la reyna de respectiva ficha
        if (temp == p1[0].pawn)
        {
            temp = p1[0].king;
        }
        else
        {
            temp = p1[1].king;
        }
    }
    //se intercambian los valores de la posicion final e inicial
    *(*(*board + (firstRow + row)) + (columnFirst + column)) = temp;
    *(*(*board + firstRow) + columnFirst) = '*';
    return eaten;
}

/**
 * Name: possibleMoves
 * Funtion: es la funcion que se encarga de ver los movimientos posibles de una ficha
 * return: (char*) retorna los posibles movimientos de la primera posicion
*/
char *possibleMoves(char *firstPosition, char **boardPlay)
{
    // se convierten los valores de fil y columna a numeros
    int row = abs((firstPosition[1] - '0') - 8);
    int column = letterToPosition(firstPosition[0]) - 1, quantity = 1;
    //se reserva memoria para las posibles posiciones
    char *possiblePositions = (char *)malloc(sizeof(char) * 4), tempPosition[4];
    strcpy(possiblePositions, "\0");
    //si la posicion es igual al jugador blanco o si es igual a una dama
    if (boardPlay[row][column] == 'P' || boardPlay[row][column] == 'K' || boardPlay[row][column] == 'k')
    {                       //white player
        if ((row + 1) <= 7) //se verifica de que no haya overflow
        {
            if ((column - 1) >= 0) //se verifica de que no haya overflow de columna izquierda
            {
                //si no hay overflow, se revisa de que la columna este vacia
                if (boardPlay[row + 1][column - 1] == '*')
                {
                    // si lo esta
                    returnMovement(tempPosition, column - 1, row + 1);
                    //se incrementa memoria y se guarda en la variable possiblePositions
                    possiblePositions = (char *)realloc(possiblePositions, (sizeof(char) * 4) * quantity);
                    strcat(possiblePositions, tempPosition);
                    quantity++;
                }
            }
            //se verifica de que no haya overflow de columna derecha
            if ((column + 1) <= 7)
            {
                //si no hay overflow, se revisa de que la columna este vacia
                if (boardPlay[row + 1][column + 1] == '*')
                {
                    // si lo esta
                    returnMovement(tempPosition, column + 1, row + 1);
                    //se incrementa memoria y se guarda en la variable possiblePositions
                    possiblePositions = (char *)realloc(possiblePositions, (sizeof(char) * 4) * quantity);
                    strcat(possiblePositions, tempPosition);
                    quantity++;
                }
            }
        }
    }

    if (boardPlay[row][column] == 'p' || boardPlay[row][column] == 'K' || boardPlay[row][column] == 'k')
    { //black player
        //se verifica de que no haya overflow
        if ((row - 1) >= 0)
        {
            //se verifica de que no haya overflow de columna izquierda
            if ((column - 1) >= 0)
            {
                //si no hay overflow, se revisa de que la columna este vacia
                if (boardPlay[row - 1][column - 1] == '*')
                {
                    // si lo esta
                    returnMovement(tempPosition, column - 1, row - 1);
                    //se incrementa memoria y se guarda en la variable possiblePositions
                    possiblePositions = (char *)realloc(possiblePositions, (sizeof(char) * 4) * quantity);
                    strcat(possiblePositions, tempPosition);
                    quantity++;
                }
            }
            //se verifica de que no haya overflow de columna derecha
            if ((column + 1) <= 7)
            {
                //si no hay overflow, se revisa de que la columna este vacia
                if (boardPlay[row - 1][column + 1] == '*')
                {
                    // si lo esta
                    returnMovement(tempPosition, column + 1, row - 1);
                    //se incrementa memoria y se guarda en la variable possiblePositions
                    possiblePositions = (char *)realloc(possiblePositions, (sizeof(char) * 4) * quantity);
                    strcat(possiblePositions, tempPosition);
                    quantity++;
                }
            }
        }
    }
    //se muestran y  retornan datos de possiblesMovimientos
    printf("Possible positions %s\n", possiblePositions);
    return possiblePositions;
}

/**
 * Name: returnMovement
 * Funtion: es la funcion que guarda el dato de columna y fila modificados
 * return: (sin retorno)
*/
void returnMovement(char *tempPosition, int column, int row)
{
    tempPosition[0] = positionToLetter(column); //cambia la columna a letra
    tempPosition[1] = abs((row - 8)) + '0';
    tempPosition[2] = ' ';
    tempPosition[3] = '\0';
}