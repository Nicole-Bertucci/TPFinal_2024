#include <stdio.h>
#include <ctype.h>

typedef struct tMulta{
    char* plate
}tMulta;

typedef struct tInfraction{
    char* nameInfr;
    int cant;
    tMulta * multas;
    int dimMultas;
}tInfraction;

typedef struct tAgency{
    struct tAgency * next;
    char* nameAgency;
    int * infractionsPopularity;
}tAgency;

typedef struct multasADT{
tInfraction * infractions;
tAgency * firstAgency;
tAgency* iterAgency;
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

