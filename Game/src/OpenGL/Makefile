SOURCES := $(wildcard Arbol/Luces/*.cpp) $(wildcard Arbol/*.cpp) $(wildcard ResourceManager/*.cpp)  $(wildcard *.cpp) $(wildcard Interfaces/*.cpp) $(wildcard HUD/*.cpp) $(wildcard Skybox/*.cpp)
OBJECTS := $(subst .cpp,.o,$(SOURCES))
LIBS 	:= -lglfw -lGL -lX11 -lassimp -lGLEW -lSOIL
INCLUDE := -I. -I$(PROJECTROOT)/Game/include/OpenGL
LDFLAGS := -L$(PROJECTROOT)/Game/lib
# Quitar el -g para la release, hace debuggeable y pesa mas, añadir -o3 para optimizar
CC		:= g++ -g -o3

# Genera el ejecutable en base a todos los .o y librerias que tengamos 
ejecutable: $(OBJECTS)
	@$(CC) -o $@ $^ $(INCLUDE) $(LDFLAGS) $(LIBS)
	@echo "Ejecutable creado." 

# Genera el .o de todos los archivos .cpp que tengamos
%.o: %.cpp
	@$(CC) -o $@ -c $^ $(INCLUDE)
	@echo "Compilado $@"

# Limpiamos todos los .o
clean:
	@rm $(OBJECTS)
	@echo "Todo limpio."

# Mostramos por pantalla todos los .cpp y .o
info:
	$(info $(SOURCES))
	$(info $(OBJECTS))

# Include paths (en un futuro)
#CPPFLAGS = -I/usr/include -I/usr/include/eigen3 -I$(PROJECTROOT)/include -I$(PROJECTROOT)/include/nanovg
# Lib paths (en un futuro)
#LDFLAGS = -L/usr/lib -L/usr/lib/x86_64-linux-gnu -L$(PROJECTROOT)/lib
