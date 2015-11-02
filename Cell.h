/* 
 * File:   Cell.h
 * Author: ubuntu-jordi
 *
 * Created on 2 de octubre de 2015, 18:38
 */

#ifndef CELL_H
#define	CELL_H
#define WALL 0
#define PATH 1
#define EMPTY 2
class Cell {
public:
    Cell();
    Cell(int, int);
    Cell(const Cell& orig);
    virtual ~Cell();
    int getRow();
    int getCol();
    int getStatus();
    bool isWall();
    bool isPath();
    bool isEmpty();
    void setAssigned(bool);
    void setStatus(int);
private:
    int col, row;
    int status;
};

#endif	/* CELL_H */
