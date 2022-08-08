#include <iostream>
#include <tuple>
#include <thread>
#include "winner.h"
using namespace std;
#define UNDERLINE "\033[4m"
#define CLOSEUNDERLINE "\033[0m"
const string player1 = "X";
const string player2 = "O";
enum State
{
    menu,
    run,
    changePjlayer,
    gameEnd
};
State state = menu;
int counter1, counter2, counter3, counter4 = 1;
void count(string values[3][3], int i, int j, int size, int &counter, string &lastValue)
{
    string currentValue = values[i][j];
    // cout << "current: " << currentValue << endl;

    // cout << "last: " << lastValue << " :" << i << "/" << j << endl;
    if (currentValue == lastValue && currentValue != " ")
    {

        counter++;
        // cout << "counter:" << counter << endl;
    }
    else
    {
        counter = 1;
        lastValue = currentValue;
    }
}
int checkWinner(string values[3][3], int size, int player)
{
    const string player1 = "X";
    const string player2 = "O";

    string lastValue1, lastValue2, lastValue3, lastValue4 = " ";
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            // cout << counter1 << "dfsdf" << endl;
            count(values, i, j, size, counter1, lastValue1);
            // count(values, j, i, size, counter2, lastValue2);
            // count(values, j, j, size, counter3, lastValue3);
            // count(values, size - j - 1, j, size, counter4, lastValue4);
            if (counter1 == size || counter2 == size || counter3 == size || counter4 == size)
            {
                return player;
            }
        }
        counter1, counter2 = 0;
        cout << "asd" << counter1 << endl;
    }
    return -1;
}
void printValue(string value)
{
    cout << "|" << UNDERLINE << value << CLOSEUNDERLINE;
}
void printTicTacToe(string values[3][3])
{
    for (int i = 0; i < 4; i++)
    {

        if (i == 0)
        {

            cout << "   " << UNDERLINE << "1" << CLOSEUNDERLINE
                 << " " << UNDERLINE << "2" << CLOSEUNDERLINE
                 << " " << UNDERLINE << "3" << CLOSEUNDERLINE << endl;
        }
        else
        {

            int k = i - 1;
            cout << i << " ";
            printValue(values[k][0]);
            printValue(values[k][1]);
            printValue(values[k][2]);
            cout << "|" << endl;
        }
    }
}
void clearBoard(string values[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            values[i][j] = " ";
        }
    }
}
tuple<int, int> getInputFromPlayer(int player = 0)
{
    string input;
    cout << "Player number " << player << " type your move: ";
    cin >> input;
    if (input == "r")
    {
        state = menu;
    }
    else if (input.length() < 2)
    {
        cout << "Not valid" << endl;
        getInputFromPlayer(player);
    }
    else
    {
        char x = input.at(0);
        char y = input.at(1);
        return make_tuple(int(x) - 49, int(y) - 49);
    }
    return make_tuple(-1, -1);
}
bool checkIfAvailable(string values[3][3], int x, int y)
{
    // cout << "her " << x << y << " dsf" << endl;
    if (values[x][y] == " ")
    {
        return true;
    }
    else
    {
        return false;
    }
}
void addPlay(string values[3][3], int x, int y, int player)
{
    if (player == 2)
    {
        values[x][y] = player2;
    }
    else
    {
        values[x][y] = player1;
    }
}
int changePlayer(int currentPlayer)
{
    int newPlayer;
    if (currentPlayer != 2)
    {
        newPlayer = 2;
    }
    else
    {
        newPlayer = 1;
    }
    return newPlayer;
}

void game()
{
    string ticTacBoard[3][3];
    int player = 1;
    int x, y;
    int winner = -1;
    int player1Count, player2Count, drawCount = 0;

    bool playing = true;
    while (playing)
    {
        switch (state)
        {
        case menu:
        {
            clearBoard(ticTacBoard);
            string input = "";
            cout << "Do you want to play? (Y/n)";
            cin >> input;
            if (input == "Y")
            {
                state = run;
            }
            break;
        }
        case run:
        {
            for (int turns = 0; turns < 9; turns++)
            {
            newTry:
                tie(x, y) = getInputFromPlayer(player);
                if (checkIfAvailable(ticTacBoard, x, y))
                {
                    addPlay(ticTacBoard, x, y, player);
                    winner = checkWinner(ticTacBoard, 3, player);
                    if (winner != -1)
                    {
                        printTicTacToe(ticTacBoard);
                        break;
                    }
                }
                else
                {
                    goto newTry;
                }
                player = changePlayer(player);
                printTicTacToe(ticTacBoard);
            }
            if (winner == -1)
            {
                cout << " DRAW!!!" << endl;
                drawCount++;
            }
            else
                cout << "Player number " << winner << " won!!!" << endl;
            if (winner == 1)
                player1Count++;
            else if (winner == 2)
                player2Count++;

            state = menu;
            cout << "Score: ";
            cout << "Player1: " << player1Count;
            cout << " - Player2: " << player2Count;
            cout << " Draw: " << drawCount << endl;
            break;
        }
        }
    }
}

int main()
{
    int fdf = add1(1, 2);
    thread t1(game);
    t1.join();
}