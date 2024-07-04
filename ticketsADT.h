#ifndef __ticketsADT_h_
#define __ticketsADT_h_
#include <stdio.h>

#define PLATE 10

#ifndef FORMATNYC
// cambiar a 0 cuando hagamos el makefile, lo dejo en 1 para que no haga warnings mientras codeamos
#define FORMATNYC 1 
#endif

#ifndef FORMATCHI
#define FORMATCHI 0
#endif

//NYC
#if FORMATNYC
#define DESCRIPTION 50
#define ISSUINGAGENCY 13
#endif

//CHI
#if FORMATCHI
#define DESCRIPTION 30
#define ISSUINGAGENCY 35
#endif

#define SEPARATOR ";"    
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
void addAgency (ticketsADT ticket, size_t id, char* name, size_t position);

char * stringCopy(const char* name, size_t lenght);

void ordenar(ticketsADT ticket);

void sortByAlph(ticketsADT ticket);

size_t getOccupied(ticketsADT ticket);

size_t getId(const ticketsADT ticket, size_t index);

void newInf(ticketsADT from,ticketsADT to, size_t index1, size_t index2);

void cpyInf(const ticketsADT ticket, ticketsADT new, size_t dim);


size_t findMax(ticketsADT ticket, size_t dim, size_t *newIndex);

size_t findIndexById(const ticketsADT ticket, size_t id, size_t dim);

size_t getTotalFines(ticketsADT ticket, size_t index);

char* getInfractionName(ticketsADT ticket, size_t index);

char * plateWithMostFines(ticketsADT ticket,size_t id,size_t * fines, char plate[PLATE]);

//libera los recursos utilizados por ticketsADT
void freeTicket(ticketsADT ticket);


#endif 