#include <SDL2/SDL.h>
#include <iostream>
//Starts up SDL and creates window
bool initgraph(std::string nombre, SDL_Window** ventana, SDL_Renderer** dibujante, int width, int height);

//Frees media and shuts down SDL
void close(SDL_Window** ventana, SDL_Renderer** dibujante);

//Maneja los eventos del teclado
int eventManager(SDL_Event evento, bool &simulation_is_running);