#ifndef __FRONT_H_
#define __FRONT_H_

#include "ticketsADT.h"

/*
* @return retorna un nuevo archivo de nombre name.
* @param name nombre del archivo a crear.
*/
FILE * newFile(char * name);

/*
* Escribe el encabezado de la Query1 en el archivo Q1CSV.
* @param Q1CSV archivo donde se quiere escribir.
*/
void writeHeaderQ1(FILE * Q1CSV);

/*
* Escribe en la proxima fila del archivo Q1CSV los datos correspondientes
* a la Query1.
* @param infractionName Nombre de la infraccion correspondiente.
* @param totalFines Cantidad de multas totales de la infraccion correspondiente.
*/
void writeRowQ1( char * infractionName, char * totalFines, FILE * Q1CSV);

/*
* Escribe el encabezado de la Query2 en el archivo Q2CSV.
* @param Q2CSV archivo donde se quiere escribir.
*/
void writeHeaderQ2(FILE * Q1CSV);

/*
* Escribe en la proxima fila del archivo Q2CSV los datos correspondientes
* a la Query2.
* @param issuingAgency Nombre de la agencia correspondiente
* @param infractionName Nombre de la infraccion popular de la agencia.
* @param totalFines Cantidad de multas totales de la infraccion popular de la agencia correspondiente.
*/
void writeRowQ2(char *issuingAgency,char * infractionName, char * totalFines, FILE * Q2CSV);

/*
* Escribe el encabezado de la Query3 en el archivo Q3CSV.
* @param Q3CSV archivo donde se quiere escribir.
*/
void writeHeaderQ3(FILE * Q3CSV);

/*
* Escribe en la proxima fila del archivo Q3CSV los datos correspondientes
* a la Query3.
* @param infractionName Nombre de la infraccion correspondiente.
* @param plate Numero de la patente con la mayor cantidad de multas de esa infraccion.
* @param totalFines Cantidad de multas totales de la patente.
*/
void writeRowQ3(char * infractionName, char * plate, char * totalFines, FILE * Q3CSV);

#endif













