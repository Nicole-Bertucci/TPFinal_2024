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

void query1(ticketsADT ticket){
    FILE * Q1CSV=newFile("query1.csv");
    writeHeaderQ1(Q1CSV);
    sortByTotal(ticket);
    size_t totalFines;
    char * infractionName;
    char * stringTotalFines;
    size_t cant = getOccupied(ticket);
    for(size_t i=0; i<cant; i++){
        infractionName = getInfractionName(ticket, i);        
        totalFines = getTotalFines(ticket, i);
         stringTotalFines = calloc(1, getSize(totalFines)+1);
        if (stringTotalFines == NULL){
            perror(ERRORMEMORIA);
            exit(EXIT_FAILURE);           
        }
        sprintf(stringTotalFines, "%zu", totalFines);
        writeRowQ1(stringTotalFines, infractionName,Q1CSV);
        free(stringTotalFines);
    }
    fclose(Q1CSV);    
}

void query2(ticketsADT ticket){
    FILE *  Q2CSV = newFile("query2.csv");
    writeHeaderQ2(Q2CSV); 
    beginAgency(ticket);
    char * issuingAgency; 
    size_t index; 
    size_t totalFines;
    char * infractionName;

    for (size_t i = 0; hasNextAgency(ticket) ; i++) {
        issuingAgency = getNameAgency(ticket); 
        totalFines = mostpopular(ticket, &index);
        infractionName = getInfractionName(ticket, index);
        char * stringTotalFines = calloc(1, getSize(totalFines)+1);
        if (stringTotalFines == NULL){
            perror(ERRORMEMORIA);
            exit(EXIT_FAILURE);           
        }
        sprintf(stringTotalFines,"%zu",totalFines);
        writeRowQ2(issuingAgency,infractionName,stringTotalFines, Q2CSV);
        free(stringTotalFines);
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
            char *stringTotalFines=calloc(1, getSize(fines)+1);
            if (stringTotalFines == NULL) {
                perror(ERRORMEMORIA);
                exit(EXIT_FAILURE);
            }

            sprintf(stringTotalFines, "%zu", fines);
            writeRowQ3(getInfractionName(ticket, id),plateAsStr,stringTotalFines,Q3CSV);
            free(stringTotalFines);
        }
    }
    fclose(Q3CSV);
}
