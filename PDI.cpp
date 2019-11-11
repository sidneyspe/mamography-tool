#include "PDI.h"

/*Transforma a imagem usando Logaritmo*/

void transformToLogarithm(const Mat &inputImage, Mat &logarithmImage, float constValue){
		
	for (int linha = 0; linha < inputImage.rows; linha++){
		for (int coluna = 0; coluna < inputImage.cols; coluna++){

				logarithmImage.at<uchar>(linha,coluna) = ( constValue * log(1 + inputImage.at<uchar>(linha,coluna)));
		}
	}
	
}
/*--------------------------------------------------------------------------------------------------------------*/
/*Transforma a imagem em negativo*/

void transformToNegative(const Mat &inputImage, Mat &negativeImage)
{
		
	 for (int linha = 0; linha < inputImage.rows; linha++){
		for (int coluna = 0; coluna < inputImage.cols; coluna++){

				negativeImage.at<uchar>(linha,coluna) = (255 - inputImage.at<uchar>(linha,coluna));
		}
	}
	
}

/*--------------------------------------------------------------------------------------------------------------*/
/*Transforma a imagem utilizando a powerTransform (correção de gamma)*/
void powerTransform(const Mat &inputImage, Mat &powerImage, float constValue)
{

	float gammaValue = 0;
	
	for (int linha = 0; linha < inputImage.rows; linha++){
		for (int coluna = 0; coluna < inputImage.cols; coluna++){
			for( int canal = 0; canal < 3; canal++ ){
		
				gammaValue = ((inputImage.at<Vec3b>(linha,coluna)[canal])/constValue);
			
				powerImage.at<Vec3b>(linha,coluna)[canal] = (exp(gammaValue) -1);
		
			}
		}
	}
	
}

/*--------------------------------------------------------------------------------------------------------------*/
