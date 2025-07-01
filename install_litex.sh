#!/bin/bash

echo "🔧 Instalação do LiteX Framework"
echo "================================="
echo ""

# Função para verificar se comando existe
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Verificar sistema operacional
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo "✅ Sistema Linux detectado"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    echo "✅ Sistema macOS detectado"
else
    echo "⚠️  Sistema não testado, tentando instalação Linux"
fi

echo ""
echo "📋 PASSO 1: Verificando dependências do sistema"
echo "================================================"

# Dependências básicas
DEPS_MISSING=0

echo "Verificando dependências básicas..."

if ! command_exists python3; then
    echo "❌ Python3 não encontrado"
    DEPS_MISSING=1
else
    echo "✅ Python3: $(python3 --version)"
fi

if ! command_exists pip3; then
    echo "❌ pip3 não encontrado"
    DEPS_MISSING=1
else
    echo "✅ pip3: $(pip3 --version | head -1)"
fi

if ! command_exists git; then
    echo "❌ Git não encontrado"
    DEPS_MISSING=1
else
    echo "✅ Git: $(git --version)"
fi

if ! command_exists make; then
    echo "❌ Make não encontrado"
    DEPS_MISSING=1
else
    echo "✅ Make: $(make --version | head -1)"
fi

if ! command_exists gcc; then
    echo "❌ GCC não encontrado"
    DEPS_MISSING=1
else
    echo "✅ GCC: $(gcc --version | head -1)"
fi

if [ $DEPS_MISSING -eq 1 ]; then
    echo ""
    echo "❌ Dependências básicas faltando. Instale com:"
    echo ""
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        echo "sudo apt update"
        echo "sudo apt install -y python3 python3-pip git build-essential"
        echo "sudo apt install -y python3-dev python3-setuptools"
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        echo "brew install python3 git"
        echo "xcode-select --install"
    fi
    echo ""
    echo "Execute este script novamente após instalar as dependências."
    exit 1
fi

echo ""
echo "📋 PASSO 2: Verificando Python e pip"
echo "====================================="

# Verificar versão do Python
PYTHON_VERSION=$(python3 -c "import sys; print(f'{sys.version_info.major}.{sys.version_info.minor}')")
echo "Python versão: $PYTHON_VERSION"

if (( $(echo "$PYTHON_VERSION < 3.8" | bc -l) )); then
    echo "⚠️  Python $PYTHON_VERSION pode ter problemas. Recomendado: Python 3.8+"
fi

# Atualizar pip
echo "Atualizando pip..."
python3 -m pip install --upgrade pip

echo ""
echo "📋 PASSO 3: Instalação do LiteX"
echo "================================"

echo "Instalando LiteX framework..."
echo "Isso pode demorar alguns minutos..."
echo ""

# Opção 1: Instalação simples via pip
echo "Tentando instalação via pip..."
python3 -m pip install --user litex[develop]

if [ $? -eq 0 ]; then
    echo "✅ LiteX instalado via pip com sucesso!"
else
    echo "⚠️  Instalação via pip falhou, tentando método alternativo..."
    
    # Opção 2: Instalação via repositório
    echo ""
    echo "Instalando via repositório GitHub..."
    
    # Criar diretório temporário
    TEMP_DIR=$(mktemp -d)
    cd "$TEMP_DIR"
    
    # Clonar repositório principal
    git clone https://github.com/enjoy-digital/litex.git
    cd litex
    
    # Instalar
    python3 -m pip install --user -e .
    
    # Voltar ao diretório original
    cd "$OLDPWD"
    rm -rf "$TEMP_DIR"
fi

echo ""
echo "📋 PASSO 4: Instalação de dependências adicionais"
echo "================================================="

echo "Instalando ferramentas adicionais..."

# Migen (dependência do LiteX)
python3 -m pip install --user migen

# Outras dependências úteis
python3 -m pip install --user colorama pexpect

echo ""
echo "📋 PASSO 5: Verificação da instalação"
echo "====================================="

echo "Testando LiteX..."

# Teste básico do LiteX
python3 -c "import litex; print('✅ LiteX importado com sucesso!')" 2>/dev/null
if [ $? -eq 0 ]; then
    echo "✅ LiteX funcionando!"
else
    echo "❌ LiteX não funciona ainda..."
    
    # Diagnóstico
    echo ""
    echo "🔍 DIAGNÓSTICO:"
    echo "Python path:"
    python3 -c "import sys; print('\n'.join(sys.path))"
    
    echo ""
    echo "Pacotes instalados relacionados ao LiteX:"
    python3 -m pip list | grep -i litex || echo "Nenhum pacote LiteX encontrado"
    
    echo ""
    echo "💡 SOLUÇÃO:"
    echo "1. Verifique se ~/.local/bin está no PATH:"
    echo "   echo \$PATH | grep -o ~/.local/bin"
    echo ""
    echo "2. Se não estiver, adicione ao ~/.bashrc:"
    echo "   echo 'export PATH=\$HOME/.local/bin:\$PATH' >> ~/.bashrc"
    echo "   source ~/.bashrc"
    echo ""
    echo "3. Tente instalar globalmente (se tiver permissão):"
    echo "   sudo python3 -m pip install litex[develop]"
fi

echo ""
echo "📋 PASSO 6: Instalação do Verilator (se necessário)"
echo "==================================================="

if ! command_exists verilator; then
    echo "Instalando Verilator..."
    
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        sudo apt update
        sudo apt install -y verilator
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        brew install verilator
    fi
    
    if command_exists verilator; then
        echo "✅ Verilator instalado: $(verilator --version | head -1)"
    else
        echo "⚠️  Verilator não foi instalado automaticamente"
        echo "   Instale manualmente conforme sua distribuição"
    fi
else
    echo "✅ Verilator já instalado: $(verilator --version | head -1)"
fi

echo ""
echo "📋 RESUMO FINAL"
echo "==============="

# Verificação final
echo "Verificando instalações..."

if python3 -c "import litex" 2>/dev/null; then
    echo "✅ LiteX: OK"
else
    echo "❌ LiteX: Falhou"
fi

if command_exists verilator; then
    echo "✅ Verilator: OK"
else
    echo "❌ Verilator: Faltando"
fi

if python3 -c "import migen" 2>/dev/null; then
    echo "✅ Migen: OK"
else
    echo "❌ Migen: Falhou"
fi
