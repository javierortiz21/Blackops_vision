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

    // Connect to a camera
    error = cam.Connect(&guid);
    if (error != FlyCapture2::PGRERROR_OK) {
        printError(error);
        ret = -1;
    }
    else {
        // Get the camera information
        FlyCapture2::CameraInfo camInfo;
        error = cam.GetCameraInfo(&camInfo);
        if (error != FlyCapture2::PGRERROR_OK) {
            printError(error);
            ret = -1;
        }
        else {
            printCameraInfo(&camInfo);
            // Start capturing images
            error = cam.StartCapture();
            if (error != FlyCapture2::PGRERROR_OK) {
                printError(error);
                ret = -1;
            }
            else {
                //read frames from camera and wait for user commands
                ret = readFramesFromCamera(&cam, idxCam);
                // Stop capturing images
                error = cam.StopCapture();
                if (error != FlyCapture2::PGRERROR_OK) {
                    printError(error);
                    ret = -1;
                }
                else {
                    // Disconnect the camera
                    error = cam.Disconnect();
                    if (error != FlyCapture2::PGRERROR_OK) {
                        printError(error);
                        ret = -1;
                    }
                }
            }
        }
    }
    return ret;
}

int readFramesFromCamera(FlyCapture2::Camera *cam, int idxCam) {
    int ret = 0;
    FlyCapture2::Error error;
    FlyCapture2::Image rawImage;
    char key = 'V', nombreImagen[100], nombreVideo[100];
    FILE *pf_video = NULL;
    bool isRecording = false, fail = false;    
    char windName[50];
    sprintf(windName, "Camera_%02d", idxCam);
    
 

    // Retrieve an image to get image size and allocate IplImage
    error = cam->RetrieveBuffer(&rawImage);
    if (error != FlyCapture2::PGRERROR_OK) {
        printError(error);
        ret = -1;
    }
    else {

        while (key != 'Q' && !fail) {
            // Retrieve an image
            error = cam->RetrieveBuffer(&rawImage);
            if (error != FlyCapture2::PGRERROR_OK) {
                printError(error);
                ret = -1;
                fail = true;
            }
            else {
                // Create a converted image
                FlyCapture2::Image convertedImage;
                // Convert the raw image
                error = rawImage.Convert(FlyCapture2::PIXEL_FORMAT_MONO8, &convertedImage);
                if (error != FlyCapture2::PGRERROR_OK) {
                    printError(error);
                    ret = -1;
                    fail = true;
                }
                else {
                    //* TO DO...
                    //* 1. Convertir la imagen de opencv a 3 canales para poder pintar sobre ella en color
                    //* 2. Si se pulsa 'G' grabar en un archivo en formato RAW (con fwrite) dentro de la carpeta /dat/
                    //*    En este caso se dibujara un rectangulo de color rojo y la palabra REC 
                    //*    en la imagen visualizada, no en la imagen que se graba.
                    //* 3. Si se pulsa 'S' salvar una imagen en formato PNG
                    //* 4. Cada vez que se grabe un video o una imagen se debe incrementar el contador correspondiente
                    
		    				cv::Mat imgRead = cv::Mat(convertedImage.GetRows(),convertedImage.GetCols(),CV_8UC1,convertedImage.GetData());	
		    				cv::cvtColor(convertedImage, convertedImageColor, CV_GRAY2RGB);	    // gris a color
		    				
		    				char aux = cv::waitKey(33); 
		    				key = toupper(aux); 
		    				switch(key){ 
				 				case 'G': 
				 					if(isRecording)
				 						isRecording = false;
				 					else 
				 						isRecording = true;
				 					 
				 					break;
				 				case 'S': 
				 					sprintf (nombreImagen, "imagen%04d.png", globalIndexImages++);
							 		pf_video = fopen(nombreImagen, "w"); 
							 		
							 		// por cada frame
							 		fwrite(imgRead.data, imgRead.rows*imgRead.cols, sizeof (unsigned char), pf_video);
							 		
							 		fclose(pf_video); pf_video=NULL; // solo se hace una vez por video
				 					break;  
		    				}
		    				
		    			if(isRecording)
		    			{
				 			sprintf (nombreVideo, "video%04d.raw", globalIndexVideo++);
					 		pf_video = fopen(nombreVideo, "w"); // solo se hace una vez por video
					 		
					 		// por cada frame
					 		fwrite(imgRead.data, imgRead.rows*imgRead.cols, sizeof (unsigned char), pf_video);
					 		
					 		
					 		fclose(pf_video); pf_video=NULL; // solo se hace una vez por video
				 		}
				 			
				 						
                }
            }
        }
        if (pf_video != NULL)
            fclose(pf_video);
    }
    return ret;
}



