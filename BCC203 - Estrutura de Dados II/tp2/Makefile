# ==========================================================
# Makefile - Trabalho Prático II - Ordenação Externa
# Estrutura de Dados II - BCC203 - UFOP
# ==========================================================

# Compilador e flags
CXX      := g++
CXXFLAGS := -Wall -Wextra -O2 -std=c++17 -Iinclude

# Diretórios do projeto
SRC_DIR   := src
INC_DIR   := include
OBJ_DIR   := obj
BIN_DIR   := bin
DATA_DIR  := data
FITAS_DIR := fitas

# Nome do executável final
TARGET    := $(BIN_DIR)/ordena

# Arquivos fonte e objeto (detectados automaticamente)
SRCS      := $(wildcard $(SRC_DIR)/*.cpp)
OBJS      := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Parâmetros padrão para o alvo "run"
METODO    ?= 2
QTD       ?= 100
SIT       ?= 3
FLAG      ?=

# ==========================================================
# Regras principais
# ==========================================================

.PHONY: all clean run rebuild dirs help

all: dirs $(TARGET)

# Garante que todas as pastas de saída existam (incluindo a pasta fitas)
dirs:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR) $(DATA_DIR) $(FITAS_DIR)

# Linkagem final do executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilação de cada arquivo .cpp em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | dirs
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Executa o programa a partir da raiz (onde está o PROVAO.TXT)
run: all
	./$(TARGET) $(METODO) $(QTD) $(SIT) $(FLAG)

# Recompila o projeto do zero
rebuild: clean all

# Remove objetos, executáveis e limpa completamente a pasta de fitas
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR) $(FITAS_DIR)
	@rm -f teste.bin

help:
	@echo "Alvos disponíveis:"
	@echo "  make         - compila o projeto (equivalente a 'make all')"
	@echo "  make run     - compila e executa o programa na raiz do projeto"
	@echo "                 parâmetros: METODO, QTD, SIT, FLAG"
	@echo "                 ex: make run METODO=3 QTD=100000 SIT=1 FLAG=-P"
	@echo "  make rebuild - limpa e recompila tudo"
	@echo "  make clean   - remove binários, objetos e a pasta de fitas"