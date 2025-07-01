#!/usr/bin/env python3
from litex.tools.litex_sim import *
from litex.soc.integration.soc_core import *
from litex.soc.integration.builder import *

print('🚀 Construindo SoC @ 100MHz (fixado)...')

# Criar plataforma
platform = Platform()

# IMPORTANTE: Adicionar clock domain antes de criar SoC
from litex.soc.cores.clock import *
platform.add_clock_constraint(platform.clk, 100e6)

# Criar SoC com clk_freq
soc = SoCCore(
    platform=platform,
    clk_freq=100e6,
    cpu_type='vexriscv',
    cpu_variant='minimal', 
    integrated_rom_size=0x8000,
    integrated_main_ram_size=0x8000,
    uart_name='sim'
)

print(f'Frequência configurada: {soc.clk_freq/1e6:.0f} MHz')

builder = Builder(soc, output_dir='build_100mhz_fixed')
builder.build(run=False)
print('✅ SoC @ 100MHz construído completamente!')
