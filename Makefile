# Variables del compilador
CXX = g++
CXXFLAGS = -Wall -g

# Nombre del ejecutable
TARGET = arbol_b_mas

# Archivos objeto
OBJS = main.o ArbolBMas.o

# Regla principal: compilar todo
all: $(TARGET)

# Regla para enlazar los archivos objeto y generar el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regla para compilar main.cpp
main.o: main.cpp ArbolBMas.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Regla para compilar ArbolBMas.cpp
ArbolBMas.o: ArbolBMas.cpp ArbolBMas.h
	$(CXX) $(CXXFLAGS) -c ArbolBMas.cpp

# Regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Limpiar archivos objeto y el ejecutable
clean:
	rm -f $(OBJS) $(TARGET)
