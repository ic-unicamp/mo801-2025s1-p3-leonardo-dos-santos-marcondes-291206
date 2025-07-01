// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vsobel_compute_tb_simple__Syms.h"
#include "Vsobel_compute_tb_simple.h"



// FUNCTIONS
Vsobel_compute_tb_simple__Syms::Vsobel_compute_tb_simple__Syms(Vsobel_compute_tb_simple* topp, const char* namep)
    // Setup locals
    : __Vm_namep(namep)
    , __Vm_didInit(false)
    // Setup submodule names
{
    // Pointer to top level
    TOPp = topp;
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOPp->__Vconfigure(this, true);
}
