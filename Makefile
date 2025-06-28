# Projeto 3 - Filtro Sobel
# Makefile para compilação multiplataforma

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -D_POSIX_C_SOURCE=199309L -Isrc
LDFLAGS = -lm -lrt
TARGET = sobel_test
SRC_DIR = src
SOURCES = $(SRC_DIR)/sobel_test.c $(SRC_DIR)/sobel_filter.c

# Configurações para debug/release
DEBUG_FLAGS = -g -O0 -DDEBUG
RELEASE_FLAGS = -O2 -DNDEBUG
PROFILE_FLAGS = -g -pg -O0
FAST_FLAGS = -O3 -DNDEBUG -ffast-math

# RISC-V cross-compilation
RISCV_CC = riscv64-unknown-elf-gcc
RISCV_CFLAGS = -march=rv32im -mabi=ilp32 -mcmodel=medlow -Isrc

.PHONY: all clean debug release profile fast riscv data test

# Default: release
all: release

# Gerar dados de teste
data: $(SRC_DIR)/sobel_data.h

$(SRC_DIR)/sobel_data.h:
	@echo "Gerando dados de teste..."
	python3 scripts/generate_data.py

# Versão debug
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)_debug

$(TARGET)_debug: $(SOURCES) $(SRC_DIR)/sobel_data.h
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/sobel_test.c $(SRC_DIR)/sobel_filter.c $(LDFLAGS)
	@echo "✓ Compilado: $@ (debug)"

# Versão release
release: CFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)_release

$(TARGET)_release: $(SOURCES) $(SRC_DIR)/sobel_data.h
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/sobel_test.c $(SRC_DIR)/sobel_filter.c $(LDFLAGS)
	@echo "✓ Compilado: $@ (release)"

# Versão para profiling
profile: CFLAGS += $(PROFILE_FLAGS)
profile: $(TARGET)_profile

$(TARGET)_profile: $(SOURCES) $(SRC_DIR)/sobel_data.h
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/sobel_test.c $(SRC_DIR)/sobel_filter.c $(LDFLAGS)
	@echo "✓ Compilado: $@ (profiling)"

# Versão otimizada
fast: CFLAGS += $(FAST_FLAGS)
fast: $(TARGET)_fast

$(TARGET)_fast: $(SOURCES) $(SRC_DIR)/sobel_data.h
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/sobel_test.c $(SRC_DIR)/sobel_filter.c $(LDFLAGS)
	@echo "✓ Compilado: $@ (fast)"

# Versão RISC-V
riscv: $(TARGET)_riscv

$(TARGET)_riscv: $(SOURCES) $(SRC_DIR)/sobel_data.h
	$(RISCV_CC) $(RISCV_CFLAGS) -o $@ $(SRC_DIR)/sobel_test.c $(SRC_DIR)/sobel_filter.c
	@echo "✓ Compilado: $@ (RISC-V)"

# Executar testes
test: release
	@echo "Executando baseline..."
	./$(TARGET)_release

# Profiling com gprof
prof: profile
	@echo "Executando profiling..."
	./$(TARGET)_profile
	gprof $(TARGET)_profile gmon.out > sobel_profile.txt
	@echo "✓ Resultados em: sobel_profile.txt"

# Benchmark comparativo
bench: debug release fast
	@echo "=== Benchmark Comparativo ==="
	@echo "Debug (-O0):"
	@./$(TARGET)_debug | grep "Tempo médio"
	@echo "Release (-O2):"
	@./$(TARGET)_release | grep "Tempo médio"
	@echo "Fast (-O3):"
	@./$(TARGET)_fast | grep "Tempo médio"

# Teste de compilação cruzada (apenas compila, não executa)
test-riscv: riscv
	@echo "✓ Compilação RISC-V bem-sucedida"
	@file $(TARGET)_riscv

# Limpeza
clean:
	rm -f $(TARGET)_debug $(TARGET)_release $(TARGET)_profile $(TARGET)_fast $(TARGET)_riscv
	rm -f gmon.out sobel_profile.txt test_images.png
	@echo "✓ Arquivos limpos"

# Ajuda
help:
	@echo "Targets disponíveis:"
	@echo "  all/release  - Compilar versão otimizada (padrão)"
	@echo "  debug        - Compilar com debug"
	@echo "  profile      - Compilar para profiling"
	@echo "  fast         - Compilar com máxima otimização"
	@echo "  riscv        - Compilar para RISC-V"
	@echo "  data         - Gerar dados de teste"
	@echo "  test         - Executar teste básico"
	@echo "  test-riscv   - Testar compilação RISC-V"
	@echo "  prof         - Executar profiling"
	@echo "  bench        - Benchmark comparativo"
	@echo "  clean        - Limpar arquivos"