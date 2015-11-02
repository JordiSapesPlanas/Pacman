#include <GL/glut.h>
#include <stdlib.h>
#include "Map.h"

void display();

Map *map;

using namespace std;
int main(int argc,char *argv[])
{

  int i,j;
  if(atoi(argv[1])%2 == 0){
    i = atoi(argv[1]) + 1;
  }
  else{
    i = atoi(argv[1]);
  }
  if(atoi(argv[2])%2 == 0){
    j = atoi(argv[2]) + 1;
  }
  else{
    j = atoi(argv[2]);
  }

  map = new Map(i, j);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(WIDTH, HEIGHT);
}
void display()
{
	//map->print();
	map->render();  
}