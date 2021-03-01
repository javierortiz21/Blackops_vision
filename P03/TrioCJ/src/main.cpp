#include <cstdlib>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <colors.h>

using namespace std;

int main(int argc, char** argv) {
    int ret = 0;
    FILE *pf_video = NULL;
    int numCols = 640, numRows = 480;
    char key = '1';

    try
    {
        if (argc != 4) 
            throw string("Bad CLI arguments :: Ejemplo: ./lee video.raw 640 480");
        
        pf_video = fopen(argv[1], "r");
        if (pf_video == NULL) 
            throw string("Error in path or file:: Can't find the file in the path");

        numCols = atoi(argv[2]);
        numRows = atoi(argv[3]);
        cv::Mat imageVideo = cv::Mat(numRows, numCols, CV_8UC1);
        cv::Mat aux_image  = cv::Mat(numRows, numCols, CV_8UC1);

        // Fread almacena la imagen en imageVideo
        while ((fread(imageVideo.data, sizeof (unsigned char), numRows * numCols, pf_video)) > 0 
                && 
                key != 'Q') 
        {
            switch (key) {
                case '1': 
                    // mostrar imagen Bayer y grabar en "./dat/BAYER.png"
                    cv::imshow("Imagen original",imageVideo);
                    cv::imwrite("./dat/BAYER.png",imageVideo);

                    break;
                case '2':
                    // llamar a la funcion de conversion Bayer a RGB y guardar resultado en "./dat/RGB.png"
                    cvt_Bayer_RGB(imgVideo, *aux_image);
                    
                    break;
                case '3':                        
                    // llamar a la funcion de conversion Bayer a HSV y guardar resultado en "./dat/HSV.png"
                    cvt_Bayer_HSV(cv::Mat imgBayer, cv::Mat *imgHSV);
                    break;
                case '4': // opcional
                    // llamar a la funcion de conversion Bayer a XYZ y guardar resultado en "./dat/XYZ.png"
                    break;
                case '5': // opcional
                    // llamar a la funcion de conversion Bayer a LAB y guardar resultado en "./dat/LAB.png"
                    break;
                case '6': // opcional            
                    // llamar a la funcion de conversion Bayer a LUV y guardar resultado en "./dat/LUV.png"
                    break;
                case '7': // opcional
                    // llamar a la funcion de conversion Bayer a YCrCb y guardar resultado en "./dat/TCrCb.png"
                    break;
            }
            char aux = cv::waitKey(0);
            key = toupper(aux);
        }
        fclose(pf_video);


    }
    
    catch (string e)
    {
        cout << e << endl;
    }
    
     
    return 0;
}
