#!/usr/bin/env python3
"""
Build script simplificado para Sobel SoC - VERSÃO CORRIGIDA
"""

import os

def simple_litex_test():
    """Teste básico sem dependências complexas"""
    print("🖼️ Build Simplificado LiteX - Sobel Accelerator")
    print("=" * 45)
    
    try:
        # Criar estrutura de diretórios
        os.makedirs("build/software/bios", exist_ok=True)
        os.makedirs("build/software/include/generated", exist_ok=True)
        
        # Criar BIOS mock
        with open("build/software/bios/bios.bin", "wb") as f:
            f.write(b"MOCK_BIOS_FOR_SOBEL_TEST" * 100)
        
        # Criar header CSR mock
        with open("build/software/include/generated/csr.h", "w") as f:
            f.write('''
/* CSR Mock para Sobel Accelerator */
#ifndef CSR_H
#define CSR_H

#define CSR_SOBEL_BASE 0x82000000

static inline void sobel_ctrl_write(unsigned int value) { }
static inline unsigned int sobel_status_read(void) { return 0x02; }
static inline void sobel_img_size_write(unsigned int value) { }
static inline void sobel_src_addr_write(unsigned int value) { }
static inline void sobel_dst_addr_write(unsigned int value) { }

#endif
            ''')
        
        print("✅ Build mock concluído com sucesso!")
        return True
        
    except Exception as e:
        print(f"❌ Erro: {e}")
        return False

if __name__ == "__main__":
    simple_litex_test()
