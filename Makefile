# Macros

MAIN = main/
MAIN_FILE = $(MAIN)main_matricula.cpp
SRC = src/
SRC_FILES = $(SRC)*.cpp
OUT = bin/
OUT_FILE = $(OUT)ABB


# Reglas explícitas

default:
	g++ -std=c++11 $(MAIN_FILE) $(SRC_FILES) -o $(OUT_FILE)

app:
	$(OUT_FILE)

run: default app
