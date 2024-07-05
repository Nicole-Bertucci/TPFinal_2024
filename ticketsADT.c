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
#define NOTFOUND ((size_t) -1)
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

void addInfraction(ticketsADT ticket, size_t id, const char* name){
    if(ticket->occupiedInfraction%BLOQUE==0){
        ticket->infractions= realloc(ticket->infractions, sizeof(tInfraction)*(ticket->dimInfraction+BLOQUE));
        if(ticket->infractions == NULL){
            perror(ERRORMEMORIA);
            exit(EXIT_FAILURE);
        }
        ticket->occupiedInfraction=(ticket->dimInfraction==0)?-1:(ticket->occupiedInfraction);
        ticket->dimInfraction+=BLOQUE;
    }
    // if (ticket->occupiedInfraction + 1 == ticket->dimInfraction) {
    //     ticket->infractions= realloc(ticket->infractions, sizeof(tInfraction) * (ticket->dimInfraction + BLOQUE));
    //     if(ticket->infractions == NULL){
    //         perror(ERRORMEMORIA);
    //         exit(EXIT_FAILURE);
    //     }
    //     ticket->dimInfraction += BLOQUE;
    // }
    ticket->occupiedInfraction++;
    int i = ticket->occupiedInfraction;
    strcpy(ticket->infractions[i].nameInfr,name);
    ticket->infractions[i].dimMultas=0;
    ticket->infractions[i].multasTotales=0;
    ticket->infractions[i].firstMulta=NULL;
    ticket->infractions[i].idNumber=id;
}
void resize(ticketsADT ticket) {
    ticket->infractions = realloc(ticket->infractions, sizeof(tInfraction) * ticket->dimInfraction);
    if (ticket->infractions == NULL) {
        perror(ERRORMEMORIA);
        exit(EXIT_FAILURE);
    }
    //ticket->dimInfraction = ticket->occupiedInfraction;
}
//44
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
    else { // dif>0
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
//busca el numero de index del arreglo de infracciones segun el numero de identificacion de la infraccion.
//devuelve el index de la infraccion con ese id, devuelve -1 en el caso de que no exista ese numero de identificacion.
static size_t findIndexById(const ticketsADT ticket, size_t id, size_t dim){
    for(size_t min=0, max=dim-1;min<=max;){
        size_t i=(max+min)/2;
        size_t idnum= ticket->infractions[i].idNumber;
        if(idnum==id){
            return i;
        }
        else if(idnum<id){
            min=i+1;
        }
        else { //(ticket->infractions[i].idNumber>id)
            max=i-1;
        }
    }
    return NOTFOUND;
}

void addMulta(ticketsADT ticket, size_t id, const char* patente, const char* agencyName){
    int index = findIndexById(ticket, id, ticket->occupiedInfraction+1);
    if(index == -1){
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



//no se usa
void newInf(ticketsADT from,ticketsADT to, size_t index1, size_t index2){
        to->infractions[index2].dimMultas=from->infractions[index1].dimMultas;
        to->infractions[index2].idNumber=from->infractions[index1].idNumber;
        to->infractions[index2].multasTotales=from->infractions[index1].multasTotales;
        strcpy(to->infractions[index2].nameInfr,from->infractions[index1].nameInfr);
        to->infractions[index2].firstMulta=from->infractions[index1].firstMulta;
}
//no se usa
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
//no se usa
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
//no se usan
size_t getId(const ticketsADT ticket, size_t index){
    return ticket->infractions[index].idNumber;
}
//no se usa
size_t cantInfraction(const ticketsADT ticket){
    return ticket->dimInfraction;
}
//Q1, Q2 y Q3
size_t getOccupied(const ticketsADT ticket){
    return ticket->occupiedInfraction;
}
//Q1, Q2 y Q3
char* getInfractionName(ticketsADT ticket, size_t index){
    return ticket->infractions[index].nameInfr;
}
//Q1
size_t getTotalFines(ticketsADT ticket, size_t index){
    return ticket->infractions[index].multasTotales;
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
//Q3
static void plateWithMostFinesRec(tMulta *first, size_t * fines, char plate[PLATE]){
    if(first==NULL){
        return;
    }
    plateWithMostFinesRec(first->izq, fines, plate);
    if(*fines<first->cantidad){
        *fines=first->cantidad;
        strcpy(plate, first->plate);
    }
    else if (*fines == first->cantidad) {
        if (strcmp(plate, first->plate) > 0) {
            strcpy(plate, first->plate);    
        }
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
    // if(firstAgency==NULL){
    //     return;
    // }
    // freeAgency(firstAgency->next);
    // free(firstAgency->infractionsPopularity);
    // free(firstAgency);
    // es mas rapido iterativo
    while (firstAgency != NULL) {
    tAgency *actual = firstAgency;
    firstAgency = firstAgency->next;
    
    free(actual->infractionsPopularity);
    free(actual);
    }
}

void freeTicket(ticketsADT ticket){
    for(int i=0; i<ticket->dimInfraction; i++){
        freeMulta(ticket->infractions[i].firstMulta);
    }
    free(ticket->infractions);
    freeAgency(ticket->firstAgency);
    free(ticket);
}