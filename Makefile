all: main.cpp
	g++ -std=c++17 main.cpp utils.cpp -lncurses -lstdc++fs -o czc
clean:
	$(RM) czc

