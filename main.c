#include <stdio.h>
#include <unistd.h>
#include <time.h>

int win_coords[2] = {0, 0};

void complex_array_print (char x[13][31]){
    for (int i = 0; i < 13; i++){
        for(int k = 0; k < 31; k++)
            printf("%c", x[i][k]);
        printf("\n");
    }
}

void timer(double n){
    double start = clock();
    while(clock() < start + (n * 1000.0)){}
}

int win_check(int board[12][10]){
    int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
    for (int y = 8; y > 2; y--){
        for (int x = 0; x < 7; x++){
            c1 = board[y][x], c2 = board[y][x], c3 = board[y][x], c4 = board[y][x];
            for (int i = 1; i < 4; i++){
                if (board[y][x] == 0)
                    break;
                c1 = board[y - i][x] + c1;
                c2 = board[y][x + i] + c2;
                c3 = board[y - i][x + i] + c3;
                c4 = board[y + i][x + i] + c4;
                if ((c1 == 4)||(c1 == -4) || (c2 == 4)||(c2 == -4) || (c3 == 4)||(c3 == -4) || (c4 == 4)||(c4 == -4))
                    win_coords[0] = x, win_coords[1] = y;
                if ((c1 == 4) || (c1 == -4))
                    return 1;
                else if ((c2 == 4) || (c2 == -4))
                    return 2;
                else if ((c3 == 4) || (c3 == -4))
                    return 3;
                else if ((c4 == 4) || (c4 == -4))
                    return 4;
            }
        }
    }
    return 0;
}

int main(){
    int c_counter[7] = {0, 0, 0, 0, 0, 0, 0};
    int player_turn=0, choice1=0, choice2 = 0, tie = 0, no_error = 1;
    char name1[15], name2[15], flash[13][31];

    int virtual[12][10] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

                           {0, 0, 0, 0, 0, 0, 0,  0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0,  0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0,  0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0,  0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0,  0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0,  0, 0, 0},

                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    char board[13][31] = {"| 1 | 2 | 3 | 4 | 5 | 6 | 7 |",
                          "|   |   |   |   |   |   |   |",
                          "|---|---|---|---|---|---|---|",
                          "|   |   |   |   |   |   |   |",
                          "|---|---|---|---|---|---|---|",
                          "|   |   |   |   |   |   |   |",
                          "|---|---|---|---|---|---|---|",
                          "|   |   |   |   |   |   |   |",
                          "|---|---|---|---|---|---|---|",
                          "|   |   |   |   |   |   |   |",
                          "|---|---|---|---|---|---|---|",
                          "|   |   |   |   |   |   |   |",
                          " --- --- --- --- --- --- --- "};

    printf("Welcome to Connect Four!\n\n");
    printf("Enter player 1 name: ");
    scanf("%s", name1);
    printf("\nEnter player 2 name: ");
    scanf("%s", name2);
    system("cls");

    while (1){
        //vcomplex_array_print(virtual, sizeof(virtual));
        complex_array_print(board);
        if (player_turn){
            printf("\n%s's column selection: ", name2);
            no_error = scanf("%d", &choice2);
            if ((6 - c_counter[choice2 - 1] > 0) && (choice2 > 0) && (choice2 <8) && (no_error == 1)){
                board[11 - (2 * c_counter[choice2 - 1])][(choice2 - 1) * 4 + 2] = 'X';
                virtual[8 - c_counter[choice2 - 1]][choice2 - 1] = 1;
                c_counter[choice2 - 1]++;
                tie++;
                if (win_check(virtual))
                    break;
                player_turn = 0;
            }
            else {
                getchar();
                printf("\nInvalid column selection. Please try again.\n");
                timer(0.7);
            }
        }
        else {
            printf("\n%s's column selection: ", name1);
            no_error = scanf("%d", &choice1);
            if ((6 - c_counter[choice1 - 1] > 0) && (choice1 > 0) && (choice1 <8) && (no_error == 1)){
                board[11 - (2 * c_counter[choice1 - 1])][(choice1 - 1) * 4 + 2] = 'O';
                virtual[8 - c_counter[choice1 - 1]][choice1 - 1] = -1;
                c_counter[choice1 - 1]++;
                tie++;
                if (win_check(virtual))
                    break;
                player_turn = 1;
            }
            else {
                getchar();
                printf("\nInvalid column selection. Please try again.\n");
                timer(0.7);
            }
        }
        if (tie == 42)
            break;
        system("cls");
    }

    memcpy(flash, board, sizeof(flash));
    switch(win_check(virtual)){
    case 0:
        break;
    case 1:
        for (int i = 0; i < 4; i++){
            flash[(2 * (win_coords[1] - i)) - 5][(win_coords[0] * 4) + 2] = ' ';
        }
        break;
    case 2:
        for (int i = 0; i < 4; i++){
            flash[(2 * win_coords[1]) - 5][((win_coords[0] + i) * 4) + 2] = ' ';
        }
        break;
    case 3:
        for (int i = 0; i < 4; i++){
            flash[(2 * (win_coords[1] - i)) - 5][((win_coords[0] + i) * 4) + 2] = ' ';
        }
        break;
    case 4:
        for (int i = 0; i < 4; i++){
            flash[(2 * (win_coords[1] + i)) - 5][((win_coords[0] + i) * 4) + 2] = ' ';
        }
        break;
    default:
        break;
    }
    if (win_check(virtual)){
        for (int i = 0; i < 10; i ++){
            system("cls");
            if (i % 2){
                complex_array_print(board);
                if (player_turn)
                    printf("\nGame over. %s is the winner.\n\n", name2);
                else
                    printf("\nGame over. %s is the winner.\n\n", name1);
                timer(0.7);
            }
            else {
                complex_array_print(flash);
                if (player_turn)
                    printf("\nGame over. %s is the winner.\n\n", name2);
                else
                    printf("\nGame over. %s is the winner.\n\n", name1);
                timer(0.3);
            }
        }
    }
    else {
        system("cls");
        complex_array_print(board);
        printf("Board is filled. Tie game.\n\n");
    }
    printf("Thanks for playing!\n\n");
    //vcomplex_array_print(virtual, sizeof(virtual));
    return 0;
}




//void vsimple_array_print (int x[], int array_size){
//    printf("{%d", x[0]);
//    for(int loop = 1; loop < (int) array_size / (int) sizeof(x[0]); loop++){
//        printf(", %d", x[loop]);
//    }
//    printf("}\n");
//}

//void vcomplex_array_print (int x[][10], int array_size){
//    for (int i = 0; i < array_size / (int) sizeof(x[0]); i++){
//        vsimple_array_print(x[i], sizeof(x[i]));
//    }
//}
