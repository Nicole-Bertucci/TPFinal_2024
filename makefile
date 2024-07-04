COMPILER=  gcc
CFLAGS= -pedantic -std=c99 -Wall -fsanitize=address -g
MAIN = parkingTickets.c 

FORMATNYC = -DFORMAT_NYC
FORMATCHI = -DFORMAT_CHI


all: programNYC programCHI clean

programNYC: $(MAIN) csvreadNYC.o front.o ticketsADT.o
	$(COMPILER) csvreadNYC.o front.o ticketsADT.o $(MAIN) -o parkingTicketsNYC $(CFLAGS)

programCHI: $(MAIN) csvreadCHI.o front.o ticketsADT.o
	$(COMPILER) csvreadCHI.o front.o ticketsADT.o $(MAIN) -o parkingTicketsCHI $(CFLAGS)

ticketsADT.o: ticketsADT.c
	$(COMPILER) $(CFLAGS) -c ticketsADT.c

csvreadNYC.o: csvread.c 
	$(COMPILER) $(FORMATNYC) $(CFLAGS) -c csvread.c -o csvreadNYC.o

csvreadCHI.o: csvread.c 
	$(COMPILER) $(FORMATCHI) $(CFLAGS) -c csvread.c -o csvreadCHI.o

front.o: front.c
	$(COMPILER) $(CFLAGS) -c front.c

clean:
	rm -f *.o