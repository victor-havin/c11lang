CXX := g++
CXXFLAGS := -std=c++17 -g -Wall -Wextra

TARGET := c11lang
SRC := c11lang.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)