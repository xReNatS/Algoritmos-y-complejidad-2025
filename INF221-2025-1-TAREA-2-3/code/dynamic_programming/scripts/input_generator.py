import os
import random

# Script: Generador de inputs con longitudes de n y m acotadas a 100
# Cada archivo input_<k>.txt en ../data/dynamic_programming_input

# Directorio de destino
directorio = os.path.join('..', 'data', 'dynamic_programming_input')
os.makedirs(directorio, exist_ok=True)

# Longitud máxima de n y m
LONGITUD_MAX = 100
# Límite de casos por archivo para no demorarse demasiado
max_casos = 100000

# Construir lista de tamaños de k con crecimiento escalonado
tamanos_k = []
k = 10
paso = 10
while k <= 10_000_000:
    tamanos_k.append(k)
    if k < 100:
        paso = 10
    elif k < 1000:
        paso = 150
    elif k < 10000:
        paso = 2250
    elif k < 100000:
        paso = 30000
    elif k < 1000000:
        paso = 450000
    else:
        paso = 9000000
    k += paso

for k in tamanos_k:
    num_casos = k if k <= max_casos else max_casos
    nombre_archivo = f'input_{k}.txt'
    ruta = os.path.join(directorio, nombre_archivo)
    with open(ruta, 'w', encoding='utf-8') as f:
        f.write(f"{num_casos}\n")
        for _ in range(num_casos):
            n = random.randint(1, min(k, LONGITUD_MAX))
            m = random.randint(1, min(k, LONGITUD_MAX))
            secuencia_s = ''.join(random.choices('ABCDEFGHIJKLMNOPQRSTUVWXYZ', k=n))
            secuencia_t = ''.join(random.choices('ABCDEFGHIJKLMNOPQRSTUVWXYZ', k=m))
            f.write(f"{n} {secuencia_s}\n")
            f.write(f"{m} {secuencia_t}\n")
    print(f"Generado: {ruta} ({num_casos} casos, n/m ≤ {LONGITUD_MAX})")
