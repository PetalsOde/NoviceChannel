CPP      = g++
CFLAGS   = -Wall 
OBJ      = Books.o main.o Tria.o Shape.o
TARGET   = exec

LINKLINE = $(CPP) $(CFLAGS) $(OBJ) -o $(TARGET) 

all: $(TARGET)

$(TARGET):$(OBJ) Makefile
	$(LINKLINE)

Books.o: Books.cpp
	$(CPP) -c Books.cpp -o Books.o 

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o 

Tria.o: Tria.cpp
	$(CPP) -c Tria.cpp -o Tria.o 

Shape.o: Shape.cpp
	$(CPP) -c Shape.cpp -o Shape.o 
