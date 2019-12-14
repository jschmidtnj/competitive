CXX      = g++
CXXFLAGS = -Ofast -pthread -std=c++11 -Wall -Werror -pedantic-errors -fmessage-length=0
OPENCV   = `pkg-config --libs --cflags opencv4`
CURSOR   = -lncurses

all:
	$(CXX) ${CURSOR} ${OPENCV} $(CXXFLAGS) int.cpp -o int.out
clean:
	rm -f *.out *.exe
