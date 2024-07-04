#include <stdio.h>
#include "csvread.h"
#include "ticketsADT.h"

int main(const char *argv[]){
    ticketsADT new = newTicket();
    csvReadInfractions(argv[FILE_INFRACTION],new);
    query2(new);
    return 0;
}

