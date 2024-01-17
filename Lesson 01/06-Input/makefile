CXX = g++
CXXFLAGS = -std=c++17

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = sample6

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)