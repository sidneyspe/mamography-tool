#include "svmLib.h"
#include "templateMatchingLbp.h"


int main (int argc, char* argv[]){

	// open a file in write mode.
	ofstream outfile;

	// open a file in read mode.
	ifstream infile;

	infile.open(argv[1]);
	outfile.open("info_log.txt");

	string caminhoSaida = argv[2];
	string outFile = argv[3];
	int P = atoi(argv[4]);
	int R = atoi (argv[5]);
	
	if (argc < 5){
		
		cout << "\n./main arquivoContendoInformacoes.txt caminhoDeSaida arquivoSVM.libsvm P R \n" << endl;
		exit(0);
	
	}
	
		if(infile.fail()){
			cout<<"Erro abrindo arquivo"<<endl;
			exit(0);
		}
	     
		system (" mkdir cropped_CIRC ");
		system (" mkdir cropped_CALC ");
		system (" mkdir cropped_SPIC ");
		system (" mkdir cropped_MISC ");
		system (" mkdir cropped_ARCH ");
		system (" mkdir cropped_ASYM ");
		string line = "";
		getline(infile, line);

		while(!infile.eof()){
		
			vector<string> vTokens;
			tokenize(line, vTokens, " ");

				if (strstr(vTokens[2].c_str(),"CIRC")){
					int classLabel_1 = 1;
					marcarRegiao ("CIRC",vTokens,caminhoSaida.c_str(), outFile, classLabel_1, P,R);
					//void marcarRegiaoCirc (vector<string>& vTokens, string pathNeg, string outFile, int classLabel, int P, int R);
					getline(infile, line);
					outfile<<"MIAS/"+vTokens[0]+".pgm"<<" CIRC"<<endl;
					//break;
				}else if (strstr(vTokens[2].c_str(),"CALC")){
					int classLabel_2 = 2;
					marcarRegiao ("CALC",vTokens,caminhoSaida.c_str(), outFile, classLabel_2, P,R);
					//void marcarRegiaoCirc (vector<string>& vTokens, string pathNeg, string outFile, int classLabel, int P, int R);
					getline(infile, line);
					outfile<<"MIAS/"+vTokens[0]+".pgm"<<" CALC"<<endl;
				
					}else if (strstr(vTokens[2].c_str(),"SPIC")){
						int classLabel_3 = 3;
						marcarRegiao ("SPIC",vTokens,caminhoSaida.c_str(), outFile, classLabel_3, P,R);
						//void marcarRegiaoCirc (vector<string>& vTokens, string pathNeg, string outFile, int classLabel, int P, int R);
						getline(infile, line);
						outfile<<"MIAS/"+vTokens[0]+".pgm"<<" SPIC"<<endl;

						}else if (strstr(vTokens[2].c_str(),"MISC")){
							int classLabel_4 = 4;
							marcarRegiao ("MISC",vTokens,caminhoSaida.c_str(), outFile, classLabel_4, P,R);
							//void marcarRegiaoCirc (vector<string>& vTokens, string pathNeg, string outFile, int classLabel, int P, int R);
							getline(infile, line);
							outfile<<"MIAS/"+vTokens[0]+".pgm"<<" MISC"<<endl;

							}else if (strstr(vTokens[2].c_str(),"ARCH")){
								int classLabel_5 = 5;
								marcarRegiao ("ARCH",vTokens,caminhoSaida.c_str(), outFile, classLabel_5, P,R);
								//void marcarRegiaoCirc (vector<string>& vTokens, string pathNeg, string outFile, int classLabel, int P, int R);
								getline(infile, line);
								outfile<<"MIAS/"+vTokens[0]+".pgm"<<" ARCH"<<endl;

								}else if (strstr(vTokens[2].c_str(),"ASYM")){
									int classLabel_6 = 6;
									marcarRegiao ("ASYM",vTokens,caminhoSaida.c_str(), outFile, classLabel_6, P,R);
									//void marcarRegiaoCirc (vector<string>& vTokens, string pathNeg, string outFile, int classLabel, int P, int R);
									getline(infile, line);
									outfile<<"MIAS/"+vTokens[0]+".pgm"<<" ASYM"<<endl;

									}else{
				
							getline(infile, line);
					}
		}

	cout<<" FIM DO ARQUIVO "<<endl;
	// close the opened file.
	outfile.close();

	// close the opened file.
	infile.close();

	//string newComando = "svm-scale -l -1 -u 1 -s ranges.txt " + outFile + " > trn.scale.libsvm";
	//system (newComando.c_str());

	return 0;
}
