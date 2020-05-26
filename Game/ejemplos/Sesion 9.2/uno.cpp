#include <iostream>
#include "dos.h"

void dibujar (const char* texto, const Cuenta& c){

    using namespace std;

    cout <<"=========================================\n"
         << texto << " : " << c.status() <<"\n"
         <<"=========================================\n\n";

    return;
}