#include <stdio.h>
#include <time.h>
#include "csvread.h"
#include "ticketsADT.h"
#include "front.h"
#include "queries.h"
//borrar
int main(int argc,const char *argv[]){

    clock_t inicio, fin;
    double tiempo;
    inicio = clock();
    ticketsADT new = newTicket();
    //printf("new finalizo\n");
    csvReadInfractions(argv,new);
    //printf("leido finalizo\n");
    query2(new);
    //printf("Q2 finalizo\n");
    query3(new);
    //printf("Q3 finalizo\n");
    query1(new);
    //printf("Q1 finalizo\n");
    freeTicket(new);
    printf("free finalizo\n");
    fin = clock();
    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("El tiempo transcurrido es %.2f segundos.\n", tiempo);

    return 0;
}