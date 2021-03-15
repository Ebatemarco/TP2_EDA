/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Simulation.h"

void PrintFloor(Floor* F, Robot* R, long NoRobots)//Por ahora con solo un robot
{
    bool HereIsARobot=1; 
    for(long i= 0; i< (F->Height) ; i++ )
    {
        printf("\n");
        for(long j=0; j< (F->Width); j++)
        {
            for(int k=0; k<NoRobots; k++)//Revisamos si en la casilla hay algun robot de entre los n que tenemos
            {
                if( (i == floor(((R+k)->y))) && (j == floor(((R+k)->x))) )
                {
                    printf(ANSI_COLOR_RED  "* "  ANSI_COLOR_RESET);
                    HereIsARobot=0;
                    break; //Si un robot esta en la casilla no nos importa si en la misma hay mas solo la pintamos una vez
                }
            }
            if(HereIsARobot)//Si en la casilla actual no hay un robot Pinto acorde
            {
                if( ((F->Tiles)[i*(F->Width)+j]) == SUCIO) 
                {
                    printf(ANSI_COLOR_GREEN  "* "  ANSI_COLOR_RESET);
                }
                else if(((F->Tiles)[i*(F->Width)+j]) == LIMPIO) 
                {
                    printf(ANSI_COLOR_YELLOW  "* "  ANSI_COLOR_RESET);
                }
            }
            HereIsARobot=1;
                
        }
        
    }
    printf("\n");
    
}