#include "Amplificador.h"

Amplificador::Amplificador(int gananciaDelAmplificador) :
Vcc(10),
Vq(6),
Vin_pico(50),
frecuencia_in(1),
Vsaturation(1),
Vcutoff(9),
tiempo_visto(1000)
{
    Av = gananciaDelAmplificador;
    Vout_pico = Av * Vin_pico / 1000;
}

Amplificador::Amplificador() : 
Av(-100),
Vcc(10),
Vq(6),
Vin_pico(50),
frecuencia_in(1),
Vsaturation(1),
Vcutoff(9),
Vout_pico(5),
tiempo_visto(1000)
{
}
Amplificador::~Amplificador()
{

}
//Función para recibir datos iniciales para el amplificador
void Amplificador::recibeDatos()
{
    std::cout << "Hola, soy Carlos Arena. Bienvenido a OneStage, el simulador de amplificador de una etapa!!!!!" << std::endl;
    std::cout << "Los siguientes valores que ingrese serán para dar inicio a la simulación" << std::endl;
    std::cout << "Podrá variarlos más adelante (Recomendados: 10, 50, 5, 6)" << std::endl;
    std::cout << "Ingrese Vcc inicial en [V]: ";
    std::cin >> Vcc;
    std::cout << "Ingrese Amplitud inicial de la entrada en [mV]: ";
    std::cin >> Vin_pico;
    std::cout << "Ingrese frecuencia inicial de la entrada en [Hz]: ";
    std::cin >> frecuencia_in;
    std::cout << "Ingrese Vce en el punto Q de trabajo inciial en [V]: ";
    std::cin >> Vq;
    std::cout << std::endl;
}
//Función para calcular el voltaje pico de salida
float Amplificador::getVoutPico()
{
    Vout_pico = Av * Vin_pico / 1000;
    return Vout_pico;
}
//Función para calcular el voltaje en un tiempo t_observado en [s]
float Amplificador::get_vo(float t_observado)
{
    float v_salida;
    v_salida = getVoutPico() * sin(2 * M_PI * frecuencia_in * t_observado) + Vq;
    if(v_salida > Vcutoff)
    {
        v_salida = Vcutoff;
    }
    if (v_salida < Vsaturation)
    {
        v_salida = Vsaturation;
    }
    return v_salida;
}
//Realizo cambios en la ganancia
void Amplificador::setAv(int ganancia_max, float freq_min, float freq_max)
{
    Av = 0;
    float freq_out = freq_max + freq_min;
    if (frecuencia_in > 0 && frecuencia_in < freq_out)
    {
        Av = ganancia_max;
        if (frecuencia_in < freq_min)
        {
            Av = (frecuencia_in / freq_min) * ganancia_max;
        }
        if (frecuencia_in > freq_max)
        {
            Av = ((frecuencia_in - freq_out) /(freq_max - freq_out)) * ganancia_max;
        }
    }

}
void Amplificador::setAv(int ganancia_max)
{
    Av = ganancia_max;
}
//Observo Vcc, Vq, Vin_pico, frecuencia y Vout_pico
void Amplificador::showMe()
{
    std::cout << "\n***********************Situación actual*********************\nVcc = " << Vcc << "[V],\nPunto Q en VceQ = " << Vq << "[V]," << std::endl; 
    std::cout << "Frecuencia = " << frecuencia_in << "[Hz], \nVoltaje pico de entrada = " << Vin_pico << "[mV],\n"
    <<  "Cada Cuadro Vertical = 1[V]\n Eje x (tiempo) llega hasta: " << tiempo_visto << "[ms]\n************************************************************" << std::endl;

}

void Amplificador::changeData(int teclaPresionada)
{
    enum KeyPressed
    {
        NO_KEY,
        FLECHA_ARRIBA,
        FLECHA_ABAJO,
        FLECHA_IZQUIERDA,
        FLECHA_DERECHA,
        W_KEY,
        S_KEY,
        A_KEY,
        D_KEY
    };

    switch (teclaPresionada)
        {
        case FLECHA_ARRIBA:
            if (Vq < Vcc - 0.1)
            {
                Vq+=0.1;
            }
            system("clear");
            showMe();
            break;
        case FLECHA_ABAJO:
            if (Vq > 0.1)
            {
                Vq-=0.1;
            }
            system("clear");
            showMe();
            break;
        case FLECHA_IZQUIERDA:
            frecuencia_in-=0.1;
            system("clear");
            showMe();
            break;
        case FLECHA_DERECHA:
            frecuencia_in+=0.1;
            system("clear");
            showMe();
            break;
        case W_KEY:
            Vin_pico++;
            system("clear");
            showMe();
            break;
        case S_KEY:
            Vin_pico--;
            system("clear");
            showMe();
            break;
        case A_KEY:
            Vcc--;
            system("clear");
            showMe();
            break;
        case D_KEY:
            Vcc++;
            system("clear");
            showMe();
            break;
        default:
            break;
        }
}

float Amplificador::getVcc()
{
    return Vcc;
}
float Amplificador::getVq()
{
    return Vq;
}
float Amplificador::getfrec()
{
    return frecuencia_in;
}
float Amplificador::setGetTiempoVisto() //en ms
{
    tiempo_visto = 10;
    tiempo_visto = (frecuencia_in < 20 && frecuencia_in >= 0)? 1000 : tiempo_visto;
    tiempo_visto = (frecuencia_in < 200 && frecuencia_in >= 20)? 50 : tiempo_visto;
    tiempo_visto = (frecuencia_in > 200 && frecuencia_in < 2000)? 5 : tiempo_visto;
    tiempo_visto = (frecuencia_in > 2000)? 1 : tiempo_visto;
    return tiempo_visto;
}
float Amplificador::getVm()
{
    Vsaturation = 0.1 * Vcc;
    return Vsaturation;
}
float Amplificador::getVn()
{
    Vcutoff = 0.9 * Vcc;
    return Vcutoff;
}