SOURCES := $(wildcard *.cpp)
OBJECTS := $(subst .cpp,.o,$(SOURCES))
LIBS 	:= -lIrrlicht -lBulletFileLoader -lBulletDynamics -lBulletCollision -lLinearMath -lBulletSoftBody -lBulletWorldImporter -lfmod -lfmodstudio -lRakNetLibStatic -lSDL
INCLUDE := -I. -I/usr/local/include -I$(PROJECTROOT)/Game/include -I/usr/include/bullet -I/usr/include -I/usr/include/raknet
LDFLAGS := -L$(PROJECTROOT)/Game/lib -L/usr/local/lib -L/usr/local/lib64
CC		:= g++

# Genera el ejecutable en base a todos los .o y librerias que tengamos 
ejecutable: $(OBJECTS)
	$(CC) -o $@ $^ $(INCLUDE) $(LDFLAGS) $(LIBS) 

# Genera el .o de todos los archivos .cpp que tengamos
%.o: %.cpp
	$(CC) -o $@ -c $^ $(INCLUDE)

# Mostramos por pantalla todos los .cpp y .o
info:
	$(info $(SOURCES))
	$(info $(OBJECTS))

# Limpiamos todos los .o y el ejecutable (ya no mas rm *.o)
clean:
	@rm $(OBJECTS)
	@rm -f ejecutable
	@echo "Todo limpio"

# INSTRUCCIONES RAKNET
# Debeis incluir el archivo .so de Raknet en vuestra carpeta /usr/local/lib para ello ejecutar
# una vez dentro de la carpeta donde esta el .so: sudo cp libRakNetLibStatic.so /usr/local/lib

# INSTRUCCIONES SDL
# En caso de que os salga error, aplicarlos los mismos pasos que con Raknet (en este caso habria
# que copiar 4 .so).
# Si no os funciona, tendreis que buildearlo con CMake. En ese caso avisadme.

# Comando para generar .so a partir de un .a: gcc -shared -o lib.so lib.a