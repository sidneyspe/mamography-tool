#include "templateMatchingLbp.h"
#include "svmLib.h"

///

uchar compareVal(uchar center, uchar val){
	return ((uchar)(val >= center));
}

///

//////////////////////////////////////////////////////////////////////////
void getLbpProjection(Mat roiImg, Mat img, Mat &backprojLbp, int P, int R){
	
	//float hue_range_clr[] = { 0, 180 };
  	//const float* ranges_clr = { hue_range_clr };
	switch (P){
		case 4 :
		{ //if (P==4)
			float hue_range[] = { 0, 8 };// o número 8 é igual a 2^3, que é igual a 2^(P-1)
			lbpProjection(roiImg, img, backprojLbp,P,R, hue_range);
			break;
		}
		
		case 8: //if (P==8)
		{
			float hue_range[] = { 0, 128 };// o número 128 é igual a 2^7, que é igual a 2^(P-1)
			lbpProjection(roiImg, img, backprojLbp,P,R, hue_range);
			break;
		}
		
		case 16: //if(P==16)
		{
			float hue_range[] = { 0, 32768 };// o número 32768 é igual a 2^15, que é igual a 2^(P-1)
			lbpProjection(roiImg, img, backprojLbp,P,R, hue_range);
			break;
		}
		
		default: //else
		{
			cout<<"ERROR"<<endl;
			break;
		}
	}



}

//////////////////////////////////////////////////////////////////////////
void getColorProjection(int x, int y, int w, int h, Mat img, Mat &backprojClr){
	Mat hsv; Mat hue;
	/// Transform it to HSV
	cvtColor( img, hsv, CV_BGR2HSV );
	
	MatND histColor;
	int histSizeColor = MAX( 180, 2 );
	/// Use only the Hue value
	float hue_range_clr[] = { 0, 180 };
  	const float* ranges_clr = { hue_range_clr };
	hue.create( hsv.size(), hsv.depth() );
	int nchannels[] = { 0, 0 };
	mixChannels( &hsv, 1, &hue, 1, nchannels, 1 );
	
	Mat roiClr = hue(Rect(x, y, h, w));
	
	calcHist( &roiClr, 1, 0, Mat(), histColor, 1, &histSizeColor, &ranges_clr, true, false );
	//normalize( hist, hist, 0, 255, NORM_MINMAX, -1, Mat() );
        /// Get Backprojection
       	const int nChannels = 0;
	
	calcBackProject( &hue, 1, &nChannels, histColor, backprojClr, &ranges_clr, 1.0, true );
	
}
//////////////////////////////////////////////////////////////////////////
void getLbpMat(const Mat& img, Mat &matLbp, int P, int R){
        matLbp = Mat::zeros(img.rows, img.cols, img.type());
        //uchar value = 0;

	switch (P+R){

		case 5: { //P=4 R =1
			for(int i = 1; i < img.rows - 1; i++){
				for(int j = 1; j < img.cols - 1; j++){
				        uchar centerVal = img.at<uchar>(i, j);
				        //matLbp.at<uchar>(i, j) = img.at<uchar>(i-1, j-1) >= centerVal | img.at<uchar>(i-1, j) >= centerVal | img.at<uchar>(i-1, j+1) >= centerVal | img.at<uchar>(i, j+1) >= centerVal | img.at<uchar>(i+1, j+1) >= centerVal | img.at<uchar>(i+1, j) >= centerVal | img.at<uchar>(i+1, j-1) >= centerVal | img.at<uchar>(i, j-1) >= centerVal;
				        matLbp.at<uchar>(i, j) = (int)compareVal(img.at<uchar>(i-1, j), centerVal)*pow(2.0, 3.0)
								+ (int)compareVal(img.at<uchar>(i, j+1), centerVal)*pow(2.0, 2.0)
								+ (int)compareVal(img.at<uchar>(i+1, j), centerVal)*pow(2.0, 1.0)
								+ (int)compareVal(img.at<uchar>(i, j-1), centerVal)*pow(2.0, 0.0);
				}
			}
			break;
		}

		case 6: {//(P==4 && R==2){
			for(int i = 2; i < img.rows - 2; i++){
				for(int j = 2; j < img.cols - 2; j++){
				        uchar centerVal = img.at<uchar>(i, j);
				        //matLbp.at<uchar>(i, j) = img.at<uchar>(i-1, j-1) >= centerVal | img.at<uchar>(i-1, j) >= centerVal | img.at<uchar>(i-1, j+1) >= centerVal | img.at<uchar>(i, j+1) >= centerVal | img.at<uchar>(i+1, j+1) >= centerVal | img.at<uchar>(i+1, j) >= centerVal | img.at<uchar>(i+1, j-1) >= centerVal | img.at<uchar>(i, j-1) >= centerVal;
				        matLbp.at<uchar>(i, j) = (int)compareVal(img.at<uchar>(i-2, j), centerVal)*pow(2.0, 3.0)
								+ (int)compareVal(img.at<uchar>(i, j+2), centerVal)*pow(2.0, 2.0)
								+ (int)compareVal(img.at<uchar>(i+2, j), centerVal)*pow(2.0, 1.0)
								+ (int)compareVal(img.at<uchar>(i, j-2), centerVal)*pow(2.0, 0.0);

				}
			}
			break;
		}
	
		case 9: {//(P==8 && R==1){
			for(int i = 1; i < img.rows - 1; i++){
				for(int j = 1; j < img.cols - 1; j++){
				        uchar centerVal = img.at<uchar>(i, j);
				        //matLbp.at<uchar>(i, j) = img.at<uchar>(i-1, j-1) >= centerVal | img.at<uchar>(i-1, j) >= centerVal | img.at<uchar>(i-1, j+1) >= centerVal | img.at<uchar>(i, j+1) >= centerVal | img.at<uchar>(i+1, j+1) >= centerVal | img.at<uchar>(i+1, j) >= centerVal | img.at<uchar>(i+1, j-1) >= centerVal | img.at<uchar>(i, j-1) >= centerVal;
				        matLbp.at<uchar>(i, j) = (int)compareVal(img.at<uchar>(i-1, j-1), centerVal)*pow(2.0, 7.0)
				                                + (int)compareVal(img.at<uchar>(i-1, j), centerVal)*pow(2.0, 6.0)
				                                + (int)compareVal(img.at<uchar>(i-1, j+1), centerVal)*pow(2.0, 5.0)
				                                + (int)compareVal(img.at<uchar>(i, j+1), centerVal)*pow(2.0, 4.0)
				                                + (int)compareVal(img.at<uchar>(i+1, j+1), centerVal)*pow(2.0, 3.0)
				                                + (int)compareVal(img.at<uchar>(i+1, j), centerVal)*pow(2.0, 2.0)
				                                + (int)compareVal(img.at<uchar>(i+1, j-1), centerVal)*pow(2.0, 1.0)
				                                + (int)compareVal(img.at<uchar>(i, j-1), centerVal)*pow(2.0, 0.0);

				}
			}
			break;
		}
	
		case 10: {//(P==8 && R==2){
			for(int i = 2; i < img.rows - 2; i++){
			       	for(int j = 2; j < img.cols - 2; j++){
					uchar centerVal = img.at<uchar>(i, j);
					//matLbp.at<uchar>(i, j) = img.at<uchar>(i-1, j-1) >= centerVal | img.at<uchar>(i-1, j) >= centerVal | img.at<uchar>(i-1, j+1) >= centerVal | img.at<uchar>(i, j+1) >= centerVal | img.at<uchar>(i+1, j+1) >= centerVal | img.at<uchar>(i+1, j) >= centerVal | img.at<uchar>(i+1, j-1) >= centerVal | img.at<uchar>(i, j-1) >= centerVal;
					matLbp.at<uchar>(i, j) = (int)compareVal(img.at<uchar>(i-2, j-2), centerVal)*pow(2.0, 7.0)
								+ (int)compareVal(img.at<uchar>(i-2, j), centerVal)*pow(2.0, 6.0)
								+ (int)compareVal(img.at<uchar>(i-2, j+2), centerVal)*pow(2.0, 5.0)
								+ (int)compareVal(img.at<uchar>(i, j+2), centerVal)*pow(2.0, 4.0)
								+ (int)compareVal(img.at<uchar>(i+2, j+2), centerVal)*pow(2.0, 3.0)
								+ (int)compareVal(img.at<uchar>(i+2, j), centerVal)*pow(2.0, 2.0)
								+ (int)compareVal(img.at<uchar>(i+2, j-2), centerVal)*pow(2.0, 1.0)
								+ (int)compareVal(img.at<uchar>(i, j-2), centerVal)*pow(2.0, 0.0);

				}
			}
			break;
		}

		case 18: {//(P==16 && R==2){
			for(int i = 2; i < img.rows - 2; i++){
				for(int j = 2; j < img.cols - 2; j++){
					uchar centerVal = img.at<uchar>(i, j);
					//matLbp.at<uchar>(i, j) = img.at<uchar>(i-1, j-1) >= centerVal | img.at<uchar>(i-1, j) >= centerVal | img.at<uchar>(i-1, j+1) >= centerVal | img.at<uchar>(i, j+1) >= centerVal | img.at<uchar>(i+1, j+1) >= centerVal | img.at<uchar>(i+1, j) >= centerVal | img.at<uchar>(i+1, j-1) >= centerVal | img.at<uchar>(i, j-1) >= centerVal;
					matLbp.at<uchar>(i, j) = (int)compareVal(img.at<uchar>(i-1, j-2), centerVal)*pow(2.0, 15.0)
								+ (int)compareVal(img.at<uchar>(i-2, j-2), centerVal)*pow(2.0, 14.0)
								+ (int)compareVal(img.at<uchar>(i-2, j-1), centerVal)*pow(2.0, 13.0)
								+ (int)compareVal(img.at<uchar>(i-2, j), centerVal)*pow(2.0, 12.0)
								+ (int)compareVal(img.at<uchar>(i-2, j+1), centerVal)*pow(2.0, 11.0)
								+ (int)compareVal(img.at<uchar>(i-2, j+2), centerVal)*pow(2.0, 10.0)
								+ (int)compareVal(img.at<uchar>(i-1, j+2), centerVal)*pow(2.0, 9.0)			
								+ (int)compareVal(img.at<uchar>(i, j+2), centerVal)*pow(2.0, 8.0)						
								+ (int)compareVal(img.at<uchar>(i+1, j+2), centerVal)*pow(2.0, 7.0)
								+ (int)compareVal(img.at<uchar>(i+2, j+2), centerVal)*pow(2.0, 6.0)
								+ (int)compareVal(img.at<uchar>(i+2, j+1), centerVal)*pow(2.0, 5.0)
								+ (int)compareVal(img.at<uchar>(i+2, j), centerVal)*pow(2.0, 4.0)
								+ (int)compareVal(img.at<uchar>(i+2, j-1), centerVal)*pow(2.0, 3.0)
								+ (int)compareVal(img.at<uchar>(i+2, j-2), centerVal)*pow(2.0, 2.0)
								+ (int)compareVal(img.at<uchar>(i+1, j-2), centerVal)*pow(2.0, 1.0)
								+ (int)compareVal(img.at<uchar>(i, j-2), centerVal)*pow(2.0, 0.0);
				}
			}
			break;
		}
	}
}

void getLbpHist(Mat &matLbp, vector<int> &vHist, int nBins, int P){
	
	vHist.assign(nBins, 0); // zera o conteudo de vHist
		
	//int denominadorNBins = ((pow(2.0, (double)P)) / P)/2;
	//int denominadorNBins = (pow(2.0, (double)P)) / P;
	int denominadorNBins = (pow(2.0, (double)P)) / nBins;
	
	for(int i = 0; i < matLbp.rows; i++){
		for(int j = 0; j < matLbp.cols; j++){
			int pixel = matLbp.at<uchar>(i,j);// obtém valor do pixel
			assert(pixel < 256 );
			//histograma[pixel] = histograma[pixel] + 1;
			int indice = pixel /(int)denominadorNBins; //obtém o valor da faixa de possibilidades de pixels
			assert(indice < nBins);
			vHist[indice] = vHist[indice] + 1;
	
		}
		
	}

}

void lbpProjection(Mat roiImg, Mat img, Mat &backprojLbp, int P, int R, float hue_range[]){
	Mat matLbp;
	MatND histLbp;
	int binsLbp = 64;// variar entre 4 e 128, com passo 8
	getLbpMat(img, matLbp,P,R);
	equalizeHist(matLbp, matLbp);
	int histSize = MAX( binsLbp, 2 );
	const int nChannels = 0;

	//float hue_range[] = { 0, 128 };// o número 128 é igual a 2^7, que é igual a 2^(P-1)
  	const float* ranges = { hue_range };
	calcHist( &roiImg, 1, 0, Mat(), histLbp, 1, &histSize, &ranges, true, false );
	calcBackProject( &img, 1, &nChannels, histLbp, backprojLbp, &ranges, 1.0, true );
}

void saveLBPFeatures(Mat &resizedAndCroppedImg, int P, int R, string outFile, int classLabel){

	//Mat matLbp;
	Mat matLbpP4R1;
	Mat matLbpP4R2;
	Mat matLbpP8R1;
	Mat matLbpP8R2;
	
	//fazer as operações de imagens aqui



	//getLbpMat(resizedAndCroppedImg, matLbp, P, R);
	
	getLbpMat(resizedAndCroppedImg, matLbpP4R1, 4, 1);
	getLbpMat(resizedAndCroppedImg, matLbpP4R2, 4, 2);
	getLbpMat(resizedAndCroppedImg, matLbpP8R1, 8, 1);
	getLbpMat(resizedAndCroppedImg, matLbpP8R2, 8, 2);			
	
	//vector<int> histLbp;
	vector<int> histLbpP4R1;
	vector<int> histLbpP4R2;
	vector<int> histLbpP8R1;
	vector<int> histLbpP8R2;

	//int nBins = (pow(2.0, (double)P))/2;
	int nBinsP4 = (pow(2.0, (double)4))/2;
	int nBinsP8 = (pow(2.0, (double)8))/2;


	//void getLbpHist(Mat matLbp, vector<int> &vHist, int nBins, int P);
	
	//getLbpHist(matLbp, histLbp, nBins, P);
	getLbpHist(matLbpP4R1, histLbpP4R1, nBinsP4, 4);
	getLbpHist(matLbpP4R2, histLbpP4R2, nBinsP4, 4);
	getLbpHist(matLbpP8R1, histLbpP8R1, nBinsP8, 8);
	getLbpHist(matLbpP8R2, histLbpP8R2, nBinsP8, 8);
		
	
	// abrir arquivo com ofstream append

	ofstream fout;
	fout.open(outFile.c_str(), ios::app);
	
		
	//arquivaDados (histLbp,fout, classLabel);
	arquivaDadosGeral (histLbpP4R1, histLbpP4R2, histLbpP8R1, histLbpP8R2,fout, classLabel);
	
	
	fout.close();
	//salvar vHist no arquivo libsvm, criar um for para salvar o histLbp
				
	//for para calcular a combinação dos classificadores
	string arquivoSaida[] = {"teste/P4R1.libsvm","teste/P4R2.libsvm","teste/P8R1.libsvm","teste/P8R2.libsvm"};

	
	for (int i = 0; i < 4; i++){
		ofstream saida;
		saida.open(arquivoSaida[i].c_str(), ios::app);
			//cout << arquivoSaida[i].c_str() << endl;
			
			if (i == 0){
				arquivaDados (histLbpP4R1, saida, classLabel);}
			if (i == 1){
				arquivaDados (histLbpP4R2, saida, classLabel);}
			if (i == 2){
				arquivaDados (histLbpP8R1, saida, classLabel);}
			if (i == 3){
				arquivaDados (histLbpP8R2, saida, classLabel);}
	
		saida.close();
	}
	
					
}
