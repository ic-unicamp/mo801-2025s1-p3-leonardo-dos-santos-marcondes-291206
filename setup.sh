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

if [ $? -eq 0 ]; then
    echo ""
    echo "✅ Setup concluído com sucesso!"
    echo ""
    echo "Próximos passos:"
    echo "1. Execute: make prof     # Para profiling"
    echo "2. Execute: make bench    # Para comparar otimizações"
    echo "3. Analise: sobel_profile.txt"
    echo ""
    echo "🎯 Baseline estabelecido! Pronto para implementar acelerador."
else
    echo "❌ Erro na compilação/teste"
    exit 1
fi