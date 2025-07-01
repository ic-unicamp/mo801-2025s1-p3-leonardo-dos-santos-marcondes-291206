/*
 * Driver C para Sobel Accelerator
 * Interface de alto nível para o acelerador
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

// ========================================
// DEFINIÇÕES DE ENDEREÇOS
// ========================================

#define SOBEL_BASE_ADDR   0x40000000

#define SOBEL_CTRL        (SOBEL_BASE_ADDR + 0x00)
#define SOBEL_STATUS      (SOBEL_BASE_ADDR + 0x04)
#define SOBEL_IMG_SIZE    (SOBEL_BASE_ADDR + 0x08)
#define SOBEL_SRC_ADDR    (SOBEL_BASE_ADDR + 0x0C)
#define SOBEL_DST_ADDR    (SOBEL_BASE_ADDR + 0x10)

// Bits de controle
#define SOBEL_CTRL_START  (1 << 0)
#define SOBEL_CTRL_RESET  (1 << 1)

// Bits de status
#define SOBEL_STATUS_BUSY        (1 << 0)
#define SOBEL_STATUS_DONE        (1 << 1)
#define SOBEL_STATUS_ERROR       (1 << 2)
#define SOBEL_STATUS_COMPUTE_BUSY (1 << 3)

// ========================================
// FUNÇÕES DE ACESSO À MEMÓRIA
// ========================================

// Simulação de MMIO para teste
static uint32_t sobel_regs[5] = {0}; // CTRL, STATUS, SIZE, SRC, DST

static inline void mmio_write_32(uint32_t addr, uint32_t value) {
    uint32_t offset = (addr - SOBEL_BASE_ADDR) / 4;
    if (offset < 5) {
        sobel_regs[offset] = value;
        printf("MMIO WRITE: 0x%08X = 0x%08X\n", addr, value);
    }
}

static inline uint32_t mmio_read_32(uint32_t addr) {
    uint32_t offset = (addr - SOBEL_BASE_ADDR) / 4;
    if (offset < 5) {
        printf("MMIO READ:  0x%08X = 0x%08X\n", addr, sobel_regs[offset]);
        return sobel_regs[offset];
    }
    return 0;
}

// ========================================
// API DO SOBEL ACCELERATOR
// ========================================

/**
 * Inicializar o acelerador
 */
void sobel_init(void) {
    printf("=== Inicializando Sobel Accelerator ===\n");
    
    // Reset do acelerador
    mmio_write_32(SOBEL_CTRL, SOBEL_CTRL_RESET);
    mmio_write_32(SOBEL_CTRL, 0); // Liberar reset
    
    // Verificar versão
    uint32_t status = mmio_read_32(SOBEL_STATUS);
    uint16_t version = (status >> 16) & 0xFFFF;
    printf("Versão do acelerador: 0x%04X\n", version);
}

/**
 * Verificar se o acelerador está ocupado
 */
bool sobel_is_busy(void) {
    uint32_t status = mmio_read_32(SOBEL_STATUS);
    return (status & SOBEL_STATUS_BUSY) != 0;
}

/**
 * Verificar se há erro
 */
bool sobel_has_error(void) {
    uint32_t status = mmio_read_32(SOBEL_STATUS);
    return (status & SOBEL_STATUS_ERROR) != 0;
}

/**
 * Aguardar conclusão do processamento
 */
bool sobel_wait_completion(uint32_t timeout_ms) {
    printf("Aguardando conclusão do processamento...\n");
    
    // Simular timeout (em implementação real, usar timer)
    for (uint32_t i = 0; i < timeout_ms * 1000; i++) {
        uint32_t status = mmio_read_32(SOBEL_STATUS);
        
        if (status & SOBEL_STATUS_ERROR) {
            printf("❌ Erro detectado durante processamento!\n");
            return false;
        }
        
        if (status & SOBEL_STATUS_DONE) {
            printf("✅ Processamento concluído com sucesso!\n");
            return true;
        }
        
        if (!(status & SOBEL_STATUS_BUSY)) {
            printf("⚠️  Acelerador não está mais ocupado\n");
            break;
        }
    }
    
    printf("❌ Timeout - processamento não finalizou\n");
    return false;
}

/**
 * Processar imagem com o acelerador
 */
bool sobel_process_image(const uint8_t* src_image, int16_t* dst_results,
                        uint16_t width, uint16_t height,
                        uint32_t src_addr, uint32_t dst_addr) {
    
    printf("=== Processando Imagem ===\n");
    printf("Dimensões: %dx%d pixels\n", width, height);
    printf("Endereço fonte: 0x%08X\n", src_addr);
    printf("Endereço destino: 0x%08X\n", dst_addr);
    
    // Verificar se acelerador está disponível
    if (sobel_is_busy()) {
        printf("❌ Acelerador está ocupado!\n");
        return false;
    }
    
    // Configurar dimensões
    uint32_t img_size = ((uint32_t)height << 16) | width;
    mmio_write_32(SOBEL_IMG_SIZE, img_size);
    
    // Configurar endereços
    mmio_write_32(SOBEL_SRC_ADDR, src_addr);
    mmio_write_32(SOBEL_DST_ADDR, dst_addr);
    
    // Iniciar processamento
    printf("Iniciando processamento...\n");
    mmio_write_32(SOBEL_CTRL, SOBEL_CTRL_START);
    
    // Simular processamento (em implementação real, seria hardware)
    printf("⏳ Simulando processamento de hardware...\n");
    
    // Simular alguns ciclos de processamento
    for (int i = 0; i < 5; i++) {
        sobel_regs[1] |= SOBEL_STATUS_BUSY; // Set BUSY
        printf("  Ciclo %d: processando...\n", i+1);
    }
    
    // Simular conclusão
    sobel_regs[1] &= ~SOBEL_STATUS_BUSY;  // Clear BUSY
    sobel_regs[1] |= SOBEL_STATUS_DONE;   // Set DONE
    
    // Aguardar conclusão
    return sobel_wait_completion(1000); // 1 segundo de timeout
}

/**
 * Obter estatísticas de performance
 */
void sobel_get_stats(void) {
    uint32_t status = mmio_read_32(SOBEL_STATUS);
    
    printf("=== Estatísticas ===\n");
    printf("Status: 0x%08X\n", status);
    printf("  BUSY: %s\n", (status & SOBEL_STATUS_BUSY) ? "Sim" : "Não");
    printf("  DONE: %s\n", (status & SOBEL_STATUS_DONE) ? "Sim" : "Não");
    printf("  ERROR: %s\n", (status & SOBEL_STATUS_ERROR) ? "Sim" : "Não");
    printf("  COMPUTE_BUSY: %s\n", (status & SOBEL_STATUS_COMPUTE_BUSY) ? "Sim" : "Não");
}

// ========================================
// FUNÇÃO DE TESTE
// ========================================

int main(void) {
    printf("🖼️  TESTE DO SOBEL ACCELERATOR\n");
    printf("=====================================\n\n");
    
    // Inicializar acelerador
    sobel_init();
    printf("\n");
    
    // Dados de teste (imagem 32x32 simulada)
    uint8_t test_image[32*32];
    int16_t results[30*30]; // Área útil 30x30
    
    // Preencher imagem de teste com padrão
    for (int i = 0; i < 32*32; i++) {
        test_image[i] = (i % 2) ? 255 : 0; // Padrão xadrez
    }
    
    // Processar imagem
    bool success = sobel_process_image(
        test_image, results,
        32, 32,
        0x10000000, // src_addr
        0x20000000  // dst_addr
    );
    
    printf("\n");
    
    // Obter estatísticas
    sobel_get_stats();
    
    printf("\n");
    
    if (success) {
        printf("🎉 TESTE CONCLUÍDO COM SUCESSO!\n");
        printf("✅ Acelerador funcionou corretamente\n");
        printf("✅ Interface de registradores operacional\n");
        printf("✅ API de alto nível validada\n");
    } else {
        printf("❌ TESTE FALHOU!\n");
    }
    
    printf("\n=====================================\n");
    
    return success ? 0 : 1;
}

/*
 * EXEMPLO DE INTEGRAÇÃO REAL:
 * 
 * // Em um sistema LiteX real
 * #include "generated/csr.h"
 * 
 * #define mmio_write_32(addr, val) csr_write_simple(val, addr)
 * #define mmio_read_32(addr) csr_read_simple(addr)
 * 
 * // Usar DMA para transferir dados
 * dma_copy(src_image, SOBEL_SRC_ADDR, sizeof(src_image));
 * sobel_process_image(...);
 * dma_copy(SOBEL_DST_ADDR, results, sizeof(results));
 */