#include <stdio.h>
#include <stdlib.h>

#include "ticketsADT.h"
#define WRITE "wt"
#define OPENCSV "Error en la apertura del archivo\n"

FILE * new(char * name){
    FILE * file=fopen(name,WRITE);
    if(file==NULL){
        perror(OPENCSV);
        exit (EXIT_FAILURE);
    }
    return file;
}

//Escribe en un archivo csv el nombre de la infraccion y la cantidad de multas totales de ella
//Se escribe ordenado de forma descendente segun la cantidad de multas, en caso de empate
// se ordenan alfabeticamente segun el nombre de la infraccion
void writeQuery1(ticketsADT ticketAdt);

/**********ideas: ordeno en un arbol las infracciones segun cantidad de multas totales
 ********** recorro el arreglo mil veces*/

//Crea un archivo csv que contiene ordenado alfabeticamente segun el nombre de la agencia:
// nombre de la agencia, la infraccion mas popular de esta y la cantidad de multas emitidas
//En caso de empate se ubican alfabeticamente segun el nombre de infraccion
void writeQuery2(ticketsADT ticket){
    FILE *  query2CSV = new("query2.csv");
    char * firstline = "issuingAgency;infraction;tickets\n";
    fputs(firstline,query2CSV);
    query2(ticket,query2CSV);
    fclose(query2CSV);
}


//Crea un archivo csv que contiene ordenada alfabeticamente por la infraccion,
// la patente con la mayor cantidad de multas segun la infraccion y su cantidad
//en caso de empate se ubican alfabeticamente segun la patente
void writeQuery3(ticketsADT ticketAdt);

/**********ideas: ordeno en un arbol las infracciones alfabeticamente
 ********** recorro el arreglo mil veces*/


