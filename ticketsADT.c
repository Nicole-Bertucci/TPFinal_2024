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

typedef struct ticketsADT{
tInfraction * infractions;
int dimInfraction;
tAgency * firstAgency;
tAgency* iterAgency;
}ticketsADT;

//hola :)
