#ifndef __ticketsADT_h_
#define __ticketsADT_h_
#include <stdio.h>

typedef struct ticketsCDT* ticketsADT;

//@return retorna un nuevo ticketADT vacio
//Crea un nuevo ticketsADT con todo inicializado
//Retorna NULL en caso de error de memoria
ticketsADT newTicket();

//@param ticket ciudad en donde ocurren las multas
//@param idInfraccion numero de identificacion de la infraccion
//@param patente numero de patente a la que se le aplico la multa
// Agrega al final del arreglo la multa segun la infraccion dada en @param idInfraccion
// Aumenta la cantidad de multas de ese tipo de infraccion
//Aumenta la cantidad de multas
void addMulta(ticketsADT ticket, size_t idInfraction, char* patente);

//@param ticket ciudad en donde ocurren las multas
//@param id numero de identificacion de la infraccion
//@param name descripcion de la infraccion
//agrega una nueva infraccion en la ciudad, si ya existe aborta
void addInfraction(ticketsADT ticket, size_t id, char* name);

//@param ticket ciudad en donde existe la agencia
//@param name nombre de la agencia
//agrega por orden alfabetico una nueva agencia, si ya existe aborta
//
void addAgency (ticketsADT ticket, char* name);


//libera los recursos utilizados por ticketsADT
void free(ticketsADT ticket);


#endif 