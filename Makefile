all: main.cpp
	g++ -std=c++17 main.cpp -lstdc++fs -o main
clean:
	$(RM) main

