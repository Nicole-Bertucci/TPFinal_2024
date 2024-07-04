#include <stdio.h>
#include <stdlib.h>

#include "ticketsADT.h"
#define WRITE "wt"
#define OPENCSV "Error en la apertura del archivo\n"
#define MAXQ1 2
#define LASTQ1 1

FILE * newFile(char * name){
    FILE * file=fopen(name,WRITE);
    if(file==NULL){
        perror(OPENCSV);
        exit (EXIT_FAILURE);
    }
    return file;
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

  



void writeHeaderQ1(FILE * Q1CSV){
 fputs("infraction;tickets\n",Q1CSV);
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


//Crea un archivo csv que contiene ordenada alfabeticamente por la infraccion,
// la patente con la mayor cantidad de multas segun la infraccion y su cantidad
//en caso de empate se ubican alfabeticamente segun la patente
void writeQuery3(ticketsADT ticketAdt);




// int main(void){

//     ticketsADT ticketAdt=newTicket();

//        addInfraction(ticketAdt, 1, "J");

//     addInfraction(ticketAdt, 12, "F");
//     addInfraction(ticketAdt, 5, "S");
//     addInfraction(ticketAdt, 14, "A"); 
//     addMulta(ticketAdt, 12, "ABC34","OSCAR FRAUDES" );
//     addMulta(ticketAdt, 12, "ABC34","JUAN MECANICO" );
//     addMulta(ticketAdt, 12, "ABC35","OSCAR FRAUDES" );
//     addMulta(ticketAdt, 12, "ABC35","OSCAR FRAUDES" );
//     addMulta(ticketAdt, 12, "ABC36","OSCAR FRAUDES" );
//     addMulta(ticketAdt, 12, "ABC38","OSCAR FRAUDES" );
//     addMulta(ticketAdt, 12, "ABC37","OSCAR FRAUDES" );
//     addMulta(ticketAdt, 12, "ABC33","OSCAR FRAUDES" );
//     addMulta(ticketAdt, 12, "ABC31","OSCAR FRAUDES" );
//     addMulta(ticketAdt, 12, "ABC15","OSCAR FRAUDES" );
//     writeQuery1(ticketAdt);


// }