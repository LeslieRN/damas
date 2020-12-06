#include <stdlib.h>
#include <stdio.h>
#include "funciones.c"
#include <string.h>
#include "boardUser.c"
#include "winner.c"
#include "file.c"
int main()
{
    /**
     * Variables char funciones:
     * boardMain -> obtiene el espacio reservado para el tablero
     * boardDisplay -> obtiene el tablero con sus fichas
     * record -> archivo de guardar jugadores
     * moves -> archivo de movimientos
     * tempPlay -> guarda cada movimiento durante la partida 
     * continuePlay -> se encarga de obtener el resultado se si el usuario quiere volver a jugar o no
    */
    char **boardMain, **boardDisplay, *record = "playRecord.txt", *moves = "movesRecord.txt", *tempPlay, continuePlay;
    /**
     * Variables in funciones:
     * turn -> turno del jugador
     * column & row -> columna y fila de movimientos
     * numberPlay -> cantidad de veces jugadas
     * option -> opcion del usuario en el menu principal
     * numberGames -> cantidad de partidad
     * tie -> guarda los empates
     * eaten -> guarda las fichas comidad
     * playerChoice -> una mez iniciado el juego, esta guarda las opciones del usuario (jugar, rendirse o pedir tablas)
     * numberCurrent y numberNuew -> guarda el numero de las 
     */
    int turn = 0, column = 0, row = 0, numberPlay = 0, option = 0, numberGames = 0, tie = 0, eaten = 0, playerChoice;

        do
    {
        option = mainMenu(); //opciones del menu
        if (option == 1)     // si es la opcion 1 (jugar)
        {
            //se piden los datos de los jugadores
            player *p1 = fillPlayerData();
            //se guardan las posiciones de blanco y negro, se reverva memoria para la tabla y se guarda en la variable boardDisplay
            boardPositions *position = secondBoard();
            boardMain = boardSpace();
            boardDisplay = fillBoard(boardMain, p1);

            do
            {
                gameHistory game;                        //se inicializa una variable game, donde se registraran los movimientos
                tempPlay = (char *)malloc(sizeof(char)); // se reserva memoria para la variable que obtendrá temporalmente los movimientos
                strcpy(tempPlay, "\0");
                strcpy(game.name, p1[0].name);
                strcat(game.name, p1[1].name);
                strcat(game.name, "\0");
                do
                {
                    numberPlay++; //se incrementa el numero de jugadas

                    fflush(stdin);
                    displayBoard(boardDisplay);      //se muestra el tablero
                    char *letterCurrent, *letterNew; //variables que guardan la primera posicion y la posicion a la que el usuario quiere ir
                    //presentancion de los datos del turno del jugador
                    printf("Turn # %d Player: %s Color: %s\n", turn + 1, p1[turn].name, p1[turn].color);
                    //opciones
                    printf("1) Play 2) Give up 3) Ask for table\n");
                    scanf("%d", &playerChoice);
                    switch (playerChoice)
                    {
                    case 1:
                        //si la opcion es 1
                        //se revisan los movimientos
                        checkIfLegalMovement(&letterCurrent, &letterNew, position, boardDisplay, turn, p1);
                        //se calculan las coordenadas a la cual se va a mover
                        coordinates(letterCurrent, letterNew, boardDisplay, &column, &row, p1);
                        //se realiza el movimiento y se guarda en la varible eaten las fichas que se haya comido
                        eaten = move(column, row, letterCurrent, letterNew, &boardDisplay, p1);
                        //se cambia de jugador
                        changePlayer(&turn);
                        //se decrementa la cantidad de piezas
                        p1[turn].pawnQuantity -= eaten;
                        //se vuelve al jugador original
                        changePlayer(&turn);
                        //se reserva memoria para guardar los movimientos en la variable tempPlay
                        tempPlay = (char *)realloc(tempPlay, (sizeof(char) * 14) * numberPlay);
                        //se concatenan los movimientos con el color del jugador que lo realizo
                        strcat(tempPlay, p1[turn].color);
                        strcat(tempPlay, " ");
                        strcat(tempPlay, letterCurrent);
                        strcat(tempPlay, " ");
                        strcat(tempPlay, letterNew);
                        strcat(tempPlay, "\0");
                        strcat(tempPlay, "\n");
                        break;
                    case 2:
                        //si la opcion es 2
                        printf("Sorry you want to leave :(\n");
                        //se cambia de jugador
                        changePlayer(&turn);
                        // se incrementa la cantidad de partidas ganadas del jugador actual (el que no se rindio)
                        p1[turn].win++;
                        break;
                    case 3:
                        //si la opcion es 3
                        if (askForTable()) //se pide por empate
                        {
                            //si este es valido, se incrementa la cantidad de empates de ambos jugadores
                            p1[0].tie++;
                            p1[1].tie++;
                            //mensaje
                            printf("The game it's a tie!!!\n");
                        }
                        else
                        {
                            //si no, se vuelve al menu de jugar
                            playerChoice = 1;
                        }
                        break;
                    default:
                        printf("Incorrrect option. Try Again!!\n");
                        break;
                    }
                    //se cambia de jugador
                    changePlayer(&turn);
                    // el ciclo siempre se hara cuando la opcion que eliga el usuario sea siferente de 2 y 3 o cuando no se haya determinado un ganador
                } while (playerChoice != 2 && playerChoice != 3 && determineWinner(&p1) == 1);

                //
                strcpy(game.moves, tempPlay);
                insert_Moves(moves, game);
                //se incrementa la cantidad de partidas
                p1[0].quantityGames++;
                p1[1].quantityGames++;

                fflush(stdin);
                //se pregunta al ususario si desea continuar con otra partida
                printf("Do you want to continue playing? (y)es or (n)o\n");
                continuePlay = getchar();
                //en caso de ser cierto
                if (continuePlay == 'y')
                {
                    //se reestablecen las variables de cantidad de piezas, se vuelve a llenar el tablero y se inicia el turn en 0
                    p1[0].pawnQuantity = 12;
                    p1[1].pawnQuantity = 12;
                    boardDisplay = fillBoard(boardMain, p1);
                    turn = 0;
                }
                //se continuara haciendo lo anterior, hasta que el usuario inserte n
            } while (continuePlay == 'y');
            // se insertan los datos de la jugada
            insert_data(record, p1);
        }
        else if (option == 2)
        {
            //menu de record de jugadores
            show_file_data(record);
            printf("\n");
        }
        else if (option == 3)
        {
            //notacion algebraica
            show_history_data(moves);
            printf("\n");
        }
        else
        {
            //adios!!!
            exit(0);
        }
    } while (option != 4);
    return 0;
}