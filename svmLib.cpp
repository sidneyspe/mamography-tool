#include "svmLib.h"
#include "templateMatchingLbp.h"
#include "PDI.h"


void cropImages(Mat inputImg, int xc, int yc, int raio, string pathNeg, int P, int R, string outFile, int classLabel){
	int count = 0;
	for(int i = 0; i < inputImg.rows - 2*raio; i = i + 2*raio){
		for(int j = 0; j < inputImg.cols - 2*raio; j = j + 2*raio){
			float dist  = sqrt(pow(xc - j, 2.0) + pow(yc - i, 2.0));
			stringstream tmp;
			string out, aux;
			tmp << count;
			tmp >> aux;
				if(dist > raio){
					Rect regiao(j,i,2*raio,2*raio);
					Mat outImage(inputImg,regiao);
					
					/* Rect r;
					r.x = j - raio;
					r.y = j + raio;
					r.width = 2*raio;
					r.height  = 2*raio; 
					Mat crop;
					inputImg(r).copyTo(crop); */
					
					Mat resizedImg(40, 40, inputImg.type());
					resize(outImage, resizedImg,resizedImg.size(), 0, 0);
					//cout<< aux <<endl;
					//out = "/home/sidney/workspace/libSVM_templateMatchingLBP/"+pathNeg + "/negativo_" + aux + ".jpg";
					//imwrite(out, resizedImg);
					equalizeHist(resizedImg,resizedImg);
					saveLBPFeatures(resizedImg, P, R, outFile, classLabel);
					
				}
			count++;
		}
	}
}

/* -------------------------------------------------------------------------------------------------------- */

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

/* -------------------------------------------------------------------------------------------------------- */

void marcarRegiao (string tipoRegiao, vector<string>& vTokens, string pathNeg, string outFile, int classLabel, int P, int R){

	int x=0, y=0, raio = 0;
	string img_path("MIAS/"+vTokens[0]+".pgm");

	cout<<img_path<<" "<< tipoRegiao<<endl;

	vector<string> vName;
	string str  = vTokens[0];
	tokenize(str, vName, ".");
	string name = vName[0] + ".pgm";

	Mat inputImage = imread(img_path.c_str(), 0);
	   
		if (!inputImage.empty() && vTokens.size() == 7){
			//cout<<vTokens[4]<<endl;
			x = atoi(vTokens[4].c_str());
			y = atoi(vTokens[5].c_str());
			raio = atoi(vTokens[6].c_str());
			string newName = vName[0] + "_"+tipoRegiao+".pgm";
			/**********************************************************************************************************************/
			//Circula e salva a imagem com a região do cancer
			string newNameCirculado = vName[0] + "_"+tipoRegiao+"_cicurlado.pgm";
			Mat imagemCirculada = imread(img_path.c_str(), 1);
			Point ROI (x,y);
						
			circle( imagemCirculada, ROI, raio, Scalar(0,255,0));
			imwrite(newNameCirculado, imagemCirculada);

			string comandoCirculado = "mv " + newNameCirculado + " cropped_"+tipoRegiao; // DAR UMA OLHADA NESSA LINHA!!! AVISO!!!
			system (comandoCirculado.c_str());

			/**********************************************************************************************************************/

			/**********************************************************************************************************************/
						//Fazer as moficações aqui em inputImage

						//Equalização do histograma:

						//cvtColor( inputImage, inputImage, CV_BGR2GRAY ); // Converte para escala de cinza;
						//equalizeHist(inputImage,inputImage);
						
						
						
						//cvtColor( logarithmImage, logarithmImage, CV_BGR2GRAY ); // Converte para escala de cinza;
						//namedWindow ("Imagem Equalizada");
						//imshow("Imagem Equalizada",inputImage);
						//waitKey(0);
						//cvDestroyWindow("Imagem Equalizada");
						
			/**********************************************************************************************************************/



			Rect regiao(x-raio,y-raio,2*raio,2*raio);

			 Rect regiao1(x+1-raio,y-raio,2*raio,2*raio);
			 string newName1 = vName[0] + "_1_"+tipoRegiao+".pgm";
			 salvaVariasRegioes(regiao1, inputImage, outFile, classLabel, P, R, newName1, tipoRegiao);

			 Rect regiao2(x-raio,y+1-raio,2*raio,2*raio);
			 string newName2 = vName[0] + "_2_"+tipoRegiao+".pgm";
			 salvaVariasRegioes(regiao2, inputImage, outFile, classLabel, P, R, newName2, tipoRegiao);

			 string newName3 = vName[0] + "_3_"+tipoRegiao+".pgm";
			 Rect regiao3(x-1-raio,y-raio,2*raio,2*raio);
			 salvaVariasRegioes(regiao3, inputImage, outFile, classLabel, P, R, newName3, tipoRegiao);

			 string newName4 = vName[0] + "_4_"+tipoRegiao+".pgm";
			 Rect regiao4(x-raio,y-1-raio,2*raio,2*raio);
			 salvaVariasRegioes(regiao4, inputImage, outFile, classLabel, P, R, newName4, tipoRegiao);

			 string newName5 = vName[0] + "_5_"+tipoRegiao+".pgm";
			 Rect regiao5(x-1-raio,y-1-raio,2*raio,2*raio);
			 salvaVariasRegioes(regiao5, inputImage, outFile, classLabel, P, R, newName5, tipoRegiao);

			 string newName6 = vName[0] + "_6_"+tipoRegiao+".pgm";
			 Rect regiao6(x+1-raio,y+1-raio,2*raio,2*raio);
			 salvaVariasRegioes(regiao6, inputImage, outFile, classLabel, P, R, newName6, tipoRegiao);

			Mat outImage(inputImage,regiao);

			Mat resizedImg(40, 40, inputImage.type());
			resize(outImage, resizedImg,resizedImg.size(), 0, 0);


			equalizeHist(resizedImg,resizedImg);
			saveLBPFeatures(resizedImg, P, R, outFile, classLabel);

			imwrite(newName, resizedImg);

			int classLabelPos = 0;
			cropImages(inputImage,x, y, raio, pathNeg, P, R, outFile, classLabelPos); //SALVA OS ARQUIVOS QUE NÃO SÃO CANCER

			string comando = "mv " + newName + " cropped_"+tipoRegiao; // DAR UMA OLHADA NESSA LINHA!!! AVISO!!!
			/* strcat(comando , "mv " );
			strcat (comando, nome);
			strcat (comando, " cropped_CIRC ");*/
			system (comando.c_str());

		} else {
			
				cout<<"erro abrindo arquivo"<<endl;
		}
		
}

void arquivaDados (vector<int> vHist, ofstream &outputFile, const int &classType){
	
	outputFile<<classType<<" ";

	int count = 1;
	for(int i = 0; i < vHist.size(); i++){
			outputFile<<count<<":"<< vHist[i] <<" ";
			count++;
	}

	outputFile<<endl;
}

void arquivaDadosGeral (vector<int> vHistP4R1, vector<int> vHistP4R2, vector<int> vHistP8R1, vector<int> vHistP8R2 , ofstream &outputFile, const int &classType){
	
	outputFile<<classType<<" ";

	int count = 1;
	//for(int i = 0; i < vHist.size(); i++){
	/*
	int i = 0;
		while (i < vHistP4R1.size() && i < vHistP4R2.size() && vHistP8R1.size() && vHistP8R2.size()){
	
			outputFile<<count<<":"<< vHistP4R1[i] <<" :"<< vHistP4R2[i] <<" :"<< vHistP8R1[i] <<" :"<< vHistP8R2[i] <<" ";
			count++;
			i++;
	}
	*/
	
	for(int i = 0; i < vHistP4R1.size(); i++){
		outputFile<<count<<":"<< vHistP4R1[i]<<" ";
		count++;
	}
	for(int i = 0; i < vHistP4R2.size(); i++){
		outputFile<<count<<":"<< vHistP4R2[i]<<" ";
		count++;
	}
	for(int i = 0; i < vHistP8R1.size(); i++){
		outputFile<<count<<":"<< vHistP8R1[i]<<" ";
		count++;
	}
	for(int i = 0; i < vHistP8R2.size(); i++){
		outputFile<<count<<":"<< vHistP8R2[i]<<" ";
		count++;
	}
	
	outputFile<<endl;
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

void salvaVariasRegioes(Rect regiao, Mat inputImage, string outFile, int classLabel, int P, int R, String newName, String tipoRegiao){

	Mat outImage(inputImage,regiao);
	Mat resizedImg(40, 40, inputImage.type());
	resize(outImage, resizedImg,resizedImg.size(), 0, 0);
	equalizeHist(resizedImg,resizedImg);
	saveLBPFeatures(resizedImg, P, R, outFile, classLabel);
	imwrite(newName, resizedImg);

	string comando = "mv " + newName + " cropped_"+tipoRegiao; // DAR UMA OLHADA NESSA LINHA!!! AVISO!!!
	system (comando.c_str());

}
