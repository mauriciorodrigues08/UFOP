CXX      = g++
CXXFLAGS = -Wall -std=c++17 -Iimports

# Diretórios
SRC_DIR    = src
GEN_DIR    = gerador
OBJ_DIR    = obj

TARGET = pesquisa

# Arquivos fonte
SRC_SRCS = $(SRC_DIR)/arvore_b_estrela.cpp \
           $(SRC_DIR)/arvore_binaria.cpp \
           $(SRC_DIR)/arvoreb.cpp \
           $(SRC_DIR)/asi.cpp

GEN_SRCS = $(GEN_DIR)/gerador.cpp

ROOT_SRCS = main.cpp

ALL_SRCS = $(SRC_SRCS) $(GEN_SRCS) $(ROOT_SRCS)

# Objetos (espelha estrutura de diretórios dentro de obj/)
OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(ALL_SRCS))

# ── Alvo principal ────────────────────────────────────────────────────────────
.PHONY: all clean run gerador

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Build concluído: $@"

# ── Compilação de objetos ─────────────────────────────────────────────────────
$(OBJ_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/$(GEN_DIR)/%.o: $(GEN_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ── Alvos auxiliares ──────────────────────────────────────────────────────────
run: all
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(TARGET).exe $(TARGET)
	@echo "Limpeza concluída."