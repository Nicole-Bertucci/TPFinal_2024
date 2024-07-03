COMPILER=  gcc
CFRAGS= -pedantic -std=c99 -Wall -fsanitize=address -g
MAIN = parkingTickets.c 

FORMAT = NO SE COMO SE HACE


all: programNYC programCHI clean

programNYC: $(MAIN) csvreadNYC.o front.o ticketsADT.o
	$(COMPILER) csvreadNYC.o front.o ticketsADT.o $(MAIN) -o parkingTicketsNYC $(CFRAGS)

programCHI: $(MAIN) csvreadCHI.o front.o ticketsADT.o
	$(COMPILER) csvreadCHI.o front.o ticketsADT.o $(MAIN) -o parkingTicketsCHI $(CFRAGS)

ticketsADT.o: ticketsADT.c
	$(COMPILER) $(CFRAGS) -c ticketsADT.c

csvreadNYC.o: csvread.c 
	$(COMPILER) $(FORMAT) $(CFRAGS) -c csvread.c -o csvreadNYC.o

csvreadCHI.o: csvread.c 
	$(COMPILER) $(FORMAT) $(CFRAGS) -c csvread.c -o csvreadCHI.o

front.o: front.c
	$(COMPILER) $(CFRAGS) -c front.c

clean:
	rm -r *.o