#include <stdio.h>

#include "ticketsADT.h"
#include "queries.h"
#include "front.h"
#include "csvread.h"


int main(void){

    ticketsADT ticketAdt=newTicket();

       addInfraction(ticketAdt, 1, "J");

    addInfraction(ticketAdt, 12, "F");
    addInfraction(ticketAdt, 5, "S");
    addInfraction(ticketAdt, 14, "A"); 
    addMulta(ticketAdt, 12, "ABC34","OSCAR FRAUDES" );
    addMulta(ticketAdt, 12, "ABC34","JUAN MECANICO" );
    addMulta(ticketAdt, 12, "ABC35","OSCAR FRAUDES" );
    addMulta(ticketAdt, 12, "ABC35","OSCAR FRAUDES" );
    addMulta(ticketAdt, 12, "ABC36","OSCAR FRAUDES" );
    addMulta(ticketAdt, 12, "ABC38","OSCAR FRAUDES" );
    addMulta(ticketAdt, 12, "ABC37","OSCAR FRAUDES" );
    addMulta(ticketAdt, 12, "ABC33","OSCAR FRAUDES" );
    addMulta(ticketAdt, 12, "ABC31","OSCAR FRAUDES" );
    addMulta(ticketAdt, 12, "ABC15","OSCAR FRAUDES" );
    Query1(ticketAdt);


}