#include "Point.hpp"
#include "Image.hpp"

Mat b, dst;
Mat colors(Size(500,768),CV_8UC3, Scalar(255,255,255));
int aux=0;
Vec3i buf;
vector<Vec3i> samples;
bool track = false;

static void onMouse( int event, int x, int y, int, void*);
static void onMouseCLICK( int event, int x, int y, int, void*);

int main(int argc, char** argv){
	Image m, m2;
	int opt;


	cout<<"1 - mahala\n"<<
		  "2 - cubo\n"<<
		  "3 - spheres\n"<<
          "4 - convolution(kernel.txt)"<<endl;


	if ( m.read(argv[1]) == false)	return -1;

	m2 = m.clone();
	cout<<"Opção de segmentação: ";
	cin>>opt;

	window_show("Selection", m, false);

	switch(opt){
		case 1:
			cout<<"selecione os pontos- (click and drag then enter to continue)"<<endl;
			mahalanobisv2(m, m.W, m.H);
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
      		convolution(m,m2,5);
      		break;
		default:
			cout<<"selecione os pontos(click and drag then enter to continue)"<<endl;
			mahalanobisv2(m, m.W, m.H);
	}

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
      default:
      cout<<"q - quit\n"
          <<"s - save\n"
          <<"w - show window"<<endl;
      break;

    }
  }
  cout<<"closed"<<endl;
  return 0;
}

