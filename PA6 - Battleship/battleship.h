#pragma warning (disable: 6031)
#ifndef LOOPS_H // guard code
#define LOOPS_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>


#define carrier_length 5
#define battleship_length 4
#define cruiser_length 3
#define submarine_length 3
#define destroyer_length 2
#define carrier_ident 'c'
#define battleship_ident 'b'
#define cruiser_ident 'r'
#define submarine_ident 's'
#define destroyer_ident 'd'

//void test(FILE* outfile);
void welcome_screen(); //displays an initial program welcome message along with the rules of Battleship.
void initialize_game_board(char board[][10], int num_rows, int num_cols); //sets each cell in a game board to '-'.
int select_who_starts_first(); //determines if Player1 or Player2 goes first in the game.
int random_or_manual();
void manually_place_ships_on_board(int ship_length, char board[][10], char ship_identifier, int dir, int row_number, int col_number); //allows the user to place each of the 5 types of ships on his/her game board.
void randomly_place_ships_on_board(int ship_length, char board[][10], char ship_identifier); //randomly places the 5 types of ships on a given board
int generate_dir(void); // generates random 1 or 2 for vertical or horiz direction
int checkshipoverlap(int row_number, int col_number, int ship_length, char board[][10], int dir);
int checkshipoverlapmanual(int row_number, int col_number, int ship_length, char board[][10], int dir);
void run_manual_placement(char p1_board[][10]);
int check_shot(int row_index, int col_index, char board[][10]); //determines if the shot taken was a hit or a miss
int is_winner(int carrier_hit_count1,int battleship_hit_count1,int cruiser_hit_count1,int submarine_hit_count1,int destroyer_hit_count1,int carrier_hit_count2,int battleship_hit_count2,int cruiser_hit_count2,int submarine_hit_count2,int destroyer_hit_count2); //determines if a winner exists
void update_count(char board[][10], int row_number, int col_number, int* carrier_hit_count, int* battleship_hit_count, int* cruiser_hit_count, int* submarine_hit_count, int* destroyer_hit_count);
void update_board(int check, char board[][10], int row_number, int col_number, int com_player); //updates the board every time a shot is taken. '*' indicates a hit and 'm' indicates a miss
void shoot_your_shot(int* row_number, int* col_number, char board[][10]);
void computer_shoot_your_shot(int* row_number, int* col_number, char board[][10]);
void display_board(char board[][10], int num_rows, int num_cols, int player1or2); //displays a board to the screen. Note that Player1's board should be displayed differently than Player2's board (see above).
//                //Hint: pass in a flag(int) that stores whether or not you just passed in Player1's or Player2's board.Then perform the different logic for Player1's board versus Player2's board.
void output_current_move(int row_number,int col_number,int player,int checkhitmiss,FILE* outfile); //writes the position of the shot taken by the current player to the log file. It also writes whether or not it was a hit, miss, and if the ship was sunk.
void check_if_sunk_ship(int carrier_hit_count, int battleship_hit_count, int cruiser_hit_count, int submarine_hit_count, int destroyer_hit_count, int* carriercheck, int* battleshipcheck, int* cruisercheck, int* submarinecheck, int* destroyercheck); //determines if a ship was sunk
void output_stats(int hits1,int hits2,int misses1,int misses2,int shots1,int shots2,FILE* outfile); //writes the statistics collected on each player to the log file
void continuemaybe();





#endif