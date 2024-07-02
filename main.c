#include <stdio.h>
#include "ticketsADT.h"
#include "csvread.h"

int main(){
    ticketsADT new = newTicket();
    csvReadInfractions(new);

    return 0;
}

