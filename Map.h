/* 
 * File:   Map.h
 * Author: ubuntu-jordi
 *
 * Created on 2 de octubre de 2015, 18:31
 */

#ifndef MAP_H
#define	MAP_H
#include "Cell.h"
#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
 
#define UP      0
#define DOWN    2
#define RIGHT   1
#define LEFT    3
#define MULTIPLIER 10
#define WIDTH 400
#define HEIGHT 400

class Map {
public:
    Map(int, int);
    Map(const Map& orig);
    virtual ~Map();
    Cell* getCell(int, int);
    void print();   
    void render();
private:
    int cols, rows;
    Cell **map;
    void mirrorHalfMap();
    void createMap();
    void fillCentralSquare();
    void initMap();
    bool isBorder(int, int);
    bool hasDiagonalNeigbour(int, int, int);
    bool hasWalls(int , int , int , int);
    void wallGenerator(int row1, int col1, int row2, 
        int col2, int totalWallSize, int partialWall, 
        int partialWallDirection, int dir);
};


#endif	/* MAP_H */
