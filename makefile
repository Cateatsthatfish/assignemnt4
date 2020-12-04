CC = g++
TARGET = e4
SRC = matrix.cpp main.cpp
$(TARGET):$(SRC)
	$(CC) -o $(TARGET) $(SRC)
	