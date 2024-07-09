#ifndef __QUERIES_H_
#define __QUERIES_H_

#include "ticketsADT.h"
#include "front.h"

/*
* Crea un archivo .csv el que contiene: nombre de la infraccion y la cantidad de multas totales de ella
* Se escribe ordenado de forma descendente segun la cantidad de multas, en caso de empate
* se ordenan alfabeticamente segun el nombre de la infraccion.
* @param ticket ciudad con las multas y las infracciones a utilizar para la query1
*/
void query1(ticketsADT ticket);

/*
* Crea un archivo .csv que contiene ordenado alfabeticamente segun el nombre de la agencia:
* nombre de la agencia, la infraccion mas popular de esta y la cantidad de multas emitidas
* En caso de empate se ubican alfabeticamente segun el nombre de infraccion.
* @param ticket ciudad con las multas y las infracciones a utilizar para la query2
*/
void query2(ticketsADT ticket);

/*
* Crea un archivo .csv que contiene ordenada alfabeticamente por la infraccion,
* la patente con la mayor cantidad de multas segun la infraccion y su cantidad
* en caso de empate se ubican alfabeticamente segun la patente.
* @param ticket ciudad con las multas y las infracciones a utilizar para la query3.
*/
void query3(ticketsADT ticket);

#endif