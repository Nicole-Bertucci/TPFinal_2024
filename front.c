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
void writeQuery1(ticketsADT ticketAdt){
//  FILE * Q1CSV=newFile("query1.csv");
//  fputs("infraction;tickets\n",Q1CSV);
   size_t dim=getOccupied(ticketAdt)+1;
   printf("okis");
   ticketsADT new=newTicket();
 
    cpyInf(ticketAdt,new, dim);
    size_t index, id, indexNew=0;
 for(size_t i=0, dimNew=dim; i<dimNew; dimNew=dimNew-1){
        id=findMax(new, dimNew, &indexNew);
        index=findIndexById(ticketAdt, id,dim );
        // writeRowQ1(ticketAdt, index);
        printf("%ld | %s\n", getTotalFines(ticketAdt, index),getInfractionName(ticketAdt, index));
        newInf(new,new,dim-1, indexNew);
}
}

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




int main(void){

    ticketsADT ticketAdt=newTicket();
     printf("wenas");
       addInfraction(ticketAdt, 1, "J");
 printf("wenas");
    addInfraction(ticketAdt, 12, "F");
    addInfraction(ticketAdt, 13, "S");
    addInfraction(ticketAdt, 14, "A"); 
    addMulta(ticketAdt, 12, "ABC34","OSCAR FRAUDES" );
    printf("*****prox add 34********\n");
    addMulta(ticketAdt, 12, "ABC34","JUAN MECANICO" );
    printf("*****prox add 35********\n");
    addMulta(ticketAdt, 12, "ABC35","OSCAR FRAUDES" );
    printf("*****prox add 35********\n");
    addMulta(ticketAdt, 12, "ABC35","OSCAR FRAUDES" );
    printf("*****prox add 36********\n");
    addMulta(ticketAdt, 12, "ABC36","OSCAR FRAUDES" );
    printf("*****prox add 38********\n");
    addMulta(ticketAdt, 12, "ABC38","OSCAR FRAUDES" );
      printf("*****prox add 37********\n");
    addMulta(ticketAdt, 12, "ABC37","OSCAR FRAUDES" );
      printf("*****prox add 33********\n");
    addMulta(ticketAdt, 12, "ABC33","OSCAR FRAUDES" );
        printf("*****prox add 31********\n");
    addMulta(ticketAdt, 12, "ABC31","OSCAR FRAUDES" );
        printf("*****prox add 15********\n");
    addMulta(ticketAdt, 12, "ABC15","OSCAR FRAUDES" );
    // writeQuery1(ticketAdt);
      size_t dim=getOccupied(ticketAdt)+1;
   printf("okis");
   ticketsADT new=newTicket();
 
    // cpyInf(ticketAdt,new, dim);
    //  printf("wot");
//     size_t index, id, indexNew=0;
//  for(size_t i=0, dimNew=dim; i<dimNew; dimNew=dimNew-1){
//         id=findMax(new, dimNew, &indexNew);
//         index=findIndexById(ticketAdt, id,dim );
//         // writeRowQ1(ticketAdt, index);
//         printf("%ld | %s\n", getTotalFines(ticketAdt, index),getInfractionName(ticketAdt, index));
//         newInf(new,new,dim-1, indexNew);
// }

}