
#include <iostream>
#include <algorithm>
using namespace std;


// ==============================
// GAME VARIABLES
// ==============================

char board[3][3];

char player_mark = 'X';
char computer_mark = 'O';


// ==============================
// RESET BOARD
// ==============================

void resetBoard()
{
    char num = '1';

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = num;
            num++;
        }
    }
}


// ==============================
// SET PLAYER AND COMPUTER MARK
// ==============================

void setMarks(char mark)
{
    player_mark = mark;

    if (mark == 'X')
    {
        computer_mark = 'O';
    }
    else
    {
        computer_mark = 'X';
    }

    resetBoard();
}


// ==============================
// CHECK EMPTY CELLS
// ==============================

bool isMovesLeft()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] >= '1' && board[i][j] <= '9')
            {
                return true;
            }
        }
    }

    return false;
}


// ==============================
// EVALUATE WINNING CONDITION
// ==============================

int evaluate()
{
    // Check Rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2])
        {
            if (board[i][0] == computer_mark)
                return 10;

            if (board[i][0] == player_mark)
                return -10;
        }
    }


    // Check Columns
    for (int j = 0; j < 3; j++)
    {
        if (board[0][j] == board[1][j] &&
            board[1][j] == board[2][j])
        {
            if (board[0][j] == computer_mark)
                return 10;

            if (board[0][j] == player_mark)
                return -10;
        }
    }


    // Check First Diagonal
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
    {
        if (board[0][0] == computer_mark)
            return 10;

        if (board[0][0] == player_mark)
            return -10;
    }


    // Check Second Diagonal
    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
    {
        if (board[0][2] == computer_mark)
            return 10;

        if (board[0][2] == player_mark)
            return -10;
    }

    return 0;
}


// ==============================
// MINIMAX + DFS + ALPHA-BETA
// ==============================

int minimax(bool isMax, int depth, int alpha, int beta)
{
    int score = evaluate();


    // Computer Wins
    if (score == 10)
    {
        return score - depth;
    }


    // Player Wins
    if (score == -10)
    {
        return score + depth;
    }


    // Draw
    if (!isMovesLeft())
    {
        return 0;
    }


    // Maximizing Player (Computer)
    if (isMax)
    {
        int best = -1000;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] >= '1' &&
                    board[i][j] <= '9')
                {
                    char temp = board[i][j];

                    board[i][j] = computer_mark;

                    best = max(
                        best,
                        minimax(false, depth + 1, alpha, beta)
                    );

                    board[i][j] = temp;

                    alpha = max(alpha, best);

                    // Alpha-Beta Pruning
                    if (beta <= alpha)
                    {
                        return best;
                    }
                }
            }
        }

        return best;
    }


    // Minimizing Player (Human)
    else
    {
        int best = 1000;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] >= '1' &&
                    board[i][j] <= '9')
                {
                    char temp = board[i][j];

                    board[i][j] = player_mark;

                    best = min(
                        best,
                        minimax(true, depth + 1, alpha, beta)
                    );

                    board[i][j] = temp;

                    beta = min(beta, best);

                    // Alpha-Beta Pruning
                    if (beta <= alpha)
                    {
                        return best;
                    }
                }
            }
        }

        return best;
    }
}


// ==============================
// COMPUTER MOVE
// ==============================

void computerMove()
{
    int bestValue = -1000;

    int bestRow = -1;
    int bestCol = -1;

    int alpha = -1000;
    int beta = 1000;


    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] >= '1' &&
                board[i][j] <= '9')
            {
                char temp = board[i][j];

                board[i][j] = computer_mark;

                int moveValue = minimax(
                    false,
                    1,
                    alpha,
                    beta
                );

                board[i][j] = temp;


                if (moveValue > bestValue)
                {
                    bestValue = moveValue;

                    bestRow = i;
                    bestCol = j;
                }

                alpha = max(alpha, bestValue);
            }
        }
    }


    // Make Best Move
    if (bestRow != -1)
    {
        board[bestRow][bestCol] = computer_mark;
    }
}


// ==============================
// DISPLAY BOARD
// ==============================

void displayBoard()
{
    cout << "\n";

    for (int i = 0; i < 3; i++)
    {
        cout << " ";

        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j];

            if (j < 2)
                cout << " | ";
        }

        cout << "\n";

        if (i < 2)
            cout << "---+---+---\n";
    }

    cout << "\n";
}


// ==============================
// PLAYER MOVE
// ==============================

void playerMove()
{
    int position;

    cout << "Enter your position (1-9): ";
    cin >> position;

    if (position < 1 || position > 9)
    {
        cout << "Invalid position!\n";
        playerMove();
        return;
    }

    int row = (position - 1) / 3;
    int col = (position - 1) % 3;

    if (board[row][col] < '1' ||
        board[row][col] > '9')
    {
        cout << "This position is already taken!\n";
        playerMove();
        return;
    }

    board[row][col] = player_mark;
}


// ==============================
// MAIN FUNCTION
// ==============================

int main()
{
    char choice;

    cout << "===== TIC TAC TOE AI =====\n";

    cout << "Choose your mark (X/O): ";
    cin >> choice;

    choice = toupper(choice);

    if (choice != 'X' && choice != 'O')
    {
        cout << "Invalid mark!\n";
        return 0;
    }

    setMarks(choice);


    // Computer starts if Player chooses O
    if (player_mark == 'O')
    {
        computerMove();
    }


    while (true)
    {
        displayBoard();

        playerMove();

        if (evaluate() == -10)
        {
            displayBoard();
            cout << "Congratulations! You Win!\n";
            break;
        }

        if (!isMovesLeft())
        {
            displayBoard();
            cout << "Game Draw!\n";
            break;
        }


        computerMove();

        if (evaluate() == 10)
        {
            displayBoard();
            cout << "Computer Wins!\n";
            break;
        }

        if (!isMovesLeft())
        {
            displayBoard();
            cout << "Game Draw!\n";
            break;
        }
    }

    return 0;
}
