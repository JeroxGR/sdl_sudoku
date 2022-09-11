#pragma once

#include <vector>

//verifie if an element exsiste in a ligne or a column or a box
int exist(int G[9][9],int x, int l, char a , int row , int column );

//verifie if the soduko map is valid (we don't need to use it if we want just solve one)
int isValide(int G[9][9]);

//remembering the empty places
typedef struct p
{
    int x, y;
}Position;

std::vector<Position> findMissingElements(int G[9][9]);

void printMap(int G[9][9]);

//solving the actual soduko :D
int solveMemeber(int S[9][9], int x, int y, int past, bool goingback);

void copyGrid(int G[9][9], int S[9][9]);

bool solve(int G[9][9],int S[9][9]);

//FUNCTIONS FOR GUI
bool isAMissing(int x, int y, std::vector<Position> Positions);

void setMissingElements(int G[9][9], std::vector<Position> Positions);