CPP = g++ -Wall -pedantic


SF = -lsfml-graphics -lsfml-window -lsfml-system 


Arquivos = main.cpp heroi.cpp base.cpp projeteis.cpp inimigo.cpp 


all:
	$(CPP) $(Arquivos) -o Base_Defense $(SF)

run:
	./Base_Defense