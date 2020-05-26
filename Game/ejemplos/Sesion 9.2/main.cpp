#include "uno.h"
#include "dos.h"

int main(void){
    Cuenta c(11);

    while(c.step()){
        dibujar("Tiempo", c);
    }
    return 0;
}