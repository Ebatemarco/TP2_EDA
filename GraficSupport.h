/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraficSupport.h
 * Author: ebatemarco
 *
 * Created on March 15, 2021, 12:53 PM
 */

#ifndef GRAFICSUPPORT_H
#define GRAFICSUPPORT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
    
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"
    
#define W_SCALE W*5
#define H_SCALE H*5   


void PrintFloor(Floor* F, Robot* R,long NoRobots);

void must_init(bool test, const char *description);

int AllegroSupport(void);

#ifdef __cplusplus
}
#endif

#endif /* GRAFICSUPPORT_H */

