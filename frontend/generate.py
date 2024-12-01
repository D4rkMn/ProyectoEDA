from sentence_transformers import SentenceTransformer
import random

file = open("nombres_yt.txt", "r")

nombres_generados = []

for line in file:
    nombres_generados.append(line.strip())

# Inicializar el modelo preentrenado de sentence-transformers
model = SentenceTransformer('all-MiniLM-L6-v2')


# Obtener los embeddings para los nombres generados
embeddings = model.encode(nombres_generados)

# Guardar los nombres y embeddings en un archivo
with open("nombres_embeddings_yt.txt", "w") as file:
    for nombre, embedding in zip(nombres_generados, embeddings):
        file.write(f"{nombre}\n")
        file.write(";".join(map(str, embedding)) + "\n")

print("Nombres y embeddings guardados en 'nombres_embeddings_yt.txt'")
