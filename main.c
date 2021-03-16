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
    Data_t userData = {5,4,1,1};
    
    parseCmdline(argc, argv, &parseCallback, &userData); 
    
    printf("Modo: %d\nRobots: %d\nH:%d\nW:%d\n",userData.mode, userData.robots, userData.h, userData.w);
    
    if (userData.mode == 1) 
    {
        Simulation* Simulation1 = CreateSimulation(userData.w, userData.h, userData.robots);
        Simulator(Simulation1);
        DeleteSimulation(Simulation1);
    }
    else if (userData.mode == 2) 
    {
        long t2 = 0;
        long t1 = 0;
        int n = 1;
        do
        {
            t1 = t2;
            t2 = 0;
            for (int i = 0; i < 1000; ++i) 
            {
                Simulation* Simulation1 = CreateSimulation(userData.w, userData.h, n);
                Simulator2(Simulation1);
                t2 += Simulation1->TickCount;
                DeleteSimulation(Simulation1);


            }
            n++;
            t2 /= 1000;
            printf("promedio: %i", t2);


        } while (abs(t1 - t2) > 0.1);
    } 
    return (EXIT_SUCCESS);  
}

int parseCallback(char *key, char *value, void *userData)
{
    Data_t *Data= userData;
    if (strcmp(key,"height") == 0)
    {
        (Data->h)=atoi(value);
    }
    else if (strcmp(key,"width") == 0)
    {
        (Data->w)=atoi(value);
    }
    else if (strcmp(key,"robots") == 0)
    {
        (Data->robots)=atoi(value);
    }
    else if (strcmp(key,"mode") == 0)
    {
        (Data->mode)=atoi(value);
    }
    else {
        printf("Error, solo se aceptan los parametros de simulacion\n");
        return ERROR;
    }
    return 0;
}


