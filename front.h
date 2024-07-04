#ifndef __FRONT_H_
#define __FRONT_H_

#include "ticketsADT.h"

FILE * newFile(char * name);
//Escribe en un archivo csv el nombre de la infraccion y la cantidad de multas totales de ella
//Se escribe ordenado de forma descendente segun la cantidad de multas, en caso de empate
// se ordenan alfabeticamente segun el nombre de la infraccion
void writeRowQ1(char*totalFines, char*infractions, FILE * Q1CSV);
void writeHeaderQ1(FILE * Q1CSV);

//Crea un archivo csv que contiene ordenado alfabeticamente segun el nombre de la agencia:
// nombre de la agencia, la infraccion mas popular de esta y la cantidad de multas emitidas
//En caso de empate se ubican alfabeticamente segun el nombre de infraccion
void writeQuery2(ticketsADT ticket);


//Crea un archivo csv que contiene ordenada alfabeticamente por la infraccion,
// la patente con la mayor cantidad de multas segun la infraccion y su cantidad
//en caso de empate se ubican alfabeticamente segun la patente

void writeHeaderQ3(FILE * Q3CSV);

void writeRowQ3(char *infraction, char* plate, char* fine, FILE * Q3CSV);


#endif













