import os
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Ruta al archivo CSV con las métricas
csv_path = os.path.join('..', 'data', 'measurements', 'metrics.csv')

# Cargar los datos
try:
    df = pd.read_csv(csv_path)
except FileNotFoundError:
    print("No se encontró el archivo metrics.csv.")
    exit()

# Convertir columna de tiempo a segundos y memoria a MB para mejor interpretación
df['tiempo(s)'] = df['tiempo(ms)'] / 1000
df['memoria(MB)'] = df['pares'].apply(lambda x: x if x >= 0 else None)  # eliminar memoria ficticia

# Extraer valor de k del nombre del archivo si es necesario (opcional si ya está en la columna)
df['k'] = df['archivo'].str.extract(r'input_(\d+)').astype(float)

# Crear gráfico de tiempo vs k
plt.figure(figsize=(10, 6))
sns.lineplot(data=df, x='k', y='tiempo(s)', marker='o')
plt.title('Tiempo de ejecución vs número de casos (k)')
plt.xlabel('k')
plt.ylabel('Tiempo (segundos)')
plt.grid(True)
plt.xscale('log')
plt.tight_layout()
plt.savefig('../data/plots/tiempo_vs_k.png')
plt.close()

# Crear gráfico de memoria vs k
plt.figure(figsize=(10, 6))
sns.lineplot(data=df, x='k', y='memoria(MB)', marker='s', color='red')
plt.title('Uso de memoria vs número de casos (k)')
plt.xlabel('k')
plt.ylabel('Memoria (MB)')
plt.grid(True)
plt.xscale('log')
plt.tight_layout()
plt.savefig('../data/plots/memoria_vs_k.png')
plt.close()

print("Gráficos generados y guardados en ../data/plots")
