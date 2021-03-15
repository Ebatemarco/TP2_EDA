/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Simulation.h"
#include "GraficSupport.h"




void PrintFloor(Floor* F, Robot* R, long NoRobots)//Por ahora con solo un robot
{
    bool HereIsARobot=1; 
    for(long i= 0; i< (F->Height) ; i++ )
    {
        printf("\n");
        for(long j=0; j< (F->Width); j++)
        {
            for(int k=0;k< (sizeof(Robot)*NoRobots);k+=sizeof(Robot))//Revisamos si en la casilla hay algun robot de entre los n que tenemos
            {
                if( (i == floor(((R+k)->y))) && (j == floor(((R+k)->x))) )
                {
                    printf(ANSI_COLOR_RED  "* "  ANSI_COLOR_RESET);
                    HereIsARobot=0;
                    break; //Si un robot esta en la casilla no nos importa si en la misma hay mas solo la pintamos una vez
                }
            }
            if(HereIsARobot)//Si en la casilla actual no hay un robot Pinto acorde
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
            HereIsARobot=1;
                
        }
        
    }
    printf("\n");
    
}


int AllegroSupport(void)
{
    must_init(al_init(), "allegro");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_DISPLAY* disp = al_create_display(H*5, W*5);
    must_init(disp, "display");

    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");
    
    must_init(al_init_primitives_addon(), "primitives");

    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    
    return 0;
}

int AllegroFloor(Floor* F, Robot* R, long NoRobots)
{   
    //ALLEGRO_EVENT event;
    
    
    bool HereIsARobot=1; 
    for(long i= 0; i< (F->Height) ; i++ )
    {
        printf("\n");
        for(long j=0; j< (F->Width); j++)
        {
            for(int k=0;k< (sizeof(Robot)*NoRobots);k+=sizeof(Robot))//Revisamos si en la casilla hay algun robot de entre los n que tenemos
            {
                if( (i == floor(((R+k)->y))) && (j == floor(((R+k)->x))) )
                {
                    al_draw_filled_rectangle(j, i, j+(W/(F->Width)), i+(W/(F->Height)), al_map_rgba_f(0, 0, 1, 1));
                    HereIsARobot=0;
                    break; //Si un robot esta en la casilla no nos importa si en la misma hay mas solo la pintamos una vez
                }
            }
            if(HereIsARobot)//Si en la casilla actual no hay un robot Pinto acorde
            {
                if( ((F->Tiles)[i*(F->Width)+j]) == SUCIO) 
                {
                    al_draw_filled_rectangle(j, i, j+(W/(F->Width)), i+(W/(F->Height)), al_map_rgba_f(0, 0, 0, 0));
                }
                else if(((F->Tiles)[i*(F->Width)+j]) == LIMPIO) 
                {
                    al_draw_filled_rectangle(j, i, j+(W/(F->Width)), i+(W/(F->Height)), al_map_rgba_f(1, 0, 0, 1));
                }
            }
            HereIsARobot=1;
                
        }
        
    }
}

void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}