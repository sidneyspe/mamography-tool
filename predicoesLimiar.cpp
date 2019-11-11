#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <dirent.h>
#include <sstream>
#include <sys/types.h>

using namespace std;

vector<string> getImageNames(string path);
void tokenize(const string& str, vector<string>& tokens, const string& delimiters);

int main (int argc, char* argv[]){

	if (argc < 4){
	
	cout << "\n ./predicoesLimiar arquivoPredicoes arquivoTeste arquivoSaida Limiar class_valor\n" <<endl;
	
	exit(0);
	
	}
	/* float truePositive = 0;
	float trueNegative = 0;
	float falsePositive = 0;
	float falseNegative = 0; */

	// Cria os arquivos
	ifstream arquivoPredicoes;
	ifstream arquivoTeste;

	//ifstream arquivo5;
	
	// Abre os arquivos
	arquivoPredicoes.open(argv[1]);
	arquivoTeste.open(argv[2]);
	float limiar = atof(argv[4]);
	int class_valor = atoi(argv[5]);
	//arquivo5.open(argv[5]);
	
	//captura as 2 primeiras linhas de cada arquivo
	string lineArquivoPredicoes = "";
	getline(arquivoPredicoes, lineArquivoPredicoes);
	getline(arquivoPredicoes, lineArquivoPredicoes);
	
	string lineArquivoTeste = "";
	getline(arquivoTeste, lineArquivoTeste);
	//getline(arquivoTeste, lineArquivoTeste);

	int valorAtual = 0;
	int contador = 1;
	while ( !arquivoPredicoes.eof()){

		// cria os tokens e os tonekiza
		vector<string> vArquivoPredicoes;
		tokenize(lineArquivoPredicoes, vArquivoPredicoes, " ");
		
		vector<string> vArquivoTeste;
		tokenize(lineArquivoTeste, vArquivoTeste, " ");

		// converte para atoi cada numero da segunda coluna ( marcados como zero )
		double valorDe0= atof(vArquivoPredicoes[1].c_str());
		int valorPredito = atoi(vArquivoPredicoes[0].c_str());
		
		int valorTeste = atoi (vArquivoTeste[0].c_str());
		//double nArquivo5_0 = atof(vArquivo5[1].c_str());
		
		// converte para atoi cada numero da terceira coluna ( marcados como um )		
		double valorDe1 = atoi(vArquivoPredicoes[2].c_str());
		
		ofstream arquivoSaida;
		arquivoSaida.open(argv[3], ios::app);
		if (valorDe0 > limiar){
			arquivoSaida << 0 << endl;
		}else{
			arquivoSaida << class_valor << endl;
		}
		
		
		/*
		if (valorDe0 > limiar){
			valorAtual = 0;
				if (valorTeste == valorAtual){
					arquivoSaida << 0 << endl;
				} else {
					arquivoSaida << 1 << endl;
					}
						
		}else{
			valorAtual = 1;
			if (valorTeste == valorAtual){
					arquivoSaida << 1 << endl;
				} else {
					arquivoSaida << 0 << endl;
					}	
		}	
		*/
		arquivoSaida.close();
		
		getline(arquivoPredicoes, lineArquivoPredicoes);
		getline(arquivoTeste, lineArquivoTeste);
		
		contador++;
	}


	arquivoPredicoes.close();
	arquivoTeste.close();

return 0;
}

void tokenize(const string& str, vector<string>& tokens, const string& delimiters){
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}
vector<string> getImageNames(string path){
    struct dirent **namelist;
    int n;
    vector<string> fileNames;
    n = scandir(path.c_str(), &namelist, 0, versionsort);
    if (n < 0){
        cout<<"\n scandir error \n";
        return fileNames;
    }else {
        int i = 0;
        while( i < n){
            fileNames.push_back(namelist[i]->d_name);
            free(namelist[i]);
            i++;
        }
        free(namelist);
    }
    return fileNames;

}
