#include "segmentador.hpp"

int int main(int argc, char** argv) {
   if(argc != 3) return -1;
   Mat input;

   input = imread(argv[1]);

   Flood segmentado(input, argv[2]);
   Mat saida = segmentado.process();

   namedWindow("saida",2);
   imshow("saida", saida);

   waitKey(0);

   return 0;
}
