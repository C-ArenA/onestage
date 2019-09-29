#include "mygraphics.h"

//***************************** SECTION FUNCTION DEFINITIONS ********************************
//**************************************** ANCHOR init ************************************
bool initgraph(std::string nombre, SDL_Window** ventana, SDL_Renderer** dibujante, int width, int height)
{
	//Bandera de éxito en el proceso
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		std::cout << "No se pudo inicializar SDL! SDL Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			std::cout << "Peligro, Textura Lineal no habilitada!" << std::endl;
		}

		//Create window
		*ventana = SDL_CreateWindow( nombre.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
		if( ventana == NULL )
		{
			std::cout << "No se pudo crear la ventana! SDL Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			*dibujante = SDL_CreateRenderer( *ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( dibujante == NULL )
			{
				std::cout << "No se pudo crear el Render! SDL Error: " << SDL_GetError() << std::endl;
				success = false;
			}
			
		}
	}
	return success;
}


//**************************************** ANCHOR close ************************************
void close(SDL_Window** ventana, SDL_Renderer** dibujante)
{
	//Destroy window	
	SDL_DestroyRenderer( *dibujante );
	SDL_DestroyWindow( *ventana );
	*ventana = NULL;
	*dibujante = NULL;

	SDL_Quit();
}

//**************************************** ANCHOR eventManager ************************************
int eventManager(SDL_Event evento, bool &simulation_is_running)
{
	int myKey; 	// UpArrow -> 1, DownArrow -> 2, LeftArrow -> 3, RightArrow -> 4
				// noKey -> 0, W -> 5, S -> 6, A -> 7, D -> 8 
	while( SDL_PollEvent( &evento ) != 0 )
		{
			//User requests quit
			if (evento.type == SDL_QUIT)
			{
				simulation_is_running = false;
			}
			else if (evento.type == SDL_KEYDOWN)
			{
				switch (evento.key.keysym.sym)
				{
				case SDLK_UP:
					myKey = 1;
					break;
				case SDLK_DOWN:
					myKey = 2;
					break;
				case SDLK_LEFT:
					myKey = 3;
					break;
				case SDLK_RIGHT:
					myKey = 4;
					break;
				case SDLK_w:
					myKey = 5;
					break;
				case SDLK_s:
					myKey = 6;
					break;
				case SDLK_a:
					myKey = 7;
					break;
				case SDLK_d:
					myKey = 8;
					break;
				case SDLK_ESCAPE:
					simulation_is_running = false;
					break;
				default:
					break;
				}
			}
		}
	return myKey;
}