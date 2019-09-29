#include <cmath>
#include <iostream>

class Amplificador
{
	public:
        //Constructores y deconstructores
        Amplificador(int gananciaDelAmplificador);
		Amplificador();
		~Amplificador();
        //Función para recibir datos iniciales para el amplificador
        void recibeDatos();
        //Función para calcular el voltaje pico de salida
        float getVoutPico();
        //Función para calcular el voltaje en un tiempo t_observado
        float get_vo(float t_observado);
        //Realizo cambios en la ganancia
        void setAv(int ganancia_max, float freq_min, float freq_max);
        void setAv(int ganancia_max);
        //Observo Vcc, Vq, Vin_pico, frecuencia y Vout_pico
        void showMe();
        void changeData(int teclaPresionada);
        float getVcc();
        float getVq();
        float getfrec();
        float setGetTiempoVisto();
        int getVm();
        int getVn();
	private:
        //Entradas
		float Vcc; //Voltaje de polarización en [V]
        float Vq; //Voltaje en punto Q (Quiescent) [V] 
        float Vin_pico; //Voltaje pico de señal de entrada [mV] 
        float frecuencia_in; //frecuencia de señal de entrada [Hz]
        //Parámetros
        int Av; //Ganancia del amplificador
        int Vsaturation;
        int Vcutoff;
        //Salidas
        float Vout_pico; //Volatje de salida pico [V]
        float tiempo_visto;
};