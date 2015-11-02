/* 
 * File:   Cell.cpp
 * Author: ubuntu-jordi
 * 
 * Created on 2 de octubre de 2015, 18:38
 */

#include "Cell.h"

Cell::Cell(int c, int r) {
    this->row = r;
    this->col = c;
    this->status = EMPTY;

}

Cell::Cell(const Cell& orig) {
}
Cell::Cell(){}
Cell::~Cell() {
}

int Cell::getRow(){
    return this->row;
}
int Cell::getCol(){
    return this->col;
}
bool Cell::isWall(){
    if(this->status == WALL){
        return true;
    }else{
        return false;
    }
}
bool Cell::isPath(){
    if(this->status == PATH){
        return true;
    }else{
        return false;
    }
}
bool Cell::isEmpty(){
    if(this->status == EMPTY){
        return true;
    }else{
        return false;
    }
}

void Cell::setStatus(int c){
    this->status = c;
}
int Cell::getStatus(){
    return this->status;
}