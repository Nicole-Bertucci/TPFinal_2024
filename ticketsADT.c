#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <ticketsADT.h>
#define ERRORMEMORIA "Error de asignacion de memoria"
#define DATOINVALIDO "Dato ingresado es invalido"
#define BLOQUE 10
typedef struct tMulta{
    struct tMulta *izq;
    struct tMulta *der;
    char* plate;
    size_t cantidad;
}tMulta;

typedef struct tInfraction{
    char* nameInfr;
    tMulta * firstMulta;
    size_t dimMultas;
    size_t multasTotales;
    size_t idNumber;
}tInfraction;

typedef struct tAgency{
    struct tAgency * next;
    char* nameAgency;
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
    qsort(ticket->infractions,ticket->dimInfraction,sizeof(ticket->infractions[0]), comparar);
}

static char * stringCopy(const char * name, size_t lens){
    char * new[lens+1]; 
    strcpy(new, name);
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
        new->nameAgency = stringCopy(name,ISSUINGAGENCY);
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

void addAgency (ticketsADT ticket,  size_t id, char * name, size_t position){
    ticket->firstAgency = addAgencyRec(ticket->firstAgency, id, name, &ticket->dimInfraction, position, ticket->dimInfraction);
}

void addInfraction(ticketsADT ticket, size_t id, const char* name){
//para mi si hacemos dimInfraction % BLOQUE == 0 deberia funcionar y no hay necesidad de hacer occupiedInfraction
    if(ticket->dimInfraction%BLOQUE==0){
        ticket->infractions= realloc(ticket->infractions, sizeof(tInfraction)*(ticket->dimInfraction+BLOQUE));
       ticket->dimInfraction+=BLOQUE;
    }
    int flag=0;
//porque un for, y porque el if de abajo?
    for(int i=ticket->dimInfraction-BLOQUE;i<ticket->dimInfraction&&flag==0;i++){
        if(ticket->infractions[i].nameInfr==NULL){
        ticket->infractions[i].nameInfr=stringCopy(name,DESCRIPTION);
        ticket->infractions[i].dimMultas=0;
        ticket->infractions[i].multasTotales=0;
        ticket->infractions[i].firstMulta=NULL;
        ticket->infractions[i].idNumber=id;
        ticket->occupiedInfraction=i;
        flag=1;
        }
    }
}
//busca el numero de index del arreglo de infracciones segun el numero de identificacion de la infraccion.
//devuelve el index de la infraccion con ese id, devuelve -1 en el caso de que no exista ese numero de identificacion.

static int findIndexById(const tInfraction* infractions, int id, int dim){
    if(id<0){
        perror(DATOINVALIDO);
        exit(EXIT_FAILURE);
    }

    for(int min=0, max=dim-1;min<=max;){
        int i=(max+min)/2;
        if(infractions[i].idNumber==id){
            return i;
        }
        else if(infractions[i].idNumber<id){
            min=i+1;
        }
        else if(infractions[i].idNumber>id){
            max=i-1;
        }

    }
   
    
return -1;
}

void newInf(const tInfraction* infraction,tInfraction* new, size_t index1, size_t index2){
     
        new[index2].dimMultas=infraction[index1].dimMultas;
     
        new[index2].idNumber=infraction[index1].idNumber;
      
        new[index2].multasTotales=infraction[index1].multasTotales;
      
        new[index2].nameInfr=stringCopy(infraction[index1].nameInfr, DESCRIPTION);
     
        new[index2].firstMulta=infraction[index1].firstMulta;
        
    }

//@return una copia del vector
tInfraction* cpyInf(const tInfraction * infraction, int dim){
if(dim<=0){
    perror(DATOINVALIDO);
    exit(EXIT_FAILURE);
}
tInfraction* new=malloc(sizeof(tInfraction)*dim); 
    for(int i=0; i<dim; i++){
        newInf(infraction,new, i,i);
    }
    return new;
}


// @return el index de la infraccion con la mayor cantidad de multas segun el dim
int findMax(tInfraction* infracciones, const size_t dim, int *newIndex){
    if(dim<0){
        perror(DATOINVALIDO);
        exit(EXIT_FAILURE);
    }
    int max=0, index=0, change=0, k=0;
    for(int i=0; i<dim; i++){

     if(infracciones[i].multasTotales==max){
        if(strcmp(infracciones[i].nameInfr, infracciones[k].nameInfr)<=0){
            printf("decidi que %s viene antes de %s\n", infracciones[i].nameInfr, infracciones[k].nameInfr);
                change=1;
                   
            }
        } 
    if(change==1||infracciones[i].multasTotales>max){
          max=infracciones[i].multasTotales;
          k=i;
          index=infracciones[i].idNumber;
      
        }
        
        change=0;

    }
         
   (*newIndex)=k;
    return index;

}

static tMulta * newMulta(const char* plate){
    tMulta* new = malloc(sizeof(tMulta));
    if(new == NULL){
        perror(ERRORMEMORIA);
        exit(EXIT_FAILURE);            
    }    
    new->plate=stringCopy(plate,PLATE);
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


void addMulta(ticketsADT ticket, int id, const char* patente, const char* agencyName){
    int index;
 //en lugar de ticket->occupiedInfraction+1 no seria ticket->dimInfraction
    if(index=findIndexById(ticket->infractions, id, ticket->occupiedInfraction+1)==-1){
//si da -1 solo hay q saltear el agregado de esa multa, no tirar error
// solo poner return; 
    return;
//extraido del tp 
//Si al procesar una multa, ésta se refiere a una infracción que no está 
//incluída en el archivo de infracciones, entonces se ignora esa multa. 

//      perror(DATOINVALIDO);
//      exit(EXIT_FAILURE);
    }

    if(ticket->infractions[index].firstMulta == NULL){
        ticket->infractions[index].firstMulta = newMulta(patente);
        ticket->infractions[index].dimMultas = 1;
    }
    else{
        addMultaRec(ticket->infractions[index].firstMulta, patente, &(ticket->infractions[index].dimMultas));
    }
    ticket->infractions[index].multasTotales++;
    addAgency(ticket, id, agencyName, index);
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
