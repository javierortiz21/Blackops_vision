#include <cstdlib>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

int main(int argc, char** argv) {
    int ret = 0;
    FILE *pf_video = NULL;
    int numCols = 640, numRows = 480;
    char key = 'W';

    if (argc != 4) {
        printf("\n Introduzca el nombre del video, y el tamaño (ancho y alto)\n");
        printf("\n      Ejemplo: ./lee video.raw 640 480\n");
        ret = -1;
    } else {

        pf_video = fopen(argv[1], "r");
        if (pf_video == NULL) {
            printf("Error al leer el video: %s\nCompruebe el nombre del fichero y su ruta\n", argv[1]);
            ret = -1;
        } else {
            numCols = atoi(argv[2]);
            numRows = atoi(argv[3]);            
            cv::Mat imageVideo = cv::Mat(numRows,numCols,CV_8UC1);

            while ((fread(imageVideo.data, sizeof (unsigned char), numRows * numCols, pf_video)) > 0 && key != 'Q') {
	      
                cv::imshow(string(argv[1]), imageVideo);
		
                char aux = cv::waitKey(33);
                key = toupper(aux);
                switch(key) {
                	case 'P':
                	cv::waitKey(0);
                	break;
                }
            }

            fclose(pf_video);
        }
    }
    return ret;
}
