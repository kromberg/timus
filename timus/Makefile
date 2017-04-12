TARGET = timus.out
SOLUTION = solution.out
CXX = clang++
CXXFLAGS = -std=c++11 -O2
OBJS = main.o 1002.o
SOLUTION_OBJS = solution.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(SOLUTION): $(SOLUTION_OBJS)
	$(CXX) $(CXXFLAGS) -o $(SOLUTION) $(SOLUTION_OBJS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

1002.o: 1002.cpp
	$(CXX) $(CXXFLAGS) -c 1002.cpp

solution.o: solution.cpp
	$(CXX) $(CXXFLAGS) -c solution.cpp

.PHONY: clean solution

solution: $(SOLUTION)

clean:
	rm $(TARGET) $(OBJS)