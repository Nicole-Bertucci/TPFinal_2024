#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "ticketsADT.h"
#include "csvread.h"

#define ERRORMEMORIA "Error de asignacion de memoria\n"
#define DATOINVALIDO "Dato ingresado es invalido"
#define NOPLATES "No plate"
#define BLOQUE 10
#define ERRORFIN "Error en el recorrido de las Agencias"
typedef struct tMulta{
    struct tMulta *izq;
    struct tMulta *der;
    char plate[PLATE];
    size_t cantidad;
}tMulta;

typedef struct tInfraction{
    char nameInfr[DESCRIPTION];
    tMulta * firstMulta;
    size_t dimMultas;
    size_t multasTotales;
    size_t idNumber;
}tInfraction;

typedef struct tAgency{
    struct tAgency * next;
    char nameAgency[ISSUINGAGENCY];
    size_t* infractionsPopularity;

}tAgency;

typedef struct ticketsCDT{
    tInfraction * infractions;
    size_t dimInfraction;
    size_t occupiedInfraction; //index de array de infracciones donde esta el ultimo elemento no vacio
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

static int comparar(const void *a, const void *b){
    tInfraction *i1 = (tInfraction *)a;
    tInfraction *i2 = (tInfraction *)b;
    return (i1->idNumber > i2->idNumber) - (i1->idNumber < i2->idNumber);
}
void sortByID(ticketsADT ticket){
    qsort(ticket->infractions, ticket->occupiedInfraction+1,sizeof(tInfraction), &comparar);
}

static int alf(const void *a, const void *b){
    tInfraction *i1 = (tInfraction *)a;
    tInfraction *i2 = (tInfraction *)b;
    return strcmp(i1->nameInfr, i2->nameInfr);
}
void sortByAlph(ticketsADT ticket){
    qsort(ticket->infractions, ticket->occupiedInfraction+1, sizeof(tInfraction), &alf);
}


static int cmp(const void *a, const void *b){
    tInfraction *i1 = (tInfraction *)a;
    tInfraction *i2 = (tInfraction *)b;
    int c = i2->multasTotales - i1->multasTotales;
    if (c == 0) {
        c = strcmp(i1->nameInfr,i2->nameInfr);
    }
    return c;
}
void sortByTotal(ticketsADT ticket){
    qsort(ticket->infractions, ticket->occupiedInfraction+1, sizeof(tInfraction), &cmp);
}


static tAgency * addAgencyRec(tAgency * agency, const char * name, size_t index, size_t dimInfraction){
    int c;
    if (agency == NULL || (c = strcmp(agency->nameAgency, name)) > 0) {
        tAgency * new = malloc(sizeof(*new));
        if(new == NULL){
            perror(ERRORMEMORIA);
            exit(EXIT_FAILURE);
        }
        new->infractionsPopularity = calloc(dimInfraction, sizeof(size_t));
        if (new->infractionsPopularity == NULL) {
            perror(ERRORMEMORIA);
            exit(EXIT_FAILURE);
        }
        new->infractionsPopularity[index] = 1;
        strcpy(new->nameAgency,name);
        new->next = agency;
        return new;
    }
    if (c == 0) {
        agency->infractionsPopularity[index]++;
        return agency;
    }
    agency->next = addAgencyRec(agency->next, name, index, dimInfraction);
    return agency;
}

void addAgency(ticketsADT ticket, const char * name, size_t index){
    ticket->firstAgency = addAgencyRec(ticket->firstAgency, name, index, ticket->dimInfraction);
}

void addInfraction(ticketsADT ticket, size_t id, const char* name){
    if(ticket->occupiedInfraction%BLOQUE==0){
        ticket->infractions= realloc(ticket->infractions, sizeof(tInfraction)*(ticket->dimInfraction+BLOQUE));
        ticket->occupiedInfraction=(ticket->dimInfraction==0)?-1:(ticket->occupiedInfraction);
        ticket->dimInfraction+=BLOQUE;
    }
    int i = ticket->occupiedInfraction+1;
    strcpy(ticket->infractions[i].nameInfr,name);
    ticket->infractions[i].dimMultas=0;
    ticket->infractions[i].multasTotales=0;
    ticket->infractions[i].firstMulta=NULL;
    ticket->infractions[i].idNumber=id;

    (ticket->occupiedInfraction)++;
}
void resize(ticketsADT ticket){
    ticket->infractions= realloc(ticket->infractions, sizeof(tInfraction)*(ticket->dimInfraction));
}

//busca el numero de index del arreglo de infracciones segun el numero de identificacion de la infraccion.
//devuelve el index de la infraccion con ese id, devuelve -1 en el caso de que no exista ese numero de identificacion.
size_t findIndexById(const ticketsADT ticket, size_t id, size_t dim){
    if(id<0){
        perror(DATOINVALIDO);
        exit(EXIT_FAILURE);
    }

    for(int min=0, max=dim-1;min<=max;){
        int i=(max+min)/2;
        if(ticket->infractions[i].idNumber==id){
            return i;
        }

        else if(ticket->infractions[i].idNumber<id){
            min=i+1;
        }

        else if(ticket->infractions[i].idNumber>id){
            max=i-1;
        }
    }
    return -1;
}

static tMulta * newMulta(const char* plate){
    tMulta* new = malloc(sizeof(tMulta));
    if(new == NULL){
        perror(ERRORMEMORIA);
        exit(EXIT_FAILURE);
    }
    strcpy(new->plate,plate);
    new->der=NULL;
    new->izq=NULL;
    new->cantidad=1;
    return new;
}

//si encuentra la patente agrega uno a su cantidad, caso contrario agrega la patente
//en el lugar correspondiente siguiendo el orden alfabetico;
static void addMultaRec(tMulta* first, const char* patente, size_t *dim){
    int dif= strcmp(patente,first->plate);
    if(dif==0) {
        first->cantidad++;
    }
    else if(dif<0) {
        if(first->izq == NULL){
            tMulta *new=newMulta(patente);
            first->izq=new;
            *dim+=1;
        }
        else{
            addMultaRec(first->izq, patente, dim);
        }
    }
    else if(dif>0) {
        if(first->der == NULL){
            tMulta *new=newMulta(patente);
            first->der=new;
            *dim+=1;
        }
        else{
            addMultaRec(first->der, patente,dim );
        }
    }
}


void addMulta(ticketsADT ticket, size_t id, const char* patente, const char* agencyName){
    int index;
    if(ticket->infractions[ticket->occupiedInfraction].idNumber>id){
        //ordenar(ticket);
    }

    if((index=findIndexById(ticket, id, ticket->occupiedInfraction+1))==-1){
        return;
    }

    if(ticket->infractions[index].firstMulta == NULL){
        ticket->infractions[index].firstMulta = newMulta(patente);
        ticket->infractions[index].dimMultas = 1;
    }
    else{
        addMultaRec(ticket->infractions[index].firstMulta, patente, &(ticket->infractions[index].dimMultas));
    }
    ticket->infractions[index].multasTotales++;
    addAgency(ticket, agencyName, index);
}

void newInf(ticketsADT from,ticketsADT to, size_t index1, size_t index2){
        to->infractions[index2].dimMultas=from->infractions[index1].dimMultas;
        to->infractions[index2].idNumber=from->infractions[index1].idNumber;
        to->infractions[index2].multasTotales=from->infractions[index1].multasTotales;
        strcpy(to->infractions[index2].nameInfr,from->infractions[index1].nameInfr);
        to->infractions[index2].firstMulta=from->infractions[index1].firstMulta;
    }

//deja en new la copia del vector ticket
void cpyInf(ticketsADT  ticket, ticketsADT new,  size_t dim){
    if(dim<=0){
        perror(DATOINVALIDO);
        exit(EXIT_FAILURE);
    }
    new->infractions=realloc(new->infractions, sizeof(tInfraction)*dim);
    for(int i=0; i<dim; i++){
        newInf(ticket,new, i,i);
    }
}

// @return el index de la infraccion con la mayor cantidad de multas segun el dim
size_t findMax(ticketsADT ticket, size_t dim, size_t *newIndex){
    if(dim<0){
        perror(DATOINVALIDO);
        exit(EXIT_FAILURE);
    }
    int max=0, index=0, change=0, k=0;
    for(int i=0; i<dim; i++){

     if(ticket->infractions[i].multasTotales==max){
        if(strcmp(ticket->infractions[i].nameInfr, ticket->infractions[k].nameInfr)<=0){

                change=1;

            }
        }
    if(change==1||ticket->infractions[i].multasTotales>max){
          max=ticket->infractions[i].multasTotales;
          k=i;

          index=ticket->infractions[i].idNumber;

        }

        change=0;

    }

   (*newIndex)=k;
    return index;

}
size_t getOccupied(const ticketsADT ticket){
    return ticket->occupiedInfraction;
}

size_t getId(const ticketsADT ticket, size_t index){
    return ticket->infractions[index].idNumber;
}
size_t cantInfraction(const ticketsADT ticket){
    return ticket->dimInfraction;
}

size_t getTotalFines(ticketsADT ticket, size_t index){
    return ticket->infractions[index].multasTotales;
}
//se usa en la Q3 y Q2
char* getInfractionName(ticketsADT ticket, size_t index){
    return ticket->infractions[index].nameInfr;
}

//Q2
size_t mostpopular(ticketsADT ticket, size_t * index){
    if (ticket->iterAgency == NULL) {
        fprintf(stderr, ERRORFIN);
        exit(EXIT_FAILURE);
    }
    size_t aux = 0;
    size_t auxindex = 0;
    for (size_t i = 0; i < ticket->dimInfraction; i++){
        int c;
        if ((c = ticket->iterAgency->infractionsPopularity[i]) > aux) {
            aux = c;
            auxindex = i;
        }
    }
    *index = auxindex;
    return aux;
}

void beginAgency(ticketsADT ticket){
    ticket->iterAgency = ticket->firstAgency;
}
char * getNameAgency(ticketsADT ticket){
    return ticket->iterAgency->nameAgency;
}


int hasNextAgency(ticketsADT ticket){
    return (ticket->iterAgency != NULL);
}

void nextAgency(ticketsADT ticket){
    if ( !hasNextAgency(ticket)) {
        fprintf(stderr, ERRORFIN);
        exit(EXIT_FAILURE);
    }
    ticket->iterAgency=ticket->iterAgency->next;
    return;
}

static void plateWithMostFinesRec(tMulta *first, size_t * fines, char plate[PLATE]){
    if(first==NULL){
        return;
    }
    plateWithMostFinesRec(first->izq, fines, plate);
    if(*fines<first->cantidad){
        *fines=first->cantidad;
        strcpy(plate, first->plate);
    }
    plateWithMostFinesRec(first->der,fines, plate);

}

void plateWithMostFines(ticketsADT ticket,size_t id,size_t * fines, char plate[PLATE]){
    if(ticket->infractions[id].firstMulta==NULL){
        return;
    }
    plateWithMostFinesRec(ticket->infractions[id].firstMulta, fines, plate);
}

//********funcion de prueba, ver como adaptar para QUERY 3 **************/
// //lee en orden alfabetico
// static int recorrerMultas(tMulta * first){

//         if(first !=NULL){
//         recorrerMultas(first->izq);
//          printf("%s /%ld\n", first->plate, first->cantidad);
//         recorrerMultas(first->der);

//     }
//     return 1;
//     }



static void freeMulta( tMulta*firstMulta){
    if(firstMulta==NULL){
        return;
    }
    else{
        freeMulta(firstMulta->izq);
        freeMulta(firstMulta->der);
        free(firstMulta);
    }
}

static void freeAgency( tAgency*firstAgency){
    if(firstAgency==NULL){
        return;
    }
    freeAgency(firstAgency->next);
    free(firstAgency->infractionsPopularity);
    free(firstAgency);
}

void freeTicket(ticketsADT ticket){
    for(int i=0; i<ticket->dimInfraction; i++){
        freeMulta(ticket->infractions[i].firstMulta);
    }
    free(ticket->infractions);
    freeAgency(ticket->firstAgency);
    free(ticket);
}