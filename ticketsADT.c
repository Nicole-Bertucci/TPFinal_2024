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

static tAgency * addAgencyRec(tAgency * agency, size_t id, char * name, size_t * dim){
    int c;
    if (agency == NULL || (c = strcasecmp(agency->nameAgency, name)) > 0) {
        tAgency * new = malloc(sizeof(*new));
        if(new == NULL){
            perror(ERRORMEMORIA);
            exit(EXIT_FAILURE);            
        }
        
        //aca tambien va la busqueda binaria si hacemos que las agencias tengan el vector entero de infracciones inicializadas en 0
        //sino hacemos lista o hacemos vector desordenado con reallocs

        if (*dim < id) {
            new->infractionsPopularity = malloc(sizeof(size_t));
            if(new->infractionsPopularity == NULL){
                perror(ERRORMEMORIA);
                exit(EXIT_FAILURE);            
            }
            
        }
        //*dim = id                 revisar esto...
        new->infractionsPopularity[id-1] = 1;
        new->nameAgency = stringCopy(name,ISSUINGAGENCY);
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

//hay q hacer busqueda binaria por posicion del ID


void addInfraction(ticketsADT ticket, size_t id, const char* name){
    if(ticket->dimInfraction==ticket->occupiedInfraction+1){
        ticket->infractions= realloc(ticket->infractions, sizeof(tInfraction)*(ticket->dimInfraction+BLOQUE));
       ticket->dimInfraction+=BLOQUE;
    }
    int flag=0;

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


void tMulta * newMulta(const char* plate){
    tMulta* new=malloc(sizeof(tMulta));
    new->plate=stringCopy(plate);
    new->der=NULL;
    new->izq=NULL;
    new->cantidad=1;
    return new;
}
//si encuentra la patente agrega uno a su cantidad, caso contrario agrega la patente
//en el lugar correspondiente siguiendo el orden alfabetico;
static void addMultaRec(tMulta* first, const char* patente, size_t *dim){
    //si es menor
    int dif= strcmp(patente,first->plate);
    if(dif==0){
        
        first->cantidad++;

    }
    else if(dif<0){
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
    else if(dif>0){
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

//busca el numero de index del arreglo de infracciones segun el numero de identificacion de la infraccion.
//devuelve el index de la infraccion con ese id, devuelve -1 en el caso de que no exista ese numero de identificacion.

static int busquedaBinaria(tInfraction* infractions, int id, int dim){
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


void addMulta(ticketsADT ticket, int id, const char* patente, const char* agencyName){
    int index;
    if(index=busquedaBinaria(ticket->infractions, id, ticket->occupiedInfraction+1)==-1){
        perror(DATOINVALIDO);
        exit(EXIT_FAILURE);
    }

    if(ticket->infractions[index].firstMulta==NULL){
        ticket->infractions[index].firstMulta=newMulta(patente);
        ticket->infractions[index].dimMultas=1;
   }
    else{
    addMultaRec(ticket->infractions[index].firstMulta, patente, &(ticket->infractions[index].dimMultas));
    }
    ticket->infractions[index].multasTotales++;
    // addAgency(ticket, index, agencyName);
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
