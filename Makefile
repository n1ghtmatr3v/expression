# Makefile для сборки проекта

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Цель по умолчанию: сборка основного приложения
all: program

program: main.o expression.o
	$(CXX) $(CXXFLAGS) -o program main.o expression.o

main.o: main.cpp expression.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

expression.o: expression.cpp expression.hpp
	$(CXX) $(CXXFLAGS) -c expression.cpp

# Цель для сборки и запуска тестов
test: test.o expression.o
	$(CXX) $(CXXFLAGS) -o test test.o expression.o
	./test

test.o: test.cpp expression.hpp
	$(CXX) $(CXXFLAGS) -c test.cpp

.PHONY: all test clean

clean:
	rm -f *.o program test
