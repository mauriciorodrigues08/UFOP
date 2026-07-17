SHELL := /bin/bash

.PHONY: compile run all test clean help jar

## Compila o projeto
compile:
	@bash scripts/compile.sh

## Roda o projeto (assume que já foi compilado)
run:
	@bash scripts/run.sh

## Gera o .jar executável (TP2.jar) a partir das classes compiladas
jar: compile
	@bash scripts/jar.sh

## Compila e roda em sequência
all: compile run

## Roda os casos de teste (TesteCasos.java) sobre os datasets em dados-teste/
test: compile
	@java -Dfile.encoding=UTF-8 -Dstdout.encoding=UTF-8 -cp out TesteCasos \
		dados-teste/teste1_verao_linear_forte.tsv \
		dados-teste/teste2_inverno_relacao_fraca.tsv \
		dados-teste/teste3_outlier_anomalia.tsv \
		dados-teste/teste4_poucos_dados.tsv \
		dados-teste/teste5_validacao_erros.tsv

## Remove os arquivos gerados pela compilação
clean:
	@rm -rf out TP2.jar
	@echo "Limpo: pasta out/ e TP2.jar removidos."

## Lista os comandos disponíveis
help:
	@echo "Comandos disponíveis:"
	@echo "  make compile  - compila o projeto"
	@echo "  make run      - executa o projeto (já compilado)"
	@echo "  make all      - compila e executa"
	@echo "  make test     - roda os casos de teste (TesteCasos.java) sobre dados-teste/"
	@echo "  make jar      - gera o .jar executável (TP2.jar)"
	@echo "  make clean    - remove arquivos gerados (out/, sources.txt)"