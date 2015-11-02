pacman:
	g++ -o pacman *.cpp *.h -lglut -lGL -lGLU 
	
clean:
	rm pacman
