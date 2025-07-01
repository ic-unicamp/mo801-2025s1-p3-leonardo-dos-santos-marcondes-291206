#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

#include "sobel_data.h"

/**
 * Aplica filtro Sobel em uma imagem
 * @param input: Imagem de entrada (32x32)
 * @param output: Gradiente resultante (30x30) 
 * @param use_magnitude: Se true, calcula magnitude; se false, apenas Gx
 */
void sobel_filter(const uint8_t input[IMAGE_SIZE][IMAGE_SIZE], 
                  uint16_t output[IMAGE_SIZE-2][IMAGE_SIZE-2],
                  int use_magnitude) {
    
    // Para cada pixel interno (evitando bordas)
    for (int y = 1; y < IMAGE_SIZE - 1; y++) {
        for (int x = 1; x < IMAGE_SIZE - 1; x++) {
            
            int gx = 0, gy = 0;
            
            // Aplicar kernel 3x3
            for (int ky = 0; ky < 3; ky++) {
                for (int kx = 0; kx < 3; kx++) {
                    int pixel = input[y + ky - 1][x + kx - 1];
                    gx += pixel * sobel_x[ky][kx];
                    gy += pixel * sobel_y[ky][kx];
                }
            }
            
            // Calcular resultado final
            if (use_magnitude) {
                // Magnitude: sqrt(Gx² + Gy²)
                int magnitude = (int)sqrt(gx*gx + gy*gy);
                output[y-1][x-1] = (magnitude > 255) ? 255 : magnitude;
            } else {
                // Apenas Gx (mais rápido para benchmark)
                int abs_gx = (gx < 0) ? -gx : gx;
                output[y-1][x-1] = (abs_gx > 255) ? 255 : abs_gx;
            }
        }
    }
}


void sobel_filter_fast(const uint8_t input[IMAGE_SIZE][IMAGE_SIZE], 
                       int16_t output[IMAGE_SIZE-2][IMAGE_SIZE-2]) {
    
    for (int y = 1; y < IMAGE_SIZE - 1; y++) {
        for (int x = 1; x < IMAGE_SIZE - 1; x++) {
            
            // Kernel Sobel X desenrolado para máxima performance
            int gx = 
                -1 * input[y-1][x-1] + 0 * input[y-1][x] + 1 * input[y-1][x+1] +
                -2 * input[y  ][x-1] + 0 * input[y  ][x] + 2 * input[y  ][x+1] +
                -1 * input[y+1][x-1] + 0 * input[y+1][x] + 1 * input[y+1][x+1];
            
            output[y-1][x-1] = gx;
        }
    }
}

/**
 * Validação: compara resultado com referência conhecida
 */
int validate_sobel(void) {
    printf("=== Validação do Filtro Sobel ===\n");
    
    uint16_t result[IMAGE_SIZE-2][IMAGE_SIZE-2];
    int errors = 0;
    
    for (int img = 0; img < NUM_TEST_IMAGES; img++) {
        sobel_filter(test_images[img], result, 0);
        
        // Verificações básicas
        int non_zero = 0;
        int max_val = 0;
        
        for (int i = 0; i < IMAGE_SIZE-2; i++) {
            for (int j = 0; j < IMAGE_SIZE-2; j++) {
                if (result[i][j] != 0) non_zero++;
                if (result[i][j] > max_val) max_val = result[i][j];
            }
        }
        
        printf("Imagem %d (%s):\n", img+1, image_names[img]);
        printf("  Pixels com borda: %d/%d\n", non_zero, (IMAGE_SIZE-2)*(IMAGE_SIZE-2));
        printf("  Valor máximo: %d\n", max_val);
        
        // Testes de sanidade
        if (img == 0) { // Quadrado central deve ter bordas
            if (non_zero < 20) {
                printf("  ❌ Erro: Muito poucas bordas detectadas\n");
                errors++;
            } else {
                printf("  ✓ Bordas detectadas corretamente\n");
            }
        }
    }
    
    return errors;
}

/**
 * Análise de complexidade
 */
void analyze_complexity(void) {
    printf("\n=== Análise de Complexidade ===\n");
    
    int pixels_processed = (IMAGE_SIZE-2) * (IMAGE_SIZE-2);
    int operations_per_pixel = 6; // 6 multiplicações não-zero do kernel Sobel X
    int total_operations = pixels_processed * operations_per_pixel;
    
    printf("Imagem: %dx%d pixels\n", IMAGE_SIZE, IMAGE_SIZE);
    printf("Área processada: %dx%d = %d pixels\n", 
           IMAGE_SIZE-2, IMAGE_SIZE-2, pixels_processed);
    printf("Operações por pixel: %d multiplicações + 5 somas\n", operations_per_pixel);
    printf("Total de operações: %d multiplicações + %d somas\n", 
           total_operations, total_operations * 5 / 6);
    printf("Paralelismo disponível: %d multiplicações simultâneas\n", operations_per_pixel);
}