#pragma once
#include "Flood.hpp"


Flood::Flood(Mat input, int thr){
	setSource(input, thr);
}

Flood::Flood(){

}

void Flood::setSource(Mat input, int threshold){
	m_Source = input.clone();
	setMask();
	m_numberofRegions=0;
	m_thr = threshold;
	GaussianBlur(input,input,Size(3,3), 3,3);
	GaussianBlur(input,m_Source,Size(3,3), 3,3);
	Canny(input, m_canny, 40, 255, 3,3);
	namedWindow("canny",2);
	imshow("canny", m_canny);
	waitKey(0);


}

void Flood::setMask(){
	m_Mask = Mat::zeros(m_Source.size(), CV_32F);
}

void Flood::updateRef(Point pt){
	Vec3b temp = m_Source.at<Vec3b>(pt);
	m_Ref[0] = (m_Ref[0] + temp[0])/2;
	m_Ref[1] = (m_Ref[1] + temp[1])/2;
	m_Ref[2] = (m_Ref[2] + temp[2])/2; 
}

int Flood::getNextPosition(Point pt){
	// UP

	if(pt.y > 0)
	{
		Point up = Point(pt.x, pt.y-1);
		if(m_Mask.at<uchar>( up ) == 0)
		{
			Vec3b current = m_Source.at<Vec3b>(pt);
			Vec3b next_p  = m_Source.at<Vec3b>( up );
			if(checkDistance(current, next_p, pt)){
				return 1;
			}
		}
	}

	//left_up

	if(( pt.y > 0) && (pt.x> 0))
	{
		Point left_up = Point(pt.x-1, pt.y-1);
		if(m_Mask.at<uchar>( left_up ) == 0)
		{
			Vec3b current = m_Source.at<Vec3b>(pt);
			Vec3b next_p  = m_Source.at<Vec3b>( left_up );
			if(checkDistance(current, next_p, pt)){
				return 2;
			}
		}
	}

	// LEFT

	if(pt.x > 0)
	{
		Point left = Point(pt.x-1, pt.y);
		if(m_Mask.at<uchar>( left ) == 0)
		{
			Vec3b current = m_Source.at<Vec3b>(pt);
			Vec3b next_p  = m_Source.at<Vec3b>( left );
			if(checkDistance(current, next_p, pt)){
				return 3;
			}
		}
	}

	// left down

	if(( pt.x > 0) && ( pt.y < m_Source.rows - 1 ))
	{
		Point left_down = Point(pt.x-1, pt.y+1);
		if(m_Mask.at<uchar>( left_down ) == 0)
		{
			Vec3b current = m_Source.at<Vec3b>(pt);
			Vec3b next_p  = m_Source.at<Vec3b>( left_down );
			if(checkDistance(current, next_p, pt)){
				return 4;
			}
		}
	}


	// DOWN

	if(pt.y < m_Source.rows-1)
	{
		Point down = Point(pt.x, pt.y+1);
		if(m_Mask.at<uchar>( down ) == 0)
		{
			Vec3b current = m_Source.at<Vec3b>(pt);
			Vec3b next_p  = m_Source.at<Vec3b>( down );
			if(checkDistance(current, next_p, pt)){
				return 5;
			}
		}
	}

	// down_right

	if((pt.y < m_Source.rows-1) && (pt.x < m_Source.cols-1))
	{
		Point down_right = Point(pt.x+1, pt.y+1);
		if(m_Mask.at<uchar>( down_right ) == 0)
		{
			Vec3b current = m_Source.at<Vec3b>(pt);
			Vec3b next_p  = m_Source.at<Vec3b>( down_right );
			if(checkDistance(current, next_p, pt)){
				return 6;
			}
		}
	}

	//right

	if(pt.x < m_Source.cols-1)
	{
		Point right = Point(pt.x+1, pt.y);
		if(m_Mask.at<uchar>( right ) == 0)
		{
			Vec3b current = m_Source.at<Vec3b>(pt);
			Vec3b next_p  = m_Source.at<Vec3b>( right );
			if(checkDistance(current, next_p, pt)){
				return 7;
			}
		}
	}

	//right_up

	if((pt.x < m_Source.cols-1) && (pt.y>0))
	{
		Point right_up = Point(pt.x+1, pt.y);
		if(m_Mask.at<uchar>( right_up ) == 0)
		{
			Vec3b current = m_Source.at<Vec3b>(pt);
			Vec3b next_p  = m_Source.at<Vec3b>( right_up );
			if(checkDistance(current, next_p, pt)){
				return 8;
			}
		}
	}
	return 0;
}

int Flood::ExtractPartition(Point ponto,  float index){
	vector<Point> stack;
	stack.push_back(ponto);

	int indexToMark = index+50;
	int area =  1;

	m_Ref = m_Source.at<Vec3b>(ponto);
	m_numberofRegions++;
	updateRef(ponto);
	namedWindow("temp",2);
	namedWindow("travel",2);


	m_Mask.at<uchar>(Point(ponto.x , ponto.y)) = indexToMark;

	while(stack.size() > 0){
		int position = getNextPosition(ponto);
		
		Mat mpt = Mat::zeros(m_Source.size(), CV_8UC1);
		mpt.at<uchar>(ponto) = 255;

		// if(area > 4) {
			
		// 	imshow("travel", mpt);
		// 	imshow("temp", m_Mask);
		// 	waitKey(10);
		// }

		// if(position == 0) {
			
		// 	
		// }

	// if(ponto.x % 75 ==0 ) {
	// 	imshow("travel", mpt);
	// 	imshow("temp", m_Mask);
	// 	cout<<"parou"<<endl;
	// 	waitKey(2);
	// 	cout<<index<<endl;
	// }
		


		switch(position){
			case 1:
				m_Mask.at<float>(Point(ponto.x , ponto.y-1)) = indexToMark;
				area++;
				
				ponto.y--;
				updateRef(ponto);

				stack.push_back(ponto);
				break;
			case 2:
				m_Mask.at<float>(Point(ponto.x-1 , ponto.y-1)) = indexToMark;
				area++;
				ponto.y--;
				ponto.x--;
				updateRef(ponto);
				stack.push_back(ponto);
				break;
			case 3:
				m_Mask.at<float>(Point(ponto.x-1 , ponto.y)) = indexToMark;
				area++;
				ponto.x--;
				updateRef(ponto);
				stack.push_back(ponto);
				break;
			case 4:
				m_Mask.at<float>(Point(ponto.x-1 , ponto.y+1)) = indexToMark;
				area++;
				ponto.y++;
				ponto.x--;
				updateRef(ponto);
				stack.push_back(ponto);
				break;
			case 5:
				m_Mask.at<float>(Point(ponto.x , ponto.y+1)) = indexToMark;
				area++;
				ponto.y++;
				stack.push_back(ponto);
				break;
			case 6:
				m_Mask.at<float>(Point(ponto.x+1 , ponto.y+1)) = indexToMark;
				area++;
				ponto.y++;
				ponto.x++;
				updateRef(ponto);
				stack.push_back(ponto);
				break;
			case 7:
				m_Mask.at<float>(Point(ponto.x+1 , ponto.y)) = indexToMark;
				area++;
				ponto.x++;
				updateRef(ponto);
				stack.push_back(ponto);
				break;
			case 8:
				m_Mask.at<float>(Point(ponto.x+1 , ponto.y-1)) = indexToMark;
				area++;
				ponto.x++;
				ponto.y--;
				updateRef(ponto);
				stack.push_back(ponto);
				break;
			case 0:
				ponto = stack.at(stack.size()-1);
				stack.pop_back();
		}
	}

	return area;


}

bool Flood::checkDistance(Vec3b current, Vec3b next, Point pt){
	float DE = sqrt ( pow((current[0]-next[0]),2) +  pow((current[1] - next[1]),2) + pow((current[2] - next[2]),2) );
	if( (DE <= m_thr) && (m_canny.at<uchar>(pt) == 0)){
		return true;
	}else{
		return false;
	}
}

Mat Flood::getRegions(){
	vector<Vec3b> cores;
	Mat output = Mat::zeros(m_Source.size(), m_Source.type());
cout<<"regions entered"<<endl;
	for(int i = 0 ; i < m_numberofRegions +10; i++){
		cores.push_back(Vec3b(rand()%256,rand()%256,rand()%256));
	}
	for (size_t i = 0; i < m_Mask.rows; i++) {
		for (size_t j = 0; j < m_Mask.cols; j++) {
			if(m_Mask.at<uchar>(Point(j,i)) > 0 ){
				output.at<Vec3b>(Point(j,i)) = cores.at(m_Mask.at<uchar>(Point(j,i)));
			}else{
				output.at<Vec3b>(Point(j,i)) = Vec3b(0,0,255);
			}
		}
	}
	return output;
}

Mat Flood::process(){
	float k=0;
	for (size_t i = 0; i < m_Source.rows; i++) {
		for (size_t j = 0; j < m_Source.cols; j++) {
			if(checkMask(Point(j,i))){
				k+=0.5;
				int area = ExtractPartition(Point(j,i), k );
			//	cout<<"area "<<k<<" = "<<area<<endl;
			}

		}
		imshow("temp", m_Mask);
		//waitKey(0);
		cout<<i<<endl;
	}

	return getRegions();
}

bool Flood::checkMask(Point pt){
	if( m_Mask.at<uchar>(pt) > 0 ) return false;
	else return true;
}
