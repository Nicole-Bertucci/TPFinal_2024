#include <stdio.h>

#include "ticketsADT.h"
#include "queries.h"
#include "front.h"
#include "csvread.h"


int main(void){

    ticketsADT ticket=newTicket();

    addInfraction(ticket, 1, "JAYWALKING");
    addInfraction(ticket, 12, "F");
    addInfraction(ticket, 5, "SPEEDING");
 
    addInfraction(ticket, 14, "AUTOROBADO"); 
    addInfraction(ticket, 24, "LITTERING");
    addInfraction(ticket, 214, "Makeshift"); 
    addInfraction(ticket, 324, "Destroying"); 
    addInfraction(ticket, 74, "M");  


    addMulta(ticket, 12, "ABC34","OSCAR FRAUDES" );
    addMulta(ticket, 12, "ABC34","OSCAR FRAUDES" );
    addMulta(ticket, 12, "ABC34","OSCAR FRAUDES" );
    addMulta(ticket, 12, "ABC34","OSCAR FRAUDES" );
    addMulta(ticket, 74, "ABC34","JUAN MECANICO" );
    addMulta(ticket, 74, "ABC34","JUAN MECANICO" );
    addMulta(ticket, 74, "ABC34","JUAN MECANICO" );
    addMulta(ticket, 74, "ABC34","JUAN MECANICO" );
    addMulta(ticket, 74, "ABC34","JUAN MECANICO" );
    addMulta(ticket, 12, "ABC35","OSCAR FRAUDES" );
    addMulta(ticket, 214, "ABC35","OSCAR FRAUDES" );
    addMulta(ticket, 5, "ABC35","OSCAR FRAUDES" );
    addMulta(ticket, 5, "ABC35","OSCAR FRAUDES" );
    addMulta(ticket, 214, "ABC35","OSCAR FRAUDES" );
    addMulta(ticket, 324, "ABC36","OSCAR FRAUDES" );
    addMulta(ticket, 1, "ABC38","OSCAR FRAUDES" );
    addMulta(ticket, 5, "ABC37","OSCAR FRAUDES" );
    addMulta(ticket, 14, "ABC33","OSCAR FRAUDES" );
    addMulta(ticket, 324, "ABC33","OSCAR FRAUDES" );
    addMulta(ticket, 12, "ABC31","OSCAR FRAUDES" );
    addMulta(ticket, 22, "ABC15","OSCAR FRAUDES" );
    query1(ticket);


    // //query3 da segmentation fault
    query3(ticket);
    // for(int i=0; i<8; i++){
    //     printf("%s\n", getInfractionName(ticket, i));
    // }
    // freeTicket(ticket);


}