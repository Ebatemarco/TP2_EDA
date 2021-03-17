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
    Data_t userData = {H,W,50,1};
    
    parseCmdline(argc, argv, &parseCallback, &userData); 
    
    printf("Modo: %d\nRobots: %d\nH:%d\nW:%d\n",userData.mode, userData.robots, userData.h, userData.w);
    
    if( ( (userData.h <= H) && (userData.w > 0) ) && ( (userData.w <= W) && (userData.w>0) ) )
    {
        if((userData.mode ==1) || (userData.mode==2))
        {
         
            if(userData.robots > 0)
            {
                printf("Modo: %d\nRobots: %d\nH:%d\nW:%d\n",userData.mode, userData.robots, userData.h, userData.w);
                if (userData.mode == 1) 
                {
                    Simulation* Simulation1 = CreateSimulation(userData.w, userData.h, userData.robots);
                    Simulator(Simulation1);
                    printf("Cantidad de Ticks: %d", Simulation1->TickCount);
                    DeleteSimulation(Simulation1);

                }
                else if (userData.mode == 2) 
                {

                    Modo2Funtion(userData.w, userData.h);

                } 
            }
            else
            {
                printf("ERROR: Invalid number of robots\n");
            }
        }
        else 
        {
            printf("ERROR: Invalid Mode\n");
        }
    }
    else
    {
        printf("ERROR: Invalid Height or Width\n");
    }
    return (EXIT_SUCCESS);  
}

int parseCallback(char *key, char *value, void *userData)
{
    Data_t *Data= userData;
    if (strcmp(key,"H") == 0)
    {
        (Data->h)=atoi(value);
    }
    else if (strcmp(key,"W") == 0)
    {
        (Data->w)=atoi(value);
    }
    else if (strcmp(key,"R") == 0)
    {
        (Data->robots)=atoi(value);
    }
    else if (strcmp(key,"M") == 0)
    {
        (Data->mode)=atoi(value);
    }
    else 
    {
        printf("Error, solo se aceptan los parametros de simulacion\n");
        return ERROR;
    }
    return 0;
}


