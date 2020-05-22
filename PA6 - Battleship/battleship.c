#include "battleship.h"

void welcome_screen()
{
    printf("\n*****Welcome to Battleship!*****\n\n");
    printf("Rules of the Game :\n");
    printf("1. This is a two player game.\n");
    printf("2. Player1 is you and Player2 is the computer.\n");
    printf("3. You and your opponent will alternate turns, calling out one shot per turn to try and hit each other's ships\n");
    printf("4. On your turn, choose a x,y location to target\n");
    printf("5. If you hit a spot that is occupied by your opponents ship, you have gotten a hit!\n");
    printf("6. If you do not hit a spot that is occupied by your opponents ship, you have gotten a miss.\n");
    printf("7. Once every spot of a ship has been hit, it is sunk\n");
    printf("8. Whoever has all of their ships sunk first will lose.\n");
    printf("\n\nHit enter to start the game!\n");
    getchar();
}

void continuemaybe()
{
    printf("Press enter to continue\n");
    //char enter = 0;
    //while (enter != '\r' && enter != '\n') { enter = getchar(); }
    //getchar();
    //printf("\n");
    //char
    getchar();
    while (getchar() != '\n');
}

void initialize_game_board(char board[][10], int num_rows, int num_cols)
{
    int row_index = 0, col_index = 0;

    for (; row_index < num_rows; ++row_index)
    {
        for (col_index = 0; col_index < num_cols;
            ++col_index)
        {
            board[row_index][col_index] = '~';
        }
    }
}

void display_board(char board[][10], int num_rows, int num_cols, int player1or2)
{
    int row_index = 0, col_index = 0;
    if (player1or2 == 1)
    {
        printf("  0 1 2 3 4 5 6 7 8 9\n");
        for (; row_index < num_rows; ++row_index)
        {
            printf("%d ", row_index);
            for (col_index = 0; col_index < num_cols; ++col_index)
            {
                printf("%c ", board[row_index][col_index]);
            }

            putchar('\n');
        }
    }
    if (player1or2 == 2)
    {
        printf("  0 1 2 3 4 5 6 7 8 9\n");
    for (; row_index < num_rows; ++row_index)
    {
        printf("%d ", row_index);
        for (col_index = 0; col_index < num_cols; ++col_index)
        {
            if (board[row_index][col_index] == '-' || board[row_index][col_index] == '~'
                || board[row_index][col_index] == 'm' || board[row_index][col_index] == '*')
                printf("%c ", board[row_index][col_index]);
            else
                printf("%c ", '~');
        }

        putchar('\n');
    }
    }
}

int select_who_starts_first() 
{
    int whichplayer;
    whichplayer = (rand() % (2 - 1 + 1) + 1); //for range, (max-min+1)+min;
    return whichplayer;
}

int random_or_manual()
{
    int random_or_manual;
    do {
        printf("Do you want to place your ships on the board or have them placed randomly?");
        printf("\nenter in a 1 if you want to randomly place them and a \n2 if you want to manually place them");
        scanf("%d", &random_or_manual);
    } while (random_or_manual != 1 && random_or_manual != 2);
    
    return random_or_manual;
}

int generate_dir(void)
{
    return rand() % 2;
}

void randomly_place_ships_on_board(int ship_length, char board[][10], char ship_identifier)
{
    int row_number = 0, col_number = 0, overlap = -1;
    int row_index = 0, col_index = 0, dir = -1;
    do
    {
        dir = generate_dir();
        // horizontal direction = 0
        if (dir == 0)
        {
            row_number = rand() % 10; //starting point can be anywhere between 0-9
            col_number = rand() % (10 - ship_length + 1); //starting point can be anywhere between 0-9
        }
        // vertical direction = 1
        if (dir == 1)
        {
            row_number = rand() % (10 - ship_length + 1); //(max-min+1)+min    10 - 5 = 5 + 1 = 6   5 6 7 8 9
            col_number = rand() % 10;
        }
        overlap = checkshipoverlap(row_number, col_number, ship_length, board, dir); // if overlap is 0, there is overlap, if 1 no overlap
    } while (overlap != 1);

    row_index = row_number;
    col_index = col_number;

    if (dir == 0)
    {
        for (; col_index < col_number + ship_length; ++col_index)
        {
            board[row_index][col_index] = ship_identifier; //10+10
        }
    }
    if (dir == 1)
    {
        for (; row_index < row_number + ship_length; ++row_index)
        {
            board[row_index][col_index] = ship_identifier;
        }
    }
}

void manually_place_ships_on_board(int ship_length, char board[][10], char ship_identifier, int dir, int row_number, int col_number)
{
    int overlap = -1;
    int row_index, col_index;
    dir -= 1;
    row_index = row_number;
    col_index = col_number;

    if (dir == 1)
    {
        for (; col_index < col_number + ship_length; ++col_index)
        {
            board[row_index][col_index] = ship_identifier;
        }
    }
    if (dir == 0)
    {
        for (; row_index < row_number + ship_length; ++row_index)
        {
            board[row_index][col_index] = ship_identifier;
        }
    }
    
}

int checkshipoverlap(int row_number, int col_number, int ship_length, char board[][10], int dir)
{
    int row_index = 0, col_index = 0, temp = -1,col_final, row_final;
    col_index = col_number;
    row_index = row_number;
    col_final = col_number + ship_length;
    row_final = row_number + ship_length;
    if (dir == 0)
    {
        for (; col_index < col_number + ship_length; ++col_index)
        {
            if (board[row_index][col_index] == 'c' || board[row_index][col_index] == 'b'|| board[row_index][col_index] == 'r' || board[row_index][col_index] == 's' || board[row_index][col_index] == 'd')
            {
                return 0;
            }
        }
    }
    if (dir == 1)
    {
        for (; row_index < row_number + ship_length; ++row_index)
        {
            if (board[row_index][col_index] == 'c' || board[row_index][col_index] == 'b'|| board[row_index][col_index] == 'r' || board[row_index][col_index] == 's' || board[row_index][col_index] == 'd')
            {
                return 0;
            }
        }
    }
    return 1;
}


int checkshipoverlapmanual(int row_number, int col_number, int ship_length, char board[][10], int dir)
{
    int row_index = 0, col_index = 0, temp = -1, col_final, row_final;
    col_index = col_number;
    row_index = row_number;
    col_final = col_number + ship_length;
    row_final = row_number + ship_length;
    dir = dir - 1;
    if (dir == 1)
    {
        for (; col_index < col_number + ship_length; ++col_index)
        {
            if (board[row_index][col_index] == 'c' || board[row_index][col_index] == 'b' || board[row_index][col_index] == 'r' || board[row_index][col_index] == 's' || board[row_index][col_index] == 'd')
            {
                return 0;
            }
        }
    }
    if (dir == 0)
    {
        for (; row_index < row_number + ship_length; ++row_index)
        {
            if (board[row_index][col_index] == 'c' || board[row_index][col_index] == 'b' || board[row_index][col_index] == 'r' || board[row_index][col_index] == 's' || board[row_index][col_index] == 'd')
            {
                return 0;
            }
        }
    }
    return 1;
}

void run_manual_placement(char p1_board[][10])
{
    int row_number = 0, col_number = 0;
    int dir = 0, check = 0;
    display_board(p1_board, 10, 10, 1);
    do
    {
        do
        {
            printf("Make sure the ships do not overlap \n\nEnter the direction you want to which you want to place the carrier ship \n1 for vertical \n2 for horizontal \n");
            scanf("%d", &dir);
        } while (dir < 1 || dir > 2);
        if (dir == 1)
        {
            do
            {
                printf("Enter in the starting row (0-9) you want to place the carrier (5 space long)");
                scanf("%d", &row_number);
            } while (row_number < 0 || row_number > 5);
            do
            {
                printf("Enter in the starting column (0-9) you want to place the carrier (5 space long)");
                scanf("%d", &col_number);
            } while (col_number < 0 || col_number > 9);
        }
        if (dir == 2)
        {
            do
            {
                printf("Enter in the starting row (0-9) you want to place the carrier (5 space long)");
                scanf("%d", &row_number);
            } while (row_number < 0 || row_number > 9);
            do
            {
                printf("Enter in the starting column (0-9) you want to place the carrier (5 space long)");
                scanf("%d", &col_number);
            } while (col_number < 0 || col_number > 5);
        }
        check = checkshipoverlapmanual(row_number, col_number, carrier_length, p1_board, dir);
        if (check == 0)
        {
            printf("One of your ships is overlapping, please reenter ship location\n");
        }
    } while (check != 1);
    manually_place_ships_on_board(carrier_length, p1_board, carrier_ident, dir, row_number, col_number);
    dir = 0;
    row_number = 0;
    col_number = 0;
    check = -1;
    
    display_board(p1_board, 10, 10, 1);
    do
    {
        do
        {
            printf("Make sure the ships do not overlap \n\nEnter the direction you want to which you want to place the battleship \n1 for vertical \n2 for horizontal");
            scanf("%d", &dir);
        } while (dir < 1 || dir > 2);
        if (dir == 1)
        {
            do
            {
                printf("Enter in the starting row (0-9) you want to place the battleship (4 space long)");
                scanf("%d", &row_number);
            } while (row_number < 0 || row_number > 6);
            do
            {
                printf("Enter in the starting column (0-9) you want to place the battleship (4 space long)");
                scanf("%d", &col_number);
            } while (col_number < 0 || col_number > 9);
        }
        if (dir == 2)
        {
            do
            {
                printf("Enter in the starting row (0-9) you want to place the battleship (4 space long)");
                scanf("%d", &row_number);
            } while (row_number < 0 || row_number > 9);
            do
            {
                printf("Enter in the starting column (0-9) you want to place the battleship (4 space long)");
                scanf("%d", &col_number);
            } while (col_number < 0 || col_number > 6);
        }
        check = checkshipoverlapmanual(row_number, col_number, battleship_length, p1_board, dir);
        if (check == 0)
        {
            printf("One of your ships is overlapping, please reenter ship location\n");
        }
    } while (check != 1);
    manually_place_ships_on_board(battleship_length, p1_board, battleship_ident, dir, row_number, col_number);
    dir = 0;
    row_number = 0;
    col_number = 0;
    check = -1;
   
    display_board(p1_board, 10, 10, 1);
    do
    {
        do
        {
            printf("Make sure the ships do not overlap \n\nEnter the direction you want to which you want to place the cruiser ship \n1 for vertical \n2 for horizontal");
            scanf("%d", &dir);
        } while (dir < 1 || dir > 2);
        if (dir == 1)
        {
            do
            {
                printf("Enter in the starting row (0-9) you want to place the cruiser (3 space long)");
                scanf("%d", &row_number);
            } while (row_number < 0 || row_number > 7);
            do
            {
                printf("Enter in the starting column (0-9) you want to place the cruiser (3 space long)");
                scanf("%d", &col_number);
            } while (col_number < 0 || col_number > 9);
        }
        if (dir == 2)
        {
            do
            {
                printf("Enter in the starting row (0-9) you want to place the cruiser (3 space long)");
                scanf("%d", &row_number);
            } while (row_number < 0 || row_number > 9);
            do
            {
                printf("Enter in the starting column (0-9) you want to place the cruiser (3 space long)");
                scanf("%d", &col_number);
            } while (col_number < 0 || col_number > 7);
        }        check = checkshipoverlapmanual(row_number, col_number, cruiser_length, p1_board, dir);
        if (check == 0)
        {
            printf("One of your ships is overlapping, please reenter ship location\n");
        }
    } while (check != 1);
    manually_place_ships_on_board(cruiser_length, p1_board, cruiser_ident, dir, row_number, col_number);
    dir = 0;
    row_number = 0;
    col_number = 0;
    check = -1;
    
    display_board(p1_board, 10, 10, 1);
    do
    {
        do
        {
            printf("Make sure the ships do not overlap \n\nEnter the direction you want to which you want to place the submarine \n1 for vertical \n2 for horizontal");
            scanf("%d", &dir);
        } while (dir < 1 || dir > 2);
        if (dir == 1)
        {
            do
            {
                printf("Enter in the starting row (0-9) you want to place the submarine (3 space long)");
                scanf("%d", &row_number);
            } while (row_number < 0 || row_number > 7);
            do
            {
                printf("Enter in the starting column (0-9) you want to place the submarine (3 space long)");
                scanf("%d", &col_number);
            } while (col_number < 0 || col_number > 9);
        }
        if (dir == 2)
        {
            do
            {
                printf("Enter in the starting row (0-9) you want to place the submarine (3 space long)");
                scanf("%d", &row_number);
            } while (row_number < 0 || row_number > 9);
            do
            {
                printf("Enter in the starting column (0-9) you want to place the submarine (3 space long)");
                scanf("%d", &col_number);
            } while (col_number < 0 || col_number > 7);
        }
        check = checkshipoverlapmanual(row_number, col_number, submarine_length, p1_board, dir);
        if (check == 0)
        {
            printf("One of your ships is overlapping, please reenter ship location\n");
        }
    } while (check != 1);
    manually_place_ships_on_board(submarine_length, p1_board, submarine_ident, dir, row_number, col_number);
    dir = 0;
    row_number = 0;
    col_number = 0;
    check = -1;
    
    display_board(p1_board, 10, 10, 1);
    do
    {
        do
        {
            printf("Make sure the ships do not overlap \n\nEnter the direction you want to which you want to place the destroyer \n1 for vertical \n2 for horizontal");
            scanf("%d", &dir);
        } while (dir < 1 || dir > 2);
        if (dir == 1)
        {
            do
            {
                printf("Enter in the starting row (0-9) you want to place the destroyer (2 space long)");
                scanf("%d", &row_number);
            } while (row_number < 0 || row_number > 8);
            do
            {
                printf("Enter in the starting column (0-9) you want to place the destroyer (2 space long)");
                scanf("%d", &col_number);
            } while (col_number < 0 || col_number > 9);
        }
        if (dir == 2)
        {
            do
            {
                printf("Enter in the starting row (0-9) you want to place the destroyer (2 space long)");
                scanf("%d", &row_number);
            } while (row_number < 0 || row_number > 9);
            do
            {
                printf("Enter in the starting column (0-9) you want to place the destroyer (2 space long)");
                scanf("%d", &col_number);
            } while (col_number < 0 || col_number > 8);
        }        check = checkshipoverlapmanual(row_number, col_number, destroyer_length, p1_board, dir);
        if (check == 0)
        {
            printf("One of your ships is overlapping, please reenter ship location\n");
        }
    } while (check != 1);
    manually_place_ships_on_board(destroyer_length, p1_board, destroyer_ident, dir, row_number, col_number);
    dir = 0;
    row_number = 0;
    col_number = 0;
    check = -1;
    
}

int check_shot(int row_index, int col_index, char board[][10])
{
    if (board[row_index][col_index] == 'c' || board[row_index][col_index] == 'b' || board[row_index][col_index] == 'r' || board[row_index][col_index] == 's' || board[row_index][col_index] == 'd')
    {
        return 1; // hit
    }
    if (board[row_index][col_index] == '*' || board[row_index][col_index] == 'm')
    {
        return 2; //redo
    }
    return 0; //miss
}

void update_board(int check, char board[][10], int row_number, int col_number, int com_player)
{
    if (check == 1)
    {
        if (com_player == 1)
        {
            printf("You have hit a ship!");
        }
        board[row_number][col_number] = '*';
    }
    if (check == 0)
    {
        if (com_player == 1)
        {
            printf("You have missed");
        }
        board[row_number][col_number] = 'm';
    }
}

void shoot_your_shot(int* row_number, int* col_number, char board[][10])
{
    int column_num, rowr_number;
    do
    {
        printf("What row do you want to make your next shot in?");
        scanf("%d", &rowr_number);
    } while (rowr_number < 0 && rowr_number > 9);
    *row_number = rowr_number;
    do
    {
        printf("What column do you want to make your next shot in?");
        scanf("%d", &column_num);
    } while (column_num < 0 && column_num > 9);
    *col_number = column_num;
}

void computer_shoot_your_shot(int* row_number, int* col_number, char board[][10])
{
    *row_number = rand() % 10;
    *col_number = rand() % 10;
}

int is_winner(int carrier_hit_count1, int battleship_hit_count1, int cruiser_hit_count1, int submarine_hit_count1, int destroyer_hit_count1, int carrier_hit_count2, int battleship_hit_count2, int cruiser_hit_count2, int submarine_hit_count2, int destroyer_hit_count2) //determines if a winner exists
{
    if (carrier_hit_count1 == 5 && battleship_hit_count1 == 4 && cruiser_hit_count1 == 3 && submarine_hit_count1 == 3 && destroyer_hit_count1 == 2)
    {
        return 1;
    }
    if (carrier_hit_count2 == 5 && battleship_hit_count2 == 4 && cruiser_hit_count2 == 3 && submarine_hit_count2 == 3 && destroyer_hit_count2 == 2)
    {
        return 2;
    }
    return -1;
}

void update_count(char board[][10], int row_number, int col_number, int* carrier_hit_count, int* battleship_hit_count, int* cruiser_hit_count, int* submarine_hit_count, int* destroyer_hit_count)
{
    if (board[row_number][col_number] == 'c')
    {
        *carrier_hit_count += 1;
    }
    else if (board[row_number][col_number] == 'b')
    {
        *battleship_hit_count += 1;
    }
    else if (board[row_number][col_number] == 'r')
    {
        *cruiser_hit_count += 1;
    }
    else if (board[row_number][col_number] == 's')
    {
        *submarine_hit_count += 1;
    }
    else if (board[row_number][col_number] == 'd')
    {
        *destroyer_hit_count += 1;
    }
}

void check_if_sunk_ship(int carrier_hit_count, int battleship_hit_count, int cruiser_hit_count, int submarine_hit_count, int destroyer_hit_count, int* carriercheck, int* battleshipcheck, int* cruisercheck, int* submarinecheck, int* destroyercheck) //determines if a ship was sunk
{
    if (carrier_hit_count == 5)
    {
        if (*carriercheck == 0)
        {
            printf("You have sunk the carrier\n");
            *carriercheck = 1;
        }
    }
    if (battleship_hit_count == 4)
    {
        if (*battleshipcheck == 0)
        {
            printf("You have sunk the battleship\n");
            *battleshipcheck = 1;
        }
    }
    if (cruiser_hit_count == 3)
    {
        if (*cruisercheck == 0)
        {
            printf("You have sunk the cruiser\n");
            *cruisercheck = 1;
        }
    }
    if (submarine_hit_count == 3)
    {
        if (*submarinecheck == 0)
        {
            printf("You have sunk the submarine\n");
            *submarinecheck = 1;
        }
    }
    if (destroyer_hit_count == 2)
    {
        if (*destroyercheck == 0)
        {
            printf("You have sunk the destroyer\n");
            *destroyercheck = 1;
        }
    }
}

void output_current_move(int row_number, int col_number, int player, int checkhitmiss, FILE* outfile)
{
    //1 hit //0 miss
    //fprintf(outfile, "test");
    //fclose(outfile);
    if (player == 1)
    {
        if (checkhitmiss == 1)
        {
            fprintf(outfile, "Player 1: %d, %d hit\n", col_number, row_number);
        }
        if (checkhitmiss == 0)
        {
            fprintf(outfile, "Player 1: %d, %d miss\n", col_number, row_number);
        }
    }
    if (player == 2)
    {
        if (checkhitmiss == 1)
        {
            fprintf(outfile, "Player 2: %d, %d hit\n", col_number, row_number);
        }
        if (checkhitmiss == 0)
        {
            fprintf(outfile, "Player 2: %d, %d miss\n", col_number, row_number);
        }
    }
}

void output_stats(int hits1, int hits2, int misses1, int misses2, int shots1, int shots2, FILE* outfile)
{
    int ratio1, ratio2;
    ratio1 = hits1 / misses1;
    ratio2 = hits2 / misses2;
    fprintf(outfile, "\n*** Player1 Stats ***\n");
    fprintf(outfile, "Number Hits: %d\n", hits1);
    fprintf(outfile, "Number Misses: %d\n", misses1);
    fprintf(outfile, "Total Shots: %d\n", hits1 + misses1);
    fprintf(outfile, "Hit/Miss Ratio: %d %%\n", ratio1);
    fprintf(outfile, "*** Player2 Stats ***\n");
    fprintf(outfile, "Number Hits: %d\n", hits2);
    fprintf(outfile, "Number Misses: %d\n", misses2);
    fprintf(outfile, "Total Shots: %d\n", hits2 + misses2);
    fprintf(outfile, "Hit/Miss Ratio: %d %%\n", ratio2);
}

//void test(FILE* outfile)
//{
//    fprintf(outfile, "\n*** Player1 Stats ***\n");
//}