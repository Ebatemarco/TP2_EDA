/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Simulation.h"

Floor* CreateFloor(long width, long height)
{
    Floor * Piso = (Floor*) malloc(sizeof(Floor));
    if(Piso != NULL)
    {
        Piso->Height=height;
        Piso->Width=width;
        Piso->Tiles= malloc(sizeof(bool)* width * height);
        
        for(int i=0; i<height;i++)//Lo ensucio
        {
            for(int j=0; j<width;j++)
            {
                (Piso->Tiles)[i+j]=SUCIO;
            }
        }
        return Piso; 
    }
    else
    {
        free(Piso);
        return NULL; 
    }
}

void DeleteFloor(Floor* f)
{
    free(f->Tiles);
    free(f);
    return; 
}