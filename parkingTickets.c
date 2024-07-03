#include <stdio.h>
#include "csvread.h"
#include "ticketsADT.h"

int main(const char *argv[]){
    ticketsADT new = newTicket();
    csvReadInfractions(argv[FILE_INFRACTION],new);

    return 0;
}

