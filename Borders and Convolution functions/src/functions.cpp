#pragma once
#include "functions.hpp"

Mat b, dst;
Mat colors(Size(500,768),CV_8UC3, Scalar(255,255,255));
int aux=0;
Vec3i buf;
vector<Vec3i> samples;
bool track = false;

static void onMouse( int event, int x, int y, int, void*){
    buf = dst.at<Vec3b>(Point(x,y));
    if(event == EVENT_LBUTTONDOWN){
      if(track){
        track = false;
      }else{
        track = true;
      }
    }
    if(event == EVENT_MOUSEMOVE  && track){
      cout<<"[ "<<buf[0]<<" , "<<buf[1]<<" , "<<buf[2]<<" ]"<<endl;
      Vec3i aux = dst.at<Vec3b>(Point(x,y));
      samples.push_back(aux);
      cout<<"mouse"<<endl;
    }
    cout<<samples.size();
    int key = waitKey(0);
    if(key == 13){
      return;
    }

}

// ONLY CLICK MOSUE EVENT
static void onMouseCLICK( int event, int x, int y, int, void*){
    buf = dst.at<Vec3b>(Point(x,y));
    if(event == EVENT_LBUTTONDOWN){
      cout<<buf[0]<<"||"<<buf[1]<<"|"<<buf[2]<<endl;
      Vec3i aux = dst.at<Vec3b>(Point(x,y));
      samples.push_back(aux);
      cout<<"mouse"<<endl;
    }
    int key = waitKey(0);
    if(key == 13){
      return;
    }
  }



void convolution(Image& src, Image& dst, char* namefile){

  int min[3] = {400,400,400};
  int max[3] = {0,0,0};
  dst = src.clone();
 

  FILE* fp = fopen(namefile, "r");
  int k_size, div=1;

  fscanf(fp, "%d",&div);
  fscanf(fp, "%d",&k_size);
  int** kernel;
  kernel = new int*[k_size];
  for(int i =0; i < k_size ; i++){
     kernel[i] = new int[k_size];
    for(int j = 0; j <k_size;j++){
      fscanf(fp, "%d", &kernel[i][j]);
    }
  }
  if(src.type[1] == '3'){
    cout<<"entrou conv p3"<<endl;
    for(int j= k_size/2; j < src.H-k_size/2 ; j++){
      for(int k = k_size/2 ; k < src.W-k_size/2 ;k++){
        int auxR=0;
        int auxG=0;
        int auxB=0;
        for(int z = 0 ; z < k_size ; z++){
          for(int u=0 ; u< k_size ; u++){
            int index = (j - k_size/2 + z)*src.W *3 + (k- k_size/2 + u)*3;
            // could work to also iterate throw the borders 
             if( (j - k_size/2 + z) >= 0  &&  (j - k_size/2 + z) <src.H  && (k- k_size/2 + u)>=0 && (k- k_size/2 + u) < src.W ){
                  auxR+= src.data[index] * kernel[z][u];
                  auxG+= src.data[index+1] * kernel[z][u];
                  auxB+= src.data[index+2] * kernel[z][u];
            }
          }
        }
        auxR =auxR/div;
        auxG =auxG/div;
        auxB =auxB/div;
        int index = (j )*src.W *3 + (k)*3;
        dst.data[index] = abs(auxR);
        dst.data[index+1] = abs(auxG);
        dst.data[index+2] = abs(auxB);
        


      }
    }
  }
  if(src.type[1]=='2'){
    for(int j= k_size/2; j < src.H-k_size/2 ; j++){
      for(int k = k_size/2 ; k < src.W-k_size/2 ;k++){
        int aux=0;
        for(int z = 0 ; z < k_size ; z++){
          for(int u=0 ; u< k_size ; u++){
            int index = (j - k_size/2 + z)*src.W  + (k- k_size/2 + u);
            // could work to also iterate throw the borders 
             if( (j - k_size/2 + z) >= 0  &&  (j - k_size/2 + z) <src.H  && (k- k_size/2 + u)>=0 && (k- k_size/2 + u) < src.W ){
                  aux= src.data[index] * kernel[z][u];
                  
            }
          }
        }

        aux =aux/div;
          
        int index = (j )*src.W + (k);
        dst.data[index] = abs(aux);
       
        


      }
    }

  }
  



  for(int i =0; i < k_size ; i++){
     free(kernel[i]);
  }
  free(kernel);

}



void kneighboor(Image& src, Image& dst, int r){
  FILE *fp;

  setMouseCallback( "Selection", onMouseCLICK, 0);

  dst = src.zeros();

  waitKey(0);
  for( int j = 0 ; j < src.H; j++){
    for( int i = 0 ; i < src.W ; i++){
      for(int k = 0 ; k < samples.size() ; k++){
        Vec3i sp = samples[k];
        int index = j*src.W*3 + i*3;
        if(pow((pow((src.data[index] - sp[2]),2) + pow((src.data[index+1] - sp[1]),2) + pow((src.data[index+2] - sp[0]),2)),0.5) < r ){
          dst.data[index] = 255;
          dst.data[index+1] = 255;
          dst.data[index+2] = 255;
        }
      }
    }
  }
}

// CONVERTING TO MAT OPENCV OBJECT  AND DISPLAYING IT//
void window_show(char* namewindow, Image& src, bool st){
  cout<<src.type<<endl;
  if(src.type[1] == '3'){
    dst = Mat( Size(src.W,src.H), CV_8UC3);
    for(int y = 0; y < src.H ; y++){
      for(int x = 0 ; x < src.W ; x++){
        int index = y*src.W*3 + x*3;
        dst.at<Vec3b>(Point(x,y)) = Vec3b(src.data[index+2], src.data[index+1], src.data[index]);
      }
    }
  }
  if(src.type[1] == '2'){
    dst = Mat( Size(src.W,src.H), CV_8UC1);
    for(int y = 0; y < src.H ; y++){
      for(int x = 0 ; x < src.W ; x++){
        int index = y*src.W + x;
        dst.at<uchar>(Point(x,y)) = src.data[index];
      }
    }
  }
  namedWindow(namewindow, WINDOW_NORMAL);
  imshow(namewindow, dst);
  if(st)
    waitKey(0);
}
// CUBE SEGMENTATION //
void cubo(Image& src, Image& dst, int thr){
  window_show("Selection", src, false);
  setMouseCallback( "Selection", onMouseCLICK, 0);

  waitKey(0);
  dst = src.clone();
  for( int j = 0 ; j < src.H; j++){
    for( int i = 0 ; i < src.W ; i++){
      for(int k=0 ;k < samples.size() ; k++){
        int index = j*src.W*3 + i*3;
        Vec3i pt = samples[k];
        if( (src.data[index] < (pt[2]+thr)) && (src.data[index] > (pt[2]-thr)) ){
          if( (src.data[index+1] < (pt[1]+thr)) && (src.data[index+1] > (pt[1]-thr)) ){
            if( (src.data[index+2] < (pt[0]+thr)) && (src.data[index+2] > (pt[0]-thr)) ){
              dst.data[index]   = 0;
              dst.data[index+1] = 0;
              dst.data[index+2] = 0;
            }
          }
        }
      }
    }
  }
}




void mahalanobisv2(Image &src, Image& dst,unsigned int W, unsigned int H)
{
    int index;
    double rgbM [3] = {0};
    int Size2;
    unsigned char *amostra_c;
    double sigma[3][3] = {0};
    double m[3] = {0};
    double temp[3] = {0};
    double dist = 0;

    setMouseCallback( "Selection", onMouse, 0);

    waitKey(0);

    unsigned char* data = new unsigned char[W*H*3];

    for(int i =0 ; i < W*H*3 ; i++){
      data[i] = src.data[i];
    }

    Size2 = samples.size();
    amostra_c = (unsigned char*) calloc(samples.size()*3, sizeof(unsigned int));

    for(int i=0; i<samples.size(); i++)
    {
      Vec3i sp = samples[i];
      amostra_c[3*i] = sp[2];
      amostra_c[3*i+1] = sp[1];
      amostra_c[3*i+2] = sp[0];
    }
    for(int i =0; i < Size2*3; i+=3)
    {

        rgbM[0] += amostra_c[i];
        rgbM[1] += amostra_c[i+1];
        rgbM[2] += amostra_c[i+2];
    }
    rgbM[0] = rgbM[0]/Size2;
    rgbM[1] = rgbM[1]/Size2;
    rgbM[2] = rgbM[2]/Size2;
    for(int i=0; i<Size2*3; i+=3)
    {
        sigma[0][0] += (amostra_c[i] - rgbM[0]) * (amostra_c[i] - rgbM[0]);
        sigma[1][1] += (amostra_c[i+1] - rgbM[1]) * (amostra_c[i+1] - rgbM[1]);
        sigma[2][2] += (amostra_c[i+2] - rgbM[2]) * (amostra_c[i+2] - rgbM[2]);
        sigma[0][1] += (amostra_c[i] - rgbM[0]) * (amostra_c[i+1] - rgbM[1]);
        sigma[0][2] += (amostra_c[i] - rgbM[0]) * (amostra_c[i+2] - rgbM[2]);
        sigma[1][2] += (amostra_c[i+1] - rgbM[1]) * (amostra_c[i+2] - rgbM[2]);
    }
    sigma[1][0] = sigma[0][1];
    sigma[2][1] = sigma[1][2];
    sigma[2][0] = sigma[0][2];

    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            sigma[i][j] = sigma[i][j]/(Size2-1);
        }
    }

    Mat cov(Size(3,3), CV_32FC1);

  for(int i =0 ; i < 3 ; i++){
    for( int j =0 ; j <3 ; j++){
        cov.at<float>(Point(i,j)) = sigma[i][j];
    }
  }

  Mat inversa = cov.inv();
  float minv[3][3];

  for(int i =0 ; i < 3 ; i++){
    for( int j =0 ; j <3 ; j++){
        minv[i][j] = inversa.at<float>(Point(i,j))  ;
    }
  }

    for(int h =0; h < H*W*3 ; h+=3)
    {
        m[0] = data[h] - rgbM[0];
        m[1] = data[h+1] - rgbM[1];
        m[2] = data[h+2] - rgbM[2];

        for(int i = 0; i<3; i++)
        {
            for(int j = 0; j<3; j++)
            {
                temp[i] += m[j] * minv[i][j];
            }
        }
    for(int l = 0; l<3; l++)
        {
            dist += temp[l] * m[l];

        }
        if((dist) < 10)
        {
            data[h] = 255;
            data[h+1] = 255;
            data[h+2] = 255;
        }else{
          data[h] = 0;
            data[h+1] = 0;
            data[h+2] = 0;

        }
        dist = 0;
        temp[0] = 0;
        temp[1] = 0;
        temp[2] = 0;
    }

    for(int i =0 ; i < W*H*3 ; i++){
      dst.data[i] = data[i];
    }
}

void sobel(Image& src, Image& dst){
  Image dx;
  Image dy;
  Image blur;

  dst = src.zeros();
  convolution(src,blur,"blur");
  convolution(blur, dx, "sobel_dx");
  convolution(blur, dy, "sobel_dy");

  if(blur.type[1] == '3'){
    for( int i = 0 ; i < src.H; i++){
      for( int j = 0 ;j < src.W ; j++){
          int index = i*src.W*3 + j*3;
          dst.data[index] = sqrt ( pow(dx.data[index],2) + pow(dy.data[index],2) );
          dst.data[index+1] = sqrt ( pow(dx.data[index+1],2) + pow(dy.data[index+1],2) );
          dst.data[index+2] = sqrt ( pow(dx.data[index+2],2) + pow(dy.data[index+2],2) );

      }
    }
  }
  if(blur.type[1] == '2'){
    for( int i = 0 ; i < src.H; i++){
      for( int j = 0 ;j < src.W ; j++){
          int index = i*src.W + j;
          dst.data[index] = sqrt ( pow(dx.data[index],2) + pow(dy.data[index],2) );
      }
    }
  }
}



void robinson(Image& src, Image& dst){
  Image dx;
  Image dy;
  Image dd;
  Image ddi;
  Image blur;

  dst = src.zeros();
  convolution(src,blur,"blur");
  convolution(blur, dx, "r_dx");
  convolution(blur, dy, "r_dy");
  convolution(blur, dd, "r_dd");
  convolution(blur, ddi, "r_ddi");

  if(blur.type[1] == '3'){
    for( int i = 0 ; i < src.H; i++){
      for( int j = 0 ;j < src.W ; j++){
          int index = i*src.W*3 + j*3;
          dst.data[index] =  0.5*sqrt ( pow(dx.data[index],2) +   pow(dy.data[index],2) +   pow(dd.data[index],2) +   pow(ddi.data[index],2)   );
          dst.data[index+1] =0.5*sqrt ( pow(dx.data[index+1],2) + pow(dy.data[index+1],2) + pow(dd.data[index+1],2) + pow(ddi.data[index+1],2) );
          dst.data[index+2] =0.5*sqrt ( pow(dx.data[index+2],2) + pow(dy.data[index+2],2) + pow(dd.data[index+2],2) + pow(ddi.data[index+2],2) );

      }
    }
  }
  if(blur.type[1] == '2'){
    for( int i = 0 ; i < src.H; i++){
      for( int j = 0 ;j < src.W ; j++){
          int index = i*src.W + j;
          dst.data[index] =  0.5*sqrt ( pow(dx.data[index],2) +   pow(dy.data[index],2) +   pow(dd.data[index],2) +   pow(ddi.data[index],2)   );
      }
    }
  }
}

void roberts(Image& src, Image& dst){
  Image dx = src.zeros();
  Image dy = src.zeros();
  Image dd = src.zeros();
  Image ddi= src.zeros();
  

  int a[2][2] = {{1,0},{0,-1}};
  int b[2][2] = {{1,0},{0,-1}};
  int c[2][2] = {{1,0},{0,-1}};
  int d[2][2] = {{1,0},{0,-1}};

  for(int i = 1 ; i < src.H ; i++){
    for(int j = 1 ; j < src.W; j++){
        int index = i*src.W*3 + j*3;
        dx.data[index] = src.data[(i-1)*src.W*3 + (j-1)*3]*a[0][0] +  src.data[(i-1)*src.W*3 + (j+1)*3]*a[0][1] +  src.data[(i+1)*src.W*3 + (j-1)*3]*a[1][0] +  src.data[(i+1)*src.W*3 + (j+1)*3]*a[1][1];
        dy.data[index] = src.data[(i-1)*src.W*3 + (j-1)*3]*b[0][0] +  src.data[(i-1)*src.W*3 + (j+1)*3]*b[0][1] +  src.data[(i+1)*src.W*3 + (j-1)*3]*b[1][0] +  src.data[(i+1)*src.W*3 + (j+1)*3]*b[1][1];
        dd.data[index] = src.data[(i-1)*src.W*3 + (j-1)*3]*c[0][0] +  src.data[(i-1)*src.W*3 + (j+1)*3]*c[0][1] +  src.data[(i+1)*src.W*3 + (j-1)*3]*c[1][0] +  src.data[(i+1)*src.W*3 + (j+1)*3]*c[1][1];
        ddi.data[index]= src.data[(i-1)*src.W*3 + (j-1)*3]*d[0][0] +  src.data[(i-1)*src.W*3 + (j+1)*3]*d[0][1] +  src.data[(i+1)*src.W*3 + (j-1)*3]*d[1][0] +  src.data[(i+1)*src.W*3 + (j+1)*3]*d[1][1];

        dx.data[index +1] = src.data[(i-1)*src.W*3 + (j-1)*3 +1]*a[0][0] +  src.data[(i-1)*src.W*3 + (j+1)*3 +1]*a[0][1] +  src.data[(i+1)*src.W*3 + (j-1)*3 +1]*a[1][0] +  src.data[(i+1)*src.W*3 + (j+1)*3 +1]*a[1][1];
        dy.data[index +1] = src.data[(i-1)*src.W*3 + (j-1)*3 +1]*b[0][0] +  src.data[(i-1)*src.W*3 + (j+1)*3 +1]*b[0][1] +  src.data[(i+1)*src.W*3 + (j-1)*3 +1]*b[1][0] +  src.data[(i+1)*src.W*3 + (j+1)*3 +1]*b[1][1];
        dd.data[index +1] = src.data[(i-1)*src.W*3 + (j-1)*3 +1]*c[0][0] +  src.data[(i-1)*src.W*3 + (j+1)*3 +1]*c[0][1] +  src.data[(i+1)*src.W*3 + (j-1)*3 +1]*c[1][0] +  src.data[(i+1)*src.W*3 + (j+1)*3 +1]*c[1][1];
        ddi.data[index+1] = src.data[(i-1)*src.W*3 + (j-1)*3 +1]*d[0][0] +  src.data[(i-1)*src.W*3 + (j+1)*3 +1]*d[0][1] +  src.data[(i+1)*src.W*3 + (j-1)*3 +1]*d[1][0] +  src.data[(i+1)*src.W*3 + (j+1)*3 +1]*d[1][1];

        dx.data[index +2] = src.data[(i-1)*src.W*3 + (j-1)*3 +2]*a[0][0] +  src.data[(i-1)*src.W*3 + (j+1)*3 +2]*a[0][1] +  src.data[(i+1)*src.W*3 + (j-1)*3 +2]*a[1][0] +  src.data[(i+1)*src.W*3 + (j+1)*3 +2]*a[1][1];
        dy.data[index +2] = src.data[(i-1)*src.W*3 + (j-1)*3 +2]*b[0][0] +  src.data[(i-1)*src.W*3 + (j+1)*3 +2]*b[0][1] +  src.data[(i+1)*src.W*3 + (j-1)*3 +2]*b[1][0] +  src.data[(i+1)*src.W*3 + (j+1)*3 +2]*b[1][1];
        dd.data[index +2] = src.data[(i-1)*src.W*3 + (j-1)*3 +2]*c[0][0] +  src.data[(i-1)*src.W*3 + (j+1)*3 +2]*c[0][1] +  src.data[(i+1)*src.W*3 + (j-1)*3 +2]*c[1][0] +  src.data[(i+1)*src.W*3 + (j+1)*3 +2]*c[1][1];
        ddi.data[index+2] = src.data[(i-1)*src.W*3 + (j-1)*3 +2]*d[0][0] +  src.data[(i-1)*src.W*3 + (j+1)*3 +2]*d[0][1] +  src.data[(i+1)*src.W*3 + (j-1)*3 +2]*d[1][0] +  src.data[(i+1)*src.W*3 + (j+1)*3 +2]*d[1][1];
 
        dst.data[ index ] = sqrt(pow(dx.data[ index ],2) + pow(dy.data[ index ],2) + pow(dd.data[ index ],2) + pow(ddi.data[ index ],2));  
        dst.data[index+1] = sqrt(pow(dx.data[index+1],2) + pow(dy.data[index+1],2) + pow(dd.data[index+1],2) + pow(ddi.data[index+1],2));  
        dst.data[index+2] = sqrt(pow(dx.data[index+2],2) + pow(dy.data[index+2],2) + pow(dd.data[index+2],2) + pow(ddi.data[index+2],2)); 
        cout<<dst.data[ index ]<<"||"<<dst.data[index+1]<<"||"<<dst.data[index+2]<<endl;
        
        


    }
  }





}


