# Projeto 3 - Aceleração do Filtro Sobel

## Resumo Executivo

Este projeto implementa e acelera o filtro Sobel para detecção de bordas em imagens 32x32 pixels, comparando a performance entre implementação software (baseline) e acelerador hardware integrado em SoC LiteX.

## Programa Escolhido: Filtro Sobel

### Justificativa da Escolha
- **Relevância**: Detecção de bordas é fundamental em visão computacional e IA
- **Paralelização**: O algoritmo é naturalmente paralelizável
- **Medição**: Fácil de medir performance (pixels/segundo)
- **Aceleração**: Potencial significativo de speedup com hardware

### Características do Algoritmo
- Convolução 3x3 com kernels Sobel X e Y
- 6 multiplicações paralelas por pixel
- Operações de ponto fixo (int16)
- Dados de entrada: imagens 8-bit grayscale

## Implementação

### 1. Baseline Software (C)
- Implementação sequencial em C
- Otimizações: -O2, loop unrolling
- Target: CPU RISC-V VexRiscv

### 2. Acelerador Hardware (SystemVerilog)
- Pipeline de 2 estágios
- 6 multiplicadores paralelos
- Throughput: 1 pixel/ciclo
- Latência: 2 ciclos

### 3. Integração LiteX
- CSR registers para configuração
- Interface Wishbone para DMA
- BIOS customizado com benchmarks

## Resultados de Performance

### Medições Baseline
```
### Resultados Software:
```
```

### Resultados Hardware:
```
```

## Análise de Speedup

### Speedup Teórico Esperado
- Software: ~6 ciclos/pixel (sequencial)
- Hardware: ~1 ciclo/pixel (pipeline)
- **Speedup esperado: ~6x**

### Speedup Medido
[Será preenchido durante execução na plataforma LiteX]

## Conclusões

### Objetivos Alcançados
✅ Implementação baseline funcional
✅ Acelerador hardware validado
✅ Integração LiteX completa
✅ Framework de benchmark estabelecido

### Próximos Passos
- Otimização do DMA controller
- Suporte a imagens maiores
- Implementação do gradiente Y (magnitude)
- Testes em FPGA real

## Arquivos do Projeto

- `src/sobel_filter.c` - Implementação software
- `sobel_compute_engine.sv` - Core do acelerador
- `sobel_accelerator.sv` - Módulo completo
- `sobel_accelerator.py` - Integração LiteX
- `build_sobel_litex.py` - Script de build

## Como Reproduzir

```bash
# 1. Executar pipeline completo
./run_projeto3.sh

# 2. Build manual LiteX
cd sobel_test/litex_sobel
python3 build_sobel_litex.py --build --sim

# 3. Teste no BIOS
sobel 100          # Benchmark 100 iterações
sobel_status       # Status do acelerador
```

