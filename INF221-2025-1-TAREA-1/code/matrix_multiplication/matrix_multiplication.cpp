#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <algorithm>
#include <windows.h>
#include <psapi.h>
#include "algorithms/matrix.hpp"
#include "algorithms/naive.hpp"
#include "algorithms/strassen.hpp"

using namespace std;
namespace fs = filesystem;


/**
 * @brief Obtiene la cantidad de memoria física utilizada actualmente por el proceso.
 *
 * Utiliza funciones del sistema operativo para consultar el uso de memoria (Working Set) del proceso actual.
 *
 * @return La cantidad de memoria utilizada en bytes.
 */
size_t obtenerMemoriaActual() {
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    return pmc.WorkingSetSize; // memoria física utilizada
}


/**
 * @brief Genera un archivo de texto a partir de una matriz.
 *
 * Escribe el contenido de la matriz resultado.
 *
 * @param matriz La matriz que se desea guardar.
 * @param ruta Ruta donde se guardará el archivo generado.
 * @return void
 */
void generarOutput (const Matrix& matriz, const string& ruta) {
    ofstream file(ruta);
    
    if (!file.is_open()) {
        cerr << "Error abriendo archivo para escritura: " << ruta << endl;
        return;
    }
    
    for (const auto& fila : matriz) {
        for (size_t i = 0; i < fila.size(); ++i) {
            file << fila[i];
            if (i != fila.size() - 1) {
                file << " ";
            }
        }
        file << "\n";
    }
    
    file.close();
}


/**
 * @brief Divide una cadena en partes usando un delimitador.
 *
 * Procesa una cadena de caracteres y la divide en varios tokens según el delimitador especificado.
 *
 * @param s Cadena de caracteres a dividir.
 * @param delimiter Caracter utilizado como delimitador.
 * @return Un vector de strings que contiene los fragmentos resultantes.
 */
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}


/**
 * @brief Extrae información codificada en el nombre de un archivo.
 *
 * Interpreta el nombre del archivo para extraer parámetros como n, t, d y m, eliminando primero la extensión si existe.
 *
 * @param nombreArchivo Nombre del archivo del cual extraer la información.
 * @param n Variable donde se almacenará el valor numérico extraído.
 * @param t Variable donde se almacenará el tipo extraído.
 * @param d Variable donde se almacenará la distribución extraída.
 * @param m Variable donde se almacenará el método extraído.
 * @return void
 */
void extraerDatosArchivo(const string& nombreArchivo, int& n, string& t, string& d, string& m) {
  
    string nombre = nombreArchivo;

    if (nombre.size() > 4 && nombre.substr(nombre.size() - 4) == ".txt") {
        nombre = nombre.substr(0, nombre.size() - 4);
    }

    // Separar por '_'
    vector<string> partes = split(nombre, '_');

    if (partes.size() == 5) {
        n = stoi(partes[0]);
        t = partes[1];
        d = partes[2];
        m = partes[3];
    } else {
        cerr << "Error: nombre de archivo no tiene el formato esperado." << endl;
    }
}


/**
 * @brief Registra los resultados de mediciones en un archivo CSV.
 *
 * Escribe los resultados de tiempo de ejecución y uso de memoria para un algoritmo dado en un archivo CSV.
 *
 * @param archivoCSV Ruta al archivo CSV donde se almacenarán los resultados.
 * @param n Número de elementos o tamaño de entrada.
 * @param t Tipo de dato o característica asociada.
 * @param d Distribución de datos.
 * @param m Método o técnica utilizada.
 * @param algoritmo Nombre del algoritmo evaluado.
 * @param tiempoMicrosegundos Tiempo de ejecución en microsegundos.
 * @param memoriaKB Memoria utilizada en kilobytes.
 * @return void
 */
void registrarResultadosCSV(const string& archivoCSV,
                           int n, const string& t, const string& d, const string& m,
                           const string& algoritmo, long tiempoMicrosegundos, long memoriaKB) {
    ofstream archivo(archivoCSV, ios::app); // Abrir en modo append
    if (archivo.is_open()) {
        archivo << n << "," << t << "," << d << "," << m << ","
                << algoritmo << "," << tiempoMicrosegundos << "," << memoriaKB << "\n";
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo CSV para escribir." << endl;
    }
}


/**
 * @brief Realiza mediciones de rendimiento sobre multiplicación de matrices.
 *
 * Mide y compara la memoria usada y el tiempo de ejecución de los algoritmos de multiplicación de matrices Naive y Strassen, genera el archivo de resultados, y guarda las mediciones en un CSV.
 *
 * @param matriz1 Primera matriz de entrada.
 * @param matriz2 Segunda matriz de entrada.
 * @param nombreArchivo Nombre del archivo relacionado para generar outputs y registros.
 * @return void
 */
void realizarMediciones(Matrix& matriz1, Matrix& matriz2, const string& nombreArchivo) {
    using namespace std::chrono;

    // --- Medir Naive ---
    auto copiaNaiveMatriz1 = matriz1;
    auto copiaNaiveMatriz2 = matriz2;
    size_t memoriaAntes = obtenerMemoriaActual();
    auto inicio = high_resolution_clock::now();
    Matrix matrizResultadoNaive = naiveMultiply(copiaNaiveMatriz1, copiaNaiveMatriz2); 
    auto fin = high_resolution_clock::now();
    size_t memoriaDespues = obtenerMemoriaActual();
    auto tiempoNaive = duration_cast<microseconds>(fin - inicio).count();
    auto memoriaUsadaNaive = (memoriaDespues - memoriaAntes)/1024; // Convertir a KB

    // --- Medir Strassen ---
    auto copiaStrassenMatriz1 = matriz1;
    auto copiaStrassenMatriz2 = matriz2;
    memoriaAntes = obtenerMemoriaActual();
    inicio = high_resolution_clock::now();
    Matrix matrizResultadoStrassen = strassenMultiply(copiaStrassenMatriz1, copiaStrassenMatriz2);
    fin = high_resolution_clock::now();
    memoriaDespues = obtenerMemoriaActual();
    auto tiempoStrassen = duration_cast<microseconds>(fin - inicio).count();
    auto memoriaUsadaStrassen = (memoriaDespues - memoriaAntes)/1024; // Convertir a KB

    // --- Generar output ---
    string rutaOutput = "data/matrix_output/" + nombreArchivo.substr(0, nombreArchivo.size() - 5) + "out.txt";
    generarOutput(matrizResultadoNaive, rutaOutput);
    //generarOutput(matrizResultadoStrassen, rutaOutput); // DESCOMENTAR SI SE QUIERE GENERAR EL OUTPUT DE STRASSEN

    // --- Registar resultados en CSV ---
    int n;
    string t, d, m;
    extraerDatosArchivo(nombreArchivo, n, t, d, m);
    registrarResultadosCSV("data/measurements/mediciones.csv", n, t, d, m, "Naive", tiempoNaive, memoriaUsadaNaive);
    registrarResultadosCSV("data/measurements/mediciones.csv", n, t, d, m, "Strassen", tiempoStrassen, memoriaUsadaStrassen);

    // --- Imprimir resultados ---
    cout << "Memoria usada: " << memoriaUsadaNaive << " KB " << "Tiempo de Naive: " << tiempoNaive/1'000'000.0 << " segundos (" << tiempoNaive/1000.0 << " milisegundos) (" << tiempoNaive << " microsegundos)" << endl;
    cout << "Memoria usada: " << memoriaUsadaStrassen << " KB " << "Tiempo de Strassen: " << tiempoStrassen/1'000'000.0 << " segundos (" << tiempoStrassen/1000.0 << " milisegundos) (" << tiempoStrassen << " microsegundos)" << endl;
}



/**
 * @brief Lee una matriz desde un archivo de texto.
 *
 * Interpreta un archivo de texto donde cada fila contiene números separados por espacios y construye la matriz correspondiente.
 *
 * @param ruta Ruta del archivo desde el cual leer la matriz.
 * @return La matriz leída desde el archivo.
 */
Matrix leerMatriz(const string& ruta) {
    ifstream file(ruta);
    Matrix matriz;
    string line;
    
    if (!file.is_open()) {
        cerr << "Error abriendo archivo: " << ruta << endl;
        return matriz;
    }
    
    while (getline(file, line)) {
        istringstream iss(line);
        vector<int> fila;
        int num;
        while (iss >> num) {
            fila.push_back(num);
        }
        matriz.push_back(fila);
    }
    
    file.close();
    return matriz;
}


/**
 * @brief Obtiene el número inicial de un nombre de archivo.
 *
 * Extrae el número que aparece antes del primer guión bajo en el nombre de un archivo, se utiliza para ordenar los archivos.
 *
 * @param filename Nombre del archivo del cual extraer el número.
 * @return El número extraído como entero. Devuelve 0 si no se encuentra número.
 */
int obtenerNumeroInicial(const string& filename) {
    size_t pos = filename.find('_');
    if (pos != string::npos) {
        return stoi(filename.substr(0, pos));
    }
    return 0;
}


/**
 * @brief Lee archivos de una carpeta, ordena y procesa las matrices de dos en dos.
 *
 * Carga matrices desde archivos en una carpeta, las ordena, y aplica las mediciones de rendimiento de multiplicación de matrices por pares.
 *
 * @param ruta Ruta de la carpeta que contiene los archivos de matrices.
 * @return void
 */
void leerArchivos(string ruta) {

    if (!fs::exists(ruta) || !fs::is_directory(ruta)) {
        cerr << "La carpeta no existe o no es un directorio." << endl;
        return;
    }

    vector<fs::path> archivos;

    for (const auto& entry : fs::directory_iterator(ruta)) {
        if (entry.is_regular_file()) {
            archivos.push_back(entry.path());
        }
    }

    // Ordenar basándose primero en el número inicial, luego por nombre
    sort(archivos.begin(), archivos.end(), [](const fs::path& a, const fs::path& b) {
        int numA = obtenerNumeroInicial(a.filename().string());
        int numB = obtenerNumeroInicial(b.filename().string());
        if (numA != numB) {
            return numA < numB;
        } else {
            return a.filename().string() < b.filename().string();
        }
    });

    // Procesar de dos en dos
    for (size_t i = 0; i < archivos.size(); i += 2) {
        cout << "Archivo 1: \"" << archivos[i].filename().string() << "\"" << endl;
        cout << "Archivo 2: \"" << archivos[i + 1].filename().string() << "\"" << endl;

        Matrix matriz1 = leerMatriz(ruta+"/"+archivos[i].filename().string());
        Matrix matriz2 = leerMatriz(ruta+"/"+archivos[i+1].filename().string());

        realizarMediciones(matriz1, matriz2, archivos[i].filename().string());

        cout << "---------------------------------" << endl;
    }
}



int main()
{
    string ruta = "data/matrix_input";
    leerArchivos(ruta);
    return 0;
}