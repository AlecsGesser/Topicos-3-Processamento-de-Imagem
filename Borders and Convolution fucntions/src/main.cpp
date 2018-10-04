#include "Image.hpp"
#include "functions.hpp"



int main(int argc, char** argv){
	Image m, m2;
	int opt;
  char namefileblur[20];


	cout<<"1 - mahala\n"<<
		  "2 - cubo\n"<<
		  "3 - spheres\n"<<
      "4 - convolution(kernel.txt)\n"<<
      "5 - Sobel(bordas)\n"<<
      "6 - Roberts\n"<<
      "7 - Robinson(bordas)"<<endl;


	if ( m.read(argv[1]) == false)	return -1;

	m2 = m.clone();
	cout<<"Opção de segmentação: ";
	cin>>opt;

	window_show("Selection", m, false);

	switch(opt){
		case 1:
			cout<<"selecione os pontos- (click and drag then enter to continue)"<<endl;
			mahalanobisv2(m, m2,m.W, m.H);
			break;
		case 2:
			cout<<"selecione os pontos(click + enter to continue)"<<endl;
			cubo(m,m2,55);
			break;
		case 3:
			cout<<"selecione os pontos(click + enter to continue)"<<endl;
			kneighboor(m,m2,40);
			break;
    	case 4:
      		cout<<"enter filename: ";
		    cin>>namefileblur;
		    convolution(m,m2, namefileblur);
      		break;
    	case 5:
      		sobel(m,m2);
      		break;
      	case 6:
      		roberts(m,m2);
      		break;
    	case 7:
   		    robinson(m,m2);
      		break;
		default:
			cout<<"selecione os pontos(click and drag then enter to continue)"<<endl;
			mahalanobisv2(m, m2,m.W, m.H);
	}

   cout<<"q - quit\n"
          <<"s - save\n"
          <<"w - show window\n"
          <<"c - covnerte Gray\n"<<endl;

  while(true){
    char key = waitKey(0);

    switch (key){
      case 'q':
        return -1;
      break;
      case 's':
        char buf[30];
        strcpy(buf,argv[1]);
        strcat(buf,"out");
        m2.save(buf);
        break;
      case 'w':
    	  window_show("Out", m2, false);
    	  window_show("Out2", m, true);
        break;
      case 'c':
        m2.cvtGray();

        break;
      default:
      cout<<"q - quit\n"
          <<"s - save\n"
          <<"w - show window\n"
          <<"c - covnerte Gray\n"<<endl;
      break;

    }
  }
  cout<<"closed"<<endl;
  return 0;
}

