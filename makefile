CXXFLAGS= -std=c++11 -Wall


all: main.o  list.o myInAndOut.o
	g++ main.o list.o -o list

main.o: main.cpp
	g++ $(CXXFLAGS) -c main.cpp -o main.o

list.o: list.cpp
	g++ $(CXXFLAGS) -c list.cpp -o list.o

myInAndOut.o: myInAndOut.cpp
	g++ $(CXXFLAGS) -c myInAndOut.cpp -o myInAndOut.o
	
clean:
	rm -f *.o
