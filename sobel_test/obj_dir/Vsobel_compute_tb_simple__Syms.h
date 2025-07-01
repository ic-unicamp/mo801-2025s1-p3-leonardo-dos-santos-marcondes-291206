// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef _VSOBEL_COMPUTE_TB_SIMPLE__SYMS_H_
#define _VSOBEL_COMPUTE_TB_SIMPLE__SYMS_H_  // guard

#include "verilated_heavy.h"

// INCLUDE MODULE CLASSES
#include "Vsobel_compute_tb_simple.h"

// SYMS CLASS
class Vsobel_compute_tb_simple__Syms : public VerilatedSyms {
  public:
    
    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_didInit;
    
    // SUBCELL STATE
    Vsobel_compute_tb_simple*      TOPp;
    
    // CREATORS
    Vsobel_compute_tb_simple__Syms(Vsobel_compute_tb_simple* topp, const char* namep);
    ~Vsobel_compute_tb_simple__Syms() {}
    
    // METHODS
    inline const char* name() { return __Vm_namep; }
    
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
