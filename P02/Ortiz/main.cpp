// Bibliotecas:
#include <fstream>
#include <iostream>
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
            throw("Cant_open_file");

        fclose(tempFile);
        remove("test.txt");

        // Leo cuantas cámaras tengo
        FlyCapture2::BusManager busMgr;
        unsigned int numCameras;
        error = busMgr.GetNumOfCameras(&numCameras);
        
        // Si no hay camaras conectadas lanzo una excepción
        if (error != FlyCapture2::PGRERROR_OK) 
            throw("Error leyendo la cámara");
        
        cout<<"Number of cameras detected: " << numCameras<<endl;

        // Enseño el frame de cada una de las cámaras
        for (unsigned int i = 0; i < numCameras; i++) {
            // Voy a subir esto pero no se si seguira funcionando:
            //FlyCapture2::PGRGuid guid;

            error = busMgr.GetCameraFromIndex(i, &guid);
            
            if (error != FlyCapture2::PGRERROR_OK)
                throw("Error leyendo la cámara");

            // Lanzo la cámara:    
            runSingleCamera(guid,i);
    }

    catch("Cant_open_file")
        printf("Failed to create file in current folder.  Please check permissions.\n");


    catch("Error leyendo la cámara")
        printError(error);

    // Compruebo si tengo los permisos para abrir ficheros:
    
    else {
        
        // Leo el número de cámaras que estan conectadas:
        // No es mejor hacer un try y un except
        else {
                        }
        }
    }
    return ret;
}
