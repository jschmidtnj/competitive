CXX      = g++
CXXFLAGS = -Ofast -pthread -std=c++11 -Wall -Werror -pedantic-errors -fmessage-length=0
OPENCV   = `pkg-config --libs --cflags opencv4`

all:
	$(CXX) ${OPENCV} $(CXXFLAGS) bios.cpp -o bios.out
clean:
	rm -f *.out *.exe
