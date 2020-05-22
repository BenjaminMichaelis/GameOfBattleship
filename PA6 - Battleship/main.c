//Programmer: Benjamin Michaelis
//Description: This is the game of battleship run in the windows console

#include "battleship.h"

//Opens an output file battleship.log for writing;
//o   Simulates the game of Battleship
//o   Outputs data to logfile
//o   Outputs stats to logfile
//o   Closes logfile

int main(void)
{
    FILE* outfile = NULL;

    outfile = fopen("battleship.log", "w");
    srand((unsigned int)time(NULL)); //prepare for random number generated

    //test(outfile);
    //fclose(outfile); // test writing to file function

    char p1_board[10][10], p2_board[10][10];
    int whosturn, random_or_manual_result;
    //continuemaybe();

    welcome_screen();

    whosturn = select_who_starts_first();
    initialize_game_board(p1_board, 10, 10); //initialize all cells as '~'
    initialize_game_board(p2_board, 10, 10); //initialize all cells as '~'
    random_or_manual_result = random_or_manual();
    display_board(p1_board, 10, 10, 1);
    

    if (random_or_manual_result == 1) //random placement of ships
    {
        //p1board
        //dir = generate_dir();
        system("cls"); //clear screen
        randomly_place_ships_on_board(carrier_length, p1_board, carrier_ident);
        randomly_place_ships_on_board(battleship_length, p1_board, battleship_ident);
        randomly_place_ships_on_board(cruiser_length, p1_board, cruiser_ident);
        randomly_place_ships_on_board(submarine_length, p1_board, submarine_ident);
        randomly_place_ships_on_board(destroyer_length, p1_board, destroyer_ident);
        //p2board
        randomly_place_ships_on_board(carrier_length, p2_board, carrier_ident);
        randomly_place_ships_on_board(battleship_length, p2_board, battleship_ident);
        randomly_place_ships_on_board(cruiser_length, p2_board, cruiser_ident);
        randomly_place_ships_on_board(submarine_length, p2_board, submarine_ident);
        randomly_place_ships_on_board(destroyer_length, p2_board, destroyer_ident);
        system("cls"); //clear screen
    }
    if (random_or_manual_result == 2) // manual place
    {
        //p1board - manual
        run_manual_placement(p1_board);
        //p2board - randomly
        randomly_place_ships_on_board(carrier_length, p2_board, carrier_ident);
        randomly_place_ships_on_board(battleship_length, p2_board, battleship_ident);
        randomly_place_ships_on_board(cruiser_length, p2_board, cruiser_ident);
        randomly_place_ships_on_board(submarine_length, p2_board, submarine_ident);
        randomly_place_ships_on_board(destroyer_length, p2_board, destroyer_ident);
        system("cls"); //clear screen
    }
    //display_board(p1_board, 10, 10, 1);
    //continuemaybe();
    //system("cls"); //clear screen
    
    int row_number = 0, col_number = 0, check = -5, winner = -1;
    int carrier_hit_count1 = 0, battleship_hit_count1 = 0, cruiser_hit_count1 = 0, submarine_hit_count1 = 0, destroyer_hit_count1 = 0;
    int carrier_hit_count2 = 0, battleship_hit_count2 = 0, cruiser_hit_count2 = 0, submarine_hit_count2 = 0, destroyer_hit_count2 = 0;
    int hits1 = 0, misses1 = 0, hits2 = 0, misses2 = 0;
    int shots1 = 0, shots2 = 0;
    int carriercheck = 0, battleshipcheck = 0, cruisercheck = 0, submarinecheck = 0, destroyercheck = 0;

    do
    {
        do
        {
            continuemaybe();
            system("cls"); //clear screen
            display_board(p2_board, 10, 10, 2);
            shoot_your_shot(&row_number, &col_number, p2_board);
            check = check_shot(row_number, col_number, p2_board);
        } while (check == 2);
        if (check == 1) // hit
        {
            hits1++;
        }
        if (check == 0) // miss
        {
            misses1++;
        }
        output_current_move(row_number, col_number, 1, check, outfile);
        update_count(p2_board, row_number, col_number, &carrier_hit_count1, &battleship_hit_count1, &cruiser_hit_count1, &submarine_hit_count1, &destroyer_hit_count1);
        update_board(check, p2_board, row_number, col_number, 1);
        check_if_sunk_ship(carrier_hit_count1, battleship_hit_count1, cruiser_hit_count1, submarine_hit_count1, destroyer_hit_count1, &carriercheck, &battleshipcheck, &cruisercheck, &submarinecheck, &destroyercheck);
        shots1++;
        check = -1;
        do
        {
        computer_shoot_your_shot(&row_number, &col_number, p1_board);
        check = check_shot(row_number, col_number, p1_board);
        } while (check == 2);
        output_current_move(row_number, col_number, 2, check, outfile);
        update_count(p1_board, row_number, col_number, &carrier_hit_count2, &battleship_hit_count2, &cruiser_hit_count2, &submarine_hit_count2, &destroyer_hit_count2);
        update_board(check, p1_board, row_number, col_number, 2);
        if (check == 1) // hit
        {
            hits2++;
        }
        if (check == 0) // miss
        {
            misses2++;
        }
        shots2++;
        check = -1;
        /*display_board(p2_board, 10, 10, 1);
        display_board(p1_board, 10, 10, 1);*/
        winner = is_winner(carrier_hit_count1, battleship_hit_count1, cruiser_hit_count1, submarine_hit_count1, destroyer_hit_count1, carrier_hit_count2, battleship_hit_count2, cruiser_hit_count2, submarine_hit_count2, destroyer_hit_count2);
        
    } while (winner == -1);
    if (winner == 1)
    {
        printf("Player1 Wins, Player2 loses\n");
    }
    if (winner == 2)
    {
        printf("Player2 Wins, Player1 Wins\n");
    }
    
    output_stats(hits1, hits2, misses1, misses2, shots1, shots2, outfile);

    fclose(outfile);

    printf("\nThanks for playing!\n\n");

    return 0;
}