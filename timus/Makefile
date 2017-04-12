TARGET = timus.out
SOLUTION = solution.out
CXX = clang++
CXXFLAGS = -g -std=c++11 -O2
OBJS = main.o 1002.o
SOLUTION_OBJS = solution.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(SOLUTION): $(SOLUTION_OBJS)
	$(CXX) $(CXXFLAGS) -o $(SOLUTION) $(SOLUTION_OBJS)

1002.generator.out: 1002.generator.o
	$(CXX) $(CXXFLAGS) -o 1002.generator.out 1002.generator.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

1002.o: 1002.cpp
	$(CXX) $(CXXFLAGS) -c 1002.cpp

1002.generator.o: 1002.generator.cpp
	$(CXX) $(CXXFLAGS) -c 1002.generator.cpp

solution.o: solution.cpp
	$(CXX) $(CXXFLAGS) -c solution.cpp

.PHONY: clean solution 1002.generator

solution: $(SOLUTION)

1002.generator: 1002.generator.out

clean:
	rm $(TARGET) $(OBJS)