from flask import Flask, request, jsonify
from flask_cors import CORS  # Importar CORS
import subprocess
from sentence_transformers import SentenceTransformer
from scipy.spatial.distance import cosine
import numpy as np

app = Flask(__name__)
CORS(app)
model = SentenceTransformer('all-MiniLM-L6-v2')


def cargar_datos(filename="nombres_embeddings_yt.txt"):
    nombres = []
    embeddings = []
    
    with open(filename, "r") as file:
        for line in enumerate(file):
            #linea 1: nombre; linea 2: embedding
            if line[0] % 2 == 0:
                nombres.append(line[1].strip())
            else:
                embedding = np.fromstring(line[1], sep=";")
                #quitar el ultimo elemento que es un espacio
                embedding = embedding[:-1]
                embeddings.append(embedding)
    
    return nombres, embeddings

def buscar_videos_mock(algoritmo, query, nombres, embeddings):
    # Crear el embedding de la query
    embedding_query = model.encode([query])[0]
    

    distancias = []
    for i, emb in enumerate(embeddings):
        distancia = cosine(embedding_query, emb)
        distancias.append((nombres[i], distancia))
    

    distancias.sort(key=lambda x: x[1])
    
    resultados = [{"titulo": nombre} for nombre, _ in distancias[:30]]
    
    return resultados

@app.route('/buscar_videos/<algoritmo>', methods=['GET'])
def buscar_videos(algoritmo):
    query = request.args.get('query')

    if (not query and query != ""):
        return jsonify({"error": "El parámetro 'query' es requerido"}), 400
    
    
    resultados = buscar_videos_mock(algoritmo, query, nombres, embeddings)

    if resultados == []:
        return jsonify({"error": "No se encontraron resultados para la búsqueda"}), 404

    return jsonify({"algoritmo": algoritmo, "query": query, "resultados": resultados, "error": None}), 200


# Cargar los datos
nombres, embeddings = cargar_datos()


if __name__ == '__main__':
    app.run(debug=True)