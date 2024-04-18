#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;

const int SIZE = 3;
const int GOAL[SIZE][SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

struct State
{
    int board[SIZE][SIZE];
    int emptyRow, emptyCol;
};

bool DFS(State initialState)
{
    stack<State> stack;
    unordered_set<string> visited;

    int emptyRow, emptyCol;
    for (emptyRow = 0; emptyRow < SIZE; ++emptyRow)
    {
        for (emptyCol = 0; emptyCol < SIZE; ++emptyCol)
        {
            if (initialState.board[emptyRow][emptyCol] == 0)
                goto found;
        }
    }
found:
    initialState.emptyRow = emptyRow;
    initialState.emptyCol = emptyCol;

    stack.push(initialState);

    while (!stack.empty())
    {
        State currentState = stack.top();
        stack.pop();

        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                if (currentState.board[i][j] != GOAL[i][j])
                    goto notGoalState;
            }
        }
        return true;
    notGoalState:

        string currentStateString = "";
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                currentStateString += to_string(currentState.board[i][j]);
            }
        }

        if (visited.find(currentStateString) != visited.end())
        {
            continue;
        }
        visited.insert(currentStateString);

        int moves[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (auto move : moves)
        {
            int newRow = currentState.emptyRow + move[0];
            int newCol = currentState.emptyCol + move[1];

            if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE)
            {
                State nextState = currentState;
                nextState.emptyRow = newRow;
                nextState.emptyCol = newCol;
                swap(nextState.board[currentState.emptyRow][currentState.emptyCol], nextState.board[newRow][newCol]);
                stack.push(nextState);
            }
        }
    }

    return false;
}

int main()
{
    State initialState = {{{1, 2, 3},
                           {4, 5, 6},
                           {0, 7, 8}}};

    if (DFS(initialState))
    {
        cout << "Lze";
    }
    else
    {
        cout << "Nelze";
    }

    return 0;
}