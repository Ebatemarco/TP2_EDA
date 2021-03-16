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

void DeleteSimulation(Simulation* S)
{
    DeleteRobot(S->robs);
    DeleteFloor(S->f);
    free(S);
    return;
}



bool AllClear(Floor* F) //Si el piso esta limpio da 1 
{
    for(long i= 0; i < ((F->Height)*(F->Width)) ; i+=(F->Width) )
    {
        for(long j=0; j<(F->Width); j++)
        {  
            if((F->Tiles)[i+j] == SUCIO)//Si alguna casilla esta sucia nos vamos
                return 0;
        }
        
    }
    return 1; //Si ya revisamos todas las casillas y ninguna esta sucia devolvemos 1
}

void SimulationUpdate(Robot* R, Floor* F, long NoRobots)
{
    for(int i=0; i < (NoRobots);i++)
    {
        srand(time(0));
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
     
}

void ClearPoint(Floor* F, Robot* R, long NoRobots)
{
    for(int i=0;i< NoRobots; i++)
    {
        *( (F->Tiles) + sizeof(bool)* ((int)((R+i)->x)) + sizeof(bool)*((int)((R+i)->y)) * (F->Width)) = LIMPIO;
    }
}



void Simulator(Simulation* Simu)
{
    
    //Modulo Allegro
    must_init(al_init(), "allegro");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_DISPLAY* disp = al_create_display(H_SCALE, W_SCALE);
    must_init(disp, "display");

    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");
    
    must_init(al_init_primitives_addon(), "primitives");
    
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    
    ALLEGRO_EVENT event;
    
    al_start_timer(timer);
    
    while( !(AllClear(Simu->f) ))
    {
        al_wait_for_event(queue, &event);
        
        SimulationUpdate(Simu->robs, Simu->f, Simu->NoRobots);//Vemos la nueva pocicion del robot
        ClearPoint(Simu->f, Simu->robs, Simu->NoRobots);
        PrintFloor(Simu->f, Simu->robs, Simu->NoRobots);//Dibuajmos el piso
        
        bool HereIsARobot=0; //Flag que nos sirve para pintar los robots en un mismo bloque con printf
        for(long i= 0, var=0; i< (Simu->f->Height) ; i++ , var+=10)//Vamos fila a fila
        {
            
            for(long j=0, var2 = 0; j< (Simu->f->Width); j++, var2+=10)//Columna a columna
            {
                for(int k=0;k< (Simu->NoRobots);k++)//Revisamos si en la casilla hay algun robot de entre los n que tenemos
                {
                    if( (i == floor(((Simu->robs+k)->y))) && (j == floor(((Simu->robs+k)->x))) )
                    {
                        al_draw_filled_rectangle(var2, var, var2+10, var+10, al_map_rgba_f(1, 0, 0, 1));
                        HereIsARobot=1;//Marcamos que en la casilla hay robot
                        break; //Si un robot esta en la casilla no nos importa si en la misma hay mas solo la pintamos una vez
                    }
                }
                if(!HereIsARobot)//Si en la casilla actual no hay un robot Pinto acorde
                {
                    if( ((Simu->f->Tiles)[i*(Simu->f->Width)+j]) == SUCIO) //Veo si esta sucia
                    {
                        al_draw_filled_rectangle(var2, var, var2+10, var+10, al_map_rgba_f(0, 0, 0, 0));
                    }
                    else if(((Simu->f->Tiles)[i*(Simu->f->Width)+j]) == LIMPIO) //veo si esta limpia 
                    {
                        al_draw_filled_rectangle(var2, var, var2+10, var+10, al_map_rgba_f(1, 1, 1, 1));
                    }
                }
                HereIsARobot=0;//Reiniciamos el flag
                

            }
            

        }
        
        
        al_flip_display();
        al_rest(1);
        
    }//Mientras el piso este sucio segumos simulando
    
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    
    printf("Todo Limpio (%d)\n", AllClear(Simu->f));
    return;
}
