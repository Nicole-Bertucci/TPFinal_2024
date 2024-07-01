#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <ticketsADT.h>

#define ERRORMEMORIA "Error de asignacion de memoria"

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
tAgency * iterAgency;
}ticketsCDT;

ticketsADT newTicket(){
    ticketsADT new = calloc(1,sizeof(*new));
    if(new == NULL){
        perror(ERRORMEMORIA);
        exit(EXIT_FAILURE);
    }
    return new;
}
static addAgencyRec(tAgency * agency, size_t id, char * name){
    
}

void addAgency (ticketsADT ticket,  size_t id, char* name){
    ticket->firstAgency = addAgencyRec(ticket->firstAgency, id, name);
}




















//@param ticket ciudad en donde ocurren las multas
//@param id numero de identificacion de la infraccion
//@param name descripcion de la infraccion
//agrega una nueva infraccion en la ciudad, si ya existe aborta
void addInfraction(ticketsADT ticket, size_t id, char* name){
    //chequeo si hay espacio
    if(ticket->dimInfraction<=id-1){
       ticket->infractions= realloc(ticket->infractions, sizeof(tInfraction)*(id));
    }
    if(ticket->infractions[id-1].nameInfr==NULL){
        strcpy(ticket->infractions[id-1].nameInfr,name);

    }

}