#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ticketsADT.h"
#include "front.h"


static size_t getSize(size_t n){
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

void query1(ticketsADT ticketAdt){
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
        
        char* finesAsStr=calloc(1, getSize(total)+1);
        char infrName[DESCRIPTION];
        strcpy(infrName,getInfractionName(ticketAdt, index));
        sprintf(finesAsStr, "%zu", total);
        writeRowQ1(finesAsStr, infrName,Q1CSV);
        newInf(new,new,dimNew-1, indexNew);
        free(finesAsStr);
        }
}


void query3(ticketsADT ticketAdt){
    FILE * Q3CSV =newFile("query3.csv");
    writeHeaderQ3(Q3CSV);
    sortByAlph(ticketAdt);
    size_t fines=0;
    char plateAsStr[PLATE];    

    for(int id=0; id<getOccupied(ticketAdt)+1; id++){
        //no funciona plateWithMostFines
       strcpy(plateAsStr, plateWithMostFines(ticketAdt,id,&fines));
       char *finesAsStr=calloc(1, getSize(fines));
       sprintf(finesAsStr, "%zu", fines);
       writeRowQ3(getInfractionName(ticketAdt, id),plateAsStr,finesAsStr,Q3CSV);
       free(finesAsStr);
    }
}




