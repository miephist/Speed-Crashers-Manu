SOURCES := $(wildcard *.cpp)
OBJECTS := $(subst .cpp,.o,$(SOURCES))
LIBS 	:= -lSDL2
INCLUDE := -I. -I$(PROJECTROOT)/Game/include/sdl
LDFLAGS := -L$(PROJECTROOT)/Game/lib -L$(PROJECTROOT)/Game/lib/sdl
CC		:= g++

# Genera el ejecutable en base a todos los .o y librerias que tengamos 
ejecutable: $(OBJECTS)
	$(CC) -o $@ $^ $(INCLUDE) $(LDFLAGS) $(LIBS)

# Genera el .o de todos los archivos .cpp que tengamos
%.o: %.cpp
	$(CC) -o $@ -c $^ $(INCLUDE)

# Limpiamos todos los .o
clean:
	@rm $(OBJECTS)


# Mostramos por pantalla todos los .cpp y .o
info:
	$(info $(SOURCES))
	$(info $(OBJECTS))

# Include paths (en un futuro)
#CPPFLAGS = -I/usr/include -I/usr/include/eigen3 -I$(PROJECTROOT)/include -I$(PROJECTROOT)/include/nanovg
# Lib paths (en un futuro)
#LDFLAGS = -L/usr/lib -L/usr/lib/x86_64-linux-gnu -L$(PROJECTROOT)/lib