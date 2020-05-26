SOURCES := $(wildcard *.cpp)
OBJECTS := $(subst .cpp,.o,$(SOURCES))
LIBS 	:= -lsfml-window -lsfml-graphics -lsfml-system -lIrrlicht
INCLUDE := -I.
CC		:= g++

# Genera el ejecutable en base a todos los .o y librerias que tengamos 
ejecutable: $(OBJECTS)
	$(CC) -o $@ $^ $(INCLUDE) $(LIBS)

# Genera el .o de todos los archivos .cpp que tengamos
%.o: %.cpp
	$(CC) -o $@ -c $^ $(INCLUDE)

# Mostramos por pantalla todos los .cpp y .o
info:
	$(info $(SOURCES))
	$(info $(OBJECTS))

# Include paths (en un futuro)
#CPPFLAGS = -I/usr/include -I/usr/include/eigen3 -I$(PROJECTROOT)/include -I$(PROJECTROOT)/include/nanovg
# Lib paths (en un futuro)
#LDFLAGS = -L/usr/lib -L/usr/lib/x86_64-linux-gnu -L$(PROJECTROOT)/lib