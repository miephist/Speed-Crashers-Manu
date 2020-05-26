#version 300 es
#undef lowp
#undef mediump
#undef highp

precision mediump float;

//Color final de la linea
out vec4 FragColor;

//Color de dibujado de las lineas
uniform vec4 color;
 
void main (void) {
    //Asignamos a cada linea un color rojo
    FragColor = color;
}
