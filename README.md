# TPFinal_2024

## Alumnos

- Santiago Fraga (64346)
- Nicole Bertucci (64415)

## Descripción del Proyecto

El proyecto TPFinal_2024 es una aplicación para gestionar y analizar multas de estacionamiento utilizando un árbol para optimizar la eficiencia en la búsqueda y almacenamiento de datos. El programa procesa dos archivos CSV: uno que contiene los tickets de estacionamiento (`tickets.csv`) y otro que contiene las infracciones (`infractions.csv`).

## Lista de Archivos

### Fuente

- **main.c**: Contiene la función principal del programa.
- **ticketsADT.c**: Implementa la lógica para manejar las estructuras de datos de las multas y agencias.
- **csvread.c**: Funciones para leer y procesar archivos CSV.
- **queries.c**: Implementa las consultas sobre las multas.
- **front.c**: Contiene las funciones para escribir la salida.
- **makefile**: Archivo para automatizar la compilación del proyecto.

### Encabezado

- **ticketsADT.h**: Declara las funciones y estructuras utilizadas en `ticketsADT.c`.
- **csvread.h**: Declara las funciones utilizadas en `csvread.c`.

## Compilacion del proyecto

```sh
make
```

## Ejecucion del proyecto

Para ejecutar el codigo hay que pasarle 2 parametros

### Para New York

´´´
​./parkingTicketsNYC ticketsNYC.csv infractionsNYC.csv
´´´

### Para Chicago

´´´
​./parkingTicketsCHI ticketsCHI.csv infractionsCHI.csv
´´´
