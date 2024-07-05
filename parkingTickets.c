#include <stdio.h>
#include "csvread.h"
#include "ticketsADT.h"
#include "front.h"
#include "queries.h"

int main(int argc,const char *argv[]){
    ticketsADT new = newTicket();
    printf("new finalizo\n");
    csvReadInfractions(argv,new);
    printf("leido finalizo\n");
    //query1(new);
    printf("Q1 finalizo\n");
    query2(new);
    printf("Q2 finalizo\n");
    query3(new);
    printf("Q3 finalizo\n");
    freeTicket(new);
    return 0;
}