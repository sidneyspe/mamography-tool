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

	if (argc < 3){
	
	cout << "\n ./compara arquivoTeste arquivoPredicoes class_valor \n" <<endl;
	
	exit(0);
	
	}
	float truePositive = 0;
	float trueNegative = 0;
	float falsePositive = 0;
	float falseNegative = 0;


	
	ifstream fileTst;
	ifstream filePredict;

	fileTst.open(argv[1]);
	filePredict.open(argv[2]);
	int class_valor = atoi(argv[3]);

	string lineTst = "";
	getline(fileTst, lineTst);

	string linePredict = "";
	getline(filePredict, linePredict);
	getline(filePredict, linePredict);

	int contador = 1;
	while (!filePredict.eof() && !fileTst.eof()){

		vector<string> vPredict;
		tokenize(linePredict, vPredict, " ");


		vector<string> vTst;
		tokenize(lineTst, vTst, " ");

		int numeroTeste = atoi(vTst[0].c_str());//vTst[cont];
		//cout << contador << " numero Teste: "<< numeroTeste;
		int numeroPredict =  atoi(vPredict[0].c_str());//(int)vPredict[cont];
		//cout << " numero Predict: "<< numeroPredict <<endl;

		//string result_message = format("Actual class = %d / Predicted class = %d.", numeroTeste,numeroPredict);
		//cout << result_message << endl;

		if (numeroTeste == class_valor){
			if (numeroPredict == class_valor){
				//trueNegative++;
					truePositive++;
				} else {
				//	falsePositive++;
					falseNegative++;
				}
		}else{
				if (numeroPredict == 0){
				//	truePositive++;
					trueNegative++;
				} else {
				// falseNegative++;
					falsePositive++;
			}
		}



		getline(fileTst, lineTst);

		getline(filePredict, linePredict);
		contador++;
	}


	fileTst.close();
	filePredict.close();

	cout << endl;
	cout<< "True Positive: "<< truePositive << endl;
	cout<< "False Negative: "<< falseNegative << endl;
	cout<< "True Negative: "<< trueNegative << endl;
	cout<< "False Positive: "<< falsePositive << endl;

	cout << endl;
	float somaPositivo = truePositive + falseNegative;
	float somaNegativo = falsePositive + trueNegative;

	cout<< "True Positive: "<< (truePositive/somaPositivo)*100 << "% "<< endl;
	float TP = (truePositive/somaPositivo)*100;
	cout<< "False Negative: "<< (falseNegative/somaPositivo)*100 << "% "<< endl;
	float FN = (falseNegative/somaPositivo)*100;
	cout<< "True Negative: "<< (trueNegative/somaNegativo)*100 << "% " <<endl;
	float TN = (trueNegative/somaNegativo)*100;
	cout<< "False Positive: "<< (falsePositive/somaNegativo)*100 << "% "<< endl;
	float FP = (falsePositive/somaNegativo)*100;

	cout << endl;

	float sensitivity = truePositive / ( truePositive+falseNegative );
	float accuracy = ( truePositive + trueNegative ) / ( somaPositivo + somaNegativo );
	float specificity = trueNegative / ( falsePositive + trueNegative );
	float positive_predictive_value = truePositive / ( truePositive + falsePositive );
	float negative_predictive_value = trueNegative / ( trueNegative + falseNegative );

	cout << "Sensitivity = " << sensitivity <<endl;
	cout << "Accuracy = " << accuracy << endl;
	cout << "Specificity = " << specificity << endl;
	cout << "positive_predictive_value = " << positive_predictive_value << endl;
	cout << "negative_predictive_value = " << negative_predictive_value << endl;

	/* string arquivoTst = argv[1];
	vector<string> vTst = getImageNames(arquivoTst);
	//int maximoTst = vNamesTst.size();

	string arquivoPredict = argv[1];
	vector<string> vPredict = getImageNames(arquivoPredict);
	int maximoPredict = vTst.size();

	for (int cont=3; cont < maximoPredict; cont++){

		int numeroTeste = atoi(vTst[cont].c_str());//vTst[cont];
		cout << "numero Teste: "<< numeroTeste <<endl;
		int numeroPredict =  atoi(vPredict[cont].c_str());//(int)vPredict[cont];
		cout << "numero Predict: "<< numeroPredict <<endl;

	} */




	


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
