#include <iostream>
#include "../../include/sdl/SDL.h"

 int main(){

    // Comprobamos que se inicia bien la libreria SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
         std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
         return 1; 
    }

    // Iniciamos la ventana
    SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480,SDL_WINDOW_SHOWN);

    if(win == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Iniciamos el render
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(ren == nullptr){
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Cargamos una imagen bmp
    SDL_Surface *bmp = SDL_LoadBMP("resources/pato.bmp");

    if(bmp == nullptr){
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }    

    // Updateamos la imagen al render
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren,bmp);
    SDL_FreeSurface(bmp);

    if(tex == nullptr){
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }    

    // Bucle para visualizar la imagen
    for(int i=0; i < 3; i++){

        // Limpiamos el render
        SDL_RenderClear(ren);

        // Dibujamos la textura
        SDL_RenderCopy(ren, tex, NULL, NULL);

        // Updateamos la pantalla
        SDL_RenderPresent(ren);

        // Metemos un delay para poder visulizar la imagen mas tiempo
        SDL_Delay(1000);

    }

    // Deletes
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
 }