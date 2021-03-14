/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParseCmLine.h
 * Author: ebatemarco
 *
 * Created on March 14, 2021, 10:48 AM
 */

#ifndef PARSECMLINE_H
#define PARSECMLINE_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include <string.h>
    
#define ERROR1 -1
#define ERROR2 -2
#define ERROR -3
#define OK 1

typedef int (*pCallback) (char *, char*, void *);
    
typedef struct {
    int h;
    int w;
    int robots;
    int mode;
} Data_t; //estructura para guardar lo ingresado por el usuario

int parseCmdline(int argc, char *argv [], pCallback p, void *userData);

#ifdef __cplusplus
}
#endif

#endif /* PARSECMLINE_H */
