#!/usr/bin/env python3
from litex.soc.integration.soc import SoCCore
from litex.soc.integration.builder import Builder
from litex.tools.litex_sim import Platform
from sobel_accelerator import add_sobel_accelerator

print("🖼️  Construindo SoC com Sobel Accelerator")
print("=" * 45)

# Criar plataforma de simulação
platform = Platform()

# Criar SoC básico
print("Criando SoC base...")
soc = SoCCore(
    platform=platform,
    cpu_type="vexriscv",
    cpu_variant="minimal",
    integrated_rom_size=0x8000,   # 32KB ROM
    integrated_main_ram_size=0x8000,  # 32KB RAM
    uart_name="sim"
)

# Adicionar Sobel accelerator
print("Adicionando Sobel Accelerator...")
sobel = add_sobel_accelerator(soc, platform)

# Adicionar regiões de memória para teste
from litex.soc.integration.soc import SoCRegion
soc.add_memory_region("test_src", 0x40000000, 0x1000, type="io")
soc.add_memory_region("test_dst", 0x50000000, 0x1000, type="io")

print("Configuração do SoC:")
print(f"  CPU: {soc.cpu_type}")
print(f"  Clock: {soc.sys_clk_freq/1e6:.1f} MHz")
print(f"  ROM: {soc.integrated_rom_size//1024}KB")
print(f"  RAM: {soc.integrated_main_ram_size//1024}KB")

# Build
print("\nIniciando build...")
builder = Builder(soc, output_dir="build", compile_software=True, compile_gateware=False)
vns = builder.build(run=False)

print("\n✅ Build concluído com sucesso!")
print("\nPara testar:")
print("  litex_sim build/software/bios/bios.bin")
print("  # No prompt BIOS, testar registradores Sobel")

# Mostrar mapa de memória
print("\n📋 Mapa de Memória:")
for name, region in soc.bus.regions.items():
    print(f"  {name:15s}: 0x{region.origin:08x} - 0x{region.origin + region.size - 1:08x}")
