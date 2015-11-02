/* 
 * File:   Map.cpp
 * Author: jordi
 * 
 * Created on 14 de octubre de 2015, 16:06
 */

#include "Map.h"

#define UP      0
#define DOWN    2
#define RIGHT   1
#define LEFT    3

int keyflag=0;

using namespace std;
Map::Map(int col, int row){
    this->cols = col; 
    this->rows = row;
    this->map = new Cell*[this->rows];
    for(int i = 0; i< this->rows; i++){
        this->map[i]= new Cell[this->cols];
    }
    srand(time(0));
    this->createMap();    
}

Map::Map(const Map& orig){}

Map::~Map(){}

void Map::mirrorHalfMap(){

    for(int i = 0 ; i < this->rows ; i++){
        for(int j = 0 ; j < this->cols/2; j ++){
	 int status = this->map[i][j].getStatus();
		this->map[i][this->cols - 1 - j].setStatus(status);
        }
    }
}

void Map::print(){
    for(int i = 0; i< this->rows; i++){
        for(int j = 0; j<this->cols; j++){
            if(this->map[i][j].getStatus() == WALL){
                cout << "o";
            }
            if(this->map[i][j].getStatus() == PATH){
                cout << "-";
            }
            if(this->map[i][j].getStatus() == EMPTY){
                cout << "x";
            }
        }
        cout << endl;
    }
}
bool Map::hasDiagonalNeigbour(int row, int col, int direction){
    if(direction==UP){
        if(this->map[row-1][col-1].isPath() || this->map[row-1][col-1].isPath()){
            return true;
        }
    }
    if(direction == DOWN){
        if(this->map[row+1][col-1].isPath() || this->map[row+1][col-1].isPath()){
            return true;
        } 
    }
    if(direction == LEFT){
        if(this->map[row-1][col-1].isPath() || this->map[row+1][col-1].isPath()){
            return true;
        } 
    }
    if(direction == RIGHT){
        if(this->map[row+1][col+1].isPath() || this->map[row+1][col+1].isPath()){
            return true;
        } 
    }
    return false;
    
}
void Map::createMap(){    
    this->initMap(); 
    int cellesTotals = this->cols * this->rows;
    int bordes = (2 * this->cols + 2 * this->rows) - 4;
    for(int i = 0; i<this->rows; i++){
        for(int j = 0; j<this->cols; j++){
            int wallLenght = (rand() % 2) + 1;
            this->wallGenerator(i, j, i, j,wallLenght, 0, 0, 0);                     
        }
    }  
    mirrorHalfMap(); 
    fillCentralSquare();   
}
    
void Map::initMap(){
    for(int i = 0; i< this->rows; i++){
        for(int j = 0; j<this->cols; j++){
            if(this->isBorder(i, j)){
                this->map[i][j].setStatus(WALL);
            }else{
                 this->map[i][j].setStatus(EMPTY);
            }          
        }       
    }  
}

bool Map::hasWalls(int srcRow, int srcCol, int row, int col){
    int walls = 0;
    if(isBorder(row, col)){
        return true;
    }
    if(this->map[row-1][col].getStatus() == WALL){
        if(srcRow != row -1 && srcCol != col){
            walls ++;
        }
    }
    if(this->map[row+1][col].getStatus() == WALL){
        if(srcRow != row + 1 && srcCol != col){
            walls ++;
        }
    }
    if(this->map[row][col+1].getStatus() == WALL){
        if(srcRow != row && srcCol != col+1){
            walls ++;
        }
    }
    if(this->map[row][col-1].getStatus() == WALL){
        if(srcRow != row && srcCol != col-1){
            walls ++;
        }
    }
    if(this->map[row-1][col-1].getStatus() == WALL){
        if(srcRow != row -1 && srcCol != col-1){
            walls ++;
        }
    }
    if(this->map[row-1][col+1].getStatus() == WALL){
        if(srcRow != row - 1 && srcCol != col+1 ){
            walls ++;
        }
    }
    if(this->map[row+1][col-1].getStatus() == WALL){
        if(srcRow != row + 1 && srcCol != col-1 ){
            walls ++;
        }
    }
    if(this->map[row+1][col+1].getStatus() == WALL){
        if(srcRow != row +1 && srcCol != col+1){
            walls ++;
        }
    }
    
    if(walls == 0){
        return false;
    }
 
    else {
        return true;
    }
}

void Map::wallGenerator(int row1, int col1, int row2, int col2, int totalWallSize, 
    int partialWall, int partialWallDirection, int dir){
    if(this->map[row2][col2].getStatus() != EMPTY){
        return;
    }else if(this->hasWalls(row1, col1, row2, col2)){
        this->map[row2][col2].setStatus(PATH);
        return;
    }else{
        this->map[row2][col2].setStatus(WALL);  
        
        if(totalWallSize == partialWall){

            
            return;

        }else{
            
            if(partialWallDirection == 0){
                partialWallDirection = (rand () % 5)+1; 
                dir = rand() % 4 ;
            }
    
            partialWall ++;
            partialWallDirection--;
            row1 = row2;
            col1 = col2;
            if(dir == UP) row2 --;
            if(dir == DOWN) row2 ++;
            if(dir == LEFT) col2 --;
            if(dir == RIGHT) col2 ++;
            this->wallGenerator(row1, col1, row2, col2, totalWallSize, partialWall,partialWallDirection,  dir);
            return;
        }
    }
}

void Map::fillCentralSquare(){
    int centerColumn = this->cols/2;
    int centerRow = this->rows/2;
    
    for(int i = centerRow -2; i<=centerRow+2; i++){
        for(int j = centerColumn -3; j<=centerColumn+3; j++){
            if(i == centerRow+1 && j ==centerColumn){
                this->map[i][j].setStatus(PATH);
            }else if(i == centerRow-2 || i == centerRow+2){
                this->map[i][j].setStatus(PATH);
            }else if(j == centerColumn-2 || j == centerColumn+2){
                this->map[i][j].setStatus(WALL);
            }
            else if(i == centerRow-1 || i == centerRow+1){
                if(j == centerColumn-3 || j == centerColumn+3)
                {
                    this->map[i][j].setStatus(PATH);
                }else{
                        this->map[i][j].setStatus(WALL);
                }
            }else{
                this->map[i][j].setStatus(PATH);
            }
        }
    }
}

   
bool Map::isBorder(int row , int col){
    if(row > 0 && row < this->rows-1 && col > 0 && col < this->cols-1){
        return false;
    }else{
        return true;
    }
}

Cell* Map::getCell(int row, int col){
    return &this->map[row][col];
}

void Map::render(){
    int i,j;

	  glClearColor(0.0,0.0,0.0,0.0);
	  glClear(GL_COLOR_BUFFER_BIT);

	  for(i=0;i<this->rows;i++){
	    for(j=0;j<this->cols;j++){
	      if(this->map[i][j].getStatus() == WALL){
	          glColor3f(0.1,0.1,0.1);
	      }
	      else{
		glColor3f(0.8,0.8,0.8);
	      }		  
		  glBegin(GL_QUADS);

		  glVertex2i(j*HEIGHT/this->rows,i*WIDTH/this->cols); 
		  glVertex2i((j+1)*HEIGHT/this->rows,i*WIDTH/this->cols); 
		  glVertex2i((j+1)*HEIGHT/this->rows,(i+1)*WIDTH/this->cols); 
		  glVertex2i(j*HEIGHT/this->rows,(i+1)*WIDTH/this->cols); 
		 
		  glEnd();
	    }
          }		  
	  glutSwapBuffers();
}