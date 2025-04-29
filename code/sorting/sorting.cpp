#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <windows.h>
#include <psapi.h>
#include <algorithm>
#include "algorithms/sort.hpp"
#include "algorithms/mergesort.hpp"
#include "algorithms/quicksort.hpp"
#include "algorithms/selectionsort.hpp"

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
 * @brief Genera un archivo de salida con los elementos de un vector ordenado.
 *
 * Escribe los elementos del vector en un archivo de texto en la carpeta especificada,
 * modificando el nombre del archivo original para indicar que es un output.
 *
 * @param vectorOrdenado Vector de enteros que contiene los datos ordenados.
 * @param nombreArchivo Nombre del archivo base desde el cual se genera el nombre de salida.
 */
void generarOutput(vector<int>& vectorOrdenado, string nombreArchivo) {

    // corta el nombre del archivo para que no tenga la extension .txt
    nombreArchivo = nombreArchivo.substr(0, nombreArchivo.size() - 4) + "_out.txt";


    ofstream archivoSalida("data/array_output/" + nombreArchivo);
    if (!archivoSalida.is_open()) {
        cerr << "No se pudo abrir el archivo de salida: " << nombreArchivo << endl;
        return;
    }

    for (size_t i = 0; i < vectorOrdenado.size(); i++) {
        archivoSalida << vectorOrdenado[i];
        if (i != vectorOrdenado.size() - 1) {
            archivoSalida << " ";
        }
    }
    archivoSalida.close();
}


/**
 * @brief Separa una cadena de texto en partes utilizando un delimitador.
 *
 * Divide la cadena de entrada en varios tokens basados en el delimitador proporcionado
 * y los almacena en un vector de cadenas.
 *
 * @param s Cadena de entrada que se desea dividir.
 * @param delimiter Carácter que se utiliza como delimitador.
 * @return Vector de cadenas resultantes después de la división.
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
 * @brief Extrae datos específicos codificados en el nombre de un archivo.
 *
 * Elimina la extensión ".txt" y divide el nombre utilizando '_' como separador
 * para asignar valores a n, t, d y m.
 *
 * @param nombreArchivo Nombre del archivo del cual se extraerán los datos.
 * @param n Variable por referencia para almacenar el número extraído.
 * @param t Variable por referencia para almacenar el tipo extraído.
 * @param d Variable por referencia para almacenar el disperso o similar extraído.
 * @param m Variable por referencia para almacenar la clasificación extraída.
 */
void extraerDatosArchivo(const string& nombreArchivo, int& n, string& t, string& d, string& m) {
    // Eliminar ".txt" si está
    string nombre = nombreArchivo;
    if (nombre.size() > 4 && nombre.substr(nombre.size() - 4) == ".txt") {
        nombre = nombre.substr(0, nombre.size() - 4);
    }

    // Separar por '_'
    vector<string> partes = split(nombre, '_');

    if (partes.size() == 4) {
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
 * Escribe una línea nueva en el archivo CSV especificado con los datos de entrada,
 * incluyendo parámetros del archivo, nombre del algoritmo, tiempo de ejecución y memoria utilizada.
 *
 * @param archivoCSV Ruta al archivo CSV donde se registrarán los datos.
 * @param n Número de elementos.
 * @param t Tipo de dato o característica del archivo.
 * @param d Densidad u otro descriptor asociado.
 * @param m Clasificación o categoría adicional.
 * @param algoritmo Nombre del algoritmo que se midió.
 * @param tiempoMicrosegundos Tiempo de ejecución en microsegundos.
 * @param memoriaKB Memoria utilizada en kilobytes.
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
 * @brief Realiza mediciones de tiempo y memoria para distintos algoritmos de ordenamiento.
 *
 * Ejecuta y mide varios algoritmos de ordenamiento sobre una copia del vector de entrada,
 * registrando sus tiempos de ejecución y memoria usada para generar archivos de salida y registros CSV.
 *
 * @param vectorDesordenado Vector original que será ordenado por los distintos algoritmos.
 * @param nombreArchivo Nombre del archivo de donde provienen los datos, utilizado para salidas y registros.
 */
void realizarMediciones(vector<int>& vectorDesordenado, const string& nombreArchivo) {
    using namespace std::chrono;

    // --- Medicion de tiempo y memoria ---


    // --- Medir sortArray ---
    auto copiaSortArray = vectorDesordenado;
    size_t memoriaAntes = obtenerMemoriaActual();
    auto inicio = high_resolution_clock::now();
    vector<int> vectorOrdenado = sortArray(copiaSortArray); 
    auto fin = high_resolution_clock::now();
    size_t memoriaDespues = obtenerMemoriaActual();
    auto tiempoSortArray = duration_cast<microseconds>(fin - inicio).count();
    auto memoriaUsadaSortArray = (memoriaDespues - memoriaAntes)/1024; // Convertir a KB


    // --- Medir QuickSort ---
    auto copiaQuickSort = vectorDesordenado;
    memoriaAntes = obtenerMemoriaActual();
    inicio = high_resolution_clock::now();
    quickSort(copiaQuickSort);
    fin = high_resolution_clock::now();
    memoriaDespues = obtenerMemoriaActual();
    auto tiempoQuickSort = duration_cast<microseconds>(fin - inicio).count();
    auto memoriaUsadaQuickSort = (memoriaDespues - memoriaAntes)/1024; // Convertir a KB


    // --- Medir MergeSort ---
    auto copiaMergeSort = vectorDesordenado;
    memoriaAntes = obtenerMemoriaActual();
    inicio = high_resolution_clock::now();
    mergeSort(copiaMergeSort, 0, copiaMergeSort.size() - 1);
    fin = high_resolution_clock::now();
    memoriaDespues = obtenerMemoriaActual();
    auto tiempoMergeSort = duration_cast<microseconds>(fin - inicio).count();
    auto memoriaUsadaMergeSort = (memoriaDespues - memoriaAntes)/1024; // Convertir a KB

    // --- Medir SelectionSort ---
    auto tiempoSelectionSort = 7'000'000; // 30 segundos
    auto memoriaUsadaSelectionSort = 0; // No se mide memoria para SelectionSort en grandes arreglos
    if (vectorDesordenado.size() < 10000000) {
        auto copiaSelectionSort = vectorDesordenado;
        memoriaAntes = obtenerMemoriaActual();
        inicio = high_resolution_clock::now();
        selectionSort(copiaSelectionSort);
        fin = high_resolution_clock::now();
        memoriaDespues = obtenerMemoriaActual();
        tiempoSelectionSort = duration_cast<microseconds>(fin - inicio).count(); 
        memoriaUsadaSelectionSort = (memoriaDespues - memoriaAntes)/1024; // Convertir a KB
    }


    // --- Generar Output ---
    generarOutput(vectorOrdenado, nombreArchivo);
    //generarOutput(copiaQuickSort, nombreArchivo); DESCOMENTAR SI SE QUIERE REVISAR LA CORRECTA ORDENACION DE QUICKSORT
    //generarOutput(copiaMergeSort, nombreArchivo); DESCOMENTAR SI SE QUIERE REVISAR LA CORRECTA ORDENACION DE MERGESORT
    //generarOutput(copiaSelectionSort, nombreArchivo); DESCOMENTAR SI SE QUIERE REVISAR LA CORRECTA ORDENACION DE SELECTIONSORT

    // --- Registar resultados en CSV ---
    int n;
    string t, d, m;
    extraerDatosArchivo(nombreArchivo, n, t, d, m);
    registrarResultadosCSV("data/measurements/mediciones.csv", n, t, d, m, "sortArray", tiempoSortArray, memoriaUsadaSortArray);
    registrarResultadosCSV("data/measurements/mediciones.csv", n, t, d, m, "QuickSort", tiempoQuickSort, memoriaUsadaQuickSort);
    registrarResultadosCSV("data/measurements/mediciones.csv", n, t, d, m, "MergeSort", tiempoMergeSort, memoriaUsadaMergeSort);
    registrarResultadosCSV("data/measurements/mediciones.csv", n, t, d, m, "SelectionSort", tiempoSelectionSort, memoriaUsadaSelectionSort);

    
    // --- Imprimir resultados --- //REVISAR
    cout << "Memoria usada: " << memoriaUsadaSortArray << " KB " << "Tiempo de sortArray: " << tiempoSortArray/1'000'000.0 << " segundos (" << tiempoSortArray/1000.0 << " milisegundos) (" << tiempoSortArray << " microsegundos)" << endl;
    cout << "Memoria usada: " << memoriaUsadaQuickSort << " KB " << "Tiempo de QuickSort: " << tiempoQuickSort/1'000'000.0 << " segundos (" << tiempoQuickSort/1000.0 << " milisegundos) (" << tiempoQuickSort << " microsegundos)" << endl;
    cout << "Memoria usada: " << memoriaUsadaMergeSort << " KB " << "Tiempo de MergeSort: " << tiempoMergeSort/1'000'000.0 << " segundos (" << tiempoMergeSort/1000.0 << " milisegundos) (" << tiempoMergeSort << " microsegundos)" << endl;
    cout << "Memoria usada: " << memoriaUsadaSelectionSort << " KB " << "Tiempo de SelectionSort: " << tiempoSelectionSort/1'000'000.0 << " segundos (" << tiempoSelectionSort/1000.0 << " milisegundos) (" << tiempoSelectionSort << " microsegundos)" << endl;
}


/**
 * @brief Lee archivos de entrada y realiza mediciones de rendimiento sobre su contenido.
 *
 * Carga todos los archivos de una carpeta específica, procesa cada uno en orden basado
 * en el número inicial de su nombre, y realiza mediciones de algoritmos de ordenamiento.
 *
 * @param Ninguno.
 * @return void
 */
void leerArchivos() {
    string carpeta = "data/array_input";

    vector<fs::directory_entry> archivos; 
    vector<int> datos;

    // Guardar primero todos los archivos .txt
    for (const auto& entrada : fs::directory_iterator(carpeta)) {
        if (entrada.is_regular_file() && entrada.path().extension() == ".txt") {
            archivos.push_back(entrada);
        }
    }

    // Ordena los archivos por el número en el nombre
    auto extraerNumero = [](const fs::path& path) -> int {
        string nombre = path.stem().string(); // nombre sin extensión
        string numero;
        for (char c : nombre) {
            if (isdigit(c)) numero += c;
            else break; // paramos al primer no número
        }
        return numero.empty() ? 0 : stoi(numero);
    };
    
    sort(archivos.begin(), archivos.end(), [extraerNumero](const fs::directory_entry& a, const fs::directory_entry& b) {
        return extraerNumero(a.path()) < extraerNumero(b.path());
    });
    

    // Ahora leer los archivos ya ordenados
    for (const auto& entrada : archivos) {
        ifstream archivo(entrada.path());
        if (archivo.is_open()) {

            string nombreArchivo = entrada.path().filename().string(); // nombre del archivo sin la ruta
            cout << "Leyendo archivo: " << nombreArchivo << "\n" << endl;

            string linea;
            datos.clear(); // Limpiamos datos antes de leer un nuevo archivo

            // Leer la línea del archivo y extraer los números para crear el vector
            while (getline(archivo, linea)) {
                istringstream stream(linea);
                int numero;
                while (stream >> numero) {
                    datos.push_back(numero);
                }
            }

            // Aqui se realizan la mediciones y se generan los archivos csv
            realizarMediciones(datos, nombreArchivo);

            archivo.close();
        } else {
            cerr << "No se pudo abrir: " << entrada.path() << endl;
        }
        cout << "----------------------------" << endl;
    }
}


int main()
{
    leerArchivos();
    return 0;
}
