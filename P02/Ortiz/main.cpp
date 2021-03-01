// Bibliotecas:
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    int ret = 0;
    FlyCapture2::Error error;
    FlyCapture2::PGRGuid guid;

    // Encapsulo los errores con try y catch:
    try
    {
        // Compruebo los permisos:
        FILE* tempFile = fopen("test.txt", "w+");
        if (tempFile == NULL) 
            throw string("Check_permissions :: Failed to create file");

        fclose(tempFile);
        remove("test.txt");

        // Leo cuantas cámaras tengo
        FlyCapture2::BusManager busMgr;
        unsigned int numCameras;
        error = busMgr.GetNumOfCameras(&numCameras);
        
        // Si no hay camaras conectadas lanzo una excepción
        if (error != FlyCapture2::PGRERROR_OK) 
            throw string("Camera_error:: Not devices conected");
        
        cout<<"Number of cameras detected: " << numCameras<<endl;

        
        // Enseño el frame de cada una de las cámaras
        for (unsigned int i = 0; i < numCameras; i++) {
            // Voy a subir esto pero no se si seguira funcionando:
            //FlyCapture2::PGRGuid guid;

            error = busMgr.GetCameraFromIndex(i, &guid);
            
            if (error != FlyCapture2::PGRERROR_OK)
                throw string("Camera_error:: Error in get camera index");

            // Lanzo la cámara:    
            runSingleCamera(guid,i);
        }   

    }
    catch (string e)
    {
        cout << e << endl;
    }


    return 0;
}
