#ifndef _COLORS_H_
#define _COLORS_H_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int cvt_Bayer_RGB (cv::Mat imgBayer, cv::Mat *imgRGB);
int cvt_Bayer_HSV (cv::Mat imgBayer, cv::Mat *imgHSV);
// opcional
//int cvt_Bayer_XYZ (cv::Mat imgBayer, cv::Mat *imgXYZ);
//int cvt_Bayer_Lab (cv::Mat imgBayer, cv::Mat *imgLAB);
//int cvt_Bayer_Luv (cv::Mat imgBayer, cv::Mat *imgLUV);
//int cvt_Bayer_YCrCb (cv::Mat imgBayer, cv::Mat *imgYCrCb);



#endif /* _COLORS_H_ */
