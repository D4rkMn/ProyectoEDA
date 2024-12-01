from sentence_transformers import SentenceTransformer
import random

# Componentes de la gramática
introducciones = [
    "Cómo hacer", "Tutorial de", "Aprende sobre", "Mira este", 
    "Guía completa de", "Top 10 de", "Lo mejor de"
]
atributos = [
    "para principiantes", "en 5 minutos", "que debes conocer", 
    "que nunca te contaron", "fácil y rápido", "para expertos"
]
contextos = ["2024", "Parte 2", "HD", "completo"]

temas = [
    "programación en Python", "recetas saludables", "juegos de terror", 
    "descubrimientos científicos", "música clásica", "herramientas para diseño gráfico",
    "desarrollo de videojuegos en Unity", "inteligencia artificial explicada", 
    "algoritmos avanzados de programación", "cómo construir una página web", 
    "desarrollo móvil con Flutter", "trucos para usar Linux como un profesional",
    "música clásica", "los mejores covers acústicos", "música lo-fi para estudiar",
    "electrónica para fiestas", "cómo aprender a tocar la guitarra", "los hits de 2024",
    "el mundo del jazz moderno", "reggaetón para bailar sin parar",
    "cómo entrenar a tu perro", "historias fascinantes de la historia", 
    "los mejores gadgets tecnológicos del año", "trucos para fotografía en celular",
    "secretos para mejorar tu salud mental", "cómo viajar barato", 
    "los libros que debes leer en tu vida", "recetas rápidas y deliciosas", 
    "cómo aprender un idioma en 3 meses", "los secretos del universo"
]

# Generador de nombres
def generar_nombres_yt(n):
    nombres = []
    for _ in range(n):
        plantilla = random.choice([
            "{introducción} {tema} {atributo}",
            "{introducción} {tema}",
            "{tema} {atributo}",
            "{introducción} {tema} {atributo} {contexto}"
        ])
        nombre = plantilla.format(
            introducción=random.choice(introducciones),
            tema=random.choice(temas),
            atributo=random.choice(atributos),
            contexto=random.choice(contextos)
        )
        nombres.append(nombre)
    return nombres

# Inicializar el modelo preentrenado de sentence-transformers
model = SentenceTransformer('all-MiniLM-L6-v2')

# Generar nombres
nombres_generados = generar_nombres_yt(1000)

# Obtener los embeddings para los nombres generados
embeddings = model.encode(nombres_generados)


# guardar los nombres y embeddings en un archivo

file = open("nombres_yt.txt", "w")
for nombre, embedding in zip(nombres_generados, embeddings):
    file.write(f"{nombre}\n")
    for e in embedding:
        file.write(f"{e};")
    file.write("\n")

file.close()

print("Nombres y embeddings guardados en 'nombres_yt.txt'")
