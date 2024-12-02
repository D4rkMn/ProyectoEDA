import unicodedata

# Abrir el archivo y leer las líneas
with open("Last.fm_data.csv", "r", encoding="utf-8") as file:
    lines = file.readlines()

# Omitir la primera línea
lines = lines[1:]

# Usar un conjunto para evitar duplicados
nombres = set()

# Función para normalizar los caracteres y eliminar caracteres especiales
def limpiar_texto(texto):
    # Normalizar texto para manejar tildes y caracteres especiales
    texto = unicodedata.normalize("NFD", texto)
    texto = "".join([c for c in texto if unicodedata.category(c) != "Mn"])  # Eliminar marcas de acento (tildes)
    return texto

# Obtener los nombres de los videos
for line in lines:
    nombre = line.split(",")[3] + " - " + line.split(",")[2]  # Obtener el nombre del video
    nombre_limpio = limpiar_texto(nombre)  # Limpiar el nombre
    nombres.add(nombre_limpio)  # Añadir al set para evitar duplicados

# Exportar los nombres a un archivo
with open("nombres_yt.txt", "w", encoding="utf-8") as file:
    for nombre in nombres:
        file.write(f"{nombre}\n")
