#ifndef __ticketsADT_h_
#define __ticketsADT_h_
#include <stdio.h>

#define PLATE 10+1

#ifndef FORMATNYC
// cambiar a 0 cuando hagamos el makefile, lo dejo en 1 para que no haga warnings mientras codeamos
#define FORMATNYC 0 
#endif

#ifndef FORMATCHI
#define FORMATCHI 0
#endif

//NYC
#if FORMATNYC
#define DESCRIPTION 30+1
#define ISSUINGAGENCY 35+1

//CHI
#elif FORMATCHI
#define DESCRIPTION 50+1
#define ISSUINGAGENCY 13+1

#endif

#define SEPARATOR ";\n"    
#define NEWLINE "\n"

typedef struct ticketsCDT* ticketsADT;

//Crea un nuevo ticketsADT con todo inicializado
//@return retorna un nuevo ticketsADT vacio o retorna NULL en caso de error de memoria
ticketsADT newTicket();

//agrega una nueva infraccion en la ciudad, si ya existe aborta
//@param ticket ciudad en donde ocurren las multas
//@param id numero de identificacion de la infraccion
//@param name descripcion de la infraccion
void addInfraction(ticketsADT ticket, size_t id, const char* name);
void resize(ticketsADT ticket);

// Si la patente no existe en el arreglo agrega al final del arreglo la multa 
//segun la infraccion dada en idInfraccion, en el caso contrario solo
//aumenta la cantidad de multas de esa patente.
//Aumenta la cantidad de multas de ese tipo de infraccion.
//Aumenta la cantidad de infracciones del tipo generado por la agencia  de nombre agency.
//@param ticket ciudad en donde ocurren las multas
//@param idInfraccion numero de identificacion de la infraccion
//@param patente numero de patente a la que se le aplico la multa
//@param nombre de la agencia que escribe la multa
void addMulta(ticketsADT ticket, size_t id, const char* patente, const char* agencyName );

//Agrega por orden alfabetico una nueva agencia, si ya existe aborta
//@param ticket ciudad en donde existe la agencia
//@param name nombre de la agencia
void addAgency (ticketsADT ticket,const char* name, size_t index);

char * stringCopy(const char* name, size_t lenght);

void ordenar(ticketsADT ticket);

void sortByAlph(ticketsADT ticket);

size_t getOccupied(ticketsADT ticket);

size_t getId(const ticketsADT ticket, size_t index);

void newInf(ticketsADT from,ticketsADT to, size_t index1, size_t index2);

void cpyInf(const ticketsADT ticket, ticketsADT new, size_t dim);

size_t findMax(ticketsADT ticket, size_t dim, size_t *newIndex);

size_t getTotalFines(ticketsADT ticket, size_t index);

char* getInfractionName(ticketsADT ticket, size_t index);

size_t cantInfraction(const ticketsADT ticket);

void beginAgency(ticketsADT ticket);

int hasNextAgency(ticketsADT ticket);

void nextAgency(ticketsADT ticket);

char * getNameAgency(ticketsADT ticket);

size_t mostpopular(ticketsADT ticket, size_t * index);

void plateWithMostFines(ticketsADT ticket,size_t id,size_t * fines, char plate[PLATE]);

void sortByID(ticketsADT ticket);

void sortByAlph(ticketsADT ticket);

void sortByTotal(ticketsADT ticket);


//libera los recursos utilizados por ticketsADT
void freeTicket(ticketsADT ticket);


#endif 