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


 Image Image::zeros(){
 	Image out;
 	out.type[0] = this->type[0];
 	out.type[1] = this->type[1];
 	out.H = this->H;
 	out.W = this->W;
 	out.alpha = this->alpha;


 	if(this->type[0] == 'P'){
 		if(this->type[1] == '2'){
 			out.data = new unsigned char[out.H*out.W];
			for(int i =0; i < this->H*this->W ; i++){
				out.data[i] = 0;
			}
 		}
 		if(type[1] == '3'){
 			out.data = new unsigned char[out.H*out.W*3];
			for(int i =0; i < H*W*3 ; i++){
				out.data[i] = 0;
			}
 		}
 	}

 	return out;
}

Vec3b Image:: at(Point2 a){
  Vec3b out;
  if(type[1] == '3'){
    int index = a.y*W*3 + a.x*3;
    out[0] = data[index];
    out[1] = data[index+1];
    out[2] = data[index+2];

    return out;
  }else{
    int index = a.y*W + a.x;
    out[0] = data[index];
    return 0;

  }
}
Image::Image(int H, int W, char* type, int value){
	if(type[1] == '2'){
		data = new unsigned char[H*W];
		for(int i ; i < H*W ; i++){
			data[i] = value;
		}
	}
	if(type[1] == '3'){
		data = new unsigned char[H*W*3];
		for(int i ; i < H*W*3 ; i++){
			data[i] = value;
		}

	}
}
Image::Image(): data(NULL){

}
Image::~Image()
{
	if(data) free(this->data);
}


