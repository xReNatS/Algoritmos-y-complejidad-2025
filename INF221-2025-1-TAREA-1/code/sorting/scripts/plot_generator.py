import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

# Leer CSV
columnas = ["n", "t", "d", "m", "algoritmo", "tiempo_microsegundos", "memoria_kb"]
df = pd.read_csv('../data/measurements/mediciones.csv', names=columnas)

# Carpeta donde guardar
output_folder = '../data/plots/'
os.makedirs(output_folder, exist_ok=True)

# Tema bonito
sns.set_theme(style="whitegrid")

# 1. Gráfico de tiempo por algoritmo
plt.figure(figsize=(10, 6))
for algoritmo in df['algoritmo'].unique():
    subset = df[df['algoritmo'] == algoritmo]
    plt.plot(subset['n'], subset['tiempo_microsegundos'], marker='o', label=algoritmo)

plt.xlabel('Cantidad de elementos (n)')
plt.ylabel('Tiempo (microsegundos)')
plt.title('Comparación de Tiempo de Algoritmos de Ordenamiento')
plt.legend()
plt.grid(True)
plt.savefig('../data/plots/tiempo_vs_algoritmo.png')  # Guardar el gráfico
plt.close()

# 2. Gráfico de memoria por algoritmo
plt.figure(figsize=(10, 6))
for algoritmo in df['algoritmo'].unique():
    subset = df[df['algoritmo'] == algoritmo]
    plt.plot(subset['n'], subset['memoria_kb'], marker='o', label=algoritmo)

plt.xlabel('Cantidad de elementos (n)')
plt.ylabel('Memoria usada (KB)')
plt.title('Comparación de Memoria de Algoritmos de Ordenamiento')
plt.legend()
plt.grid(True)
plt.savefig('../data/plots/memoria_vs_algoritmo.png')  # Guardar el gráfico
plt.close()

# Gráfico 3: Tiempo vs N para todos los algoritmos
plt.figure(figsize=(10, 6))
sns.lineplot(data=df, x='n', y='tiempo_microsegundos', hue='algoritmo', marker="o")
plt.title('Tiempo de Ejecución por Algoritmo')
plt.xlabel('Cantidad de Elementos (n)')
plt.ylabel('Tiempo (microsegundos)')
plt.legend(title='Algoritmo')
plt.savefig(os.path.join(output_folder, 'tiempo_vs_algoritmo.png'))
plt.close()

# Gráfico 4: Memoria vs N para todos los algoritmos
plt.figure(figsize=(10, 6))
sns.lineplot(data=df, x='n', y='memoria_kb', hue='algoritmo', marker="o")
plt.title('Memoria Usada por Algoritmo')
plt.xlabel('Cantidad de Elementos (n)')
plt.ylabel('Memoria (KB)')
plt.legend(title='Algoritmo')
plt.savefig(os.path.join(output_folder, 'memoria_vs_algoritmo.png'))
plt.close()

# Gráficos separados por tipo de matriz (t)
tipos = df['t'].unique()

for tipo in tipos:
    df_tipo = df[df['t'] == tipo]

    # Tiempo vs N para un tipo específico
    plt.figure(figsize=(10, 6))
    sns.lineplot(data=df_tipo, x='n', y='tiempo_microsegundos', hue='algoritmo', marker="o")
    plt.title(f'Tiempo de Ejecución por Algoritmo ({tipo})')
    plt.xlabel('Cantidad de Elementos (n)')
    plt.ylabel('Tiempo (microsegundos)')
    plt.legend(title='Algoritmo')
    plt.savefig(os.path.join(output_folder, f'tiempo_vs_algoritmo_{tipo}.png'))
    plt.close()

    # Memoria vs N para un tipo específico
    plt.figure(figsize=(10, 6))
    sns.lineplot(data=df_tipo, x='n', y='memoria_kb', hue='algoritmo', marker="o")
    plt.title(f'Memoria Usada por Algoritmo ({tipo})')
    plt.xlabel('Cantidad de Elementos (n)')
    plt.ylabel('Memoria (KB)')
    plt.legend(title='Algoritmo')
    plt.savefig(os.path.join(output_folder, f'memoria_vs_algoritmo_{tipo}.png'))
    plt.close()

print("Gráficos generados exitosamente")
