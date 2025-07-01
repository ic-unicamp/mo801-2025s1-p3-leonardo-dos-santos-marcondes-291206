/*
 * Testbench C++ para Sobel Compute Engine - VERSÃO CORRIGIDA
 */

#include <iostream>
#include "Vsobel_compute_tb.h"
#include "verilated.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    
    Vsobel_compute_tb* tb = new Vsobel_compute_tb;
    
    std::cout << "Teste Sobel Compute Engine (C++)" << std::endl;
    
    // Executar simulação
    for (int i = 0; i < 10000 && !Verilated::gotFinish(); i++) {
        tb->eval();
    }
    
    delete tb;
    return 0;
}
