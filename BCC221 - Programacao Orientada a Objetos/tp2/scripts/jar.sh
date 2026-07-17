#!/bin/bash
# jar.sh - Gera o .jar executável do TP2 a partir das classes já compiladas
# Pode ser executado de qualquer lugar: ./scripts/jar.sh ou de dentro de scripts/

set -e  # para o script se algum comando falhar

# Descobre o diretório onde este script está, e sobe um nível para achar a raiz do projeto
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"

# Pasta com os .class compilados (gerada pelo compile.sh)
OUT_DIR="$ROOT_DIR/out"

# Nome e classe principal do .jar final
JAR_NAME="TP2.jar"
MAIN_CLASS="Main"

if [ ! -d "$OUT_DIR" ]; then
    echo "ERRO: pasta '$OUT_DIR' não encontrada."
    echo "Rode 'make compile' (ou './scripts/compile.sh') antes de gerar o .jar."
    exit 1
fi

if [ ! -f "$OUT_DIR/Main.class" ]; then
    echo "ERRO: '$OUT_DIR/Main.class' não encontrado."
    echo "As classes parecem desatualizadas ou incompletas. Rode 'make compile' novamente."
    exit 1
fi

echo "Raiz do projeto: $ROOT_DIR"
echo "Gerando $JAR_NAME a partir de '$OUT_DIR'..."

MANIFEST_TMP="$OUT_DIR/manifest.txt"
echo "Main-Class: $MAIN_CLASS" > "$MANIFEST_TMP"

# Empacota todas as classes de out/ num único .jar executável na raiz do projeto
jar cfm "$ROOT_DIR/$JAR_NAME" "$MANIFEST_TMP" -C "$OUT_DIR" .

rm "$MANIFEST_TMP"

echo ""
echo "✅ JAR gerado com sucesso!"
echo "Arquivo: $ROOT_DIR/$JAR_NAME"
echo "Para executar: java -jar $JAR_NAME"