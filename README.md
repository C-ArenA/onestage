PROGRAMADOR:

//========================================================================================================
//                                                                                                        
//   ####    ###    #####    ##       #####    ####          ###    #####    #####  ##     ##    ###    
//  ##      ## ##   ##  ##   ##      ##   ##  ##            ## ##   ##  ##   ##     ####   ##   ## ##   
//  ##     ##   ##  #####    ##      ##   ##   ###         ##   ##  #####    #####  ##  ## ##  ##   ##  
//  ##     #######  ##  ##   ##      ##   ##     ##        #######  ##  ##   ##     ##    ###  #######  
//   ####  ##   ##  ##   ##  ######   #####   ####         ##   ##  ##   ##  #####  ##     ##  ##   ##  
//                                                                                                        
//========================================================================================================

PROYECTO: 

//=======================================================================
//                                                                       
//   #####   ##     ##  #####   ####  ######    ###     ####    #####  
//  ##   ##  ####   ##  ##     ##       ##     ## ##   ##       ##     
//  ##   ##  ##  ## ##  #####   ###     ##    ##   ##  ##  ###  #####  
//  ##   ##  ##    ###  ##        ##    ##    #######  ##   ##  ##     
//   #####   ##     ##  #####  ####     ##    ##   ##   ####    #####  
//                                                                       
//=======================================================================

Este programa realiza la simulación de un amplificador de una sola etapa en C++ con entorno Linux (Ubuntu 18.04), 
de acuerdo a las siguientes características:

-------> Posibilidad de INGRESAR y VARIAR los siguientes parámetros:
            > Vcc      : Voltaje de polarización en [V]
            > VQ       : Punto de trabajo Q 
                                    (En el programa se controla mediante el voltaje correspondiente) en [V]
            > Vipeak   : Amplitud de la señal sinusoidal de entrada en [mV]
            > frec_in  : Frecuencia de la señal de entrada en [Hz]
-------> Posibilidad de GRAFICAR la salida del amplificador (simulación)
            > Esto se realiza utilizando la librería gráfica SDL2.h
            > [DISCLAIMER]: La librería graphics.h que se debería utilizar (para Linux)
                            está hecha en base a la librería SDL, pero con muchos 
                            errores y/o incompatibilidades que se han salvado al
                            trabajar con la librería aún más fundamental, SDL2. Se tuvo el
                            cuidado de usar solamente su función análoga al putpixel de
                            la librería graphics.h. Es más, se generó una función putpixel
                            para hacerlo más explícito.
            > SDL2 tiene como una de sus principales ventajas que es multiplataforma.
                Además, cuenta con muchas herramientas que en este proyeto nos limitamos de 
                usar para no disminuir la complejidad del mismo. Sin embargo, futuras modificaciones
                pueden contar con estas funciones. Entre ellas, manejo de texto, imágenes y sonido.
-----------------------------------------------------------------------------------------------------------------
NOTAS PARA LA PRIMERA VERSIÓN:
    - Al no estar especificada la introducción de valores de resistencia de carga se asumieron valores arbitrarios
    que definen la ganancia e imitan el filtrado de un amplificador de acuerdo a la frecuencia. En este caso, la
    ganancia es de -100 con frecuencias de corte inferior y superior: 3[Hz] y 50[Hz]. 
    - Este proyecto se encuentra en un repositorio de GitHub: https://github.com/C-ArenA/onestage 

    

                                    