# Compilador e flags
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Diretórios
SRC_HEADERS = imports
SRC_CLASSES = src
OBJ_DIR     = build

# Nome do executável
TARGET = exe

# Arquivos fonte e objetos
SRCS = $(SRC_CLASSES)/Pessoa.cpp \
       $(SRC_CLASSES)/Transacao.cpp \
       $(SRC_CLASSES)/Cliente.cpp \
       $(SRC_CLASSES)/Gerente.cpp \
       $(SRC_CLASSES)/Menu.cpp \
       $(SRC_CLASSES)/Controller.cpp \
       $(SRC_CLASSES)/Data.cpp \
       $(SRC_CLASSES)/Horario.cpp \
       $(SRC_CLASSES)/CartaoDeCredito.cpp \
       main.cpp

OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))

# ─────────────────────────────────────────────
# Regra padrão: compilar
# ─────────────────────────────────────────────
all: $(OBJ_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo ""
	@echo "✔  Build concluído: ./$(TARGET)"

# ─────────────────────────────────────────────
# Compilação dos objetos
# ─────────────────────────────────────────────
$(OBJ_DIR)/Pessoa.o: $(SRC_CLASSES)/Pessoa.cpp $(SRC_HEADERS)/Pessoa.h
	$(CXX) $(CXXFLAGS) -I$(SRC_HEADERS) -c $< -o $@

$(OBJ_DIR)/Transacao.o: $(SRC_CLASSES)/Transacao.cpp $(SRC_HEADERS)/Transacao.h
	$(CXX) $(CXXFLAGS) -I$(SRC_HEADERS) -c $< -o $@

$(OBJ_DIR)/Cliente.o: $(SRC_CLASSES)/Cliente.cpp $(SRC_HEADERS)/Cliente.h
	$(CXX) $(CXXFLAGS) -I$(SRC_HEADERS) -c $< -o $@

$(OBJ_DIR)/Gerente.o: $(SRC_CLASSES)/Gerente.cpp $(SRC_HEADERS)/Gerente.h
	$(CXX) $(CXXFLAGS) -I$(SRC_HEADERS) -c $< -o $@

$(OBJ_DIR)/Menu.o: $(SRC_CLASSES)/Menu.cpp $(SRC_HEADERS)/Menu.h
	$(CXX) $(CXXFLAGS) -I$(SRC_HEADERS) -c $< -o $@

$(OBJ_DIR)/Controller.o: $(SRC_CLASSES)/Controller.cpp $(SRC_HEADERS)/Controller.h
	$(CXX) $(CXXFLAGS) -I$(SRC_HEADERS) -c $< -o $@

$(OBJ_DIR)/Data.o: $(SRC_CLASSES)/Data.cpp $(SRC_HEADERS)/Data.h
	$(CXX) $(CXXFLAGS) -I$(SRC_HEADERS) -c $< -o $@

$(OBJ_DIR)/Horario.o: $(SRC_CLASSES)/Horario.cpp $(SRC_HEADERS)/Horario.h
	$(CXX) $(CXXFLAGS) -I$(SRC_HEADERS) -c $< -o $@

$(OBJ_DIR)/CartaoDeCredito.o: $(SRC_CLASSES)/CartaoDeCredito.cpp $(SRC_HEADERS)/CartaoDeCredito.h
	$(CXX) $(CXXFLAGS) -I$(SRC_HEADERS) -c $< -o $@

$(OBJ_DIR)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -I$(SRC_HEADERS) -c $< -o $@

# Cria a pasta build se não existir
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# ─────────────────────────────────────────────
# Compilar e executar
# ─────────────────────────────────────────────
run: all
	@echo ""
	@echo "──────────── Executando $(TARGET) ────────────"
	./$(TARGET)

# ─────────────────────────────────────────────
# Limpar arquivos gerados
# ─────────────────────────────────────────────
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "✔  Arquivos removidos."

.PHONY: all run clean