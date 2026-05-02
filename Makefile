CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = mhd

SRCS = main.cpp \
       src/Driver.cpp \
       src/Route.cpp \
       src/Ticket.cpp \
       src/Vehicle.cpp \
       src/Bus.cpp \
       src/Tram.cpp \
       src/TransportSystem.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
