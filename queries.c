#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ticketsADT.h"
#include "front.h"
#include "queries.h"

#define ERRORMEMORIA "Error de asignacion de memoria\n"


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

// void query1(ticketsADT ticket){
//     FILE * Q1CSV=newFile("query1.csv");
//     writeHeaderQ1(Q1CSV);
//     size_t index, id, indexNew=0;
//     ticketsADT new=newTicket();
//     size_t dim=getOccupied(ticket)+1;
//     cpyInf(ticket,new, dim);
    
//     for(size_t i=0, dimNew=dim; i<dimNew; dimNew=dimNew-1){
//         id=findMax(new, dimNew, &indexNew);
//         index=findIndexById(ticket, id,dim );
        
//         size_t total=getTotalFines(ticket, index);
        
//         char* finesAsStr=calloc(1, getSize(total)+1);
//         char infrName[DESCRIPTION];
//         strcpy(infrName,getInfractionName(ticket, index));
//         sprintf(finesAsStr, "%zu", total);
//         writeRowQ1(finesAsStr, infrName,Q1CSV);
//         newInf(new,new,dimNew-1, indexNew);
//         free(finesAsStr);
//     }
//     fclose(Q1CSV);    
// }
//borrar
void query1(ticketsADT ticket){
    FILE * Q1CSV=newFile("query1.csv");
    writeHeaderQ1(Q1CSV);
    sortByTotal(ticket);
    size_t totaltickets;
    char * infractionName;
    char * stringTotalTickets;
    size_t cant = getOccupied(ticket);
    for(size_t i=0; i<cant; i++){
        infractionName = getInfractionName(ticket, i);        
        totaltickets = getTotalFines(ticket, i);
         stringTotalTickets = calloc(1, getSize(totaltickets)+1);
        if (stringTotalTickets == NULL){
            perror(ERRORMEMORIA);
            exit(EXIT_FAILURE);           
        }
        sprintf(stringTotalTickets, "%zu", totaltickets);
        writeRowQ1(stringTotalTickets, infractionName,Q1CSV);
        free(stringTotalTickets);
    }
    fclose(Q1CSV);    
}

void query2(ticketsADT ticket){
    FILE *  Q2CSV = newFile("query2.csv");
    writeHeaderQ2(Q2CSV); 
    beginAgency(ticket);
    char * issuingAgency; 
    size_t index; 
    size_t totaltickets;
    char * infractionName;

    for (size_t i = 0; hasNextAgency(ticket) ; i++) {
        issuingAgency = getNameAgency(ticket); 
        totaltickets = mostpopular(ticket, &index);
        infractionName = getInfractionName(ticket, index);
        char * stringTotalTickets = calloc(1, getSize(totaltickets)+1);
        if (stringTotalTickets == NULL){
            perror(ERRORMEMORIA);
            exit(EXIT_FAILURE);           
        }
        sprintf(stringTotalTickets,"%zu",totaltickets);
        writeRowQ2(issuingAgency,infractionName,stringTotalTickets, Q2CSV);
        free(stringTotalTickets);
        nextAgency(ticket);
    }
    fclose(Q2CSV);    
}

void query3(ticketsADT ticket){
    FILE * Q3CSV =newFile("query3.csv");
    writeHeaderQ3(Q3CSV);
    sortByAlph(ticket);
    size_t fines=0;
    char plateAsStr[PLATE];    

    for(int id=0; id<getOccupied(ticket)+1; id++){
        fines=0;
        plateWithMostFines(ticket,id,&fines,plateAsStr);
        if (fines != 0) {
            char *finesAsStr=calloc(1, getSize(fines)+1);
            if (finesAsStr == NULL) {
                perror(ERRORMEMORIA);
                exit(EXIT_FAILURE);
            }

            sprintf(finesAsStr, "%zu", fines);
            writeRowQ3(getInfractionName(ticket, id),plateAsStr,finesAsStr,Q3CSV);
            free(finesAsStr);
        }
    }
    fclose(Q3CSV);
}
