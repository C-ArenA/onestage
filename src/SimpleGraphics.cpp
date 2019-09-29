#include "SimpleGraphics.h"

//************************************** SECTION SimpleGraphics Definitions **********************************

//*************************************** ANCHOR constructor ***************************************
SimpleGraphics::SimpleGraphics() : 
rojo(255), verde(0), azul(0), dibujante(NULL), renderHeight(0), renderWidth(0)
{
}
//*************************************** ANCHOR deconstructor ***************************************
SimpleGraphics::~SimpleGraphics()
{
}
//*************************************** ANCHOR myRenderer ***************************************
void SimpleGraphics::setRenderer(SDL_Renderer* el_que_dibuja)
{
	dibujante = el_que_dibuja;
    int w, h;
    int myheight = SDL_GetRendererOutputSize(dibujante, &w, &h);
    renderWidth = w;
    renderHeight = h;
	SDL_SetRenderDrawColor(dibujante, 0, 0, 0, 255);
    SDL_RenderClear(dibujante);
}
//*************************************** ANCHOR setcolor ***************************************
void SimpleGraphics::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	rojo = r;
	verde = g;
	azul = b;
}
//*************************************** ANCHOR drawLine ***************************************
void SimpleGraphics::drawLine(int x, int y, int length, bool hv)
{
	if(hv) //vertical = 1
	{
		for (int i = 0; i < length; i++)
		{
			putpixel(x, y + i);
		}
	}
	else
	{
		for (int j = 0; j < length; j++)
		{
			putpixel(x + j, y);
		}
	}
	
}
//*************************************** ANCHOR drawLine ***************************************
void SimpleGraphics::drawGridLine(int x, int y, int length, bool hv)
{
	if(hv) //vertical = 1
	{
		for (int i = 0; i < length; i++)
		{
            if ((y + i) % (renderHeight/100) > (renderHeight/200))
            {
                putpixel(x, y + i);
            }
		}
	}
	else
	{
		for (int j = 0; j < length; j++)
		{
            if ((x + j) % (renderWidth/100) > (renderWidth/200))
            {
			    putpixel(x + j, y);
            }
		}
	}
	
}
//*************************************** ANCHOR putpixel ***************************************
void SimpleGraphics::putpixel(int x, int y)
{
	SDL_SetRenderDrawColor( dibujante, rojo, verde, azul, 0xFF );
	SDL_RenderDrawPoint(dibujante, x, renderHeight - y);
}

//*************************************** ANCHOR grid ***************************************
void SimpleGraphics::grid(float Vq) //time in ms
{
	//Dibuja el grid
	setColor(100,100,100);
	for (int i = 0; i <= renderHeight; i += pix_per_ylevel)
	{
		drawGridLine(0,i,renderWidth,0);
	}

	for (int j = 0; j <= renderWidth; j += pix_per_vgrid)
		{
			drawGridLine(j,0,renderHeight,1);
		}		
	//Dibuja niveles especiales: Vcc, Vcorte, Vsatura
	setColor(200,200,0);
	drawGridLine(0,(Vq+1)*pix_per_ylevel,renderWidth,0);
	
}

//*************************************** ANCHOR escalas ***************************************
void SimpleGraphics::escalas(float vcc, float time)
{
	ylevels_in_screen = ceil(vcc) + 2;
	pix_per_ylevel = renderHeight / ylevels_in_screen;

	xlevels_in_screen = time;
	pix_per_xlevel = renderHeight / xlevels_in_screen;

	int ums_in_screen = time + 1;
	int dms_in_screen = time + 10;
	int cms_in_screen = time + 100;

	if (time >= 0 && time < 50)
	{
		pix_per_vgrid = renderWidth / ums_in_screen;
	}
	if(time >= 50 && time < 500)
	{
		pix_per_vgrid = (renderWidth * 10 / dms_in_screen);
	}
	if(time >= 500)
	{
		pix_per_vgrid = (renderWidth * 100 / cms_in_screen);
	}
	limit_time = time / 1000; //[s]
}

//*************************************** ANCHOR axis ***************************************
void SimpleGraphics::axis() //time in ms
{
	setColor(255,255,255);
	/*int volts_in_screen = ceil(vcc) + 2;
	int pix_per_volt = renderHeight / volts_in_screen;
*/
	//Dibujo eje x
	drawLine(0,pix_per_ylevel,renderWidth,0);
	//Dibujo eje y
	drawLine(pix_per_vgrid, 0, renderHeight, 1);
	
}

//*************************************** ANCHOR renderGraphics ***************************************
void SimpleGraphics::update()
{
	SDL_RenderPresent(dibujante);
}

/*
//*************************************** ANCHOR drawOutput ***************************************
void SimpleGraphics::drawOutput(int xo_screen, int yo_screen, float freq_real, float amplitud_real, int desfase_en_X, int Vsaturation, int Vcutoff, float tiempo_visto)
{
	float v_salida;
	for (float x = 0; x < tiempo_visto; x += 0.0001)
	{
		v_salida = amplitud_real * sin(2 * M_PI * freq_real * x) + desfase_en_X;
		if(v_salida > Vcutoff)
		{
			v_salida = Vcutoff;
		}
		if (v_salida < Vsaturation)
		{
			v_salida = Vsaturation;
		}
		int xscreen = xo_screen + 
		putpixel()
	}
	float v_salida;
	for (float x = 0; x < tiempo_visto; x += 0.0001)
	{
		v_salida = amplitud_real * sin(2 * M_PI * freq_real * x) + desfase_en_X;
		xscreen = (x / tiempo_visto) * re
		putpixel()
	}
}
*/
void SimpleGraphics::drawSomeFunc(float freq, float Vq, float Voutpeak, float Vsat, float Vcut)
{
	setColor(0,255,0);
	float v_salida;
	for (float x = 0; x < limit_time; x += 0.0001)
	{
		v_salida = Voutpeak * sin(2 * M_PI * freq * x) + Vq;
		if(v_salida > Vcut)
		{
			v_salida = Vcut;
		}
		if (v_salida < Vsat)
		{
			v_salida = Vsat;
		}
		float xscreenf = ((x * (renderWidth - pix_per_vgrid))/ limit_time) + pix_per_vgrid;
		int xscreen = ceil(xscreenf);
		float yLevel = v_salida + 1;
		int yscreen = yLevel * pix_per_ylevel;
		putpixel(xscreen,yscreen);
	}
	//std::cout << "Tenemos limit_time: " << limit_time << std::endl;	 
}

int SimpleGraphics::getpixpervgrid()
{
	return pix_per_vgrid;
}
//-----------------------------------------------------------------------------------------!SECTION 
