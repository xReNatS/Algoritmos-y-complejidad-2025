## Descripción

- **sorting/**  
  Contiene un archivo (`sorting.cpp`) que:
  1. Lee vectores de `data/array_input/`
  2. Mide tiempo y memoria de cuatro algoritmos de ordenamiento:
     - `sortArray` (std::sort)
     - `QuickSort`
     - `MergeSort`
     - `SelectionSort`
  3. Genera archivos de salida en `data/array_output/`
  4. Registra resultados en `data/measurements/mediciones.csv`

- **matrix_multiplication/**  
  Contiene un archivo (`matrix_multiplication.cpp`) que:
  1. Lee pares de matrices de `data/matrix_input/`
  2. Mide tiempo de dos algoritmos de multiplicación:
     - `Naive`
     - `Strassen`
  3. Genera archivos de salida en `data/matrix_output/`
  4. Registra resultados en `data/measurements/mediciones.csv`

---
## Consideraciones

1. Para la ejecución del programa basta con escribir por consola:
```text
make
```
   lo que generara el archivo ejecutable main, que para correrlo basta con poner:
```text
.\main
```
2. Ademas es importante revisar la version del compilador g++, puesto que la libreria _filesystem_ solo se encuentra en versiones recientes.
---

## Requisitos y Entorno

- **Sistema operativo**: Windows 11  
- **Compilador**:  
  ```text
  g++ (Rev2, Built by MSYS2 project) 14.2.0
