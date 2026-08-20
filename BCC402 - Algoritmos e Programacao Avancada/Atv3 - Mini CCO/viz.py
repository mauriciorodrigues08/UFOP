import pyvista as pv
import numpy as np
import pandas as pd

# 1. Carregar o arquivo gerado pelo C/C++
dados = pd.read_csv("arvore.csv")

# 2. Descobre quais nós são terminais (não aparecem como "pai" de ninguém)
ids_pais = set(dados["pai"].unique())
ids_terminais = set(dados["id"].unique()) - ids_pais

# os raios são normalizados pelo tronco (Parte D do enunciado) e não têm a mesma
# escala das coordenadas geométricas; escala visualmente para o maior raio ficar
# em torno de 30% do comprimento médio dos segmentos
escala_raio = (dados["comprimento"].mean() / dados["raio"].max()) * 0.3
dados["raio_visual"] = dados["raio"] * escala_raio
raio_visual_maximo = dados["raio_visual"].max()

# 3. Desenha cada segmento como um tubo, com espessura proporcional ao raio
plotter = pv.Plotter()

for _, row in dados.iterrows():
    p0 = np.array([row["x0"], row["y0"], row["z0"]])
    p1 = np.array([row["x1"], row["y1"], row["z1"]])

    if np.allclose(p0, p1): #segmento de comprimento ~0, não dá para desenhar como tubo
        continue

    linha = pv.Line(p0, p1)
    tubo = linha.tube(radius=max(row["raio_visual"], raio_visual_maximo * 0.05))

    cor = "tomato" if row["id"] in ids_terminais else "firebrick"
    plotter.add_mesh(tubo, color=cor)

# 4. Desenha o domínio circular (apenas o contorno, para não esconder a árvore)
raio = float(input("Insira o raio do domínio circular utilizado: "))
circle = pv.Circle(radius=raio)
plotter.add_mesh(circle, color="blue", style="wireframe", line_width=2)

plotter.view_xy()
plotter.show()