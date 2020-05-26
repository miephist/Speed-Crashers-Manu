DEPURACIÓN VISUAL DE LA IA:

A continuación, se procedera a explicar la depuración visual de la ia presente en el videojuego. Cabe destacar que tambien se dispone de un video explicativo asi como de una demo para poder probar uno mismo todas estas funcionalidades.

Leyenda:

    Este sección la podemos dividir en dos apartados:
    
        - Texto descriptivo: A continuación, explicaremos cada uno:
            - Color de las lineas (Ataque, Mediocampo, Defensa): Cada color representa una de las zonas del campo. En función de en cual este la IA tendrá un comportamiento u otro.
            - Nitro: Cargas de nitro de la IA actual.
            - Semaforo (mismos colores que las lineas): Este icono nos ayudará para tener una visualización más rápida y concisa de en que zona se encuentra actualmente la IA.
            - Poder actual: Cada IA dispone de un poder disponible, por lo que ira rotando entre dicho poder y el cooldown del mismo.
            - Estado: Nos permite saber si la IA actual es atacante o defensiva, lo que influirá en su comportamiento y toma de decisiones.

        - Controles:
            - M: Activar/desactivar el propio modo debug.
            - C: Cambio de cámara en la ia actual en la que nos encontramos. Tendremos disponible tanto cámara enfocada a tercera persona en la ia actual como cámara con perspectiva cenital para poder visualizar todo el escenario y sus componentes.
            - X: Cambia entre las diferentes IAs disponibles en el escenario.
            - Z: Oculta la leyenda.

    
Interfaz:

La interfaz nos permite obtener un vistazo rápido de las características más importantes de la IA (nitro, zona, poder y estado) y que han sido explicadas anteriormente en la leyenda. 

Esta interfaz va en función de la IA en la que estemos actualmente e ira cambiando conforme vayamos cambiando la misma mediante la tecla X.


Código:

En cuanto a código, la representación de las lineas se encuentra en el metodo setLinesEscenario de GameState mientras que su creación esta disponible en el motor gráfico en la clase Lines. Los diferentes controles se encuentran en la clase Jugador y el HUD de la IA se encuentra en la misma en el método updaeDebugHud.

Por último, decir que se ha realizado también la implementación de texto mediante OpenGL (TResourceText.cpp) y la recogida de datos mediante JSON (TResourceJSON.cpp) aunque al final no se hayan utilizado debido a diversos factores.


Participantes del equipo:
    - Borja García Pizarro.
    - Ismael Bertaïba Fernandez.
    - Manuel Juárez Giménez.
    - Pablo Fraile Anuarbe.
    - Sergio Pérez Pérez.
