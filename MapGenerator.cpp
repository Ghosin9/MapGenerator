// MapGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

const int row = 15;
const int col = 15;

const string BORDER = "#";
const string WALL = "*";
const string ROAD = "=";
const string ENEMY = "!";
const string CHEST = "?";
const string TREE = "^";
const string WATER = "~";

pair<int, int> RandomPoint() {
    return make_pair(rand() % (row-2) + 1, rand() % (col-2) + 1);
}

void SpawnBorders(string map[row][col]) {
    //side
    for (int x = 0; x < row; ++x) {
        map[x][0] = BORDER;
        map[x][col - 1] = BORDER;
    }

    //top and bottom borders
    for (int y = 0; y < col; ++y) {
        map[0][y] = BORDER;
        map[row - 1][y] = BORDER;
    }
}

void SpawnWalls(string map[row][col], int length) {
    pair<int, int> point = RandomPoint();

    map[point.first][point.second] = ROAD;

    int upOrDown = rand() % 3 - 1;
    int leftOrRight = rand() % 3 - 1;

    for (int x = 0; x < length; ++x) {
        int newX = max(min(point.first + (upOrDown * x), row - 1), 1);
        int newY = max(min(point.second + (leftOrRight * x), col - 1), 1);
        map[newX][newY] = WALL;
    }
}

void SpawnRoad(string map[row][col], int length) {
    pair<int, int> point = RandomPoint();

    map[point.first][point.second] = ROAD;

    int upOrDown = rand() % 3 - 1;
    int leftOrRight = rand() % 3 - 1;

    for (int x = 0; x < length; ++x) {
        int newX = max(min(point.first + (upOrDown * x), row-1), 1);
        int newY = max(min(point.second + (leftOrRight * x), col-1), 1);
        map[newX][newY] = ROAD;
    }
}

void SpawnEnemies(string map[row][col], int amount, int xCord, int yCord) {
    for (int x = 0; x <= amount; ++x) {
        int upOrDown = rand() % 5 - 2;
        int leftOrRight = rand() % 5 - 2;

        int newX = max(min(xCord + (upOrDown * x), row - 1), 1);
        int newY = max(min(yCord + (leftOrRight * x), col - 1), 1);

        if (map[newX][newY].compare(CHEST) != 0) {
            map[newX][newY] = ENEMY;
        }
    }
}

void SpawnChests(string map[row][col], int amount) {
    for (int x = 0; x < amount; ++x) {
        pair<int, int> point = RandomPoint();

        map[point.first][point.second] = CHEST;

        SpawnEnemies(map, 2, point.first, point.second);
    }
}

void SpawnTrees(string map[row][col], int amount) {

    for (int x = 0; x <= amount; ++x){
        pair<int, int> point = RandomPoint();

        map[point.first][point.second] = TREE;
    }

}

void SpawnPond(string map[row][col], int length) {
    pair<int, int> point = RandomPoint();

    map[point.first][point.second] = WATER;

    for (int x = -length; x < length; ++x) {
        for (int y = -length; y < length; ++y) {
            int newX = max(min(point.first + x, row - 1), 1);
            int newY = max(min(point.second + y, col - 1), 1);

            map[newX][newY] = WATER;
        }
    }
}

void PrintMap(string mapToPrint[row][col]) {

    for (int x = 0; x < row; ++x) {
        for (int y = 0; y < col; ++y) {
            cout << mapToPrint[x][y];
        }

        cout << endl;
    }
}

int main()
{
    srand(time(0));

    string map[row][col];

    for (int x = 0; x < row; ++x) {
        for (int y = 0; y < col; ++y) {
            map[x][y] = " ";
        }
    }

    SpawnTrees(map, 8);

    SpawnRoad(map, 7);

    SpawnWalls(map, 4);
    SpawnWalls(map, 4);

    SpawnChests(map, 3);

    SpawnPond(map, 2);

    SpawnBorders(map);

    PrintMap(map);
}
