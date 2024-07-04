#include <stdio.h>

#include "ticketsADT.h"
#include "queries.h"
#include "front.h"
#include "csvread.h"


int main(void){

    ticketsADT ticketAdt=newTicket();

    addInfraction(ticketAdt, 1, "JAYWALKING");
    addInfraction(ticketAdt, 12, "F");
    addInfraction(ticketAdt, 5, "SPEEDING");
 
    addInfraction(ticketAdt, 14, "AUTOROBADO"); 
    addInfraction(ticketAdt, 24, "LITTERING");
    addInfraction(ticketAdt, 214, "Makeshift"); 
    addInfraction(ticketAdt, 324, "Destroying"); 
    addInfraction(ticketAdt, 74, "M");  


    addMulta(ticketAdt, 12, "ABC34","OSCAR FRAUDES" );
    addMulta(ticketAdt, 12, "ABC34","OSCAR FRAUDES" );
    addMulta(ticketAdt, 12, "ABC34","OSCAR FRAUDES" );
    addMulta(ticketAdt, 12, "ABC34","OSCAR FRAUDES" );
    addMulta(ticketAdt, 74, "ABC34","JUAN MECANICO" );
    addMulta(ticketAdt, 74, "ABC34","JUAN MECANICO" );
    addMulta(ticketAdt, 74, "ABC34","JUAN MECANICO" );
    addMulta(ticketAdt, 74, "ABC34","JUAN MECANICO" );
    addMulta(ticketAdt, 74, "ABC34","JUAN MECANICO" );
    addMulta(ticketAdt, 12, "ABC35","OSCAR FRAUDES" );
    addMulta(ticketAdt, 214, "ABC35","OSCAR FRAUDES" );
    addMulta(ticketAdt, 5, "ABC35","OSCAR FRAUDES" );
    addMulta(ticketAdt, 5, "ABC35","OSCAR FRAUDES" );
    addMulta(ticketAdt, 214, "ABC35","OSCAR FRAUDES" );
    addMulta(ticketAdt, 324, "ABC36","OSCAR FRAUDES" );
    addMulta(ticketAdt, 1, "ABC38","OSCAR FRAUDES" );
    addMulta(ticketAdt, 5, "ABC37","OSCAR FRAUDES" );
    addMulta(ticketAdt, 14, "ABC33","OSCAR FRAUDES" );
    addMulta(ticketAdt, 324, "ABC33","OSCAR FRAUDES" );
    addMulta(ticketAdt, 12, "ABC31","OSCAR FRAUDES" );
    addMulta(ticketAdt, 22, "ABC15","OSCAR FRAUDES" );
    query1(ticketAdt);


    // //query3 da segmentation fault
    query3(ticketAdt);
    // for(int i=0; i<8; i++){
    //     printf("%s\n", getInfractionName(ticketAdt, i));
    // }
    // freeTicket(ticketAdt);


}