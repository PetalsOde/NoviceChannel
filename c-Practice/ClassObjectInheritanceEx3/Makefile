CPP      = g++
CFLAGS   = -Wall 
OBJ      = Cost.o main.o Rectangle.o 
TARGET   = exec

LINKLINE = $(CPP) $(CFLAGS) $(OBJ) -o $(TARGET) 

all: $(TARGET)

$(TARGET):$(OBJ) Makefile
	$(LINKLINE)

Cost.o: Cost.cpp
	$(CPP) -c Cost.cpp -o Cost.o 

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o 

Rectangle.o: Rectangle.cpp
	$(CPP) -c Rectangle.cpp -o Rectangle.o 
