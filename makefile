COMPILER=  gcc
CFLAGS= -pedantic -std=c99 -Wall -fsanitize=address -g
MAIN = parkingTickets.c 

FORMATNYC = -DFORMATNYC\=1
FORMATCHI = -DFORMATCHI\=1


all: programNYC programCHI clean

programNYC: $(MAIN) csvreadNYC.o front.o ticketsADTNYC.o queriesNYC.o
	$(COMPILER) $(CFLAGS) csvreadNYC.o front.o queriesNYC.o ticketsADTNYC.o $(MAIN) -o parkingTicketsNYC 

programCHI: $(MAIN) csvreadCHI.o front.o ticketsADTCHI.o queriesCHI.o
	$(COMPILER) $(CFLAGS) csvreadCHI.o front.o queriesCHI.o ticketsADTCHI.o $(MAIN) -o parkingTicketsCHI 

ticketsADTNYC.o: ticketsADT.c
	$(COMPILER) $(FORMATNYC) $(CFLAGS) -c ticketsADT.c -o ticketsADTNYC.o

ticketsADTCHI.o: ticketsADT.c
	$(COMPILER) $(FORMATCHI) $(CFLAGS) -c ticketsADT.c -o ticketsADTCHI.o

queriesNYC.o: queries.c
	$(COMPILER) $(FORMATNYC) $(CFLAGS) -c queries.c -o queriesNYC.o

queriesCHI.o: queries.c
	$(COMPILER) $(FORMATCHI) $(CFLAGS) -c queries.c -o queriesCHI.o

csvreadNYC.o: csvread.c 
	$(COMPILER) $(FORMATNYC) $(CFLAGS) -c csvread.c -o csvreadNYC.o

csvreadCHI.o: csvread.c 
	$(COMPILER) $(FORMATCHI) $(CFLAGS) -c csvread.c -o csvreadCHI.o

front.o: front.c
	$(COMPILER) $(CFLAGS) -c front.c

clean:
	rm -f *.o