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

Simulation* CreateSimulation(long width, long height, long robCount)
{
    Simulation* Sim = malloc(sizeof(Simulation));
    if(Sim!=NULL)
    {
        Sim->f= CreateFloor(width, height);
        Sim->robs = CreateRobots(robCount,width,height); 
        Sim->TickCount= 0;
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

void DeleteSimulation(Simulation* S)
{
    DeleteRobot(S->robs);
    DeleteFloor(S->f);
    free(S);
    return;
}

void PrintFloor(Floor* F, Robot* R)//Por ahora con solo un robot
{
    
    for(long i= 0; i< (F->Height) ; i++ )
    {
        printf("\n");
        for(long j=0; j< (F->Width); j++)
        {
            if( (i == (R->y)) && (j == (R->x)) )
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
bool AllClear(Floor* F) //Si el piso esta limpio da 1 
{
    for(long i= 0; i< (F->Height) ; i++ )
    {
        for(long j=0; j<(F->Width); j++)
        {  
            if((F->Tiles)[i+j] == SUCIO)//Si alguna casilla esta sucia nos vamos
                return 0;
        }
        
    }
    return 1; //Si ya revisamos todas las casillas y ninguna esta sucia devolvemos 1
}
void SimulationUpdate(Robot* R, Floor* F)
{
    
    srand(time(0));
    int Flag = 0;//Creamos el flag para los cuadrantes
    do
    {
        
        if(Flag>0)//Vemos en que caso estamos
        {
            R->Orientation = (rand() % 360);//Randomizamos la orientacion
            switch(Flag){//En base al flag restauramos el posicion previa del robot
                case 1: R->x -=1 ;break;
                case 2: R->y -=1 ;break;
                case 3: R->x +=1 ;break;
                case 4: R->y +=1 ;break;
                case 5: R->y -=1 ;
                        R->x -=1 ;break;
                case 6: R->y -=1 ;
                        R->x +=1 ;break;
                case 7: R->y +=1 ; 
                        R->x +=1 ;break;
                case 8: R->y +=1 ;
                        R->x -=1 ;break;
                default: break; 
                
            }
            
        }
        if( (R->Orientation) >= 337 || (R->Orientation) < 22 )//Elrobot se mueve en 4 direcciones nada mas
        {
            R->x += 1 ;
            Flag = 1; 
        }
        else if( (R->Orientation) <67 && (R->Orientation) >= 22)
        {
            R->y+=1;
            R->x+=1;
            Flag=5;
            
        }
        else if( (R->Orientation) >= 67 && (R->Orientation) < 112 )
        {
            R->y += 1 ;
            Flag =2;
        }
        else if((R->Orientation) >= 112 && (R->Orientation) < 157)
        {
            R->y+=1;
            R->x-=1;
            Flag=6;
        }
        else if((R->Orientation) < 202 && (R->Orientation) >= 157 )
        {
            R->x -= 1 ;
            Flag =3;
        }
        else if((R->Orientation) >= 202 && (R->Orientation) < 247)
        {
            R->y-=1;
            R->x-=1;
            Flag=7;
        }
        else if( (R->Orientation) >= 247 && (R->Orientation) < 292 )
        {
            R->y -= 1 ;
            Flag =4;
        }
        else if( (R->Orientation) >= 292 && (R->Orientation) < 337 )
        {
            R->y-=1;
            R->x+=1;
            Flag=8;
        }
        
        
    }while( ((R->x) < 0 || (R->x) >= (F->Width)) || ( ((R->y) < 0) || ((R->y) >= (F->Height))) );
    
     
}

void ClearPoint(Floor* F, Robot* R)
{
    *( (F->Tiles) + sizeof(bool)*(R->x) + sizeof(bool)*(R->y) * (F->Width)) = LIMPIO;
}

void Simulator(Simulation* Simu)
{
    while( !(AllClear(Simu->f) ))//Mientras el piso este sucio segumos simulando
    {
        PrintFloor(Simu->f, Simu->robs);//Dibuajmos el piso 
        SimulationUpdate(Simu->robs, Simu->f);//Vemos la nueva pocicion del robot
        ClearPoint(Simu->f, Simu->robs);
        sleep(TIME);
    }
    printf("Todo Limpio (%d)\n", AllClear(Simu->f));
    return;
}
