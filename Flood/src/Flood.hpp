// ENGENHEIRO ALECSANDER PASQUALLI GESSER
// INSTITUIÇÃO: UNIVERSIDADE FEDERAL DE SANTA CATARINA - CAMPUS ARARANGUÁ
// TOPICOS ESPECIAS 3 - IMAGE PROCESSING - ANTÔNIO CARLOS SOBIERANSKI
// ALGORITMO PARA SEGMENTAÇÃO DE IMAGEM POR REGIÕES aka>> FLOOD SEGMENTATOR
#pragma once
#ifndef FLOOD_HPP
#define FLOOD_HPP
#include<iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>

using namespace std;
using namespace cv;

class Flood{
private:
	Mat m_Source;
	Mat m_Mask;
	vector<vector<Point> > mean;
	int m_numberofRegions;
	int m_thr;

public:
	Flood();
	Flood(Mat input, int thr);
	void setSource(Mat input, int threshold);
	void setMask();
	int getNextPosition(Point pt);
	int ExtractPartition(Point ponto, unsigned int index);
	bool checkDistance(Vec3b current, Vec3b next);
	Mat getRegions();
	Mat process();
	bool checkMask(Point pt);
};

#endif // FLOOD_HPP defined
