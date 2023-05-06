#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;
namespace filesystem = std::filesystem;

void crearArchivos(int cantidadArchivos) {
    string directorio;
    string nombreArchivo;
    string rutaArchivo;

    for (int i = 1; i <= cantidadArchivos; i++) {
        // Este pedazo es para definir el directorio dependiendo si la cantidad de archivos es par o impar
        if (cantidadArchivos % 2 == 0) {
            directorio = "C:/Users/steven/Documents/par";
        } else {
            directorio = "C:/Users/steven/Desktop/impar";
        }

        // Este es para crear el directorio si no existe
        if (!filesystem::exists(directorio)) {
            filesystem::create_directories(directorio);
        }

        // Este es para definir el nombre y la ruta del archivo
        nombreArchivo = "file" + to_string(i) + ".txt";
        rutaArchivo = directorio + "/" + nombreArchivo;

        // este me sirve para crear el archivo si no existe
        if (!filesystem::exists(rutaArchivo)) {
            ofstream archivo(rutaArchivo);
            archivo.close();
        }

        // este es para poder abrir el archivo y agregar texto
        ofstream archivo(rutaArchivo, ios_base::app);
        for (int j = 1; j <= i; j++) {
            archivo << "Línea " << j << " del archivo " << nombreArchivo << endl;
        }
        archivo.close();
    }
}

int buscarArchivoMasGrande(string directorio) {
    int maxLineas = 0;
    string nombreArchivoMasGrande;

    for (const auto &archivo : filesystem::directory_iterator(directorio)) {
        if (filesystem::is_regular_file(archivo)) {
            ifstream archivoActual(archivo.path());
            int lineas = 0;
            string linea;
            while (getline(archivoActual, linea)) {
                lineas++;
            }
            if (lineas > maxLineas) {
                maxLineas = lineas;
                nombreArchivoMasGrande = archivo.path().filename().string();
            }
            archivoActual.close();
        }
    }

    cout << "\rEl archivo mas grande es " << nombreArchivoMasGrande << " con " << maxLineas << " lineas." << endl;
    return maxLineas;
}

int main() {
    int cantidadArchivos;
    cout << "Ingrese la cantidad de archivos a crear: ";
    cin >> cantidadArchivos;

    crearArchivos(cantidadArchivos);

    string directorioBusqueda;
    cout << "Ingrese el directorio en el que buscar el archivo mas grande: ";
    cin >> directorioBusqueda;

    buscarArchivoMasGrande(directorioBusqueda);

    return 0;
}
