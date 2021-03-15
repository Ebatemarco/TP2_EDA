/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Simulation.h"

void PrintFloor(Floor* F, Robot* R)//Por ahora con solo un robot
{
    
    for(long i= 0; i< (F->Height) ; i++ )
    {
        printf("\n");
        for(long j=0; j< (F->Width); j++)
        {
            if( (i == floor((R->y))) && (j == floor((R->x))) )
            {
                printf(ANSI_COLOR_RED  "* "  ANSI_COLOR_RESET);
            }
            else
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
                
        }
        
    }
    printf("\n");
    
}