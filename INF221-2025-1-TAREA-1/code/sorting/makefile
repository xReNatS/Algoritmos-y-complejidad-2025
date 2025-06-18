# Variables
CXX = g++
CXXFLAGS = -Wall -O2
TARGET = main

# Archivos fuente
SRCS = sorting.cpp algorithms/sort.cpp algorithms/mergesort.cpp algorithms/quicksort.cpp algorithms/selectionsort.cpp

# Regla principal
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Limpiar archivos generados
clean:
	del /Q $(TARGET).exe
