
#include "Flood.hpp"

int main(int argc, char** argv) {
   if(argc != 3) return -1;
   Mat input;

   input = imread(argv[1]);
   //cvtColor(input, input, CV_BGR2HSV);

   Flood segmentado(input, atoi(argv[2]));
   Mat saida = segmentado.process();

   namedWindow("saida",2);
   namedWindow("entrada",2);
   imshow("saida", saida);
   imshow("entrada", input);

   waitKey(0);

   return 0;
}
