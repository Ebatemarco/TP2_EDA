/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Simulation.h"
#include "GraficSupport.h"

Simulation* CreateSimulation(long width, long height, long robCount)
{
    Simulation* Sim = malloc(sizeof(Simulation));
    if(Sim!=NULL)
    {
        Sim->f= CreateFloor(width, height);
        Sim->robs = CreateRobots(robCount,width,height); 
        Sim->TickCount= 0;
        Sim->NoRobots=robCount;
        if( ((Sim->f)!= NULL) && ((Sim->robs)!=NULL) )
        {
            return Sim;
        }
        else
        {
            free(Sim);
            return NULL; 
        }
    }
    else
    {
        free(Sim);
        return NULL; 
    }
}

int SimulationUpdate(Robot* R, Floor* F, long NoRobots)
{
    for(int i=0; i < (NoRobots);i++)//Actualizamos la posicion de cada robot
    {
        srand(time(NULL));
        int Flag = 0;//Creamos el flag para los cuadrantes
        do
        {

            if(Flag>0)
            {
                ((R+i)->x)-=cos((R+i)->Orientation);
                ((R+i)->y)-=sin((R+i)->Orientation);
                ((R+i)->Orientation) = (rand() % 360);//Randomizamos la orientacion
            }
            ((R+i)->x)+=cos((R+i)->Orientation);
            ((R+i)->y)+=sin((R+i)->Orientation);
            Flag=1;


        }while( (((R+i)->x) < 0 || ((R+i)->x) >= (F->Width)) || ( (((R+i)->y) < 0) || (((R+i)->y) >= (F->Height))) );
    }
    return 1; 
}

void ClearPoint(Floor* F, Robot* R, long NoRobots)
{
    for(int i=0;i< NoRobots; i++)//Para cada robot
    {
        *( (F->Tiles) +  ((int)((R+i)->x)) + ((int)((R+i)->y)) * (F->Width)) = LIMPIO;//Me muevo incrementando el punteor del piso tal que x*ancho+y
    }
}

void DeleteSimulation(Simulation* S)
{
    DeleteRobot(S->robs);
    DeleteFloor(S->f);
    free(S);
    return;
}

