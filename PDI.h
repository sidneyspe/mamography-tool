#ifndef _PDI_H_
#define _PDI_H

#include <stdio.h>
#include <cstdlib>
#include <string>


#include <highgui.hpp>
#include "ml.hpp"
#include "core.hpp"

using namespace std;// utiliza as bibliotecas padrão (standard) do c++ 
using namespace cv; // utiliza as bibliotecas do opencv


void transformToNegative(const Mat &inputImage, Mat &negativeImage);
void transformToLogarithm(const Mat &inputImage, Mat &logarithmImage, float constValue);
void powerTransform(const Mat &inputImage, Mat &powerImage, float constValue);

#endif
