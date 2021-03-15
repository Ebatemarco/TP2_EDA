/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ebatemarco
 *
 * Created on March 13, 2021, 10:22 AM
 */
#include "ParseCmLine.h"
#include "Simulation.h"

typedef struct {
    int h;
    int w;
    int robots;
    int mode;
} Data_t; //estructura para guardar lo ingresado por el usuario

int parseCallback(char *key, char *value, void *userData);

int main(int argc, char** argv) 
{
    Data_t userData = {4,6,1,1};
    
    parseCmdline(argc, argv, &parseCallback, &userData); 
    
    printf("Modo: %d\nRobots: %d\nH:%d\nW:%d\n",userData.mode, userData.robots, userData.h, userData.w);
    
    Simulation* Simulation1 = CreateSimulation(5,5,2)/*(userData.w, userData.h , userData.robots)*/; 
    Simulator(Simulation1);
    DeleteSimulation(Simulation1); 
    return (EXIT_SUCCESS);  
}

int parseCallback(char *key, char *value, void *userData)
{
    Data_t *Data= userData;
    static int i=0;
    if (strcmp(key,"height") == 0)
    {
        (Data->h)=value;
    }
    else if (strcmp(key,"width") == 0)
    {
        (Data->w)=value;
    }
    else if (strcmp(key,"robots") == 0)
    {
        (Data->robots)=value;
    }
    else if (strcmp(key,"mode") == 0)
    {
        (Data->mode)=value;
    }
    else {
        printf("Error, solo se aceptan los parametros de simulacion\n");
        return ERROR;
    }
}


