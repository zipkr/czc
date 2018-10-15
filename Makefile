all: main.cpp
	g++ -std=c++17 main.cpp -lncurses -lstdc++fs -o main
clean:
	$(RM) main

