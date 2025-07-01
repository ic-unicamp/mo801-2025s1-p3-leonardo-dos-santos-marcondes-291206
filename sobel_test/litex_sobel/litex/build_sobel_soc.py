#!/usr/bin/env python3
"""
LiteX SoC Build Script Corrigido - Sobel Accelerator
Build completo com medição de performance
"""

import os
import argparse
from migen import *

# LiteX imports
from litex.soc.integration.soc_core import *
from litex.soc.integration.builder import *
from litex.soc.integration.soc import SoCRegion
from litex.tools.litex_sim import Platform

# Sobel accelerator
from sobel_accelerator import add_sobel_accelerator

class SobelSoC(SoCCore):
    """SoC com Sobel Accelerator para benchmark"""
    
    def __init__(self, platform, **kwargs):
        
        # Configuração básica do SoC
        SoCCore.__init__(
            self,
            platform=platform,
            sys_clk_freq=100e6,
            cpu_type="vexriscv",
            cpu_variant="standard",
            integrated_rom_size=0x8000,   # 32KB ROM
            integrated_main_ram_size=0x20000,  # 128KB RAM
            uart_name="sim",
            **kwargs
        )
        
        # Adicionar Sobel accelerator
        print("🖼️ Adicionando Sobel Accelerator...")
        self.sobel = add_sobel_accelerator(self, platform)
        
        # Adicionar regiões de memória para teste
        self.add_memory_region("test_images", 0x40000000, 0x2000, type="cached")  # 8KB para imagens
        self.add_memory_region("test_results", 0x50000000, 0x2000, type="cached") # 8KB para resultados
        
        # Adicionar timer para medição
        self.add_timer("timer0")
        
        print(f"✅ SoC configurado:")
        print(f"   CPU: {self.cpu_type} @ {self.sys_clk_freq/1e6:.1f} MHz")
        print(f"   ROM: {self.integrated_rom_size//1024}KB")
        print(f"   RAM: {self.integrated_main_ram_size//1024}KB")

def create_test_bios():
    """Criar BIOS customizado com testes de performance"""
    
    bios_code = '''
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <generated/csr.h>
#include <generated/mem.h>
#include <libbase/timer.h>

// Configuração do teste
#define IMG_SIZE 32
#define IMG_PIXELS (IMG_SIZE * IMG_SIZE)
#define RESULT_PIXELS ((IMG_SIZE-2) * (IMG_SIZE-2))

// Endereços de memória
#define TEST_IMG_ADDR    0x40000000
#define TEST_RESULT_ADDR 0x50000000

// Implementação software do filtro Sobel (baseline)
void sobel_software(uint8_t *input, int16_t *output) {
    const int8_t sobel_x[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2}, 
        {-1, 0, 1}
    };
    
    for (int y = 1; y < IMG_SIZE - 1; y++) {
        for (int x = 1; x < IMG_SIZE - 1; x++) {
            int gx = 0;
            
            // Aplicar kernel 3x3
            for (int ky = 0; ky < 3; ky++) {
                for (int kx = 0; kx < 3; kx++) {
                    int pixel = input[(y + ky - 1) * IMG_SIZE + (x + kx - 1)];
                    gx += pixel * sobel_x[ky][kx];
                }
            }
            
            output[(y-1) * (IMG_SIZE-2) + (x-1)] = gx;
        }
    }
}

// Teste com acelerador hardware
int sobel_hardware(uint8_t *input, int16_t *output) {
    #ifdef CSR_SOBEL_BASE
    // Configurar acelerador
    sobel_img_size_write((IMG_SIZE << 16) | IMG_SIZE);
    sobel_src_addr_write((uint32_t)input);
    sobel_dst_addr_write((uint32_t)output);
    
    // Iniciar processamento
    sobel_ctrl_write(1);  // START bit
    
    // Aguardar conclusão
    int timeout = 100000;
    while (timeout-- > 0) {
        uint32_t status = sobel_status_read();
        if (status & (1 << 1)) {  // DONE
            return 1;  // Sucesso
        }
        if (status & (1 << 2)) {  // ERROR
            return -1; // Erro
        }
    }
    return 0;  // Timeout
    #else
    return -2;  // Não disponível
    #endif
}

// Gerar imagem de teste
void generate_test_image(uint8_t *image) {
    printf("Gerando imagem de teste %dx%d...", IMG_SIZE, IMG_SIZE);
    
    // Padrão de teste: quadrado central
    memset(image, 0, IMG_PIXELS);
    for (int y = 10; y < 22; y++) {
        for (int x = 10; x < 22; x++) {
            image[y * IMG_SIZE + x] = 255;
        }
    }
    
    printf(" OK\\n");
}

// Comparar resultados
int compare_results(int16_t *sw_result, int16_t *hw_result) {
    int errors = 0;
    for (int i = 0; i < RESULT_PIXELS; i++) {
        if (sw_result[i] != hw_result[i]) {
            if (errors < 5) {  // Mostrar só os primeiros erros
                printf("Erro pixel %d: SW=%d, HW=%d\\n", i, sw_result[i], hw_result[i]);
            }
            errors++;
        }
    }
    return errors;
}

// Teste principal de performance
void sobel_benchmark(int iterations) {
    printf("=== BENCHMARK SOBEL ACCELERATOR ===\\n");
    printf("Imagem: %dx%d pixels\\n", IMG_SIZE, IMG_SIZE);
    printf("Iterações: %d\\n", iterations);
    printf("\\n");
    
    // Alocar memória
    uint8_t *test_image = (uint8_t*)TEST_IMG_ADDR;
    int16_t *sw_result = (int16_t*)(TEST_RESULT_ADDR);
    int16_t *hw_result = (int16_t*)(TEST_RESULT_ADDR + 0x1000);
    
    // Gerar imagem de teste
    generate_test_image(test_image);
    
    printf("--- TESTE SOFTWARE (Baseline) ---\\n");
    timer_enable(0);
    uint64_t sw_start = timer_value(0);
    
    for (int i = 0; i < iterations; i++) {
        sobel_software(test_image, sw_result);
    }
    
    uint64_t sw_end = timer_value(0);
    uint64_t sw_cycles = sw_end - sw_start;
    
    printf("Tempo total: %lu ciclos\\n", (unsigned long)sw_cycles);
    printf("Tempo por imagem: %lu ciclos\\n", (unsigned long)(sw_cycles / iterations));
    printf("Throughput: %.2f pixels/ms @ 100MHz\\n", 
           (double)(IMG_PIXELS * iterations) / (sw_cycles / 100000.0));
    
    #ifdef CSR_SOBEL_BASE
    printf("\\n--- TESTE HARDWARE (Acelerado) ---\\n");
    
    uint64_t hw_start = timer_value(0);
    
    for (int i = 0; i < iterations; i++) {
        int result = sobel_hardware(test_image, hw_result);
        if (result != 1) {
            printf("Erro no acelerador: %d\\n", result);
            return;
        }
    }
    
    uint64_t hw_end = timer_value(0);
    uint64_t hw_cycles = hw_end - hw_start;
    
    printf("Tempo total: %lu ciclos\\n", (unsigned long)hw_cycles);
    printf("Tempo por imagem: %lu ciclos\\n", (unsigned long)(hw_cycles / iterations));
    printf("Throughput: %.2f pixels/ms @ 100MHz\\n", 
           (double)(IMG_PIXELS * iterations) / (hw_cycles / 100000.0));
    
    // Calcular speedup
    double speedup = (double)sw_cycles / hw_cycles;
    printf("\\n--- RESULTADOS ---\\n");
    printf("Speedup: %.2fx\\n", speedup);
    printf("Eficiência: %.1f%%\\n", (speedup - 1) * 100);
    
    // Validar resultados
    printf("\\n--- VALIDAÇÃO ---\\n");
    sobel_software(test_image, sw_result);
    sobel_hardware(test_image, hw_result);
    
    int errors = compare_results(sw_result, hw_result);
    if (errors == 0) {
        printf("✅ Resultados idênticos!\\n");
    } else {
        printf("❌ %d diferenças encontradas!\\n", errors);
    }
    
    #else
    printf("\\n❌ Acelerador não disponível neste build\\n");
    #endif
}

// Comandos do BIOS
static void sobel_test_cmd(int nb_params, char **params) {
    int iterations = 10;
    if (nb_params > 0) {
        iterations = atoi(params[0]);
    }
    sobel_benchmark(iterations);
}

static void sobel_status_cmd(int nb_params, char **params) {
    #ifdef CSR_SOBEL_BASE
    printf("Sobel Accelerator Status:\\n");
    printf("Base address: 0x%08x\\n", CSR_SOBEL_BASE);
    printf("Status: 0x%08x\\n", sobel_status_read());
    #else
    printf("Sobel Accelerator não disponível\\n");
    #endif
}

define_command(sobel, sobel_test_cmd, "Benchmark Sobel accelerator", "SOBEL [iterations]");
define_command(sobel_status, sobel_status_cmd, "Show Sobel status", "SOBEL_STATUS");
'''
    
    # Salvar código do BIOS
    os.makedirs("bios_extensions", exist_ok=True)
    with open("bios_extensions/sobel_benchmark.c", "w") as f:
        f.write(bios_code)
    
    print("✅ Criado: bios_extensions/sobel_benchmark.c")

def main():
    parser = argparse.ArgumentParser(description="Build Sobel SoC")
    parser.add_argument("--build", action="store_true", help="Execute build")
    parser.add_argument("--sim", action="store_true", help="Run simulation")
    
    args = parser.parse_args()
    
    print("🖼️ Projeto 3 - Sobel Accelerator LiteX")
    print("=" * 45)
    
    # Criar extensão do BIOS
    create_test_bios()
    
    # Criar plataforma de simulação
    platform = Platform()
    
    # Criar SoC
    soc = SobelSoC(platform)
    
    if args.build:
        print("\\nIniciando build...")
        
        # Configurar builder com extensão do BIOS
        builder = Builder(
            soc, 
            output_dir="build",
            compile_software=True,
            compile_gateware=False,  # Só simulação
            bios_additional_sources=["bios_extensions/sobel_benchmark.c"]
        )
        
        # Build
        vns = builder.build(run=False)
        
        print("\\n✅ Build concluído!")
        
        # Mostrar mapa de memória
        print("\\n📋 Mapa de Memória:")
        for name, region in soc.bus.regions.items():
            print(f"  {name:15s}: 0x{region.origin:08x} - 0x{region.origin + region.size - 1:08x}")
        
        if args.sim:
            print("\\n🚀 Executando simulação...")
            os.system("cd build && litex_sim --rom-init=software/bios/bios.bin")
    
    else:
        print("\\nUse --build para compilar e --sim para executar")
        print("\\nComandos de teste no BIOS:")
        print("  sobel 100       # Benchmark com 100 iterações")
        print("  sobel_status    # Status do acelerador")
    
    return 0

if __name__ == "__main__":
    exit(main())