#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H

#include "Image.hpp"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;




static void onMouse( int event, int x, int y, int, void*);
static void onMouseICK( int event, int x, int y, int, void*);
void mahalanobisv2(Image &src,Image& dst,unsigned int W, unsigned int H);
void threshold(Image& src, Image& out);
void window_show(char* namewindow, Image& src, bool st);
void kneighboor(Image& src, Image& dst, int r);
void cubo(Image& src, Image& dst, int thr);
void convolution(Image& src,Image& dst, char* filename);
void sobel(Image& src, Image& dst);
void robinson(Image& src, Image& dst);
void roberts(Image& src, Image& dst);






#endif //is