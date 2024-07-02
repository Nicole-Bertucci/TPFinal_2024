#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <ticketsADT.h>

#define ERRORMEMORIA "Error de asignacion de memoria"
#define DATOINVALIDO "Dato ingresado es invalido"

typedef struct tMulta{
    struct tMulta* izq;
    struct tMulta *der;
    char* plate;
    size_t cantidad;
}tMulta;

typedef struct tInfraction{
    char* nameInfr;
   // tMulta * multas;
    tMulta * firstMulta;
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
static char * stringCopy(const char * name){
    size_t largo = strlen(name);
    char * new = malloc(largo+1);
    if (new) {
        perror(ERRORMEMORIA);
        exit(EXIT_FAILURE);   
    }
    strcpy(new, name);
    return new;
}

static tAgency * addAgencyRec(tAgency * agency, size_t id, char * name, size_t * dim){
    int c;
    if (agency == NULL || (c = strcasecmp(agency->nameAgency, name)) > 0) {
        tAgency * new = malloc(sizeof(*new));
        if(new == NULL){
            perror(ERRORMEMORIA);
            exit(EXIT_FAILURE);            
        }
        if (*dim < id) {
            new->infractionsPopularity = malloc(id*sizeof(size_t));
            if(new->infractionsPopularity == NULL){
                perror(ERRORMEMORIA);
                exit(EXIT_FAILURE);            
            }
            
        }
        //*dim = id                 revisar esto...
        new->infractionsPopularity[id-1] = 1;
        new->nameAgency = stringCopy(name);
        new->next = agency; 
        return new;
    }
    if (c == 0) {
        agency->infractionsPopularity[id-1]++;
        return agency;
    }
    agency->next = addAgencyRec(agency->next, id, name, dim);
    return agency;
}

void addAgency (ticketsADT ticket,  size_t id, char * name){
    ticket->firstAgency = addAgencyRec(ticket->firstAgency, id, name, &ticket->dimInfraction);
}






















void addInfraction(ticketsADT ticket, size_t id, const char* name){
    if(ticket->dimInfraction<=id-1){
       ticket->infractions= realloc(ticket->infractions, sizeof(tInfraction)*(id));
       ticket->dimInfraction=id;
    }
    if(ticket->infractions[id-1].nameInfr==NULL){
        ticket->infractions[id-1].nameInfr=stringCopy(name);
        ticket->infractions[id-1].dimMultas=0;
        ticket->infractions[id-1].multasTotales=0;
       // ticket->infractions[id-1].multas=NULL;
       ticket->infractions[id-1].firstMulta=NULL;
    }


}



//devuelve el index +1 del arreglo donde esta la patente 
//o en el caso de lista deja el iterador ahi y devuelve 1 si existe 0 si no
// static int exist(int id, char* plateNumber){

// }

//****VERSION DE ADDMULTA CON ARBOL */
//si encuentra la patente agrega uno a su cantidad, caso contrario agrega la patente
//en el lugar correspondiente siguiendo el orden alfabetico;
static void addMultaRec(tMulta * firstMulta, const char* patente){
    printf("entre\n");

    if(firstMulta==NULL){
        printf("aca llegue\n");
        tMulta* new=malloc(sizeof(tMulta));
        new->plate= stringCopy(patente);
        new->cantidad=1;
        new->der=NULL;
        new->izq=NULL;
        firstMulta=new;
        return;
    }
    printf("me meti aca\n ");
    if(strcmp(firstMulta->plate,patente )<0){
        printf("pase por aca <0\n");
      addMultaRec(firstMulta->der, patente);
    }
     printf("pase por aca\n ");
    if(strcmp(firstMulta->plate,patente )>0){
        printf("UWUUU\n ");
     addMultaRec(firstMulta->izq, patente);
    }
    firstMulta->cantidad++;

}



 void addMulta(ticketsADT ticket, size_t idInfraction, const char* patente, char* agencyName){
    if(ticket->dimInfraction<idInfraction){
        perror(DATOINVALIDO);
        exit(EXIT_FAILURE);
    }
    if(ticket->infractions[idInfraction-1].firstMulta==NULL){
        tMulta* new=malloc(sizeof(tMulta));
        new->plate= stringCopy(patente);
        new->cantidad=1;
        new->der=NULL;
        new->izq=NULL;
        ticket->infractions[idInfraction-1].firstMulta=new;
        return;
    }
addMultaRec(ticket->infractions[idInfraction-1].firstMulta, patente);
 
    // addAgency(ticket,idInfraction, agencyName);
 }
//****VERSION DE ADDMULTA CON VECTORES */

// void addMulta(ticketsADT ticket, size_t idInfraction, const char* patente, char* agencyName ){
// if(ticket->dimInfraction<idInfraction){
//     perror(DATOINVALIDO);
//     exit(EXIT_FAILURE);
// }
// int index=!exist(idInfraction, patente);
//     if(!index){
//      ticket->infractions[idInfraction-1].multas=realloc(ticket->infractions[idInfraction-1].multas, sizeof(tMulta)*(ticket->infractions[idInfraction-1].dimMultas+1));
//     ticket->infractions[idInfraction-1].dimMultas++;
//     index=ticket->infractions[idInfraction-1].dimMultas;
//     ticket->infractions[idInfraction-1].multas[index].plate= stringCopy(patente);
// }
//     ticket->infractions[idInfraction-1].multas[index-1].cantidad++;
//     ticket->infractions[idInfraction-1].multasTotales++;
//     addAgency(ticket, idInfraction, agencyName);
// }





