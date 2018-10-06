#include "segmentator.hpp"

Flood::Flood(Mat input){
	setSource(input);
}

Flood::Flood(){
	
}

void Flood::setSource(Mat input){
	m_Source = input.clone();
	setMask();
}

void Flood::SetMask(){
	m_Mask = Mat::zeros(m_Source.size(), CV_8UC1);
}

int Flood::getNextPosition(Point pt, float threshold){
	// UP

	if(pt.y > 0)
	{
		Point up = Point(pt.x, pt.y-1);
		if(m_Mask.at<uchar>( up ) == 0)
		{
			Vec3b current = m_Source.at<Vec3b>(pt);
			Vec3b next_p  = m_Source.at<Vec3b>( up );
			if(checkDistance(current, next_p, threshold)){
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
			if(checkDistance(current, next_p, threshold)){
				return 1;
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
			if(checkDistance(current, next_p, threshold)){
				return 2;
			}
		}
	}

	// left down

	if(( pt.x > 0) && ( pt.y < m_Source.rows - 1 ))
	{
		Point left_down = Point(pt.x-1, pt.y);
		if(m_Mask.at<uchar>( left_down ) == 0)
		{
			Vec3b current = m_Source.at<Vec3b>(pt);
			Vec3b next_p  = m_Source.at<Vec3b>( left_down );
			if(checkDistance(current, next_p, threshold)){
				return 2;
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
			if(checkDistance(current, next_p, threshold)){
				return 3;
			}
		}
	}

	// down_right

	if(pt.y < m_Source.rows-1)
	{
		Point down_right = Point(pt.x, pt.y+1);
		if(m_Mask.at<uchar>( down_right ) == 0)
		{
			Vec3b current = m_Source.at<Vec3b>(pt);
			Vec3b next_p  = m_Source.at<Vec3b>( down_right );
			if(checkDistance(current, next_p, threshold)){
				return 3;
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
			if(checkDistance(current, next_p, threshold)){
				return 4;
			}
		}
	}
	return 0;
}

bool Flood::checkDistance(Vec3b current, Vec3b next, float thr){
	float DE = sqrt ( pow((current[0]-next[0]),2) +  pow((current[1]-next[1]),2) + pow((current[2]-next[2]),2) );
	if( DE <= thr){
		return true;
	}else{
		return false;
	}
}







