#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "ticketsADT.h"
#include "csvread.h"
#define LINE 250
#define READ "rt"

void csvReadInfractions(const char * argv[], ticketsADT tickets){


    FILE * infractionFile = fopen(argv[FILE_INFRACTION], READ); 
    if (infractionFile == NULL) {
        perror("Error en la apertura del archivo de infacciones");
        exit(EXIT_FAILURE);
    }
    char s[LINE];
    fgets(s,LINE,infractionFile);
    while (fgets(s,LINE,infractionFile), infractionFile){
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
            addInfraction(tickets,id,name);
        }       
    }
    fclose(infractionFile);
    //falta la funciones para ordenar el vector de infracciones
    ordenar(tickets);
    csvReadTickets(argv,tickets);
}

void csvReadTickets(const char * argv[], ticketsADT tickets) {
    FILE * ticketsFile = fopen(argv[FILE_TICKET], READ); 
    if (ticketsFile == NULL) {
        perror("Error en la apertura del archivo de tickets");
        exit(EXIT_FAILURE);
    }    
    char s[LINE];
    fgets(s,LINE,ticketsFile);
    while (fgets(s,LINE,ticketsFile), ticketsFile){
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
            addMulta(tickets,id,plate,agency);
        }       
    }
    fclose(ticketsFile);
}
