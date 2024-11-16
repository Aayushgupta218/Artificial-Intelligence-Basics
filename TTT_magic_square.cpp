#include <iostream>
#include <vector>
using namespace std;

vector<int> play_board(10, 2);  
vector<int> magic_board = {0, 8, 1, 6, 3, 5, 7, 4, 9, 2}; 
int turn = 1;
int userSymbol;
int aiSymbol;

int Make2()
{
    if (play_board[5] == 2)
        return 5;
    if (play_board[2] == 2)
        return 2;
    if (play_board[4] == 2)
        return 4;
    if (play_board[6] == 2)
        return 6;
    if (play_board[8] == 2)
        return 8;
    return 0;
}

void Go(int n)
{
    play_board[n] = (turn % 2 != 0) ? userSymbol : aiSymbol;
    turn++;
}

int PossWin(int p)
{
    vector<int> positions;
    for (int i = 1; i < play_board.size(); i++)
    {
        if (play_board[i] == p)
        {
            positions.push_back(magic_board[i]);
        }
    }

    for (int i = 0; i < positions.size(); i++)
    {
        for (int j = i + 1; j < positions.size(); j++)
        {
            int required_sum = 15 - (positions[i] + positions[j]);
            if (required_sum >= 1 && required_sum <= 9)
            {
                for (int k = 1; k <= 9; k++)
                {
                    if (magic_board[k] == required_sum && play_board[k] == 2)
                    {
                        return k;
                    }
                }
            }
        }
    }
    return 0;
}

void print_board()
{
    for (int i = 1; i <= 9; i++)
    {
        if (play_board[i] == 2)
            cout << "- ";
        else if (play_board[i] == 3)
            cout << "X ";
        else
            cout << "O ";

        if (i % 3 == 0)
            cout << endl;
    }
}

void AIMove()
{
    if (turn == 1)
    {
        Go(1);  
    }
    else if (turn == 2)
    {
        if (play_board[5] == 2)  
            Go(5);
        else
            Go(1);  
    }
    else if (turn == 3)
    {
        if (play_board[9] == 2) 
            Go(9);
        else
            Go(3);
    }
    else if (turn == 4)
    {
        int blockMove = PossWin(userSymbol);
        if (blockMove != 0)
        {
            Go(blockMove);
        }
        else
        {
            if (play_board[2] == userSymbol && play_board[6] == userSymbol)
            {
                Go(play_board[1] == 2 ? 1 : 9);
            }
            else if (play_board[6] == userSymbol && play_board[8] == userSymbol)
            {
                Go(play_board[3] == 2 ? 3 : 7);
            }
            else if (play_board[4] == userSymbol && play_board[8] == userSymbol)
            {
                Go(play_board[1] == 2 ? 1 : 9);
            }
            else if (play_board[2] == userSymbol && play_board[4] == userSymbol)
            {
                Go(play_board[3] == 2 ? 3 : 7);
            }
            else if (play_board[1] == userSymbol && play_board[8] == userSymbol)
            {
                Go(7);
            }
            else if (play_board[3] == userSymbol && play_board[8] == userSymbol)
            {
                Go(9);
            }
            else if (play_board[2] == userSymbol && play_board[9] == userSymbol)
            {
                Go(3);
            }
            else if (play_board[2] == userSymbol && play_board[7] == userSymbol)
            {
                Go(1);
            }
            else if (play_board[1] == userSymbol && play_board[9] == userSymbol)
            {
                Go(play_board[2] == 2 ? 2 : 8);
            }
            else if (play_board[3] == userSymbol && play_board[7] == userSymbol)
            {
                Go(play_board[2] == 2 ? 2 : 8);
            }
            else
            {
                for (int i = 1; i <= 9; i++)
                {
                    if (i != Make2() && play_board[i] == 2)
                    {
                        Go(i);
                        break;
                    }
                }
            }
        }
    }
    else
    {
        int winMove = PossWin(aiSymbol);
        if (winMove != 0)
        {
            Go(winMove);
        }
        else
        {
            int blockMove = PossWin(userSymbol);
            if (blockMove != 0)
            {
                Go(blockMove);
            }
            else
            {
                for (int i = 1; i <= 9; i++)
                {
                    if (play_board[i] == 2)
                    {
                        Go(i);
                        break;
                    }
                }
            }
        }
    }
}

bool check_winner(int symbol)
{
    vector<int> played_positions;
    for (int i = 1; i <= 9; i++)
    {
        if (play_board[i] == symbol)
        {
            played_positions.push_back(magic_board[i]);
        }
    }

    for (int i = 0; i < played_positions.size(); i++)
    {
        for (int j = i + 1; j < played_positions.size(); j++)
        {
            for (int k = j + 1; k < played_positions.size(); k++)
            {
                if (played_positions[i] + played_positions[j] + played_positions[k] == 15)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool is_board_full()
{
    for (int i = 1; i <= 9; i++)
    {
        if (play_board[i] == 2)
            return false;
    }
    return true;
}

void PlayGame()
{
    char choice;
    do
    {
        cout << "Do you want to be X or O? Enter X or O: ";
        cin >> choice;
    } while (choice != 'X' && choice != 'x' && choice != 'O' && choice != 'o');

    userSymbol = (choice == 'O' || choice == 'o') ? 5 : 3;
    aiSymbol = (userSymbol == 3) ? 5 : 3;

    while (true)
    {
        print_board();

        if (turn % 2 != 0)
        {
            int move;
            cout << "Your turn (enter a number 1-9): ";
            cin >> move;
            if (move < 1 || move > 9 || play_board[move] != 2)
            {
                cout << "Invalid move, please try again." << endl;
                continue;
            }
            Go(move);
        }
        else
        {
            cout << "AI's turn..." << endl;
            AIMove();
        }

        if (check_winner(userSymbol))
        {
            print_board();
            cout << "Congratulations! You won!" << endl;
            break;
        }
        else if (check_winner(aiSymbol))
        {
            print_board();
            cout << "AI won! Better luck next time!" << endl;
            break;
        }

        if (is_board_full())
        {
            print_board();
            cout << "It's a draw!" << endl;
            break;
        }
    }
}

int main()
{
    PlayGame();
    return 0;
}
