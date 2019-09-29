#include "mygraphics.h"
#include "SimpleGraphics.h"
#include "Amplificador.h"

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 700;

SDL_Window* oneStageWindow = nullptr;
SDL_Renderer* oneStageRenderer = nullptr;

Amplificador oneStageAmp;
SimpleGraphics osciloscopio;

int main( int argc, char* args[] )
{
    
    int myKey;
    oneStageAmp.recibeDatos();
    
    if( initgraph("OneStage - Carlos Arena", &oneStageWindow, &oneStageRenderer, SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        float freq;
        float VceQ;
        float Vout_peak;
        int Vsatura;
        int Vcorta;
        bool isRunning = true;
        bool &isRunningRef = isRunning;
        

        SDL_Event mariposa;
        oneStageAmp.showMe();
        std::cout << "La ventana   " << oneStageWindow << std::endl;
        std::cout << "El render   " << oneStageRenderer << std::endl;
        //GameLoop
        while (isRunning == true)
        {
            myKey = eventManager(mariposa, isRunningRef);
            //*******************Decido qué hacer de acuerdo a las teclas
            oneStageAmp.changeData(myKey);
            oneStageAmp.setAv(-100,3,50);
            osciloscopio.setRenderer(oneStageRenderer);
            osciloscopio.escalas(oneStageAmp.getVcc(), oneStageAmp.setGetTiempoVisto());
            freq = oneStageAmp.getfrec();
            VceQ = oneStageAmp.getVq();
            Vout_peak = oneStageAmp.getVoutPico();
            Vsatura = oneStageAmp.getVm();
            Vcorta = oneStageAmp.getVn();
            osciloscopio.axis();
            osciloscopio.grid(VceQ);
            osciloscopio.drawSomeFunc(freq, VceQ, Vout_peak, Vsatura, Vcorta);
            //std::cout << "tiempo máximo" << oneStageAmp.setGetTiempoVisto() << std::endl;
            //std::cout << "pixpervgrid: " << osciloscopio.getpixpervgrid() << std::endl;
            //------------ ANCHOR UPDATES ---------------
            osciloscopio.update();
            /*
            SDL_SetRenderDrawColor( oneStageRenderer, 0x00, 0xFF, 0x00, 0xFF );
			SDL_RenderClear( oneStageRenderer );
            SDL_RenderPresent( oneStageRenderer);
			*/	
        }
        

    }

    close(&oneStageWindow, &oneStageRenderer);
}
