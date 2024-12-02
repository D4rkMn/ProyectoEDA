from flask import Flask, request, jsonify
from flask_cors import CORS
import subprocess
from sentence_transformers import SentenceTransformer
import numpy as np
import os
from scipy.spatial.distance import cosine

app = Flask(__name__)
CORS(app)  # Habilitar CORS
model = SentenceTransformer('all-MiniLM-L6-v2')


# Cargar datos desde el archivo `nombres_embeddings_yt.txt`
def cargar_datos(filename="nombres_embeddings_yt.txt"):
    nombres = []
    embeddings = []
    try:
        with open(filename, "r") as file:
            for line_num, line in enumerate(file):
                if line_num % 2 == 0:
                    nombres.append(line.strip())
                else:
                    embedding = np.fromstring(line.strip(), sep=";")
                    embeddings.append(embedding)
    except FileNotFoundError:
        print(f"Error: No se encontró el archivo {filename}.")
    return nombres, embeddings


# Buscar videos con un mock (Python, para pruebas rápidas)
def buscar_videos_mock(algoritmo, query, nombres, embeddings):
    embedding_query = model.encode([query])[0]
    distancias = [(nombres[i], cosine(embedding_query, emb)) for i, emb in enumerate(embeddings)]
    distancias.sort(key=lambda x: x[1])
    resultados = [{"titulo": nombre, "distancia": distancia} for nombre, distancia in distancias[:30]]
    return resultados


# Buscar videos con el programa C++
def buscar_videos_cpp(algoritmo, query):
    embedding_query = model.encode([query])[0]

    # Guardar en el archivo `query.txt`
    query_txt_path = "query.txt"
    with open(query_txt_path, "w") as file:
        file.write(f"{algoritmo}\n")
        file.write(";".join(map(str, embedding_query)) + ";\n")
        file.write(query + "\n")

    # Ejecutar el programa en C++
    try:
        result = subprocess.run(
            ["./DFM"],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )

        if result.returncode != 0:
            print(f"Error al ejecutar el programa C++: {result.stderr}")
            return []

        # Leer resultados desde la consola
        output_lines = result.stdout.strip().split("\n")

        # quitar la primera linea que dice "resultados"
        output_lines = output_lines[1:]

        return [{"titulo": line} for line in output_lines]

    except FileNotFoundError:
        print("Error: No se encontró el programa `main` en la carpeta `frontend`.")
        return []
    except Exception as e:
        print(f"Error inesperado: {e}")
        return []


@app.route('/buscar_videos/<algoritmo>', methods=['GET'])
def buscar_videos(algoritmo):
    query = request.args.get('query')

    if not query:
        return jsonify({"error": "El parámetro 'query' es requerido"}), 400

    if algoritmo not in ["Motley", "BRID", "Swap", "MMR", "Mock-KNN"]:
        algoritmo = "Motley"

    if algoritmo == "Mock-KNN":
        resultados = buscar_videos_mock(algoritmo, query, nombres, embeddings)
        resultados = [{"titulo": res["titulo"]} for res in resultados]
        return jsonify({"algoritmo": algoritmo, "query": query, "resultados": resultados, "error": None}), 200
    else:
        resultados = buscar_videos_cpp(algoritmo, query)
    
    if not resultados:
        return jsonify({"error": "No se encontraron resultados para la búsqueda"}), 404

    return jsonify({"algoritmo": algoritmo, "query": query, "resultados": resultados, "error": None}), 200

@app.route('/first_impression', methods=['GET'])
def first_impression():
    # buscar el video que sea un promedio de los embeddings
    embedding_query = 0

    for emb in embeddings:
        embedding_query += emb
    
    embedding_query /= len(embeddings)

    distancias = [(nombres[i], cosine(embedding_query, emb)) for i, emb in enumerate(embeddings)]

    distancias.sort(key=lambda x: x[1])

    resultados = [{"titulo": nombre, "distancia": distancia} for nombre, distancia in distancias[:30]]

    return jsonify({"resultados": resultados, "error": None}), 200


# Cargar los datos al iniciar el servidor
nombres, embeddings = cargar_datos()

if __name__ == '__main__':
    app.run(debug=True)
