#include <iostream>
#include <vector>
#include <string>

using namespace std;

int currentTurn = 1;
const int MAX_DEPTH = 4;
int recursiveCalls = 0;

struct MinimaxOutcome {
    int score;
    vector<int> path;
};

void getUserMove(vector<vector<int>> &gameBoard, int turn)
{
    bool moveValid = false;
    int chosenMove;
    while (!moveValid)
    {
        cout << "Enter your move (Valid moves: 1-9): ";
        cin >> chosenMove;
        int row = (chosenMove - 1) / 3;
        int col = (chosenMove - 1) % 3;

        if (chosenMove >= 1 && chosenMove <= 9 && (gameBoard[row][col] == 2))
        {
            gameBoard[row][col] = (turn % 2 != 0) ? 3 : 5;
            moveValid = true;
        }
        else
        {
            cout << "Invalid move! Try again." << endl;
        }
    }
}

bool hasPlayerWon(const vector<vector<int>> &gameBoard, int player)
{
    int winProduct = player * player * player;

    //  rows and columns
    for (int i = 0; i < 3; ++i)
    {
        if ((gameBoard[i][0] * gameBoard[i][1] * gameBoard[i][2]) == winProduct ||
            (gameBoard[0][i] * gameBoard[1][i] * gameBoard[2][i]) == winProduct)
        {
            return true;
        }
    }

    //  diagonals
    if ((gameBoard[0][0] * gameBoard[1][1] * gameBoard[2][2]) == winProduct ||
        (gameBoard[0][2] * gameBoard[1][1] * gameBoard[2][0]) == winProduct)
    {
        return true;
    }

    return false;
}

int findWinningMove(vector<vector<int>> &gameBoard, int player)
{
    int neededProduct = player * player * 2;

    for (int i = 0; i < 3; ++i)
    {
        if ((gameBoard[i][0] * gameBoard[i][1] * gameBoard[i][2]) == neededProduct)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (gameBoard[i][j] == 2)
                    return i * 3 + j + 1;
            }
        }
        if ((gameBoard[0][i] * gameBoard[1][i] * gameBoard[2][i]) == neededProduct)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (gameBoard[j][i] == 2)
                    return j * 3 + i + 1;
            }
        }
    }

    if ((gameBoard[0][0] * gameBoard[1][1] * gameBoard[2][2]) == neededProduct)
    {
        for (int i = 0; i < 3; ++i)
        {
            if (gameBoard[i][i] == 2)
                return i * 3 + i + 1;
        }
    }

    if ((gameBoard[0][2] * gameBoard[1][1] * gameBoard[2][0]) == neededProduct)
    {
        for (int i = 0; i < 3; ++i)
        {
            if (gameBoard[i][2 - i] == 2)
                return i * 3 + (2 - i) + 1;
        }
    }

    return 0;
}

// Rating function
int evaluateBoard(vector<vector<int>> &gameBoard, int move, int player)
{
    int score = 0;
    int opponent = (player == 3) ? 5 : 3;

    if (hasPlayerWon(gameBoard, player))
        score += 100;
    else if (hasPlayerWon(gameBoard, opponent))
        score -= 100;
    else
    {
        if (findWinningMove(gameBoard, player) != 0)
            score += 50;
        if (findWinningMove(gameBoard, opponent) != 0)
            score -= 50;
    }

    return score;
}

void showGameBoard(const vector<vector<int>> &gameBoard)
{
    cout << "-------------------" << endl;
    for (int i = 0; i < 3; ++i)
    {
        cout << "| ";
        for (int j = 0; j < 3; ++j)
        {
            if (gameBoard[i][j] == 3)
                cout << " X  | ";
            else if (gameBoard[i][j] == 5)
                cout << " O  | ";
            else
                cout << "    | ";
        }
        cout << endl;
        cout << "-------------------" << endl;
    }
}

// Minimax function
MinimaxOutcome minimax(vector<vector<int>> gameBoard, int player, int depth, int alpha, int beta, int position)
{
    recursiveCalls++;
    MinimaxOutcome outcome;
    outcome.score = 0;

    if (depth >= MAX_DEPTH || hasPlayerWon(gameBoard, 3) || hasPlayerWon(gameBoard, 5))
    {
        outcome.score = evaluateBoard(gameBoard, position, player);
        return outcome;
    }

    vector<int> possibleMoves;
    for (int i = 1; i <= 9; ++i)
    {
        int row = (i - 1) / 3;
        int col = (i - 1) % 3;
        if (gameBoard[row][col] == 2)
            possibleMoves.push_back(i);
    }

    if (possibleMoves.empty())
    {
        outcome.score = evaluateBoard(gameBoard, position, player);
        return outcome;
    }

    int bestScore = -1000;
    vector<int> optimalPath;

    for (int move : possibleMoves)
    {
        auto updatedBoard = gameBoard;
        int row = (move - 1) / 3;
        int col = (move - 1) % 3;
        updatedBoard[row][col] = player;

        MinimaxOutcome childOutcome = minimax(updatedBoard, (player == 3) ? 5 : 3, depth + 1, -beta, -alpha, move);
        int moveScore = -childOutcome.score;

        if (moveScore > alpha)
        {
            alpha = moveScore;
            optimalPath = childOutcome.path;
            optimalPath.insert(optimalPath.begin(), move);

            if (alpha >= beta)
            {
                outcome.score = alpha;
                outcome.path = optimalPath;
                return outcome;
            }
        }
    }

    outcome.score = alpha;
    outcome.path = optimalPath;
    return outcome;
}

// Computer's move
void makeComputerMove(vector<vector<int>> &gameBoard, int turn)
{
    recursiveCalls = 0;
    int player = (turn % 2 == 0) ? 5 : 3;

    int alpha = -1000;
    int beta = 1000;

    MinimaxOutcome bestOutcome = minimax(gameBoard, player, 0, alpha, beta, 0);

    if (!bestOutcome.path.empty())
    {
        int chosenMove = bestOutcome.path[0];
        int row = (chosenMove - 1) / 3;
        int col = (chosenMove - 1) % 3;
        gameBoard[row][col] = player;

        cout << "Computer chose move: " << chosenMove << endl;
    }
}

int main()
{
    vector<vector<int>> gameBoard(3, vector<int>(3, 2));

    while (true)
    {
        showGameBoard(gameBoard);

        if (hasPlayerWon(gameBoard, 5))
        {
            cout << "Computer wins!" << endl;
            break;
        }
        if (hasPlayerWon(gameBoard, 3))
        {
            cout << "User wins!" << endl;
            break;
        }
        if (currentTurn > 9)
        {
            cout << "It's a tie!" << endl;
            break;
        }

        if (currentTurn % 2 != 0)
            getUserMove(gameBoard, currentTurn);
        else
            makeComputerMove(gameBoard, currentTurn);

        currentTurn++;
    }

    cout << "Total recursive calls during the game: " << recursiveCalls << endl;

    return 0;
}
