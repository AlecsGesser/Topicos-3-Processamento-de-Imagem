#include <iostream>
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
 	~Mat();

 }; 
  void threshold(Mat& src, Mat& output, int value);

 Mat::~Mat(){
	delete[] this->data;
}

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
			for(int i =0; i < H*W*3 ; i+=3){
				out.data[i] = this->data[i];
				out.data[i+1] = this->data[i+1];
				out.data[i+2] = this->data[i+2];
			}			
 		}
 	}

 	return out;
 	free(out.data);
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
 	Mat m1, m2;
 	//if(!argv[1]) return -1;

 	m1.read(argv[1]);

 	m2 = m1.clone();

	m2.save("vivi.pgm");
 
 	m1.save("saida.pgm");

 	return 0;
 }

void threshold(Mat& src, Mat& output, int value)
{
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
			for(int i =0; i < src.H*src.W*3 ; i+=3){
				output.data[i] = src.data[i];
				output.data[i+1] = src.data[i+1];
				output.data[i+2] = src.data[i+2];
			}			
 		}
 	}



}
