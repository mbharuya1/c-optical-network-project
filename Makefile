PROGRAMS = ChaineMain ReconstitueReseau main graph Graphe.o graph.o main.o ReconstitueReseau.o Hachagee.o Reseau.o ChaineMain.o Chaine.o ArbreQuat.o SVGwriter.o
.PHONY: all clean

all: $(PROGRAMS)

SVGwriter.o : SVGwriter.c SVGwriter.h
	gcc -Wall -c SVGwriter.c SVGwriter.o

ChaineMain: ChaineMain.o Chaine.o SVGwriter.o
	gcc -Wall -o ChaineMain ChaineMain.o Chaine.o SVGwriter.o -lm

Chainemain.o: ChaineMain.c Chaine.o SVGwriter.o
	gcc -c ChaineMain.c -o ChaineMain.o -lm

Chaine.o: Chaine.c Chaine.h
	gcc -c Chaine.c -o Chaine.o SVGwriter.o -lm

Reseau.o: Reseau.c Reseau.h Chaine.h
	gcc -c Reseau.c -o Reseau.o Chaine.o

Hachagee.o: Hachagee.c Hachage.h Reseau.h 
	gcc -c Hachagee.c -o Hachagee.o Reseau.o

ArbreQuat.o: ArbreQuat.c ArbreQuat.h Reseau.h
	gcc -c ArbreQuat.c -o ArbreQuat.o Reseau.o

ReconstitueReseau.o: ReconstitueReseau.c Reseau.o Chaine.o Hachagee.o ArbreQuat.o
	gcc -c ReconstitueReseau.c -o ReconstitueReseau.o

ReconstitueReseau: ReconstitueReseau.o Reseau.o Chaine.o SVGwriter.o Hachagee.o ArbreQuat.o
	gcc -Wall -o ReconstitueReseau ReconstitueReseau.o Hachagee.o Reseau.o Chaine.o ArbreQuat.o SVGwriter.o -lm

main.o: main.c Reseau.o Chaine.o Hachagee.o ArbreQuat.o SVGwriter.o
	gcc -c main.c -o main.o

main: main.o Reseau.o Chaine.o Hachagee.o ArbreQuat.o SVGwriter.o
	gcc -Wall -o main main.o Hachagee.o Reseau.o Chaine.o ArbreQuat.o SVGwriter.o -lm

graph.o: graph.c Reseau.o Chaine.o Hachagee.o ArbreQuat.o SVGwriter.o
	gcc -c graph.c -o graph.o

graph: graph.o Reseau.o Chaine.o Hachagee.o ArbreQuat.o SVGwriter.o
	gcc -Wall -o graph graph.o Hachagee.o Reseau.o Chaine.o ArbreQuat.o SVGwriter.o -lm

Graphe.o: Graphe.c Graphe.h Reseau.h Struct_File.h
	gcc -c Graphe.c -o Graphe.o

clean:
	rm -f $(PROGRAMS) *.o