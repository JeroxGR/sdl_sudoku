#include "Soduko_Solution.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//verifie if an element exsiste in a ligne or a column or a box
int exist(int G[9][9], int x, int l, char a = 'l', int row = 0, int column = 0)
{
    if (a == 'l')
    {
        for (int i = 0; i < 9; i++)
        {
            if (G[l][i] == x)
            {
                return 1;
            }
        }
    }
    else if (a == 'c')
    {
        for (int i = 0; i < 9; i++)
        {
            if (G[i][l] == x)
            {
                return 1;
            }
        }
    }
    else
    {
        int c = column - column % 3;
        int r = row - row % 3;

        for (int i = c; i < c + 3; i++)
        {
            for (int j = r; j < r + 3; j++)
            {
                if (G[i][j] == x)
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}

//verifie if the soduko map is valid (we don't need to use it if we want just solve one)
int isValide(int G[9][9])
{
    //verifie the 9 lines and columns
    for (int i = 0; i < 9; i++)
    {
        for (int k = 1; k <= 9; k++)
        {
            if (!exist(G,k, i) || !exist(G,k, i, 'c'))
            {
                return 0;
            }
        }
    }

    //verifie the 9 boxes
    for (int i = 0; i < 7; i = i + 3)
    {
        for (int j = 0; j < 7; j = j + 3)
        {
            for (int k = 1; k <= 9; k++)
            {
                if (!exist(G,k, 0, 'b', i, j))
                {
                    return 0;
                }
            }
        }
    }

    return 1;
}

vector<Position> findMissingElements(int G[9][9])
{
    vector<Position> Tab;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (G[i][j] == 0)
            {
                Position p;
                p.x = i;
                p.y = j;
                Tab.push_back(p);
            }
        }
    }

    return Tab;
}

//printing the soduko map
void printMap(int G[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++) { cout << G[i][j]; }
        cout << endl;
    }
}

void copyGrid(int G[9][9], int S[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            S[i][j] = G[i][j];
        }
    }
}

//solving the actual soduko :D
int solveMemeber(int S[9][9], int x, int y, int past, bool goingback)
{
    for (int i = past; i <= 9; i++)
    {
        if (i != past && !exist(S,i, x) && !exist(S,i, y, 'c') && !exist(S,i, 0, 'b', y, x))
        {
            S[x][y] = i;
            return 1;
        }
    }

    S[x][y] = 0;
    return 0;

}

bool solve(int G[9][9],int S[9][9])
{
    copyGrid(G, S);

    //store the missing elements:
    vector<Position> Positions = findMissingElements(S);

    bool goingback = false;
    int i = 0;
    while (i < (int)Positions.size() && i>=0)
    {
        Position p = Positions.at(i);

        if (!solveMemeber(S,p.x, p.y, S[p.x][p.y], goingback))
        {
            i--;
        }
        else { i++; }
    }

    if (i < 0)
    {
        return false;
    }

    return true;
}


//FUNCTIONS THAT ARE USED IN THE GRAPHICAL USER INTERFACE
bool isAMissing(int x, int y, vector<Position> Positions)
{
    for (auto ele : Positions)
    {
        if (ele.x == x && ele.y == y)
        {
            return true;
        }
    }

    return false;
}

void setMissingElements(int G[9][9], std::vector<Position> Positions)
{
    for (auto ele : Positions)
    {
        G[ele.x][ele.y] = 0;
    }
}