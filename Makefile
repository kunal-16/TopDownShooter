all:
	g++ -o game main.cpp -lGL -lGLU -lglut
clean:
	rm game
