/*
 * svmLib.h
 *
 *  Created on: 20/05/2013
 *      Author: sidney
 */

#ifndef SVMLIB_H_
#define SVMLIB_H_

#include "highgui.hpp"
#include "imgproc.hpp"

#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <dirent.h>
#include <sstream>


using namespace std;
using namespace cv;


void cropImages(Mat inputImg, int xc, int yc, int raio, string pathNeg, int P, int R, string outFile, int classLabel);
void tokenize(const string& str, vector<string>& tokens, const string& delimiters);
void marcarRegiao (string tipoRegiao, vector<string>& vTokens, string pathNeg, string outFile, int classLabelNeg, int P, int R);
void arquivaDados (vector<int> vHist, ofstream &outputFile, const int &classType);
void arquivaDadosGeral (vector<int> vHistP4R1, vector<int> vHistP4R2, vector<int> vHistP8R1, vector<int> vHistP8R2 , ofstream &outputFile, const int &classType);
vector<string> getImageNames(string path);
void salvaVariasRegioes(Rect regiao, Mat inputImage, string outFile, int classLabel, int P, int R, String newName, String tipoRegiao);

#endif /* SVMLIB_H_ */
