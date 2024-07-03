#ifndef __csvread_h_
#define  __csvread_h_

#include "ticketsADT.h"

#define FORMAT_INFRACTION \
    idInfraction, \
    description, 

enum INFRACTIONS{
    FORMAT_INFRACTION
};

#if FORMATNYC
#define FORMAT_TICKETS_NYC \
    Plate, \
    issueDate, \
    infractionId, \
    fineAmount, \
    issuingAgency

enum TICKETSNYC{
    FORMAT_TICKETS_NYC
};

#elif FORMATCHI
#define FORMAT_TICKETS_CHI \
    issueDate, \
    Plate, \
    issuingAgency, \
    infractionId, \
    fineAmount, \

enum TICKETSCHI{
    FORMAT_TICKETS_CHI
}; 

#endif
#define FILE_INFRACTION 2
#define FILE_TICKET 1


// Funcion que lee el archivo de las infracciones
void csvReadInfractions(const char * argv[],ticketsADT tickets);



void csvReadTickets();


#endif