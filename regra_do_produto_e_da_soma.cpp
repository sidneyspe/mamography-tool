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
	
	cout << "\n ./regra_do_produto_e_da_soma prediçõesP4R1 prediçõesP4R2 prediçõesP8R1 prediçõesP8R2 \n" <<endl;
	
	exit(0);
	
	}
	/* float truePositive = 0;
	float trueNegative = 0;
	float falsePositive = 0;
	float falseNegative = 0; */

	// Cria os arquivos
	ifstream arquivo1;
	ifstream arquivo2;
	ifstream arquivo3;
	ifstream arquivo4;
	//ifstream arquivo5;
	
	// Abre os arquivos
	arquivo1.open(argv[1]);
	arquivo2.open(argv[2]);
	arquivo3.open(argv[3]);
	arquivo4.open(argv[4]);
	//arquivo5.open(argv[5]);
	
	//captura as 2 primeiras linhas de cada arquivo
	string lineArquivo1 = "";
	getline(arquivo1, lineArquivo1);
	getline(arquivo1, lineArquivo1);

	string lineArquivo2 = "";
	getline(arquivo2, lineArquivo2);
	getline(arquivo2, lineArquivo2);
	
	string lineArquivo3 = "";
	getline(arquivo3, lineArquivo3);
	getline(arquivo3, lineArquivo3);
	
	string lineArquivo4 = "";
	getline(arquivo4, lineArquivo4);
	getline(arquivo4, lineArquivo4);
	
	/*string lineArquivo5 = "";
	getline(arquivo5, lineArquivo5);
	getline(arquivo5, lineArquivo5);*/

	int contador = 1;
	while ( !arquivo1.eof() && !arquivo2.eof() && !arquivo3.eof() && !arquivo4.eof() ){

		// cria os tokens e os tonekiza
		vector<string> vArquivo1;
		tokenize(lineArquivo1, vArquivo1, " ");

		vector<string> vArquivo2;
		tokenize(lineArquivo2, vArquivo2, " ");
		
		vector<string> vArquivo3;
		tokenize(lineArquivo3, vArquivo3, " ");
		
		vector<string> vArquivo4;
		tokenize(lineArquivo4, vArquivo4, " ");
		
		/*vector<string> vArquivo5;
		tokenize(lineArquivo5, vArquivo5, " ");*/

		// converte para atoi cada numero da segunda coluna ( marcados como zero )
		double prob_p4_r1_classe0 = atof(vArquivo1[1].c_str());
		double prob_p4_r2_classe0 = atof(vArquivo2[1].c_str());
		double prob_p8_r1_classe0 = atof(vArquivo3[1].c_str());
		double prob_p8_r2_classe0 = atof(vArquivo4[1].c_str());
		//double nArquivo5_0 = atof(vArquivo5[1].c_str());
		
		// converte para atoi cada numero da terceira coluna ( marcados como um )		
		double prob_p4_r1_classe1 = atof(vArquivo1[2].c_str());
		double prob_p4_r2_classe1 = atof(vArquivo2[2].c_str());
		double prob_p8_r1_classe1 = atof(vArquivo3[2].c_str());
		double prob_p8_r2_classe1 = atof(vArquivo4[2].c_str());
		//double nArquivo5_5 = atof(vArquivo5[2].c_str());
		
		// regra da soma
		double prob_classe0_soma = prob_p4_r1_classe0 + prob_p4_r2_classe0 + prob_p8_r1_classe0 + prob_p8_r2_classe0;
		double prob_classe1_soma = prob_p4_r1_classe1 + prob_p4_r2_classe1 + prob_p8_r1_classe1 + prob_p8_r2_classe1;		
		

		//regra do produto
		double prob_classe0_produto = prob_p4_r1_classe0 * prob_p4_r2_classe0 * prob_p8_r1_classe0 * prob_p8_r2_classe0;
		double prob_classe1_produto = prob_p4_r1_classe1 * prob_p4_r2_classe1 * prob_p8_r1_classe1 * prob_p8_r2_classe1;	

		ofstream saidaSoma;
		saidaSoma.open("newPredicoes_soma", ios::app);
		
			if(prob_classe0_soma > prob_classe1_soma)
    				saidaSoma << 0 << endl;

			if(prob_classe1_soma > prob_classe0_soma)
				saidaSoma << 1 << endl;
		
		saidaSoma.close();
		
		
		ofstream saidaProduto;
		saidaProduto.open("newPredicoes_produto", ios::app);
		
			if(prob_classe0_produto > prob_classe1_produto)
    				saidaProduto << 0 << endl;

			if(prob_classe1_produto > prob_classe0_produto)
				saidaProduto << 1 << endl;
		
		saidaProduto.close();
		

		getline(arquivo1, lineArquivo1);
		getline(arquivo2, lineArquivo2);
		getline(arquivo3, lineArquivo3);
		getline(arquivo4, lineArquivo4);
		//getline(arquivo5, lineArquivo5);

		contador++;
	}


	arquivo1.close();
	arquivo2.close();
	arquivo3.close();
	arquivo4.close();
	//arquivo5.close();


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
