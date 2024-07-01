#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <ticketsADT.h>

typedef struct tMulta{
    char* plate;
    size_t cantidad;
}tMulta;

typedef struct tInfraction{
    char* nameInfr;
    tMulta * multas;
    size_t dimMultas;
    size_t multasTotales;
}tInfraction;

typedef struct tAgency{
    struct tAgency * next;
    char* nameAgency;
    size_t* infractionsPopularity;
}tAgency;

typedef struct ticketsCDT{
tInfraction * infractions;
size_t dimInfraction;
tAgency * firstAgency;
tAgency* iterAgency;
}ticketsCDT;

ticketsADT newTicket(){
    ticketsADT new = calloc(1,sizeof(*new));
    if(new == NULL){
        perror();
        exit();
    }
    new->
}
