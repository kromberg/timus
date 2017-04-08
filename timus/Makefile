TARGET = timus
CXX = clang++
CXXFLAGS = -std=c++11 -O2
OBJS = main.o 1002.o


$(TARGET): main.o 1002.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

1002.o: 1002.cpp
	$(CXX) $(CXXFLAGS) -c 1002.cpp

.PHONY: clean

clean:
	rm $(TARGET) $(OBJS)