FUENTE = lambda
PRUEBA = examples.txt
LIB = lfl

all: compile run

compile:
	flex $(FUENTE).l
	bison -d $(FUENTE).y
	gcc -o $(FUENTE) lex.yy.c $(FUENTE).tab.c -$(LIB)

run:
	./$(FUENTE) < $(PRUEBA)

clean:
	rm -f $(FUENTE) lex.yy.c $(FUENTE).tab.c $(FUENTE).tab.h
