#ifndef IMAGE_HPP
#define IMAGE_HPP_DEFINED

  /* ALECSANDER PASQUALLI GESSER UFSC ARA
	TRABALHO 1 DE TOPICOS 3 - PROCESSAMENTO DE IMAGENS
	MAHALONOBIS, CUBE, SPHERES,*/

#include <iostream>
#include "stdlib.h"
#include"stdio.h"
#include "math.h"
#include<vector>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

// MOUSE EVENT VARIABLES //


class Image{
 public:
 	unsigned char* data;
 	int H,W, alpha;
 	char type[2];
 	Image();
 	Image(int H, int W, char* type, int value);

 	bool read(char* src);
 	void save(char* namefile);
 	Image clone();
 	Image zeros();
  	Vec3b at(Point2 a);
  	~Image();
 };




#endif