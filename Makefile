all: cooke_analyzer

cooke_analyzer: front.o cooke_analyzer.o
	$(CC) -Wall front.o cooke_analyzer.o -o cooke_analyzer	

.c.o:
	$(CC) -Wall -c $<


test: cooke_analyzer front.in
	./cooke_analyzer

clean:
	$(RM) cooke_analyzer.o front.o cooke_analyzer
