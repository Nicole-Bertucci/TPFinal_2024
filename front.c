#include <stdio.h>
#include <stdlib.h>
#include "ticketsADT.h"

#define WRITE "wt"
#define OPENCSV "Error en la apertura del archivo\n"
#define MAXQ1 2
#define LASTQ1 MAXQ1-1
#define MAXQ2 3
#define LASTQ2 MAXQ2-1
#define MAXQ3 3
#define LASTQ3 MAXQ3-1
#define SEPARAT ";"  
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
//borrar
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
            fputs(SEPARAT,Q1CSV);
            break;
        }
    }
}

void writeHeaderQ2(FILE * Q2CSV){
   fputs("issuingAgency;infraction;tickets\n",Q2CSV);
}  

void writeRowQ2(char *issuingAgency,char * infractionName, char * totaltickets, FILE * Q2CSV){
    char * line[] = {issuingAgency,infractionName,totaltickets}; 
    for (int i = 0; i < MAXQ2; i++) {
        fputs(line[i],Q2CSV);
        switch (i) {
        case LASTQ2:
            fputs(NEWLINE,Q2CSV);
            break;
        
        default:
            fputs(SEPARAT,Q2CSV);
            break;
        }
    }
}


void writeHeaderQ3(FILE * Q3CSV){
   fputs("infraction;plate;tickets\n",Q3CSV);
}

void writeRowQ3(char *infraction, char* plate, char* fine, FILE * Q3CSV){
    char * row[]={infraction, plate, fine };
    for (int i=0; i<MAXQ3; i++){
        fputs(row[i],Q3CSV);
        switch (i)
        {
        case LASTQ3:
            fputs(NEWLINE,Q3CSV);
            break;
        
        default:
            fputs(SEPARAT,Q3CSV);
            break;
        }
    }
}




