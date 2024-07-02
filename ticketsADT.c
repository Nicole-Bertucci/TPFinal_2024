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
       ticket->infractions[id-1].firstMulta=NULL;
    }


}


//si encuentra la patente agrega uno a su cantidad, caso contrario agrega la patente
//en el lugar correspondiente siguiendo el orden alfabetico;
static void addMultaRec(tMulta* first, const char* patente, size_t *dim){
    //si es menor
    if(strcmp(patente,first->plate)==0){
        
        first->cantidad++;

    }
    if(strcmp(patente,first->plate)<0){
        //si hay lugar
        if(first->izq==NULL){
            tMulta *new=newMulta(patente);
            first->izq=new;
            *dim+=1;
        }
        else{

            addMultaRec(first->izq, patente, dim);
        }
     

    }
    if(strcmp(patente,first->plate)>0){
        if(first->der==NULL){
            tMulta *new=newMulta(patente);
            first->der=new;
            *dim+=1;
        }
        else{
       
            addMultaRec(first->der, patente,dim );

        }
   
    }


}

void addMulta(ticketsADT ticket, int id, const char* patente, const char* agentcyName){
    if(id>=ticket->dimInfraction){
        perror(DATOINVALIDO);
        exit(EXIT_FAILURE);
    }
    if(ticket->infractions[id-1].firstMulta==NULL){
        ticket->infractions[id-1].firstMulta=newMulta(patente);
        ticket->infractions[id-1].dimMultas=1;
   }
    else{
    addMultaRec(ticket->infractions[id-1].firstMulta, patente, &(ticket->infractions[id-1].dimMultas));
    }
    ticket->infractions[id-1].multasTotales++;
    // addAgency(ticket, id, agentcyName);
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
