#ifndef __FRONT_H_
#define __FRONT_H_

#include "ticketsADT.h"

FILE * newFile(char * name);

void writeRowQ1(char*totalFines, char*infractions, FILE * Q1CSV);
void writeHeaderQ1(FILE * Q1CSV);

void writeRowQ2(char *issuingAgency,char * infractionName, char * totaltickets, FILE * Q2CSV);
void writeHeaderQ2(FILE * Q1CSV);

void writeHeaderQ3(FILE * Q3CSV);
void writeRowQ3(char *infraction, char* plate, char* fine, FILE * Q3CSV);

#endif













