#include <stdio.h>
#include <stdlib.h>

#include "ticketsADT.h"
#define WRITE "wt"
#define OPENCSV "Error en la apertura del archivo\n"
#define MAXQ1 2
#define LASTQ1 1
#define MAXQ3 3
#define LASTQ3 2

FILE * newFile(char * name){
    FILE * file=fopen(name,WRITE);
    if(file==NULL){
        perror(OPENCSV);
        exit (EXIT_FAILURE);
    }
    return file;
}

void writeHeaderQ1(FILE * Q1CSV){
 fputs("infraction;tickets\n",Q1CSV);
}

void writeRowQ1(char*totalFines, char*infractions, FILE * Q1CSV){
  char * row[]={infractions, totalFines};
     for (int i=0; i<MAXQ1; i++)
    {
        fputs(row[i],Q1CSV);
        switch (i)
        {
        case LASTQ1:
            fputs(NEWLINE,Q1CSV);
            break;
        
        default:
            fputs(SEPARATOR,Q1CSV);
            break;
        }
    }
}

  


//Crea un archivo csv que contiene ordenado alfabeticamente segun el nombre de la agencia:
// nombre de la agencia, la infraccion mas popular de esta y la cantidad de multas emitidas
//En caso de empate se ubican alfabeticamente segun el nombre de infraccion
void writeQuery2(ticketsADT ticket){
    FILE *  query2CSV = newFile("query2.csv");
    char * firstline = "issuingAgency;infraction;tickets\n";
    fputs(firstline,query2CSV);
    query2(ticket,query2CSV);
    fclose(query2CSV);
}


void writeHeaderQ3(FILE * Q3CSV){
   fputs("infraction;plate;tickets\n",Q3CSV);
}

void writeRowQ3(char *infraction, char* plate, char* fine, FILE * Q3CSV){
    char * row[]={infraction, plate, fine };
     for (int i=0; i<MAXQ3; i++)
    {
        fputs(row[i],Q3CSV);
        switch (i)
        {
        case LASTQ3:
            fputs(NEWLINE,Q3CSV);
            break;
        
        default:
            fputs(SEPARATOR,Q3CSV);
            break;
        }
    }
}




