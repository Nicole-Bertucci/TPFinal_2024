#ifndef __QUERIES_H_
#define __QUERIES_H_

#include "ticketsADT.h"
#include "front.h"

size_t getSize(size_t n);

//Escribe en un archivo csv el nombre de la infraccion y la cantidad de multas totales de ella
//Se escribe ordenado de forma descendente segun la cantidad de multas, en caso de empate
// se ordenan alfabeticamente segun el nombre de la infraccion
void query1(ticketsADT ticketAdt);


//Crea un archivo csv que contiene ordenada alfabeticamente por la infraccion,
// la patente con la mayor cantidad de multas segun la infraccion y su cantidad
//en caso de empate se ubican alfabeticamente segun la patente
void query3(ticketsADT ticketAdt);

#endif