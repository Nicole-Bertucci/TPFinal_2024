#ifndef __ticketsADT_h_
#define __ticketsADT_h_
#include <stdio.h>

#define PLATE 10+1

#ifndef FORMATNYC
#define FORMATNYC 0 
#endif

#ifndef FORMATCHI
#define FORMATCHI 0
#endif

#if FORMATNYC
#define DESCRIPTION 30+1
#define ISSUINGAGENCY 35+1

#elif FORMATCHI
#define DESCRIPTION 50+1
#define ISSUINGAGENCY 13+1

#endif

#define SEPARATOR ";\n"    
#define NEWLINE "\n"

typedef struct ticketsCDT* ticketsADT;

/*
* Crea un nuevo ticketsADT con todo inicializado.
* @return retorna un nuevo ticketsADT vacio o retorna NULL en caso de error de memoria.
*/
ticketsADT newTicket();

/*
* Agrega una nueva infraccion en la ciudad.
* @param ticket ciudad en donde ocurren las multas.
* @param id numero de identificacion de la infraccion.
* @param name descripcion de la infraccion.
*/
void addInfraction(ticketsADT ticket, size_t id, const char* name);

/*
* Crea un nuevo espacio vacio al final del arreglo de infracciones de ticket
* @param ticket ciudad donde se encuentran las infracciones.
*/
void resize(ticketsADT ticket); 

/*
* @return devuelve la cantidad de infracciones diferentes guardadas.
* @param ticket ciudad en donde ocurren las multas.
*/
size_t getOccupied(ticketsADT ticket);

/*
* @return devuelve el nombre de la infraccion de indice index.
* @param ticket ciudad en donde ocurren las multas.
* @param index indice de la infraccion buscada.
*/
char* getInfractionName(ticketsADT ticket, size_t index);

/*
* @return devuelve la cantidad total de multas de el tipo de infraccion
* de indice index.
* @param ticket ciudad en donde ocurren las multas.
* @index indice de la infraccion buscada.
*/
size_t getTotalFines(ticketsADT ticket, size_t index);

/* 
* Si la patente no existe en el arreglo agrega la multa alfabeticamente en el arbol segun la patente en 
* infraccion con numero de identificacion id, en el caso contrario solo aumenta la cantidad de
* multas de esa patente. Aumenta la cantidad de multas totales de ese tipo de infraccion.Aumenta
* la cantidad de infracciones del tipo generado por la agencia de nombre agency. En el caso en el que
* no exista tal infraccion con ese ID se omite el guardado de la multa.
* @param ticket ciudad en donde ocurren las multas.
* @param idInfraccion numero de identificacion de la infraccion.
* @param patente numero de patente a la que se le aplico la multa.
* @param nombre de la agencia que escribe la multa.
*/
void addFine(ticketsADT ticket, size_t id, const char* patente, const char* agencyName );

/*
* Resetea el iterador que recorre la lista de Agency.
* @param ticket ciudad en donde existe la agencia. 
*/
void beginAgency(ticketsADT ticket);

/*
* @return devuelve 1 si hay un elemento siguiente en el iterador que recorre
* la lista de Agency, en el caso contrario retorna 0.
* @param ticket ciudad en donde existe la agencia.
*/
int hasNextAgency(ticketsADT ticket);

/*
* Deja al iterador en la proxima agencia de la lista.
* @param ticket ciudad en donde existe la agencia.
*/
void nextAgency(ticketsADT ticket);

/* 
* @return Devuelve el nombre de la agencia del iterador.
* @param ticket ciudad en donde existe la agencia.
*/
char * getNameAgency(ticketsADT ticket);

/*
* @return Devuelve la cantidad total de multas redactadas de la infraccion mas 
* popular de la agencia en el iterador.
* @param ticket ciudad donde existe la agencia.
* @param index indice de la infraccion mas popular en la agencia.
*/
size_t mostpopular(ticketsADT ticket, size_t * index);


/*
* @return Devuelve la cantidad de multas totales de la patente con
* la mayor cantidad de multas segun la infraccion con ID id.
* Ademas deja el numero de la patente con mayor cantidad de multas
* segun la infraccion en plate.
* @param ticket ciudad donde se redactan las multas.
* @param id numero de identificacion de la infraccion.
* @param plate vector de salida donde se coloca el numero de patente 
* con mayor cantidad de multas segun la infraccion.
*/
size_t plateWithMostFines(ticketsADT ticket,size_t id, char plate[PLATE]);

/*
* Ordena las infracciones de forma ascendente segun su numero de ID.
* @param ticket ciudad en donde existen las infracciones.
*/
void sortByID(ticketsADT ticket);

/*
* Ordena las infracciones alfabeticamente segun su nombre. 
* @param ticket ciudad en donde existen las infracciones.
*/
void sortByAlph(ticketsADT ticket);

/*
* Ordena las infracciones de forma ascendente segun la cantidad
* de multas totales, en el caso de encontrarse con un empate se 
* ubican alfabeticamente.
* @param ticket ciudad en donde existen las infracciones.
*/
void sortByTotal(ticketsADT ticket);


/*
* Libera los recursos utilizados por ticket
* @param ticket ciudad en donde se redactan las multas.
*/
void freeTicket(ticketsADT ticket);


#endif 