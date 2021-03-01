#include <CaptureCode.h>
using namespace std;

int main(int argc, char** argv) {
    int ret = 0;
    FlyCapture2::Error error;

    // Since this application saves images in the current folder
    // we must ensure that we have permission to write to this folder.
    // If we do not have permission, fail right away.
    FILE* tempFile = fopen("test.txt", "w+");
    if (tempFile == NULL) {
        printf("Failed to create file in current folder.  Please check permissions.\n");
        ret = -1;
    }
    else {
        fclose(tempFile);
        remove("test.txt");

        //get the number of connected cameras
        FlyCapture2::BusManager busMgr;
        unsigned int numCameras;
        error = busMgr.GetNumOfCameras(&numCameras);
        if (error != FlyCapture2::PGRERROR_OK) {
     
            printError(error);
            ret = -1;
        }
        else {
            printf("Number of cameras detected: %u\n", numCameras);

            //for each connected camera, show current frame
            for (unsigned int i = 0; i < numCameras; i++) {
                FlyCapture2::PGRGuid guid;
                error = busMgr.GetCameraFromIndex(i, &guid);
                if (error != FlyCapture2::PGRERROR_OK) {
                    printError(error);
                    ret = -1;
                }
                runSingleCamera(guid,i);
            }
        }
    }
    return ret;
}
