#!/usr/bin/env python3
"""
Sobel Accelerator - LiteX Integration (Versão Corrigida)
Para usar em sobel_test/litex_sobel/sobel_accelerator.py
"""

from migen import *
from litex.soc.interconnect.csr import *
from litex.soc.interconnect import wishbone

class SobelAccelerator(Module, AutoCSR):
    """Sobel Edge Detection Accelerator para LiteX - Versão Simplificada"""
    
    def __init__(self, platform=None):
        
        # ========================================
        # CSR REGISTERS
        # ========================================
        
        self.ctrl = CSRStorage(32, description="Control Register")
        self.status = CSRStatus(32, description="Status Register") 
        self.img_size = CSRStorage(32, description="Image Size")
        self.src_addr = CSRStorage(32, description="Source Address")
        self.dst_addr = CSRStorage(32, description="Destination Address")
        
        # ========================================
        # WISHBONE MASTER INTERFACE
        # ========================================
        
        self.wishbone = wishbone.Interface()
        
        # ========================================
        # LÓGICA SIMPLIFICADA PARA DEMONSTRAÇÃO
        # ========================================
        
        # Contador de ciclos para simular processamento
        processing = Signal()
        cycle_count = Signal(16)
        start_detected = Signal()
        
        # Detectar borda de subida do bit START
        last_start = Signal()
        self.sync += last_start.eq(self.ctrl.storage[0])
        self.comb += start_detected.eq(self.ctrl.storage[0] & ~last_start)
        
        # Máquina de estados simplificada
        self.sync += [
            If(start_detected & ~processing,
                # Iniciar processamento
                processing.eq(1),
                cycle_count.eq(0)
            ).Elif(processing,
                # Simular processamento
                cycle_count.eq(cycle_count + 1),
                If(cycle_count >= 100,  # Simular 100 ciclos de processamento
                    processing.eq(0)
                )
            )
        ]
        
        # Status register
        self.comb += [
            self.status.status[0].eq(processing),      # BUSY
            self.status.status[1].eq(~processing & (cycle_count > 0)),  # DONE
            self.status.status[2].eq(0),               # ERROR (sempre 0)
            self.status.status[3].eq(processing),      # COMPUTE_BUSY
            self.status.status[31:16].eq(0x0001)       # VERSION
        ]
        
        # Auto-clear START bit (write-only behavior)
        self.sync += [
            If(self.ctrl.storage[0],
                self.ctrl.storage[0].eq(0)
            )
        ]
        
        # ========================================
        # WISHBONE INTERFACE (PLACEHOLDER)
        # ========================================
        
        # Por enquanto, interface inativa (para demonstração)
        self.comb += [
            self.wishbone.cyc.eq(0),
            self.wishbone.stb.eq(0),
            self.wishbone.we.eq(0),
            self.wishbone.adr.eq(0),
            self.wishbone.dat_w.eq(0),
            self.wishbone.sel.eq(0xF)
        ]

def add_sobel_accelerator(soc, platform=None):
    """Adicionar Sobel accelerator ao SoC LiteX"""
    
    print("🖼️ Adicionando Sobel Accelerator ao SoC...")
    
    # Criar instância
    sobel = SobelAccelerator(platform)
    
    # Adicionar ao SoC
    soc.submodules.sobel = sobel
    
    # Conectar Wishbone master ao bus principal
    soc.bus.add_master("sobel", sobel.wishbone)
    
    # Adicionar registradores CSR
    soc.add_csr("sobel")
    
    print(f"✅ Sobel Accelerator adicionado:")
    print(f"   - CSR registers mapeados")
    print(f"   - Wishbone master conectado")
    print(f"   - Versão: 0.1 (demonstração)")
    
    return sobel

# ========================================
# TESTE STANDALONE
# ========================================

if __name__ == "__main__":
    print("Sobel Accelerator LiteX Module")
    print("Versão simplificada para demonstração")
    print("")
    print("Funcionalidades:")
    print("- ✅ CSR registers (ctrl, status, img_size, src_addr, dst_addr)")
    print("- ✅ Simulação de processamento")
    print("- ✅ Interface Wishbone")
    print("- ⚠️  Hardware real não conectado (demonstração)")
    print("")
    print("Para usar:")
    print("  from sobel_accelerator import add_sobel_accelerator")
    print("  sobel = add_sobel_accelerator(soc, platform)")