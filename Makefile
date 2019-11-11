all: main

INCLUDEPATH= -I /usr/local/include/opencv2/highgui/ -I /usr/local/include/opencv2/ml -I /usr/local/include/opencv2/core -I /usr/local/include/opencv2/imgproc/
LIBPATH=-L /usr/local/lib/
LIBS= -lopencv_highgui -lopencv_ml -lopencv_core -lm -lopencv_imgproc
COMPILADOR = g++ -g -Wall -Wextra -pedantic


PDI.o : PDI.cpp PDI.h
	$(COMPILADOR) -c PDI.cpp -o PDI.o   $(INCLUDEPATH) 

svmLib.o : svmLib.cpp svmLib.h
	$(COMPILADOR) -c svmLib.cpp -o svmLib.o $(INCLUDEPATH)

templateMatchingLbp.o : templateMatchingLbp.cpp templateMatchingLbp.h
	$(COMPILADOR) -c templateMatchingLbp.cpp -o templateMatchingLbp.o $(INCLUDEPATH)

main : main.cpp svmLib.o templateMatchingLbp.o PDI.o
	$(COMPILADOR) PDI.o svmLib.o templateMatchingLbp.o main.cpp -o main   $(INCLUDEPATH) $(LIBPATH) $(LIBS)
	
compara: compara.cpp 
	$(COMPILADOR)  compara.cpp -o compara
	

regra: regra_do_produto_e_da_soma.cpp
	$(COMPILADOR) regra_do_produto_e_da_soma.cpp -o regra_do_produto_e_da_soma
	
predicoesLimiar: predicoesLimiar.cpp
	$(COMPILADOR) predicoesLimiar.cpp -o predicoesLimiar
	
comparaLimiar: comparaLimiar.cpp
	$(COMPILADOR) comparaLimiar.cpp -o comparaLimiar

clear:
	rm *.o
