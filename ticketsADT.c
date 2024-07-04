#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "ticketsADT.h"
#define ERRORMEMORIA "Error de asignacion de memoria\n"
#define DATOINVALIDO "Dato ingresado es invalido"
#define BLOQUE 10
#define ELEMQ2 3

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

void ordenar(ticketsADT ticket){
    qsort(ticket->infractions,ticket->occupiedInfraction+1,sizeof(tInfraction), &comparar);
}

char * stringCopy(const char* name, size_t lenght){
    int size=sizeof(name);
    if(size>lenght){
        perror(DATOINVALIDO);
        exit(EXIT_FAILURE);
    }
    char* new=malloc(size);
    strcpy(new,name);    
    return new;
}


static tAgency * addAgencyRec(tAgency * agency, size_t id, char * name, size_t * dim, size_t position, size_t dimInfraction){
    int c;
    if (agency == NULL || (c = strcmp(agency->nameAgency, name)) > 0) {
        tAgency * new = malloc(sizeof(*new));
        if(new == NULL){
            perror(ERRORMEMORIA);
            exit(EXIT_FAILURE);            
        }
        new->infractionsPopularity[dimInfraction];        
        new->infractionsPopularity[position-1] = 1;
        strcpy(new->nameAgency,name);
        new->next = agency; 
        return new;
    }
    if (c == 0) {
        agency->infractionsPopularity[position-1]++;
        return agency;
    }
    agency->next = addAgencyRec(agency->next, id, name, dim, position, dimInfraction);
    return agency;
}

void addAgency(ticketsADT ticket,  size_t id, char * name, size_t position){
    ticket->firstAgency = addAgencyRec(ticket->firstAgency, id, name, &ticket->dimInfraction, position, ticket->dimInfraction);
}

void addInfraction(ticketsADT ticket, size_t id, const char* name){
    
    if(ticket->dimInfraction%BLOQUE==0){
        ticket->infractions= realloc(ticket->infractions, sizeof(tInfraction)*(ticket->dimInfraction+BLOQUE));
    ticket->occupiedInfraction=(ticket->dimInfraction==0)?-1:(ticket->occupiedInfraction);
       ticket->dimInfraction+=BLOQUE;
    }
    int i=ticket->occupiedInfraction+1;
    strcpy(ticket->infractions[i].nameInfr,name);
    ticket->infractions[i].dimMultas=0;
    ticket->infractions[i].multasTotales=0;
    ticket->infractions[i].firstMulta=NULL;
    ticket->infractions[i].idNumber=id;

    (ticket->occupiedInfraction)++;
        
}
//busca el numero de index del arreglo de infracciones segun el numero de identificacion de la infraccion.
//devuelve el index de la infraccion con ese id, devuelve -1 en el caso de que no exista ese numero de identificacion.
size_t findIndexById(const ticketsADT ticketAdt, size_t id, size_t dim){
    if(id<0){
        perror(DATOINVALIDO);
        exit(EXIT_FAILURE);
    }

    for(int min=0, max=dim-1;min<=max;){
        int i=(max+min)/2;
        if(ticketAdt->infractions[i].idNumber==id){
            return i;
        }

        else if(ticketAdt->infractions[i].idNumber<id){
            min=i+1;
        }

        else if(ticketAdt->infractions[i].idNumber>id){
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
    ordenar(ticket);}
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
    // addAgency(ticket, id, agencyName, index);
}

void newInf(ticketsADT from,ticketsADT to, size_t index1, size_t index2){
        to->infractions[index2].dimMultas=from->infractions[index1].dimMultas;
        to->infractions[index2].idNumber=from->infractions[index1].idNumber;
        to->infractions[index2].multasTotales=from->infractions[index1].multasTotales;
        strcpy(to->infractions[index2].nameInfr,from->infractions[index1].nameInfr);
        to->infractions[index2].firstMulta=from->infractions[index1].firstMulta;
    }

//deja en new la copia del vector ticketAdt
void cpyInf(ticketsADT  ticketAdt, ticketsADT new,  size_t dim){
if(dim<=0){
    perror(DATOINVALIDO);
    exit(EXIT_FAILURE);
}
new->infractions=realloc(new->infractions, sizeof(tInfraction)*dim); 
    for(int i=0; i<dim; i++){
        newInf(ticketAdt,new, i,i);
    }
}

size_t getOccupied(const ticketsADT ticket){
    return ticket->occupiedInfraction;
}

size_t getId(const ticketsADT ticket, size_t index){
    return ticket->infractions[index].idNumber;
}

tInfraction * getInfraction(const ticketsADT ticket){
    return ticket->infractions;
}

// @return el index de la infraccion con la mayor cantidad de multas segun el dim
size_t findMax(ticketsADT ticketAdt, size_t dim, size_t *newIndex){
    if(dim<0){
        perror(DATOINVALIDO);
        exit(EXIT_FAILURE);
    }
    int max=0, index=0, change=0, k=0;
    for(int i=0; i<dim; i++){

     if(ticketAdt->infractions[i].multasTotales==max){
        if(strcmp(ticketAdt->infractions[i].nameInfr, ticketAdt->infractions[k].nameInfr)<=0){
 
                change=1;
                   
            }
        } 
    if(change==1||ticketAdt->infractions[i].multasTotales>max){
          max=ticketAdt->infractions[i].multasTotales;
          k=i;
  
          index=ticketAdt->infractions[i].idNumber;
      
        }
        
        change=0;

    }
         
   (*newIndex)=k;
    return index;

}

size_t mostpopular(tAgency * agency, size_t * infraction, size_t dim){
    if (agency == NULL) {
        //....................................
    }
    size_t aux = 0;
    size_t i = 0;
    for (; i < dim; i++){
        int c;
        if ((c = agency->infractionsPopularity[i]) > aux) {
            aux = c;
        }
    }
    *infraction = i;
    return aux;
}

void query2(ticketsADT ticket, FILE * query2CSV){
    for (size_t i = 0; ticket->firstAgency == NULL ; i++) {
        char * issuingAgency = ticket->firstAgency->nameAgency; 
        size_t *infraction;  
        size_t totaltickets = mostpopular(ticket->firstAgency, &infraction,ticket->dimInfraction);
        char * infractionName = ticket->infractions[*infraction].nameInfr;
        char line[] = {issuingAgency,infractionName,totaltickets}; 
        for (int i = 0; i < ELEMQ2; i++) {
            fputs(line[i],query2CSV);
            switch (i) {
            case ELEMQ2-1:
                fputs(NEWLINE,query2CSV);
                break;
            
            default:
                fputs(SEPARATOR,query2CSV);
                break;
            }
        }
    }
}






size_t getTotalFines(ticketsADT ticket, size_t index){
    return ticket->infractions[index].multasTotales;
}

char* getInfractionName(ticketsADT ticket, size_t index){
    return ticket->infractions[index].nameInfr;
}
//********funcion de prueba, ver como adaptar para QUERY 3 **************/
//lee en orden alfabetico
static int recorrerMultas(tMulta * first){

        if(first !=NULL){
        recorrerMultas(first->izq);
         printf("%s /%ld\n", first->plate, first->cantidad); 
        recorrerMultas(first->der);

    }
    return 1;
    }
