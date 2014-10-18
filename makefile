CXXFLAGS= -std=c++11 -Wall
GTEST_DIR= /home/tomasz/gtests/libs/gmock-1.7.0/gtest
GMOCK_DIR= /home/tomasz/gtests/libs/gmock-1.7.0
TO_CLEAN= list test

all: main.o  list.o myInAndOut.o
	g++ main.o list.o -o list

test: list.o
	g++ $(CXXFLAGS) -isystem ${GTEST_DIR}/include -isystem ${GMOCK_DIR}/include -pthread test.cpp ${GMOCK_DIR}/../libgmock.a -o list


main.o: main.cpp
	g++ $(CXXFLAGS) -c main.cpp -o main.o

list.o: list.cpp
	g++ $(CXXFLAGS) -c list.cpp -o list.o

myInAndOut.o: myInAndOut.cpp
	g++ $(CXXFLAGS) -c myInAndOut.cpp -o myInAndOut.o
	
clean:
	rm -f $(TO_CLEAN) *.o 

