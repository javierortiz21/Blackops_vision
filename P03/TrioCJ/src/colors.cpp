#include <cstdlib>
#include <colors.h>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

int cvt_Bayer_RGB(cv::Mat imgBayer, cv::Mat *imgRGB) {
  cv::Mat canales[3];
  //convertir a RGB y mostrar resultado
  // A lo mejor hay que usar una variable auxiliar
  cv::cvtColor(imagBayer, *imgRGB, cv::COLOR_BayerGR2RGB)
  cv::imshow("RGB",imgRGB);
  //separar los canales con split y mostrarlos por separado
  // ..
  cv::split(imgColor, canales);
  cv::imshow("B", canales[0]);
  cv::imshow("G", canales[1]);
  cv::imshow("R", canales[2]);
  // asignar la imagen RGB al segundo parametro de entrada
  
  return 0;
}


int cvt_Bayer_HSV(cv::Mat imgBayer, cv::Mat *imgHSV) {
  //convertir a HSV y mostrar resultado
  // ..
  
  //separar los canales con split y mostrarlos por separado
  // ..

  // asignar la imagen HSV al segundo parametro de entrada

  return 0;
}

// OPCIONAL
// int cvt_Bayer_XYZ (cv::Mat imgBayer, cv::Mat *imgXYZ)
// int cvt_Bayer_Lab (cv::Mat imgBayer, cv::Mat *imgLAB)
// int cvt_Bayer_Luv (cv::Mat imgBayer, cv::Mat *imgLUV)
// int cvt_Bayer_YCrCb (cv::Mat imgBayer, cv::Mat *imgYCrCb)


