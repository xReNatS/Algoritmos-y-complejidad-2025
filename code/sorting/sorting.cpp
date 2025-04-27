#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
namespace fs = filesystem;


void realizarMediciones(){

}

void leerArchivos(){

    string carpeta = "/data/array_input"; // Carpeta donde está el archivo

    vector<int> datos; // Aquí guardamos los números originales

    // Recorrer los archivos
    for (const auto& entrada : fs::directory_iterator(carpeta)) {
        if (entrada.is_regular_file() && entrada.path().extension() == ".txt") {
            cout << "Leyendo archivo: " << entrada.path() << endl;

            ifstream archivo(entrada.path());
            if (archivo.is_open()) {
                string linea;
                while (getline(archivo, linea)) {
                    istringstream stream(linea);
                    int numero;
                    while (stream >> numero) {
                        datos.push_back(numero);
                    }
                }
                archivo.close();
            } else {
                cerr << "No se pudo abrir: " << entrada.path() << endl;
            }
            cout << "----------------------------" << endl;
        }


    }

}

void crearVector(){

}

void generarOutput(){

}

int main()
{
    cout << "hola" <<endl;

    return 0;
}
