#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "ticketsADT.h"
#include "csvread.h"
#define LINE 250
void csvReadInfractions(ticketsADT tickets){


    FILE * infractionFile = fopen(); ///
    if (infractionFile == NULL) {
        perror("Error en la apertura del archivo de infacciones");
        exit(EXIT_FAILURE);
    }
    char s[LINE];
    fgets(s,LINE,infractionFile);
    
}