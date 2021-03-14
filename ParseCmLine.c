/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ParseCmLine.h"

int parseCmdline(int argc, char *argv [], pCallback p, void *userData) 
{
    int result;
    for (int i=1; i<argc; ++i) 
    {

        if(argv[i][0] == '-') //si arranca con - es porque es una opcion
        {
            if (i != (argc - 1)) //si no es lo ultimo ingresado
            {
                if (argv[i][1] == '\0') //si es una opcion sin clave
                {
                    return ERROR1;
                    printf("ERROR 1\n");
                }
                else 
                {
                    result=p(argv[i]+1, argv[i+1], userData); //guardo la opcion sin el -
                    i++; //salteo la clave
                }
            }
            else //si es lo ultimo ingresado y empieza con -, hay error tipo 2
            {
                return ERROR2;
                printf("ERROR 2\n");
            }
        }
        if(result != OK)
        {
            return result;
        }
    }

}