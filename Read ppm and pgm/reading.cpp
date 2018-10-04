// ALECSANDER PASQUALLI GESSER
// UNIVERSIDADE FEDERAL DE SANTA CATARINA - CAMPUS ARARANGUA

#include <iostream>
#include "stdlib.h"
#include "math.h"
using namespace std;

 class Mat{
 public:
 	unsigned char* data;
 	int H,W, alpha;
 	char type[2];

 	void read(char* src);
 	void save(char* namefile);
 	int get(int x, int y);
 	void set(int x, int y);
 	Mat clone();


 };
  void threshold(Mat& src, Mat& output, int value);
  void negative(Mat& src, Mat& dst);
  void brilho(Mat& src, Mat& dst, int value);






 void Mat::read(char* src){
 	FILE* fp = fopen(src, "r");
 	if(!fp)
 		cout<<"no file"<<endl;;

 	fscanf(fp,"%c %c", &type[0], &type[1]);
 	fscanf(fp,"%d %d", &H, &W);
 	fscanf(fp,"%d", &alpha);



 	if(type[0] == 'P'){
 		if(type[1] == '2'){
			data = new unsigned char[H*W];
			for(int i =0; i < H*W ; i++){
				fscanf(fp,"%hhu", &data[i]);
			}
 		}
 		if(type[1] == '3'){
 			data = new unsigned char[H*W*3];
			for(int i =0; i < H*W*3 ; i++){
				fscanf(fp,"%hhu", &data[i]);
			}
 		}
 	}
 	fclose(fp);
 }

 void Mat::save(char* namefile){

 	remove(namefile);

 	FILE* fp = fopen(namefile, "w");
 	if(!fp)
 		cout<<"error"<<endl;;

 	fprintf(fp,"%c%c\n", type[0], type[1]);
 	fprintf(fp,"%d %d\n", H, W);
 	fprintf(fp,"%d\n", alpha);

 	if(type[0] == 'P'){
 		if(type[1] == '2'){
			for(int i =0; i < H*W ; i++){
				fprintf(fp,"%hhu\n", data[i]);
			}
 		}
 		if(type[1] == '3'){
			for(int i =0; i < H*W*3 ; i++){
				fprintf(fp,"%hhu\n", data[i]);
			}
 		}
 	}

 	fclose(fp);

 }

 Mat Mat::clone(){
 	Mat out;
 	out.type[0] = this->type[0];
 	out.type[1] = this->type[1];
 	out.H = this->H;
 	out.W = this->W;
 	out.alpha = this->alpha;


 	if(this->type[0] == 'P'){
 		if(this->type[1] == '2'){
 			out.data = new unsigned char[out.H*out.W];
			for(int i =0; i < this->H*this->W ; i++){
				out.data[i] = this->data[i];
			}
 		}
 		if(type[1] == '3'){
 			out.data = new unsigned char[out.H*out.W*3];
			for(int i =0; i < H*W*3 ; i++){
				out.data[i] = this->data[i];
			}
 		}
 	}

 	return out;
}

 int Mat::get(int x, int y){
 	int index = x*H + y ;

 	return data[index];

 }

 void Mat::set(int x, int y){
 	int index = x*H + y ;

 	data[index] =  data[index];

 }



int main(int argc, char** argv)
{
 	Mat m1,m2;
 	if(argc != 2){
 		cout<<"1 file only"<<endl;
 		return -1;
 	}

 	m1.read(argv[1]);

 	threshold(m1, m2, 50);

 	m2.save("m2");


 	m1.save("saida");



 	return 0;
 }

void threshold(Mat& src, Mat& output, int value)
{
	double r=200,g=200,b=100;
	output = src.clone();
	if(src.type[0] == 'P'){
 		if(src.type[1] == '2'){
			for(int i =0; i < src.H*src.W ; i++){
				if( src.data[i] < value){
					output.data[i] = 255;
				}else{
					output.data[i] = 0;
				}
			}
 		}
 		if(src.type[1] == '3'){
			for(int i =0; i < src.H*src.W*3 ; i=+3){
				double auxR, auxG, auxB;
				auxR = (src.data[i] - r);
				auxG = (src.data[i+1] - g);
				auxB = (src.data[i+2] - b);

				double d = pow(( pow(auxR,2) + pow(auxG,2) + pow(auxB,2)),0.5);


				if( src.data[i] < d){
					output.data[i] = 255;
				}else{
					output.data[i] = 0;
				}
			}
 		}
 	}
}

void negative(Mat& src, Mat& dst){
	dst = src.clone();
	if(src.type[0] == 'P'){
 		if(src.type[1] == '2'){
			for(int i =0; i < src.H*src.W ; i++){
					dst.data[i] =  255 - src.data[i];
			}
 		}
 		if(src.type[1] == '3'){
			for(int i =0; i < src.H*src.W*3 ; i+=3){
				dst.data[i] = 255 - src.data[i];
				dst.data[i+1] = 255 - src.data[i+1];
				dst.data[i+2] = 255 - src.data[i+2];
			}
 		}
 	}
}

void brilho(Mat& src, Mat& dst, int value){
	dst = src.clone();
	if(src.type[0] == 'P'){
 		if(src.type[1] == '2'){
			for(int i =0; i < src.H*src.W ; i++){
				double aux = src.data[i] + value;
				if(aux >= 255){
					dst.data[i] = 255;
				}else{
					dst.data[i] =  src.data[i] + value;
				}
			}
 		}
 		if(src.type[1] == '3'){
			for(int i =0; i < src.H*src.W*3 ; i++){
				double aux = src.data[i] + value;
				if(aux >= 255){
					dst.data[i] = 255;
				}else{
					dst.data[i] =  src.data[i] + value;
				}
			}
 		}
 	}
}
