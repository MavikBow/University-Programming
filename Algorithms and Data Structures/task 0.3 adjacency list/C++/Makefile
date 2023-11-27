CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11
SRC = $(wildcard *.cpp)
EXECUTABLES = $(SRC:.cpp=.exe)

.PHONY: all clean

all: $(EXECUTABLES)

%.exe: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf build *.exe
