#include <SDL2/SDL.h>
#include <iostream>
//**************************** ANCHOR SimpleGraphics CLASS DEFINITION ******************************
class SimpleGraphics
{
	public:
		SimpleGraphics();
		~SimpleGraphics();
		void setRenderer(SDL_Renderer* el_que_dibuja);
		void setColor(Uint8 r, Uint8 g, Uint8 b);
		//Renders a line
		void drawLine(int x_inicial_primer_octante, int y_inicial_primer_octante, int largo, bool horizontal0_vertical1);
		void putpixel(int x, int y_primer_octante);
        void drawGridLine(int x_inicial_primer_octante, int y_inicial_primer_octante, int largo, bool horizontal0_vertical1);
        void escalas(float vcc, float time);
        void grid(float Vq);
        void axis(); //time in ms
        void drawSomeFunc(float freq, float Vq, float Voutpeak, int Vsat, int Vcut);
        void update();
        int getpixpervgrid();
	private:
		SDL_Renderer* dibujante;
		Uint8 rojo;
		Uint8 verde;
		Uint8 azul;
        int renderHeight;
        int renderWidth;
        int ylevels_in_screen;
        int pix_per_ylevel;
        int xlevels_in_screen;
        int pix_per_xlevel;
        int pix_per_vgrid;
        float limit_time; //[s]
};