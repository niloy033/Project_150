
#include <stdio.h>
#include <windows.h>/// Windows API is used for console manipulation
#include <conio.h>

#define H 20
#define W 40      ///character space

int ball_X, ball_Y;
int PlayerY, ComputerY;
int ball_Dir_X, ball_Dir_Y;
int PlayerScore, ComputerScore;
int GAMEOVER;

void setup() {              ///Initializes game variables, placing the ball and paddles at the center, setting initial directions, and resetting scores
    GAMEOVER = 0;
    ball_X = W / 2;
    ball_Y = H / 2;
    ball_Dir_X = -1;         ///starting from left in x axis
    ball_Dir_Y = 1;          ///    "      "   downward in the y aixis    [positive value along the Y-axis indicates movement downward.]
    PlayerY = H / 2;
    ComputerY = H / 2;
    PlayerScore = 0;
    ComputerScore = 0;
}

void draw() {        /// draws the game board and other things like ball,paddle
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);  ///to set the cursor position in the console window /// (GetStdHandle)to retrieve the standard output handle for the console
    for (int i = 0; i < W + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (j == 0 || j == W - 1)
                printf("#");
            else if (j == ball_X && i == ball_Y)
                printf("o");
            else if (j == W - 2 && i >= ComputerY - 2 && i <= ComputerY + 2)
                printf("|");
            else if (j == 1 && i >= PlayerY - 2 && i <= PlayerY + 2)
                printf("|");
            else
                printf(" ");
        }
        printf("\n");
    }

    for (int i = 0; i < W + 2; i++)
        printf("#");
    printf("\n");
    printf("Player: %d\tComputer: %d\n", PlayerScore, ComputerScore);
}

void input() {
    if (_kbhit()) {
        char key = _getch();
        if (key == 'w' && PlayerY > 3)   ///playerY is the vertical position of the paddle [ 3 means the first '|' is in the 3rd row]
            /// If playerY is already less than or equal to 3, it means the paddle is close to the top of the screen
            /// or has reached the top, and further pressing the 'w' key won't move it any further up
            PlayerY--;
        else if (key == 's' && PlayerY < H - 4)   ///ensures that the player's paddle doesn't go too far down on the screen
            PlayerY++;
        else if (key == 'x')
            GAMEOVER = 1;
    }
}

void logic() {
    if (ball_Y == 0 || ball_Y == H - 1)     ///Vertical Direction
        ball_Dir_Y = -ball_Dir_Y;           ///If ball hits the top or bottom, ball_Dir_Y is negated


        /// horizontal direction(after hitting the paddle )
    if (ball_X == W - 2 && (ball_Y >= ComputerY - 2 && ball_Y <= ComputerY + 2))  ///if it is in the right boundary and in the vertical range of the comp.paddle
        ball_Dir_X = -ball_Dir_X;
    else if (ball_X == 1 && (ball_Y >= PlayerY - 2 && ball_Y <= PlayerY + 2))     ///if it is in the left boundary and in the vertical range of the player.paddle
        ball_Dir_X = -ball_Dir_X;
    else if (ball_X == W - 1) {      /// ball crosses the right bar means player got a point:reinit the values
        PlayerScore++;
        ball_X = W / 2;
        ball_Y = H / 2;
        ball_Dir_X = -ball_Dir_X;
    } else if (ball_X == 0) {           /// ball crosses the left bar means comp. got a point:reinit the values
        ComputerScore++;
        ball_X = W / 2;
        ball_Y = H / 2;
        ball_Dir_X = -ball_Dir_X;
    }

    ball_X += ball_Dir_X;
    ball_Y += ball_Dir_Y;       ///these 2 lins update the position of the ball based on its current direction.


    /// ballY> means ball is under the comp.paddle , compY is +++ to move down
    ///vice versa

    ///#main
    if (ball_Y > ComputerY)
        ComputerY++;
    else if (ball_Y < ComputerY)
        ComputerY--;    ///   player paddle has a range but in this case we didnt give any range to the comp.paddle


        /// #2
/*int paddleSpeed = 2;
if (ballY > computerY)
    computerY += paddleSpeed;
else if (ballY < computerY)
    computerY -= paddleSpeed;
*/


/// #1
/*if (rand() % 10 == 0) {  // Adjust the probability (e.g., 10% chance)
    int randomMove = rand() % 3 - 1;  // -1, 0, or 1
    computerY += randomMove;
}*/
}

int main() {
    setup();
    while (1) {          /// Change the game loop condition to an infinite loop
        draw();
        input();
        logic();
        if (PlayerScore >= 5 || ComputerScore >= 5) {
            printf("Game Over! Player: %d\tComputer: %d\n", PlayerScore, ComputerScore);
            break;
        }
        Sleep(100);       ///  in each iteration of the game loop, controlling the speed of the game.
    }
    return 0;
}


/*
height 6

Row  1
Row  2
Row  3
Row  4
Row  5
Row  6   |
Row  7   |
Row  8   |
Row  9   |
Row 10   |
Row 11
Row 12
  ...
*/

