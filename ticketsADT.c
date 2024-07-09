#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "ticketsADT.h"

#define ERRORMEMORIA "Error de asignacion de memoria\n"
#define DATOINVALIDO "Dato ingresado es invalido"
#define NOPLATES "No plate"
#define BLOQUE 10
#define NOTFOUND -1
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
    qsort(ticket->infractions, ticket->occupiedInfraction,sizeof(tInfraction), &comparar);
}

static int alf(const void *a, const void *b){
    tInfraction *i1 = (tInfraction *)a;
    tInfraction *i2 = (tInfraction *)b;
    return strcmp(i1->nameInfr, i2->nameInfr);
}
void sortByAlph(ticketsADT ticket){
    qsort(ticket->infractions, ticket->occupiedInfraction, sizeof(tInfraction), &alf);
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
    qsort(ticket->infractions, ticket->occupiedInfraction, sizeof(tInfraction), &cmp);
}

void addInfraction(ticketsADT ticket, size_t id, const char* name){
    if(ticket->occupiedInfraction%BLOQUE==0){
        ticket->infractions= realloc(ticket->infractions, sizeof(tInfraction)*(ticket->occupiedInfraction+BLOQUE));
        if(ticket->infractions == NULL){
            perror(ERRORMEMORIA);
            exit(EXIT_FAILURE);
        }
    }

    int i = ticket->occupiedInfraction;
    strcpy(ticket->infractions[i].nameInfr,name);
    ticket->infractions[i].dimMultas=0;
    ticket->infractions[i].multasTotales=0;
    ticket->infractions[i].firstMulta=NULL;
    ticket->infractions[i].idNumber=id;
    ticket->occupiedInfraction++;
}


void resize(ticketsADT ticket) { 
    ticket->infractions = realloc(ticket->infractions, sizeof(tInfraction) * (ticket->occupiedInfraction+1));
    if (ticket->infractions == NULL) {
        perror(ERRORMEMORIA);
        exit(EXIT_FAILURE);
    }
}


size_t getOccupied(const ticketsADT ticket){
    return ticket->occupiedInfraction;
}

char* getInfractionName(ticketsADT ticket, size_t index){
    if(index>=ticket->occupiedInfraction){ //**********OCCUPIED es el indice del ultimo ocupado o es la cant de ocupados?
        perror(DATOINVALIDO);
        exit(EXIT_FAILURE); 
    }
    return ticket->infractions[index].nameInfr;
}

size_t getTotalFines(ticketsADT ticket, size_t index){
    if(index>=ticket->occupiedInfraction){ //*********OCCUPIED es el indice del ultimo ocupado o es la cant de ocupados?
        perror(DATOINVALIDO);
        exit(EXIT_FAILURE); 
    }
    return ticket->infractions[index].multasTotales;
}

/*
*crea una nueva multa vacia.
*/
static tMulta * newFine(const char* plate){
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

/*
* Si encuentra la patente agrega uno a su cantidad, caso contrario agrega la patente
* en el lugar correspondiente siguiendo el orden alfabetico.
*/
static void addFineRec(tMulta* first, const char* patente, size_t *dim){
    int dif= strcmp(patente,first->plate);
    if(dif==0) {
        first->cantidad++;
    }
    else if(dif<0) {
        if(first->izq == NULL){
            tMulta *new=newFine(patente);
            first->izq=new;
            (*dim)++;
        }
        else{
            addFineRec(first->izq, patente, dim);
        }
    }
    else { // dif>0
        if(first->der == NULL){
            tMulta *new=newFine(patente);
            first->der=new;
            (*dim)++;
        }
        else{
            addFineRec(first->der, patente,dim );
        }
    }
}
/*
* Busca el numero de index del arreglo de infracciones segun el numero de identificacion de la infraccion.
* devuelve el index de la infraccion con ese id, devuelve NOTFOUND en el caso de que no exista ese numero de identificacion.
*/
static long int findIndexById(const ticketsADT ticket, size_t id, size_t dim){
    long int min = 0;
    long int max = dim - 1;
    while (min <= max) {
        long int i=(max+min)/2;
        size_t idnum= ticket->infractions[i].idNumber;
        if(idnum==id){
            return i;
        }
        else if(idnum<id){
            min=i+1;
        }
        else {
            max=i-1;
        }
    }
    return NOTFOUND;
}

static tAgency * addAgencyRec(tAgency * agency, const char * name, long int index, size_t occupiedInfraction){
    int c;
    if (agency == NULL || (c = strcmp(agency->nameAgency, name)) > 0) {
        tAgency * new = malloc(sizeof(*new));
        if(new == NULL){
            perror(ERRORMEMORIA);
            exit(EXIT_FAILURE);
        }
        new->infractionsPopularity = calloc(occupiedInfraction+1, sizeof(size_t));
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
    agency->next = addAgencyRec(agency->next, name, index, occupiedInfraction);
    return agency;
}
/*
* Agrega en la lista por orden alfabetico una nueva agencia.
* @param ticket ciudad en donde existe la agencia.
* @param name nombre de la agencia.
*/
static void addAgency(ticketsADT ticket, const char * name, long int index){
    ticket->firstAgency = addAgencyRec(ticket->firstAgency, name, index, ticket->occupiedInfraction);
}

void addFine(ticketsADT ticket, size_t id, const char* patente, const char* agencyName){
    long int index = findIndexById(ticket, id, ticket->occupiedInfraction+1);
    if(index == NOTFOUND){
        return;
    }

    if(ticket->infractions[index].firstMulta == NULL){
        ticket->infractions[index].firstMulta = newFine(patente);
        ticket->infractions[index].dimMultas = 1;
    }
    else{
        addFineRec(ticket->infractions[index].firstMulta, patente, &(ticket->infractions[index].dimMultas));
    }
    ticket->infractions[index].multasTotales++;
    addAgency(ticket, agencyName, index);
}


void beginAgency(ticketsADT ticket){
    ticket->iterAgency = ticket->firstAgency;
}

int hasNextAgency(ticketsADT ticket){
    return (ticket->iterAgency != NULL);
}
char * getNameAgency(ticketsADT ticket){
    return ticket->iterAgency->nameAgency;
}
void nextAgency(ticketsADT ticket){
    if ( !hasNextAgency(ticket)) {
        fprintf(stderr, ERRORFIN);
        exit(EXIT_FAILURE);
    }
    ticket->iterAgency=ticket->iterAgency->next;
    return;
}


size_t mostpopular(ticketsADT ticket, size_t * index){
    if (ticket->iterAgency == NULL) {
        fprintf(stderr, ERRORFIN);
        exit(EXIT_FAILURE);
    }
    size_t aux = 0;
    size_t auxindex = 0;
    for (size_t i = 0; i < ticket->occupiedInfraction; i++){
        int c = ticket->iterAgency->infractionsPopularity[i];

        if (c == aux && (strcmp(ticket->infractions[auxindex].nameInfr,ticket->infractions[i].nameInfr)) > 0) {
            auxindex = i;
        }
        else if (c > aux) {
            aux = c;
            auxindex = i;
        }
    }
    *index = auxindex;
    return aux;
}


static void plateWithMostFinesRec(tMulta *first, size_t * fines, char **plate){
    if(first==NULL){
        return;
    }
    plateWithMostFinesRec(first->izq, fines, plate);
    if(*fines<first->cantidad){
        *fines=first->cantidad;
        *plate = first->plate;
    }
    else if (*fines == first->cantidad) {
        if (strcmp(*plate, first->plate) > 0) {
            *plate = first->plate;

        }
    }
    plateWithMostFinesRec(first->der,fines, plate);
}

size_t plateWithMostFines(ticketsADT ticket,size_t id, char plate[PLATE]){
    if(ticket->infractions[id].firstMulta==NULL){
        return 0;
    }
    size_t fines = 0;
    char *mostFinesPlate = NULL;
    plateWithMostFinesRec(ticket->infractions[id].firstMulta, &fines, &mostFinesPlate);
    if (mostFinesPlate != NULL) {
        strcpy(plate, mostFinesPlate);
    }   
    return fines;
}

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
    while (firstAgency != NULL) {
    tAgency *actual = firstAgency;
    firstAgency = firstAgency->next;
    
    free(actual->infractionsPopularity);
    free(actual);
    }
}

void freeTicket(ticketsADT ticket){
    for(int i=0; i<ticket->occupiedInfraction; i++){
        freeMulta(ticket->infractions[i].firstMulta);
    }
    free(ticket->infractions);
    freeAgency(ticket->firstAgency);
    free(ticket);
}