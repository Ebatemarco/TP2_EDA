/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Simulation.h"

Robot* CreateRobots(int NoRobots, long width, long height)
{
    srand( time(0)); 
    Robot* RobotsArr = malloc(sizeof(Robot)*NoRobots);//Reserbamos el espacio para un arreglo de N Robots
    if(RobotsArr != NULL)
    {
        for(int i=0;i< (sizeof(Robot)*NoRobots);i+=sizeof(Robot))
        {
           
                (RobotsArr+i)->x = (rand() % width); //Le asignamos a cada robot una posicion en X
                (RobotsArr+i)->y = (rand() % height);// Una en y
                (RobotsArr+i)->Orientation = (rand() % 360);// y una orientacion 
            
        }
        return RobotsArr; 
    }
    else
    {
        free(RobotsArr);
        return NULL; 
    }
}

void DeleteRobot(Robot* R)
{
    free(R);
    return; 
}