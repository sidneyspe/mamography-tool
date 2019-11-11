#ifndef _TMLBP_
#define _TMLBP_

//#include "cv.h"

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

void getLbpProjection(Mat roiImg, Mat img, Mat &backprojLbp, int P, int R);
void getColorProjection(int x, int y, int w, int h, Mat img, Mat &backprojClr);

uchar compareVal(uchar center, uchar val);
void getLbpMat(const Mat& img, Mat &matLbp, int P, int R);
void lbpProjection(Mat roiImg, Mat img, Mat &backprojLbp, int P, int R, float hue_range[]);
void getLbpHist(Mat &matLbp, vector<int> &vHist, int nBins, int P);
void saveLBPFeatures(Mat &resizedAndCroppedImg, int P, int R, string outFile, int classLabel);

#endif
