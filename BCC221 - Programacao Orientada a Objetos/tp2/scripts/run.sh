#!/bin/bash
# run.sh - Executa o projeto TP2 (após compilar com compile.sh)
# Pode ser executado de qualquer lugar: ./scripts/run.sh ou de dentro de scripts/

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"

OUT_DIR="$ROOT_DIR/out"
MAIN_CLASS="Main"

if [ ! -d "$OUT_DIR" ]; then
    echo "ERRO: Pasta '$OUT_DIR' não encontrada. Rode ./scripts/compile.sh primeiro."
    exit 1
fi

echo "Executando $MAIN_CLASS ..."
java -cp "$OUT_DIR" "$MAIN_CLASS"