
#include "Flood.hpp"

int main(int argc, char** argv) {
   if(argc != 3) return -1;
   Mat input;

   input = imread(argv[1]);

   Flood segmentado(input, atoi(argv[2]));
   Mat saida = segmentado.process();

   namedWindow("saida",2);
   imshow("saida", saida);

   waitKey(0);

   return 0;
}
