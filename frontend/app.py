from flask import Flask, request, jsonify
import subprocess

app = Flask(__name__)

# Mock de resultados de búsqueda
def buscar_videos_mock(algoritmo, query):
    # Esto es solo un mock. Aquí es donde ejecutarías el C++ como subproceso en el futuro.
    resultados = [
        {"titulo": f"Resultado 1 usando {algoritmo} para '{query}'", "descripcion": "Descripción del resultado 1"},
        {"titulo": f"Resultado 2 usando {algoritmo} para '{query}'", "descripcion": "Descripción del resultado 2"},
        {"titulo": f"Resultado 3 usando {algoritmo} para '{query}'", "descripcion": "Descripción del resultado 3"}
    ]
    return resultados

@app.route('/buscar_videos/<algoritmo>', methods=['GET'])
def buscar_videos(algoritmo):
    # Obtener el parámetro 'query' de la URL
    query = request.args.get('query')
    
    # Si no se especifica query, respondemos con un error
    if not query:
        return jsonify({"error": "El parámetro 'query' es requerido"}), 400
    
    # Aquí ejecutaremos el código de búsqueda (en este caso, un mock)
    resultados = buscar_videos_mock(algoritmo, query)
    
    # En el futuro, aquí ejecutamos el C++ y obtenemos los resultados como:
    # result = subprocess.run(["./busqueda_cpp", query], capture_output=True, text=True)
    # resultado_final = procesar_resultados(result.stdout)

    return jsonify({"algoritmo": algoritmo, "query": query, "resultados": resultados})

if __name__ == '__main__':
    app.run(debug=True)