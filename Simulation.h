/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Simulation.h
 * Author: ebatemarco
 *
 * Created on March 14, 2021, 10:50 AM
 */

#ifndef SIMULATION_H
#define SIMULATION_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
    
#define H 100
#define W 70
#define SUCIO 0
#define LIMPIO 1
#define TIME 1   
    
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct{
    long Width;
    long Height;
    bool* Tiles;
    
}Floor;

typedef struct{
    int Orientation;
    double x;
    double y;
}Robot;

typedef struct{
    Robot * robs;
    Floor * f;
    long TickCount; 
}Simulation;

Floor* CreateFloor(long width, long height);

void DeleteFloor(Floor* f);

Robot* CreateRobots(int NoRobots, long width, long height);

void DeleteRobot(Robot* R);

Simulation* CreateSimulation(long width, long height, long robCount);

void DeleteSimulation(Simulation* S);

void PrintFloor(Floor* F, Robot* R);//Por ahora con solo un robot

bool AllClear(Floor* F); //Si el piso esta limpio da 1

void SimulationUpdate(Robot* R, Floor* F);

void ClearPoint(Floor* F, Robot* R);

void Simulator(Simulation* Simu);


#ifdef __cplusplus
}
#endif

#endif /* SIMULATION_H */

