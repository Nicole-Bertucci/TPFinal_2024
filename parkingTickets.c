#include <stdio.h>
#include <time.h>
#include "csvread.h"
#include "ticketsADT.h"
#include "front.h"
#include "queries.h"

int main(int argc,const char *argv[]){
    clock_t inicio, fin;
    double tiempo;
    inicio = clock();
    ticketsADT new = newTicket();
    csvReadInfractions(argv,new);
    query2(new);
    query3(new);
    query1(new);
    freeTicket(new);
    fin = clock();
    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("El tiempo transcurrido es %.2f segundos.\n", tiempo);
    return 0;
}