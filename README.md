# TPFinal_2024

## Alumnos

- Santiago Fraga (64346)
- Nicole Bertucci (64415)

## Descripción del Proyecto

El proyecto TPFinal_2024 es una aplicación para gestionar y analizar multas de estacionamiento utilizando un árbol para optimizar la eficiencia en la búsqueda y almacenamiento de datos. El programa procesa dos archivos CSV: uno que contiene los tickets de estacionamiento (`tickets.csv`) y otro que contiene las infracciones (`infractions.csv`), y con esto llevan a cabo las queries 1, 2 y 3.

### Query 1: Total de multas por infracción
Cada línea de la salida debe contener, separados por “;” el nombre de la infracción y la cantidad total de multas con esa infracción. 
La información debe listarse ordenada en forma descendente por la cantidad total de multas y a igualdad de multas desempatar alfabéticamente por nombre de la infracción. 


### Query 2: Infracción más popular por agencia emisora
Donde cada línea de la salida debe contener, separados por “;” el nombre de la agencia emisora, la infracción más popular de esa agencia emisora y la cantidad de multas correspondiente.
La infracción más popular de una agencia emisora es la que tiene la mayor cantidad de multas. En caso de que existan dos o más infracciones con la misma cantidad de multas para la misma agencia emisora considerar la menor infracción en orden alfabético.
La información debe listarse ordenada en forma alfabética por agencia emisora.

### Query 3: Patente con más multas por infracción
Donde cada línea de la salida contenga, separados por “;” el nombre de la infracción, la patente con la mayor cantidad de multas de esa infracción y la cantidad de multas.
En caso de que existan dos o más patentes con la misma cantidad de multas para la misma infracción considerar la menor patente en orden alfabético.
La información debe listarse ordenada en forma alfabética por infracción. 


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
- **queries.h**: Declara las funciones utilizadas en `queries.c`.
- **front.h**: Declara las funciones utilizadas en `front.c`.

## Compilacion del proyecto

Para compilar el proyecto solamente es necesario utilizar el comando make, esto genera dos archivos ejecutables: parkingTicketsCHI y parkingTicketsNYC, donde el primero corresponde a la ciudad de Chicago y el segundo a Nueva York.

```sh
make
```

## Ejecucion del proyecto

Para ejecutar el codigo hay que pasarle 2 parametros: primero el archivo de tickets y luego el de infracciones (ambos archivos .csv)


### Para New York

´´´
​./parkingTicketsNYC ticketsNYC.csv infractionsNYC.csv
´´´

### Para Chicago

´´´
​./parkingTicketsCHI ticketsCHI.csv infractionsCHI.csv
´´´
