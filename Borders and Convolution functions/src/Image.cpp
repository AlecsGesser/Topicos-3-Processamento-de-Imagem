
#include "Image.hpp"


bool Image::read(char* src){
 	FILE* fp = fopen(src, "r");
 	if(!fp){
 		cout<<"no file"<<endl;
 		return false;
 	}else{

	 	fscanf(fp,"%c %c", &type[0], &type[1]);
	 	fscanf(fp,"%d %d", &W, &H);
	 	fscanf(fp,"%d", &alpha);

	 	if(type[0] == 'P'){

	 		if(type[1] == '2'){
				data = new  int[H*W];
				for(int i =0; i < H*W ; i++){
					fscanf(fp,"%hhu", &data[i]);
				}
	 		}
	 		if(type[1] == '3'){
	 			data = new  int[H*W*3];
				for(int i =0; i < H*W*3 ; i++){
					fscanf(fp,"%hhu", &data[i]);
				}
	 		}
	 	}else{
	 		cout<<"no ppm ou pgm file"<<endl;
	 		fclose(fp);
	 		return false;
	 	}
	 	fclose(fp);
	 	return true;
	 }
 }

void Image::save(char* namefile){

 	remove(namefile);
 	if(data != NULL){
	 	FILE* fp = fopen(namefile, "w");
	 	if(!fp){
	 		cout<<"error"<<endl;
	 		fclose(fp);

	 	}else{

		 	fprintf(fp,"%c%c\n", type[0], type[1]);
		 	fprintf(fp,"%d %d\n", W, H);
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
		 	cout<<"save"<<endl;
		}
	 	fclose(fp);
	 }

 }

Image Image::clone(){
 	Image out;
 	out.type[0] = this->type[0];
 	out.type[1] = this->type[1];
 	out.H = this->H;
 	out.W = this->W;
 	out.alpha = this->alpha;


 	if(this->type[0] == 'P'){
 		if(this->type[1] == '2'){
 			out.data = new  int[out.H*out.W];
			for(int i =0; i < this->H*this->W ; i++){
				out.data[i] = this->data[i];
			}
 		}
 		if(type[1] == '3'){
 			out.data = new  int[out.H*out.W*3];
			for(int i =0; i < H*W*3 ; i++){
				out.data[i] = this->data[i];
			}
 		}
 	}

 	return out;
}


 Image Image::zeros(){
 	Image out;
 	out.type[0] = this->type[0];
 	out.type[1] = this->type[1];
 	out.H = this->H;
 	out.W = this->W;
 	out.alpha = this->alpha;


 	if(this->type[0] == 'P'){
 		if(this->type[1] == '2'){
 			out.data = new  int[out.H*out.W];
			for(int i =0; i < this->H*this->W ; i++){
				out.data[i] = 0;
			}
 		}
 		if(type[1] == '3'){
 			out.data = new  int[out.H*out.W*3];
			for(int i =0; i < H*W*3 ; i++){
				out.data[i] = 0;
			}
 		}
 	}

 	return out;
}

// Vec3b Image:: at(Point2m a){
//   Vec3b out;
//   if(type[1] == '3'){
//     int index = a.y*W*3 + a.x*3;
//     out[0] = data[index];
//     out[1] = data[index+1];
//     out[2] = data[index+2];

//     return out;
//   }else{
//     int index = a.y*W + a.x;
//     out[0] = data[index];
//     return 0;

//   }
// }


void  Image::cvtGray(Image& dst){
	

	if(dst.data) free(dst.data);

	if(this->type[1] == '3'){
		dst.type[0] = 'P';
		dst.type[1] = '2';
		dst.H = this->H;
		dst.W = this->W;
		dst.data = new int[W*H];
		for(int i =0 ; i < H ; i++ ){
			for(int j = 0 ; j < W ; j++){
				int indexC = i*W*3 + j*3;
				int indexG = i*W + j;
				dst.data[indexG] = 0.3*this->data[indexC] +0.59*this->data[indexC+1] +0.11*this->data[indexC+2];
			}
					cout<<"covnerteugrey"<<endl;

		}
	}
	

}

void  Image::cvtGray(){
	
	int* dataT;
	dataT = new int[H*W];

	if(this->data){
		
		if(this->type[1] == '3'){
			for(int i =0 ; i < H ; i++ ){
				for(int j = 0 ; j < W ; j++){
					int indexC = i*W*3 + j*3;
					int indexG = i*W + j;
					dataT[indexG] = (0.3*this->data[indexC] +0.59*this->data[indexC+1] +0.11*this->data[indexC+2]);
				}
			}
			// free(this->data);
			// this->data = new int[H*W]; 
			this->type[1] = '2';
			
			for(int i =0 ; i < H ; i++ ){
				for(int j = 0 ; j < W ; j++){
					int indexG = i*W + j;
					this->data[indexG] = dataT[indexG];
				}
			}
		}
		cout<<"covnerteu"<<endl;

	}
	

}

Image::Image(int H, int W, char* type, int value){
		this->H = H;
		this->W = W;
		this->type[0] = type[0];
		this->type[1] = type[1];
	if(type[1] == '2'){
		data = new int[H*W];
		for(int i ; i < H*W ; i++){
			data[i] = value;
		}
	}
	if(type[1] == '3'){
		data = new int[H*W*3];
		for(int i ; i < H*W*3 ; i++){
			data[i] = value;
		}

	}
}
Image::Image(): data(NULL){

}


Image::~Image()
{
	int a = 1010;
	//if(data) delete [] this->data;
}


