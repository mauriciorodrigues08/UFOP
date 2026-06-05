import pyvista as pv
import numpy as np
import pandas as pd

# 1. Carregar os arquivos gerados pelo C/C++
nos_df = pd.read_csv("nos.csv")
linhas_df = pd.read_csv("linhas.csv")

# 2. Configurar array de pontos para o PyVista
points = np.zeros((len(nos_df), 3))
points[:, 0] = nos_df['x'].values
points[:, 1] = nos_df['y'].values

# Mapear o id do nó para o índice do array de pontos
id_to_index = {row['id']: idx for idx, row in nos_df.iterrows()}

# 3. Configurar array de linhas (formato PyVista: [2, pt1, pt2, 2, pt3, pt4...])
lines = []
for _, row in linhas_df.iterrows():
    lines.append(2) # 2 pontos por linha (segmento)
    lines.append(id_to_index[row['id_pai']])
    lines.append(id_to_index[row['id_filho']])

# 4. Criar a malha e plotar
mesh = pv.PolyData()
#mesh.points = points
mesh.points = np.array(points)
mesh.lines = np.hstack(lines)

plotter = pv.Plotter()
plotter.add_mesh(mesh, line_width=3, color="red")

# Desenhar o domínio circular
raio = float(input("Insira o raio do domínio circular utilizado: "))
circle = pv.Circle(radius=raio) 
plotter.add_mesh(circle, color="lightblue", opacity=0.3)

plotter.view_xy()
plotter.show()