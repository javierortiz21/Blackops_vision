#ifndef _CAPTURE_CODE_H_
#define _CAPTURE_CODE_H_

#include <FlyCapture2.h>
#include <cstdlib>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

//using namespace FlyCapture2;

typedef union _AbsValueConversion {
    unsigned int ulValue;
    float fValue;
} AbsValueConversion_t;

void printError(FlyCapture2::Error /* error */);
void printCameraInfo(FlyCapture2::CameraInfo* pCamInfo);
int readFramesFromCamera(FlyCapture2::Camera *cam, int idxCam);
int runSingleCamera(FlyCapture2::PGRGuid guid, int idxCam);


#endif /* _CAPTURE_CODE_H_ */
