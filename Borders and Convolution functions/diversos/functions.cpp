#include "functions.hpp"


void convolution(Image& src, Image& dst, int iterations){
  char namefile[20];
  dst = src.clone();
  cout<<"enter the file name"<<endl;
  cin>>namefile;

  FILE* fp = fopen(namefile, "r");
  int k_size;
  fscanf(fp, "%d",&k_size);
  int kernel** = new int*[k_size];

  for(int i =0; i < k_size ; i++){
    for(int j = 0; j <k_size;j++){
      kernel[i] = new int[k_size];
      fscanf(fp, "%d", &kernel[i][j]);
    }
  }
  for(int i=0 ; i < iterations ; i++){
    for(int j= 0; j < src.H ; j++){
      for(int k = 0 ; k < src.W ;k++){
        int auxR=0;
        int auxG=0;
        int auxB=0;
        int div = 0;
        for(int z = 0 ; z < k_size ; z++){
          for(int u=0 ; u< k_size ; u++){
            int index = (j - k_size/2 + z)*src.W *3 + (k- k_size/2 + u)*3;
             if( (j - k_size/2 + z) >= 0  &&  (j - k_size/2 + z) <src.H  && (k- k_size/2 + u)>=0 && (k- k_size/2 + u) < src.W ){
                  auxR+= src.data[index] * kernel[z][u];
                  auxG+= src.data[index+1] * kernel[z][u];
                  auxB+= src.data[index+2] * kernel[z][u];
                  div+=kernel[z][u];
            }
          }
        }
        if(div == 0) div =1;
        if(auxR >= 255)
          auxR =auxR/div;
          auxG =auxG/div;
          auxB =auxB/div;
        int index = (j )*src.W *3 + (k)*3;
        dst.data[index] = auxR;
        dst.data[index+1] = auxG;
        dst.data[index+2] = auxB;

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
  dst = Mat( Size(src.W,src.H), CV_8UC3);
  for(int y = 0; y < src.H ; y++){
    for(int x = 0 ; x < src.W ; x++){
      int index = y*src.W*3 + x*3;
      dst.at<Vec3b>(Point(x,y)) = Vec3b(src.data[index+2], src.data[index+1], src.data[index]);
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




void mahalanobisv2(Image &src, unsigned int W, unsigned int H)
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
      src.data[i] = data[i];
    }
}
