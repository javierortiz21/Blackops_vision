#include <CaptureCode.h>
using namespace std;

int globalIndexImages = 0;
int globalIndexVideo = 0;

void printError(FlyCapture2::Error error) {
    error.PrintErrorTrace();
}

void printCameraInfo(FlyCapture2::CameraInfo* pCamInfo) {
    printf(
           "\n*** CAMERA INFORMATION ***\n"
           "Serial number - %u\n"
           "Camera model - %s\n"
           "Camera vendor - %s\n"
           "Sensor - %s\n"
           "Resolution - %s\n"
           "Firmware version - %s\n"
           "Firmware build time - %s\n\n",
           pCamInfo->serialNumber,
           pCamInfo->modelName,
           pCamInfo->vendorName,
           pCamInfo->sensorInfo,
           pCamInfo->sensorResolution,
           pCamInfo->firmwareVersion,
           pCamInfo->firmwareBuildTime);
}

int runSingleCamera(FlyCapture2::PGRGuid guid, int idxCam) {
    int ret = 0;
    FlyCapture2::Error error;
    FlyCapture2::Camera cam;
    FlyCapture2::CameraInfo camInfo;

    // Connect to a camera
    try
    {
        error = cam.Connect(&guid);
        if (error != FlyCapture2::PGRERROR_OK) 
            throw  string("Camera_error:: Error while connecting to a camera");
        // Get the camera information
        error = cam.GetCameraInfo(&camInfo);
        if (error != FlyCapture2::PGRERROR_OK) 
            throw  string("Camera_error:: Error while getting info of the cam");


        printCameraInfo(&camInfo);
        // Start capturing images
        error = cam.StartCapture();
        if (error != FlyCapture2::PGRERROR_OK) 
            throw  string("Camera_error:: Error while capturing");
            
        //read frames from camera and wait for user commands
        ret = readFramesFromCamera(&cam, idxCam);
        // Stop capturing images
        error = cam.StopCapture();
        if (error != FlyCapture2::PGRERROR_OK) 
            throw  string("Camera_error:: Error while stopt the record");
     
        // Disconnect the camera
        error = cam.Disconnect();
        if (error != FlyCapture2::PGRERROR_OK) 
            throw  string("Camera_error:: Error while disconecting the record");           
    }
    return ret;
}



int readFramesFromCamera(FlyCapture2::Camera *cam, int idxCam) {
    int ret = 0;
    FlyCapture2::Error error;
    FlyCapture2::Image rawImage;
    FlyCapture2::Image convertedImage;

    char key = 'V', nombreImagen[100], nombreVideo[100];
    FILE *pf_video = NULL;
    bool isRecording = false, fail = false;    
    char windName[50];
    sprintf(windName, "Camera_%02d", idxCam);
    
 

    // Retrieve an image to get image size and allocate IplImage
    error = cam->RetrieveBuffer(&rawImage);
    if (error != FlyCapture2::PGRERROR_OK) 
        throw  string("Camera_error:: Error while retrieve an image");           

    while (key != 'Q') {
        // Retrieve an image
        error = cam->RetrieveBuffer(&rawImage);
        if (error != FlyCapture2::PGRERROR_OK) 
            throw  string("Camera_error:: Error while retrieve an image");           
    
        
        // Convert the raw image
        error = rawImage.Convert(FlyCapture2::PIXEL_FORMAT_MONO8, &convertedImage);
        if (error != FlyCapture2::PGRERROR_OK) 
            throw  string("Camera_error:: Error in image conversion");           

        cv::Mat imgRead = cv::Mat(convertedImage.GetRows(),convertedImage.GetCols(),CV_8UC1,convertedImage.GetData());	
        cv::cvtColor(convertedImage, convertedImageColor, CV_GRAY2RGB);	    // gris a color
        
        char aux = cv::waitKey(33); 
        key = toupper(aux); 
        switch(key)
        { 
            
            // Hacemos toggle a la grabación
            case 'G': 
                    // Hay que poner el cuadrito naranja
                    isRecording != isRecording;
                    break;

            // Hacemos una foto
            case 'S': 
                sprintf (nombreImagen, "imagen%04d.png", globalIndexImages++);
                pf_video = fopen(nombreImagen, "w"); 
                fwrite(imgRead.data, imgRead.rows*imgRead.cols, sizeof (unsigned char), pf_video);
                fclose(pf_video); 
                pf_video=NULL;
                break;  
        }
            
        // Se guarda el frame en un fichero:
        if(isRecording)
        {
            sprintf (nombreVideo, "video%04d.raw", globalIndexVideo++);
            pf_video = fopen(nombreVideo, "w");             
            fwrite(imgRead.data, imgRead.rows*imgRead.cols, sizeof (unsigned char), pf_video);
            fclose(pf_video); 
            pf_video=NULL; 
        }
                
				 						
            
        if (pf_video != NULL)
            fclose(pf_video);
    }
    return ret;
}



