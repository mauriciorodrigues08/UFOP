#!/bin/bash
# compile.sh - Compila o projeto TP2
# Pode ser executado de qualquer lugar: ./scripts/compile.sh ou de dentro de scripts/

set -e  # para o script se algum comando falhar

# Descobre o diretório onde este script está, e sobe um nível para achar a raiz do projeto
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"

# Pasta onde estão os .java, relativa à raiz do projeto
SRC_DIR="$ROOT_DIR/src"

# Pasta de saída dos .class compilados
OUT_DIR="$ROOT_DIR/out"

if [ ! -d "$SRC_DIR" ]; then
    echo "ERRO: pasta '$SRC_DIR' não encontrada."
    echo "Verifique se a estrutura do projeto tem uma pasta 'src/' na raiz."
    exit 1
fi

echo "Raiz do projeto: $ROOT_DIR"
echo "Procurando arquivos .java em '$SRC_DIR'..."

# Usa array + delimitador nulo para lidar corretamente com espaços no caminho
mapfile -d '' JAVA_FILES < <(find "$SRC_DIR" -name "*.java" -print0)

QTD=${#JAVA_FILES[@]}
if [ "$QTD" -eq 0 ]; then
    echo "ERRO: Nenhum arquivo .java encontrado em '$SRC_DIR'."
    exit 1
fi

echo "Encontrados $QTD arquivo(s) .java. Compilando..."

mkdir -p "$OUT_DIR"
javac -d "$OUT_DIR" -encoding UTF-8 "${JAVA_FILES[@]}"

echo ""
echo "✅ Compilação concluída com sucesso!"
echo "Classes geradas em: $OUT_DIR/"