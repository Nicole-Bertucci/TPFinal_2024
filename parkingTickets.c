#include <stdio.h>
#include "csvread.h"
#include "ticketsADT.h"
#include "front.h"
#include "queries.h"

int main(int argc,const char *argv[]){
    ticketsADT new = newTicket();
    csvReadInfractions(argv,new);
    query1(new);
    query2(new);
    query3(new);
    return 0;
}