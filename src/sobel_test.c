#define _POSIX_C_SOURCE 199309L  // Para clock_gettime

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

#include "sobel_data.h"

// Declarações das funções do sobel_filter.c
void sobel_filter(const uint8_t input[IMAGE_SIZE][IMAGE_SIZE], 
                  uint16_t output[IMAGE_SIZE-2][IMAGE_SIZE-2], int use_magnitude);
void sobel_filter_fast(const uint8_t input[IMAGE_SIZE][IMAGE_SIZE], 
                       int16_t output[IMAGE_SIZE-2][IMAGE_SIZE-2]);
int validate_sobel(void);
void analyze_complexity(void);

// Sistema de medição multiplataforma
#ifdef __riscv
#define read_csr(reg) ({ unsigned long __tmp; asm volatile ("csrr %0, " #reg : "=r" (__tmp)); __tmp; })
static inline uint64_t get_cycles(void) { return read_csr(mcycle); }
static inline void memory_barrier(void) {
    asm volatile("fence.i" ::: "memory");
    asm volatile("fence" ::: "memory");
}
#else
static inline uint64_t get_cycles(void) {
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
        // Fallback para sistemas sem clock_gettime
        return (uint64_t)clock() * 1000000ULL / CLOCKS_PER_SEC;
    }
    return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
}
static inline void memory_barrier(void) {
    __asm__ __volatile__("" ::: "memory");
}
#endif

/**
 * Benchmark principal
 */
void benchmark_sobel(int iterations) {
    printf("\n=== Benchmark do Filtro Sobel ===\n");
    printf("Executando %d iterações por imagem...\n", iterations);
    
    int16_t output[IMAGE_SIZE-2][IMAGE_SIZE-2];
    volatile int16_t dummy_sum = 0; // Anti-otimização
    
    uint64_t total_cycles = 0;
    int total_images = 0;
    
    for (int img = 0; img < NUM_TEST_IMAGES; img++) {
        uint64_t img_cycles = 0;
        
        for (int iter = 0; iter < iterations; iter++) {
            memory_barrier();
            uint64_t start = get_cycles();
            
            sobel_filter_fast(test_images[img], output);
            
            memory_barrier();
            uint64_t end = get_cycles();
            
            img_cycles += (end - start);
            
            // Anti-otimização: usar resultado
            dummy_sum += output[15][15];
        }
        
        uint64_t avg_cycles = img_cycles / iterations;
        total_cycles += img_cycles;
        total_images += iterations;
        
        #ifdef __riscv
        printf("Imagem %d (%s): %lu ciclos/imagem\n", img+1, image_names[img], avg_cycles);
        #else
        printf("Imagem %d (%s): %lu ns/imagem\n", img+1, image_names[img], avg_cycles);
        #endif
    }
    
    uint64_t overall_avg = total_cycles / total_images;
    int pixels_per_image = (IMAGE_SIZE-2) * (IMAGE_SIZE-2);
    uint64_t cycles_per_pixel = overall_avg / pixels_per_image;
    
    printf("\nResultados Consolidados:\n");
    #ifdef __riscv
    printf("  Tempo médio por imagem: %lu ciclos\n", overall_avg);
    printf("  Tempo por pixel: %lu ciclos\n", cycles_per_pixel);
    printf("  Throughput: %.2f Mpixels/s @ 50MHz\n", 
           50.0 / cycles_per_pixel);
    #else
    printf("  Tempo médio por imagem: %lu ns\n", overall_avg);
    printf("  Tempo por pixel: %lu ns\n", cycles_per_pixel);
    printf("  Throughput: %.2f Mpixels/s\n", 
           1000.0 / cycles_per_pixel);
    #endif
    
    printf("Anti-otimização checksum: %d\n", dummy_sum);
}

/**
 * Teste de diferentes níveis de otimização
 */
void test_optimization_levels(void) {
    printf("\n=== Análise de Otimizações ===\n");
    printf("Compile com diferentes flags para comparar:\n");
    printf("  -O0: Sem otimização\n");
    printf("  -O1: Otimização básica\n");
    printf("  -O2: Otimização padrão\n");
    printf("  -O3: Máxima otimização\n");
    printf("  -Ofast: Otimização agressiva\n");
    
    #ifdef __GNUC__
    printf("\nInformações do compilador:\n");
    printf("  GCC versão: %d.%d.%d\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
    #ifdef __OPTIMIZE__
    printf("  Otimização: Ativada\n");
    #else
    printf("  Otimização: Desativada\n");
    #endif
    #endif
}

/**
 * Estimativa de speedup esperado
 */
void estimate_speedup(void) {
    printf("\n=== Estimativa de Speedup Hardware ===\n");
    
    int ops_per_pixel = 6; // multiplicações do kernel Sobel
    int pixels = (IMAGE_SIZE-2) * (IMAGE_SIZE-2);
    int total_mults = ops_per_pixel * pixels;
    
    printf("Análise teórica:\n");
    printf("  Multiplicações por pixel: %d\n", ops_per_pixel);
    printf("  Pixels processados: %d\n", pixels);
    printf("  Total de multiplicações: %d\n", total_mults);
    
    printf("\nSoftware (sequencial):\n");
    printf("  Tempo por multiplicação: ~2-5ns\n");
    printf("  Tempo total estimado: %d-%.0fns\n", 
           total_mults * 2, total_mults * 5.0);
    
    printf("\nHardware (paralelo):\n");
    printf("  Pipeline de 3 ciclos @ 50MHz\n");
    printf("  Tempo por imagem: ~60ns\n");
    printf("  Speedup esperado: 10-50x\n");
    
    printf("\nConsiderações para implementação:\n");
    printf("  - Pipeline permite processamento de 1 pixel/ciclo\n");
    printf("  - Paralelização de 6 multiplicadores por pixel\n");
    printf("  - Buffer interno para janela 3x3 deslizante\n");
    printf("  - Interface DMA para transferência eficiente\n");
}

int main(void) {
    printf("🖼️ Projeto 3 - Filtro Sobel (Baseline)\n");
    printf("=====================================\n\n");
    
    // Análise de complexidade
    analyze_complexity();
    
    // Validação funcional
    printf("\n");
    if (validate_sobel() > 0) {
        printf("❌ Falhas na validação!\n");
        return 1;
    }
    
    // Benchmark principal
    #ifdef __riscv
    int iterations = 1000;  // Menos iterações para embedded
    #else
    int iterations = 10000; // Mais iterações para development
    #endif
    
    benchmark_sobel(iterations);
    
    // Análises adicionais
    test_optimization_levels();
    estimate_speedup();
    
    printf("\n✅ Benchmark baseline concluído!\n");
    
    return 0;
}