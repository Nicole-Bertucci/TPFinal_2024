#include <stdio.h>
#include <time.h>
#include "csvread.h"
#include "ticketsADT.h"
#include "queries.h"

int main(int argc,const char *argv[]){
    ticketsADT new = newTicket();
    csvReadInfractions(argv,new);
    query2(new);
    query3(new);
    query1(new);
    freeTicket(new);
    return 0;
}