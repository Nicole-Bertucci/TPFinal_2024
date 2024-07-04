#include <stdio.h>
#include "csvread.h"
#include "ticketsADT.h"

int main(const char *argv[]){
    ticketsADT new = newTicket();
    csvReadInfractions(argv[FILE_INFRACTION],new);
    query1(new);
    query2(new);
    query3(new);
    return 0;
}

