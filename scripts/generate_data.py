#!/usr/bin/env python3
"""
Gerador de dados de teste para filtro Sobel
Adapta para estrutura com pasta src/
"""

import numpy as np
import os

def generate_test_images():
    """Gera imagens de teste com bordas conhecidas"""
    
    size = 32  # Imagem 32x32 (pequena para testes rápidos)
    
    # Imagem 1: Quadrado central (bordas verticais/horizontais)
    img1 = np.zeros((size, size), dtype=np.uint8)
    img1[10:22, 10:22] = 255  # Quadrado branco no centro
    
    # Imagem 2: Gradiente diagonal
    img2 = np.zeros((size, size), dtype=np.uint8)
    for i in range(size):
        for j in range(size):
            if i + j > size:
                img2[i, j] = 255
    
    # Imagem 3: Círculo (bordas circulares)
    img3 = np.zeros((size, size), dtype=np.uint8)
    center = size // 2
    radius = 8
    for i in range(size):
        for j in range(size):
            dist = np.sqrt((i - center)**2 + (j - center)**2)
            if dist <= radius:
                img3[i, j] = 255
    
    # Imagem 4: Padrão xadrez (bordas regulares)
    img4 = np.zeros((size, size), dtype=np.uint8)
    for i in range(size):
        for j in range(size):
            if (i // 4 + j // 4) % 2 == 0:
                img4[i, j] = 255
    
    return [img1, img2, img3, img4]

def save_as_c_header(images, filename):
    """Salva imagens como arrays C"""
    
    # Garantir que o diretório src/ existe
    os.makedirs('src', exist_ok=True)
    
    with open(filename, 'w') as f:
        f.write('#ifndef SOBEL_DATA_H\n')
        f.write('#define SOBEL_DATA_H\n\n')
        f.write('#include <stdint.h>\n\n')
        
        f.write('#define IMAGE_SIZE 32\n')
        f.write('#define NUM_TEST_IMAGES 4\n\n')
        
        # Arrays de entrada
        f.write('// Imagens de teste (32x32 pixels)\n')
        f.write('static const uint8_t test_images[NUM_TEST_IMAGES][IMAGE_SIZE][IMAGE_SIZE] = {\n')
        
        for idx, img in enumerate(images):
            f.write(f'    // Imagem {idx + 1}\n    {{\n')
            for i in range(32):
                f.write('        {')
                for j in range(32):
                    f.write(f'{img[i, j]:3d}')
                    if j < 31:
                        f.write(', ')
                f.write('}')
                if i < 31:
                    f.write(',')
                f.write('\n')
            f.write('    }')
            if idx < len(images) - 1:
                f.write(',')
            f.write('\n')
        
        f.write('};\n\n')
        
        # Kernels Sobel
        f.write('// Kernels Sobel para detecção de bordas\n')
        f.write('static const int8_t sobel_x[3][3] = {\n')
        f.write('    {-1,  0,  1},\n')
        f.write('    {-2,  0,  2},\n')
        f.write('    {-1,  0,  1}\n')
        f.write('};\n\n')
        
        f.write('static const int8_t sobel_y[3][3] = {\n')
        f.write('    {-1, -2, -1},\n')
        f.write('    { 0,  0,  0},\n')
        f.write('    { 1,  2,  1}\n')
        f.write('};\n\n')
        
        # Nomes das imagens para debug
        f.write('static const char* image_names[NUM_TEST_IMAGES] = {\n')
        f.write('    "Quadrado Central",\n')
        f.write('    "Gradiente Diagonal",\n')
        f.write('    "Círculo",\n')
        f.write('    "Padrão Xadrez"\n')
        f.write('};\n\n')
        
        f.write('#endif // SOBEL_DATA_H\n')

def main():
    print("🖼️ Gerando imagens de teste para filtro Sobel...")
    
    # Gerar imagens
    images = generate_test_images()
    
    # Salvar como header C na pasta src/
    output_file = 'src/sobel_data.h'
    save_as_c_header(images, output_file)
    print(f"✓ Dados salvos em: {output_file}")
    
    print("\n🎯 Dados de teste gerados com sucesso!")
    print("   - 4 imagens 32x32 pixels")
    print("   - Kernels Sobel X e Y") 
    print("   - Arrays prontos para C")
    print("   - Arquivo salvo em src/sobel_data.h")

if __name__ == "__main__":
    main()