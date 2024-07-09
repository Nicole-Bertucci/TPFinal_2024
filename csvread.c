#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "csvread.h"

#define LINE 250
#define READ "rt"

void csvReadInfractions(const char * argv[], ticketsADT ticket){

    FILE * infractionFile = fopen(argv[FILE_INFRACTION], READ); 
    if (infractionFile == NULL) {
        perror("Error en la apertura del archivo de infacciones\n");
        exit(EXIT_FAILURE);
    }
    char s[LINE];
    fgets(s,LINE,infractionFile);
    while (fgets(s,LINE,infractionFile)){
        
        size_t id;
        char * name;
        char * token = strtok(s,SEPARATOR);
        if (token != NULL) {
            for (int i = 0; token != NULL; i++) {
                switch (i) {
                case idInfraction:
                    id = atoi(token);
                    break;
                
                case description:
                    name = token;
                    break;

                default:
                    break;
                }
            token = strtok(NULL,SEPARATOR);
            
            }
            addInfraction(ticket,id,name);
        }       
    }
    fclose(infractionFile);
    resize(ticket);
    sortByID(ticket);
    csvReadTickets(argv,ticket);
}

void csvReadTickets(const char * argv[], ticketsADT ticket) {
    FILE * ticketsFile = fopen(argv[FILE_TICKET], READ); 
    if (ticketsFile == NULL) {
        perror("Error en la apertura del archivo de tickets\n");
        exit(EXIT_FAILURE);
    }    
    char s[LINE];
    fgets(s,LINE,ticketsFile);
    while (fgets(s,LINE,ticketsFile)){
        size_t id;
        char * plate;
        char * agency;
        char * token = strtok(s,SEPARATOR);
        if (token != NULL) {
            for (int i = 0; token != NULL; i++) {
                switch (i) {
                case infractionId:
                    id = atoi(token);
                    break;
                
                case Plate:
                    plate = token;
                    break;

                case issuingAgency:
                    agency = token;
                    break;

                default:
                    break;
                }
            token = strtok(NULL,SEPARATOR);
            }
            addFine(ticket,id,plate,agency);
        }       
    }
    fclose(ticketsFile);

}
