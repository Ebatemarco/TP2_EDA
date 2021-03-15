/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Simulation.h"
#include "GraficSupport.h"




void PrintFloor(Floor* F, Robot* R, long NoRobots)
{
    bool HereIsARobot=0; //Flag que nos sirve para pintar los robots en un mismo bloque con printf
    for(long i= 0; i< (F->Height) ; i++ )//Vamos fila a fila
    {
        printf("\n");
        for(long j=0; j< (F->Width); j++)//Columna a columna
        {
            for(int k=0;k< (NoRobots);k++)//Revisamos si en la casilla hay algun robot de entre los n que tenemos
            {
                if( (i == floor(((R+k)->y))) && (j == floor(((R+k)->x))) )
                {
                    printf(ANSI_COLOR_RED  "* "  ANSI_COLOR_RESET);
                    HereIsARobot=1;//Marcamos que en la casilla hay robot
                    break; //Si un robot esta en la casilla no nos importa si en la misma hay mas solo la pintamos una vez
                }
            }
            if(!HereIsARobot)//Si en la casilla actual no hay un robot Pinto acorde
            {
                if( ((F->Tiles)[i*(F->Width)+j]) == SUCIO) //Veo si esta sucia
                {
                    printf(ANSI_COLOR_GREEN  "* "  ANSI_COLOR_RESET);
                }
                else if(((F->Tiles)[i*(F->Width)+j]) == LIMPIO) //veo si esta limpia 
                {
                    printf(ANSI_COLOR_YELLOW  "* "  ANSI_COLOR_RESET);
                }
            }
            HereIsARobot=0;//Reiniciamos el flag
                
        }
        
    }
    printf("\n");
    
}

void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}
