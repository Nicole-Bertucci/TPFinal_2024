#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <ticketsADT.h>

#define ERRORMEMORIA "Error de asignacion de memoria"
#define DATOINVALIDO "Dato ingresado es invalido"
#define AGENCIAINVALIDA "El nombre de agencia es invalido"

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





















void addInfraction(ticketsADT ticket, size_t id, const char* name){
    if(ticket->dimInfraction<=id-1){
       ticket->infractions= realloc(ticket->infractions, sizeof(tInfraction)*(id));
    }
    if(ticket->infractions[id-1].nameInfr==NULL){
        ticket->infractions[id-1].nameInfr=malloc(sizeof(name));
        strcpy(ticket->infractions[id-1].nameInfr,name);
        ticket->infractions[id-1].dimMultas=0;
        ticket->infractions[id-1].multasTotales=0;
        ticket->infractions[id-1].multas=NULL;
    }

}


//@param ticket ciudad en donde ocurren las multas
//@param idInfraccion numero de identificacion de la infraccion
//@param patente numero de patente a la que se le aplico la multa
//@param nombre de la agencia que escribe la multa
// Si la patente no existe en el arreglo agrega al final del arreglo la multa 
//segun la infraccion dada en @param idInfraccion, en el caso contrario solo
//aumenta la cantidad de multas de esa patente
// Aumenta la cantidad de multas de ese tipo de infraccion
//Aumenta la cantidad de infracciones del tipo generado por la agencia  de nombre agency
void addMulta(ticketsADT ticket, size_t idInfraction, const char* patente, char* agencyName ){
if(ticket->dimInfraction<idInfraction){
    perror(DATOINVALIDO);
    exit(EXIT_FAILURE);
}
int index=!exist(idInfraction, patente);
if(!index){
   ticket->infractions[idInfraction-1].multas=realloc(ticket->infractions[idInfraction-1].multas, sizeof(tMulta)*(ticket->infractions[idInfraction-1].dimMultas+1));
   ticket->infractions[idInfraction-1].dimMultas++;
   ticket->infractions[idInfraction-1].multas[ticket->infractions[idInfraction-1].dimMultas].plate=malloc(sizeof(patente));
    strcpy(ticket->infractions[idInfraction-1].multas[ticket->infractions[idInfraction-1].dimMultas-1].plate, patente);
   index=ticket->infractions[idInfraction-1].dimMultas;
}
ticket->infractions[idInfraction-1].multas[index-1].cantidad++;
ticket->infractions[idInfraction-1].multasTotales++;
addToAgency(ticket->firstAgency, agencyName, idInfraction);
}


//devuelve el index +1 del arreglo donde esta la patente 
//o en el caso de lista deja el iterador ahi y devuelve 1 si existe 0 si no
static int exist(int id, char* plateNumber){

}

//
static void addToAgency(tAgency *first, char* agencyName, int idInfraction){
if(first==NULL){
perror(AGENCIAINVALIDA);
error(EXIT_FAILURE);
}
if(!strcmp(agencyName, first->nameAgency)){
    first->infractionsPopularity[idInfraction-1]++;
}
else{
    addToAgency(first->next,agencyName, idInfraction);
    }
    }
    


