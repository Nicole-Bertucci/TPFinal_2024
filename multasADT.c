#include <stdio.h>
#include <ctype.h>

typedef struct tInfraction{
    char* name;
    int cant;
}tInfraction;

typedef struct tAgency{
    struct tAgency * next;
    char* name;
    tInfraction * infractions;
}tAgency;

typedef struct multasADT{
tInfraction * infractions;
tAgency * first;
tAgency* iter;
}multasADT;


// odenadas alfabeticamente 
// typedef struct tAgency{
//     tMulta* firstFine;
//     char* nameAgency;
//     char* infPop;
//     int cantInfPop;
//     struct tAgency nextAgency;
// }tAgency;

// typedef struct tInfraction{
//     unsigned int id;
//     char* name;
//     int totalInf;
//     char* popPlate;
//     int cantPopPlate;
//     struct tInfraction * nextInf
// } tInfraction;

// typedef struct fineCDT{
// tAgency * firstAgency;
// tAgency * iterAgency;
// tInfraction * firstInfraction;
// tInfraction * iterInfraction;
// }fineCDT;

