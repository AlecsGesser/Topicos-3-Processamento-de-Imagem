// ENGENHEIRO ALECSANDER PASQUALLI GESSER
// INSTITUIÇÃO: UNIVERSIDADE FEDERAL DE SANTA CATARINA - CAMPUS ARARANGUÁ
// TOPICOS ESPECIAS 3 - IMAGE PROCESSING - ANTÔNIO CARLOS SOBIERANSKI
// ALGORITMO PARA SEGMENTAÇÃO DE IMAGEM POR REGIÕES aka>> FLOOD SEGMENTATOR

#ifndef FLOOD_HPP
#define FLOOD_HPP
#include<iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

class Flood{
private:
	Mat m_source;
	Mat m_mask;
	vector<vector<Point> > mean;

public:
	Flood();
	void setSource(Mat input);
	void setMask();
	int getAvailableDirection();
	bool checkMask(Point pt);
	int getNextPosition();
	Mat getRegions();


};

#endif // FLOOD_HPP defined
