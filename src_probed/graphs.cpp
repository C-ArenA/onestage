#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

int main()
{
    int gv = -100;
    float volt_out_pico, volt_m, volt_n, t_analizado, vo;
    float vcc, volt_in_pico, freq_in, volt_Q;
    cout << "Bienvenido a OneStage, el simulador de amplificador de una etapa" << endl;

    cout << "Ingrese Vcc en [V]: ";
    cin >> vcc;
    cout << "Ingrese Amplitud de la entrada en [mV]: ";
    cin >> volt_in_pico;
    cout << "Ingrese frecuencia de la entrada en [Hz]: ";
    cin >> freq_in;
    cout << "Ingrese Vce en el punto Q de trabajo [V]: ";
    cin >> volt_Q;
    cout << endl;
 
/*   
    //Valores forzados para las pruebas
    vcc = 10;
    volt_in_pico = 50;
    freq_in = 1;
    volt_Q = 10;
*/    
    //Calculo
    volt_out_pico = gv * volt_in_pico / 1000;
    volt_m = 0.1 * vcc;
    volt_n = 0.9 * vcc;
/*
    //Genero pares
    int i;
    do
    {
        cout << "Ingrese tiempo en [ms]: ";
        cin >> t_analizado;
        vo = volt_out_pico * sin(2*3.14*freq_in*t_analizado) + volt_Q;
        if (vo > volt_n)
        {
            cout << "Cutoff" << endl;
        } 
        else if (vo < volt_m)
        {
            cout << "Saturation" << endl;
        }
        else
        {
            cout << "Sinusoidal" << endl;
        }
        
        cout << "1  para salir, 0 para continuar";
        cin >> i;
        
        
    } while (i == 0);
*/
    SDL_Init(SDL_INIT_EVERYTHING);
    const auto Width = 1360;
    const auto Height = 710;
    SDL_Window* w = SDL_CreateWindow("Graphs", 0, 0, Width, Height, SDL_WINDOW_SHOWN);
    SDL_Renderer* r = SDL_CreateRenderer(w, -1, 0);

    for (auto done = false; !done; )
    {
        SDL_Event e;
        if (!SDL_WaitEvent(&e))
        {
            done = true;
            break;
        }
        switch (e.type)
        {
        case SDL_QUIT:
            done = true;
            break;
        }
        SDL_SetRenderDrawColor(r, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(r);
        SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0xff);
        //auto oldX = -1;
        //auto oldY = 0;
        for (float x = 0; x < 2; x += 0.0001)
        {
            vo = volt_out_pico * sin(2*3.14*freq_in*x) + volt_Q;
            auto y = vo;
            if (vo > volt_n)
            {
                y = volt_n;
            } 
            else if (vo < volt_m)
            {
                y = volt_m;
            }
            else
            {
                y = vo;
            }
            
            SDL_RenderDrawPoint(r, x / 2 * Width, -((y) / 10 * Height) + Height);
        }
        SDL_SetRenderDrawColor(r, 0xff, 0x00, 0x00, 0xff);
        //SDL_RenderDrawLine(r, Width/2, 0, Width/2, Height);
        //SDL_RenderDrawLine(r, 0, Height/2, Width, Height/2);
        SDL_RenderPresent(r);
        
        
    }
    SDL_Quit;

    return 0;
}