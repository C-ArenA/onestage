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
    bool isRunning;
    int myKey;
    float freq;
    float VceQ;
    float Vout_peak;
    float Vsatura;
    float Vcorta;
    system("clear");
    oneStageAmp.recibeDatos();
    system("clear");
    std::cout << "\t****************INSTRUCCIONES******************:\nUtilice las teclas para modificar los siguientes valores: \n" 
        << "Punto Q\t\t\t\t: Flechas arriba/abajo\nFrecuencia\t\t\t: Flechas Izquierda/Derecha\n" 
        << "Amplitud de la señal de entrada\t: Teclas W/S\nVoltaje de Polarización\t\t: Teclas A/D\n\n" 
        << "Algo más: Si quiere salir de la simulación puede presionar la tecla ESC\n\n"
        << "Recuerde: Cada vez que realice una modificación se le mostrarán en la consola los nuevos valores. \n"
        << "Los valores se mostraran así:"<< std::endl;
        oneStageAmp.showMe();
        std::cout << "\n*********************************************************************************\nENTENDIDO? Presione 1 para comenzar o 0 para salir:" << std::endl;
        std::cin >> isRunning;

    if( initgraph("OneStage - Carlos Arena", &oneStageWindow, &oneStageRenderer, SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        SDL_Event mariposa;
        bool &isRunningRef = isRunning;
        
        //*************************** ANCHOR GameLoop ************************************
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
            //------------ ANCHOR UPDATES ---------------
            osciloscopio.update();
        }
        

    }

    close(&oneStageWindow, &oneStageRenderer);
}
