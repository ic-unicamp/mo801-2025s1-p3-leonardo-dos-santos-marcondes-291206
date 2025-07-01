#!/bin/bash
echo "🖼️ Setup do Projeto 3 - Filtro Sobel"
echo "==================================="

# Verificar Python
if ! command -v python3 &> /dev/null; then
    echo "❌ Python3 não encontrado"
    exit 1
fi

# Gerar dados de teste
echo "Gerando dados de teste..."
python3 scripts/generate_data.py

# Compilar e testar
echo "Compilando projeto..."
make clean
make data
make test
