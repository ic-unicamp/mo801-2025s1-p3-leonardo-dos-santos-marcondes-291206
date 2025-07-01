// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VSOBEL_COMPUTE_TB_SIMPLE_H_
#define _VSOBEL_COMPUTE_TB_SIMPLE_H_  // guard

#include "verilated_heavy.h"

//==========

class Vsobel_compute_tb_simple__Syms;

//----------

VL_MODULE(Vsobel_compute_tb_simple) {
  public:
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    CData/*0:0*/ sobel_compute_tb__DOT__clk;
    CData/*0:0*/ sobel_compute_tb__DOT__rst_n;
    CData/*0:0*/ sobel_compute_tb__DOT__valid_in;
    CData/*0:0*/ sobel_compute_tb__DOT__enable;
    CData/*0:0*/ sobel_compute_tb__DOT__test_running;
    CData/*0:0*/ sobel_compute_tb__DOT__dut__DOT__stage1_valid;
    CData/*0:0*/ sobel_compute_tb__DOT__dut__DOT__stage2_valid;
    WData/*71:0*/ sobel_compute_tb__DOT__pixels_3x3[3];
    IData/*31:0*/ sobel_compute_tb__DOT__cycle_count;
    IData/*31:0*/ sobel_compute_tb__DOT__test_phase;
    IData/*18:0*/ sobel_compute_tb__DOT__dut__DOT__sum_intermediate;
    CData/*7:0*/ sobel_compute_tb__DOT__dut__DOT__p[9];
    SData/*15:0*/ sobel_compute_tb__DOT__dut__DOT__mult_result[6];
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*0:0*/ __VinpClk__TOP__sobel_compute_tb__DOT__clk;
    CData/*0:0*/ __VinpClk__TOP__sobel_compute_tb__DOT__rst_n;
    CData/*0:0*/ __Vclklast__TOP____VinpClk__TOP__sobel_compute_tb__DOT__clk;
    CData/*0:0*/ __Vclklast__TOP____VinpClk__TOP__sobel_compute_tb__DOT__rst_n;
    CData/*0:0*/ __Vchglast__TOP__sobel_compute_tb__DOT__clk;
    CData/*0:0*/ __Vchglast__TOP__sobel_compute_tb__DOT__rst_n;
    IData/*31:0*/ __Vdly__sobel_compute_tb__DOT__cycle_count;
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vsobel_compute_tb_simple__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vsobel_compute_tb_simple);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vsobel_compute_tb_simple(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vsobel_compute_tb_simple();
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vsobel_compute_tb_simple__Syms* symsp, bool first);
  private:
    static QData _change_request(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp);
    static QData _change_request_1(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__1(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _initial__TOP__5(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__3(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp);
    static void _sequent__TOP__4(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp);
    static void _sequent__TOP__6(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp);
    static void _settle__TOP__7(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
