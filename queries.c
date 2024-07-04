#include <stdio.h>
#include <stdlib.h>

#include "ticketsADT.h"
#include "front.h"

size_t getSize(size_t n){
    int size=0;
    if(n==0){
        size=1;
    }
    else{
        while(n!=0){
            n/=10;
            size++;
        }
    }
    return size;
}

void Query1(ticketsADT ticketAdt){
    FILE * Q1CSV=newFile("query1.csv");
    size_t index, id, indexNew=0;
    ticketsADT new=newTicket();
    
    size_t dim=getOccupied(ticketAdt)+1;
    writeHeaderQ1(Q1CSV);
   
    cpyInf(ticketAdt,new, dim);
    for(size_t i=0, dimNew=dim; i<dimNew; dimNew=dimNew-1){
        id=findMax(new, dimNew, &indexNew);
        index=findIndexById(ticketAdt, id,dim );
        
        size_t total=getTotalFines(ticketAdt, index);
        
        char* totalMultas=calloc(1, getSize(total)+1);
        char* infrName=stringCopy(getInfractionName(ticketAdt, index), DESCRIPTION);
        sprintf(totalMultas, "%zu", total);
        writeRowQ1(totalMultas, infrName,Q1CSV);
        newInf(new,new,dimNew-1, indexNew);
        }
}





