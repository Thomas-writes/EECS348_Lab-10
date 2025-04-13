CXX = g++

TARGET = calculator.exe

SRC = main.cpp calculator.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(SRC) -o $(TARGET)

clean:
	del $(TARGET) 2>nul || true

run:
	./$(TARGET)