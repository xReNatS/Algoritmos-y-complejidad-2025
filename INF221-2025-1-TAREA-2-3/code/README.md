## Descripción

- **brute_force/**  
  Contiene un archivo (`brute_force.cpp`) que:
  1. Lee inputs de `data/brute_force_input/`
  2. Mide tiempo y memoria de la ejecución del algoritmo de diferencia de secuencia.
  3. Genera archivos de salida en `data/brute_force_output/`
  4. Registra resultados en `data/measurements/metrics.csv`
  5. Se crean los inputs en `scripts/input_generator.py`
  6. Se se generan los gráficos a partir del código que se encuentra en `scripts/plot_generator.py`

- **dynamic_programming/**  
  Contiene un archivo (`dynamic_programming.cpp`) que:
  1. Lee inputs de `data/dynamic_programming_input/`
  2. Mide tiempo y memoria de la ejecución del algoritmo de diferencia de secuencia.
  3. Genera archivos de salida en `data/dynamic_programming_output/`
  4. Registra resultados en `data/measurements/metrics.csv`
  5. Se crean los inputs en `scripts/input_generator.py`
  6. Se se generan los gráficos a partir del código que se encuentra en `scripts/plot_generator.py`

---
## Consideraciones

1. Para la ejecución del programa basta con escribir por consola:
```text
make run
```

2. Ademas es importante revisar la version del compilador g++, puesto que la libreria _filesystem_ solo se encuentra en versiones recientes.
---

3. Para ejecutar los scripts solo hace falta escribir un comando de python más el nombre del script:
```text
python3 input_generator.py ó plot_generator.py
```
---

## Requisitos y Entorno

- **Sistema operativo**: Windows 11  
- **Consola**: CMD
- **Compilador**:  
  ```text
  g++ (Rev2, Built by MSYS2 project) 14.2.0
- **Pandas**: 2.3.0
- **Matplotlib**: 3.10.3
- **Seaborne**: 0.13.2