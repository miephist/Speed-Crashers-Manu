SOURCES := $(wildcard src/*.cpp) $(wildcard src/*/*.cpp) $(wildcard src/*/*/*.cpp) $(wildcard src/*/*/*/*.cpp)
# recordatorio: $(wildcard src/*.cpp) $(wildcard src/*/*.cpp) poner solo esto cuando no haya que excluir la carpeta de OpenGL
OBJECTS := $(subst src/, obj/,$(subst .cpp,.o,$(SOURCES)))
LIBS 	:= -lIrrlicht -lBulletFileLoader -lBulletDynamics -lBulletCollision -lLinearMath -lBulletSoftBody -lBulletWorldImporter -lfmod -lfmodstudio -lRakNetLibStatic -lSDL
LIBS_OPENGL	:= -lglfw -lGL -lX11 -lassimp -lGLEW -lfreetype
INCLUDE := -I. -I/usr/local/include -I$(PROJECTROOT)/Game/include -I/usr/include/bullet -I/usr/include -I/usr/include/raknet
LDFLAGS := -L$(PROJECTROOT)/Game/lib -L/usr/local/lib -L/usr/local/lib64

CPP_ARCHIVES := -I. -I/src -I/src/Engines -I/src/Game -I/src/Player -I/src/States
CC		:= g++ -g -o3

# Orden de ejecucion para todos los comandos
all: objdir ejecutable

# Orden de ejecucion para el comando run
run: objdir ejecutable runner

# Genera el ejecutable en base a todos los .o y librerias que tengamos 
ejecutable: $(OBJECTS)

	@export LD_LIBRARY_PATH=lib:lib/bullet:lib/fmod:lib/raknet:lib/sdl
	@$(CC) -o $@ $^ $(INCLUDE) $(CPP_ARCHIVES) $(LDFLAGS) $(LIBS) $(LIBS_OPENGL)
	@echo "Ejecutable creado." 

# Ejecuta el videojuego directamente
runner: 
	@sh ./SC.sh

# Genera el .o de todos los archivos .cpp que tengamos
obj/%.o: src/%.cpp
	@$(CC) -o $@ -c $^ $(INCLUDE) $(CPP_ARCHIVES)
	@echo "Compilado $@."

# Mostramos por pantalla todos los .cpp y .o
info:
	$(info $(SOURCES))
	$(info $(OBJECTS))

# Limpiamos todos los .o (incluida su carpeta) y el ejecutable (ya no mas rm *.o)
clean:
	@rm $(OBJECTS)
	@rm -f -r obj
	@rm -f ejecutable
	@echo "Todo limpio."

# Creamos .o en la carpeta obj
objdir:
	@mkdir -p obj/
	@mkdir -p obj/Engines
	@mkdir -p obj/FuzzyLogic
	@mkdir -p obj/Game
	@mkdir -p obj/Player
	@mkdir -p obj/States
	@mkdir -p obj/OpenGL
	@mkdir -p obj/OpenGL/Arbol
	@mkdir -p obj/OpenGL/Arbol/Luces	
	@mkdir -p obj/OpenGL/HUD
	@mkdir -p obj/OpenGL/Interfaces
	@mkdir -p obj/OpenGL/ResourceManager
	@mkdir -p obj/OpenGL/Skybox
	@echo "Creada carpeta obj."

# Comando que te muestra todos los comandos posibles a ejecutar y una breve descripcion.
help:
	@echo -en "\n"
	@echo "=========================== SPEED CRASHERS ============================"
	@echo -en "\n"
	@echo "Comandos posibles a ejecutar:"
	@echo "- make: Compila el videojuego."
	@echo "- make run: Compila y ejecuta el videojuego."
	@echo "- make info: Informacion de los archivos a compilar."
	@echo "- make clean: Borra la carpeta obj (con todos sus .o) y el ejecutable."
	@echo -en "\n"
	@echo "======================================================================="
	@echo -en "\n"
