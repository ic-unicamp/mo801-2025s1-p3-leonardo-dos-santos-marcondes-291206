// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsobel_compute_tb_simple.h for the primary calling header

#include "Vsobel_compute_tb_simple.h"
#include "Vsobel_compute_tb_simple__Syms.h"

//==========

void Vsobel_compute_tb_simple::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vsobel_compute_tb_simple::eval\n"); );
    Vsobel_compute_tb_simple__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vsobel_compute_tb_simple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("sobel_compute_tb_simple.sv", 8, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vsobel_compute_tb_simple::_eval_initial_loop(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("sobel_compute_tb_simple.sv", 8, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vsobel_compute_tb_simple::_combo__TOP__1(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsobel_compute_tb_simple::_combo__TOP__1\n"); );
    Vsobel_compute_tb_simple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->sobel_compute_tb__DOT__clk = (1U & (~ (IData)(vlTOPp->sobel_compute_tb__DOT__clk)));
}

VL_INLINE_OPT void Vsobel_compute_tb_simple::_sequent__TOP__3(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsobel_compute_tb_simple::_sequent__TOP__3\n"); );
    Vsobel_compute_tb_simple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__sobel_compute_tb__DOT__cycle_count 
        = vlTOPp->sobel_compute_tb__DOT__cycle_count;
    if (VL_UNLIKELY(VL_LTS_III(1,32,32, 0x64U, vlTOPp->sobel_compute_tb__DOT__cycle_count))) {
        VL_WRITEF("TIMEOUT - For\303\247ando finaliza\303\247\303\243o\n");
        VL_FINISH_MT("sobel_compute_tb_simple.sv", 203, "");
    }
    if (VL_UNLIKELY(((IData)(vlTOPp->sobel_compute_tb__DOT__dut__DOT__stage2_valid) 
                     & (IData)(vlTOPp->sobel_compute_tb__DOT__test_running)))) {
        VL_WRITEF("[@%0d] Resultado obtido: %0d\n",
                  32,vlTOPp->sobel_compute_tb__DOT__cycle_count,
                  16,(VL_LTS_III(1,19,19, 0x7fffU, vlTOPp->sobel_compute_tb__DOT__dut__DOT__sum_intermediate)
                       ? 0x7fffU : (VL_GTS_III(1,19,19, 0x78000U, vlTOPp->sobel_compute_tb__DOT__dut__DOT__sum_intermediate)
                                     ? 0x8000U : (0xffffU 
                                                  & vlTOPp->sobel_compute_tb__DOT__dut__DOT__sum_intermediate))));
        if ((1U == vlTOPp->sobel_compute_tb__DOT__test_phase)) {
            if ((0x2fdU == (VL_LTS_III(1,19,19, 0x7fffU, vlTOPp->sobel_compute_tb__DOT__dut__DOT__sum_intermediate)
                             ? 0x7fffU : (VL_GTS_III(1,19,19, 0x78000U, vlTOPp->sobel_compute_tb__DOT__dut__DOT__sum_intermediate)
                                           ? 0x8000U
                                           : (0xffffU 
                                              & vlTOPp->sobel_compute_tb__DOT__dut__DOT__sum_intermediate))))) {
                VL_WRITEF("\342\234\223 TESTE 1 PASSOU!\n");
            } else {
                VL_WRITEF("\342\234\227 TESTE 1 FALHOU! Esperado: 765, Obtido: %0#\n",
                          16,(VL_LTS_III(1,19,19, 0x7fffU, vlTOPp->sobel_compute_tb__DOT__dut__DOT__sum_intermediate)
                               ? 0x7fffU : (VL_GTS_III(1,19,19, 0x78000U, vlTOPp->sobel_compute_tb__DOT__dut__DOT__sum_intermediate)
                                             ? 0x8000U
                                             : (0xffffU 
                                                & vlTOPp->sobel_compute_tb__DOT__dut__DOT__sum_intermediate))));
            }
        } else {
            if ((2U == vlTOPp->sobel_compute_tb__DOT__test_phase)) {
                if ((0x50U == (VL_LTS_III(1,19,19, 0x7fffU, vlTOPp->sobel_compute_tb__DOT__dut__DOT__sum_intermediate)
                                ? 0x7fffU : (VL_GTS_III(1,19,19, 0x78000U, vlTOPp->sobel_compute_tb__DOT__dut__DOT__sum_intermediate)
                                              ? 0x8000U
                                              : (0xffffU 
                                                 & vlTOPp->sobel_compute_tb__DOT__dut__DOT__sum_intermediate))))) {
                    VL_WRITEF("\342\234\223 TESTE 2 PASSOU!\n");
                } else {
                    VL_WRITEF("\342\234\227 TESTE 2 FALHOU! Esperado: 80, Obtido: %0#\n",
                              16,(VL_LTS_III(1,19,19, 0x7fffU, vlTOPp->sobel_compute_tb__DOT__dut__DOT__sum_intermediate)
                                   ? 0x7fffU : (VL_GTS_III(1,19,19, 0x78000U, vlTOPp->sobel_compute_tb__DOT__dut__DOT__sum_intermediate)
                                                 ? 0x8000U
                                                 : 
                                                (0xffffU 
                                                 & vlTOPp->sobel_compute_tb__DOT__dut__DOT__sum_intermediate))));
                }
            }
        }
    }
    if (VL_UNLIKELY(((IData)(vlTOPp->sobel_compute_tb__DOT__test_running) 
                     & VL_LTS_III(1,32,32, 5U, vlTOPp->sobel_compute_tb__DOT__cycle_count)))) {
        VL_WRITEF("[@%0d] valid_in=%b, valid_out=%b, busy=%b, gradient_x=%0d\n",
                  32,vlTOPp->sobel_compute_tb__DOT__cycle_count,
                  1,(IData)(vlTOPp->sobel_compute_tb__DOT__valid_in),
                  1,vlTOPp->sobel_compute_tb__DOT__dut__DOT__stage2_valid,
                  1,(((IData)(vlTOPp->sobel_compute_tb__DOT__valid_in) 
                      | (IData)(vlTOPp->sobel_compute_tb__DOT__dut__DOT__stage1_valid)) 
                     | (IData)(vlTOPp->sobel_compute_tb__DOT__dut__DOT__stage2_valid)),
                  16,(VL_LTS_III(1,19,19, 0x7fffU, vlTOPp->sobel_compute_tb__DOT__dut__DOT__sum_intermediate)
                       ? 0x7fffU : (VL_GTS_III(1,19,19, 0x78000U, vlTOPp->sobel_compute_tb__DOT__dut__DOT__sum_intermediate)
                                     ? 0x8000U : (0xffffU 
                                                  & vlTOPp->sobel_compute_tb__DOT__dut__DOT__sum_intermediate))));
    }
}

VL_INLINE_OPT void Vsobel_compute_tb_simple::_sequent__TOP__4(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsobel_compute_tb_simple::_sequent__TOP__4\n"); );
    Vsobel_compute_tb_simple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*0:0*/ __Vdlyvset__sobel_compute_tb__DOT__dut__DOT__mult_result__v0;
    CData/*0:0*/ __Vdlyvset__sobel_compute_tb__DOT__dut__DOT__mult_result__v6;
    SData/*15:0*/ __Vdlyvval__sobel_compute_tb__DOT__dut__DOT__mult_result__v0;
    SData/*15:0*/ __Vdlyvval__sobel_compute_tb__DOT__dut__DOT__mult_result__v1;
    SData/*15:0*/ __Vdlyvval__sobel_compute_tb__DOT__dut__DOT__mult_result__v2;
    SData/*15:0*/ __Vdlyvval__sobel_compute_tb__DOT__dut__DOT__mult_result__v3;
    SData/*15:0*/ __Vdlyvval__sobel_compute_tb__DOT__dut__DOT__mult_result__v4;
    SData/*15:0*/ __Vdlyvval__sobel_compute_tb__DOT__dut__DOT__mult_result__v5;
    // Body
    __Vdlyvset__sobel_compute_tb__DOT__dut__DOT__mult_result__v0 = 0U;
    __Vdlyvset__sobel_compute_tb__DOT__dut__DOT__mult_result__v6 = 0U;
    vlTOPp->sobel_compute_tb__DOT__dut__DOT__stage2_valid 
        = ((IData)(vlTOPp->sobel_compute_tb__DOT__rst_n) 
           & ((IData)(vlTOPp->sobel_compute_tb__DOT__enable) 
              & (IData)(vlTOPp->sobel_compute_tb__DOT__dut__DOT__stage1_valid)));
    if (vlTOPp->sobel_compute_tb__DOT__rst_n) {
        if (((IData)(vlTOPp->sobel_compute_tb__DOT__enable) 
             & (IData)(vlTOPp->sobel_compute_tb__DOT__dut__DOT__stage1_valid))) {
            vlTOPp->sobel_compute_tb__DOT__dut__DOT__sum_intermediate 
                = (0x7ffffU & (((((VL_EXTENDS_II(19,16, 
                                                 vlTOPp->sobel_compute_tb__DOT__dut__DOT__mult_result
                                                 [0U]) 
                                   + VL_EXTENDS_II(19,16, 
                                                   vlTOPp->sobel_compute_tb__DOT__dut__DOT__mult_result
                                                   [1U])) 
                                  + VL_EXTENDS_II(19,16, 
                                                  vlTOPp->sobel_compute_tb__DOT__dut__DOT__mult_result
                                                  [2U])) 
                                 + VL_EXTENDS_II(19,16, 
                                                 vlTOPp->sobel_compute_tb__DOT__dut__DOT__mult_result
                                                 [3U])) 
                                + VL_EXTENDS_II(19,16, 
                                                vlTOPp->sobel_compute_tb__DOT__dut__DOT__mult_result
                                                [4U])) 
                               + VL_EXTENDS_II(19,16, 
                                               vlTOPp->sobel_compute_tb__DOT__dut__DOT__mult_result
                                               [5U])));
        }
    } else {
        vlTOPp->sobel_compute_tb__DOT__dut__DOT__sum_intermediate = 0U;
    }
    if (vlTOPp->sobel_compute_tb__DOT__rst_n) {
        if (((IData)(vlTOPp->sobel_compute_tb__DOT__enable) 
             & (IData)(vlTOPp->sobel_compute_tb__DOT__valid_in))) {
            __Vdlyvval__sobel_compute_tb__DOT__dut__DOT__mult_result__v0 
                = (0xffffU & VL_MULS_III(16,16,16, (IData)(0xffffU), 
                                         vlTOPp->sobel_compute_tb__DOT__dut__DOT__p
                                         [0U]));
            __Vdlyvset__sobel_compute_tb__DOT__dut__DOT__mult_result__v0 = 1U;
            __Vdlyvval__sobel_compute_tb__DOT__dut__DOT__mult_result__v1 
                = vlTOPp->sobel_compute_tb__DOT__dut__DOT__p
                [2U];
            __Vdlyvval__sobel_compute_tb__DOT__dut__DOT__mult_result__v2 
                = (0xffffU & VL_MULS_III(16,16,16, (IData)(0xfffeU), 
                                         vlTOPp->sobel_compute_tb__DOT__dut__DOT__p
                                         [3U]));
            __Vdlyvval__sobel_compute_tb__DOT__dut__DOT__mult_result__v3 
                = (0xffffU & VL_MULS_III(16,16,16, (IData)(2U), 
                                         vlTOPp->sobel_compute_tb__DOT__dut__DOT__p
                                         [5U]));
            __Vdlyvval__sobel_compute_tb__DOT__dut__DOT__mult_result__v4 
                = (0xffffU & VL_MULS_III(16,16,16, (IData)(0xffffU), 
                                         vlTOPp->sobel_compute_tb__DOT__dut__DOT__p
                                         [6U]));
            __Vdlyvval__sobel_compute_tb__DOT__dut__DOT__mult_result__v5 
                = vlTOPp->sobel_compute_tb__DOT__dut__DOT__p
                [8U];
        }
    } else {
        __Vdlyvset__sobel_compute_tb__DOT__dut__DOT__mult_result__v6 = 1U;
    }
    if (__Vdlyvset__sobel_compute_tb__DOT__dut__DOT__mult_result__v0) {
        vlTOPp->sobel_compute_tb__DOT__dut__DOT__mult_result[0U] 
            = __Vdlyvval__sobel_compute_tb__DOT__dut__DOT__mult_result__v0;
        vlTOPp->sobel_compute_tb__DOT__dut__DOT__mult_result[1U] 
            = __Vdlyvval__sobel_compute_tb__DOT__dut__DOT__mult_result__v1;
        vlTOPp->sobel_compute_tb__DOT__dut__DOT__mult_result[2U] 
            = __Vdlyvval__sobel_compute_tb__DOT__dut__DOT__mult_result__v2;
        vlTOPp->sobel_compute_tb__DOT__dut__DOT__mult_result[3U] 
            = __Vdlyvval__sobel_compute_tb__DOT__dut__DOT__mult_result__v3;
        vlTOPp->sobel_compute_tb__DOT__dut__DOT__mult_result[4U] 
            = __Vdlyvval__sobel_compute_tb__DOT__dut__DOT__mult_result__v4;
        vlTOPp->sobel_compute_tb__DOT__dut__DOT__mult_result[5U] 
            = __Vdlyvval__sobel_compute_tb__DOT__dut__DOT__mult_result__v5;
    }
    if (__Vdlyvset__sobel_compute_tb__DOT__dut__DOT__mult_result__v6) {
        vlTOPp->sobel_compute_tb__DOT__dut__DOT__mult_result[0U] = 0U;
        vlTOPp->sobel_compute_tb__DOT__dut__DOT__mult_result[1U] = 0U;
        vlTOPp->sobel_compute_tb__DOT__dut__DOT__mult_result[2U] = 0U;
        vlTOPp->sobel_compute_tb__DOT__dut__DOT__mult_result[3U] = 0U;
        vlTOPp->sobel_compute_tb__DOT__dut__DOT__mult_result[4U] = 0U;
        vlTOPp->sobel_compute_tb__DOT__dut__DOT__mult_result[5U] = 0U;
    }
    vlTOPp->sobel_compute_tb__DOT__dut__DOT__stage1_valid 
        = ((IData)(vlTOPp->sobel_compute_tb__DOT__rst_n) 
           & ((IData)(vlTOPp->sobel_compute_tb__DOT__enable) 
              & (IData)(vlTOPp->sobel_compute_tb__DOT__valid_in)));
}

VL_INLINE_OPT void Vsobel_compute_tb_simple::_sequent__TOP__6(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsobel_compute_tb_simple::_sequent__TOP__6\n"); );
    Vsobel_compute_tb_simple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->sobel_compute_tb__DOT__test_running) {
        vlTOPp->__Vdly__sobel_compute_tb__DOT__cycle_count 
            = ((IData)(1U) + vlTOPp->sobel_compute_tb__DOT__cycle_count);
        if ((((((0U == vlTOPp->sobel_compute_tb__DOT__cycle_count) 
                | (1U == vlTOPp->sobel_compute_tb__DOT__cycle_count)) 
               | (2U == vlTOPp->sobel_compute_tb__DOT__cycle_count)) 
              | (3U == vlTOPp->sobel_compute_tb__DOT__cycle_count)) 
             | (4U == vlTOPp->sobel_compute_tb__DOT__cycle_count))) {
            vlTOPp->sobel_compute_tb__DOT__rst_n = 0U;
            vlTOPp->sobel_compute_tb__DOT__enable = 0U;
        } else {
            if (VL_UNLIKELY((5U == vlTOPp->sobel_compute_tb__DOT__cycle_count))) {
                VL_WRITEF("Reset liberado, engine habilitado\n");
                vlTOPp->sobel_compute_tb__DOT__rst_n = 1U;
                vlTOPp->sobel_compute_tb__DOT__enable = 1U;
            } else {
                if (VL_UNLIKELY((7U == vlTOPp->sobel_compute_tb__DOT__cycle_count))) {
                    VL_WRITEF("=== Teste 1: Borda Vertical ===\nInput: [0,0,255; 0,0,255; 0,0,255]\nEsperado: 765\n");
                    vlTOPp->sobel_compute_tb__DOT__pixels_3x3[0U] = 0xff0000ffU;
                    vlTOPp->sobel_compute_tb__DOT__pixels_3x3[1U] = 0xff0000U;
                    vlTOPp->sobel_compute_tb__DOT__pixels_3x3[2U] = 0U;
                    vlTOPp->sobel_compute_tb__DOT__valid_in = 1U;
                    vlTOPp->sobel_compute_tb__DOT__test_phase = 1U;
                } else {
                    if ((8U == vlTOPp->sobel_compute_tb__DOT__cycle_count)) {
                        vlTOPp->sobel_compute_tb__DOT__valid_in = 0U;
                    } else {
                        if (VL_UNLIKELY((0xfU == vlTOPp->sobel_compute_tb__DOT__cycle_count))) {
                            VL_WRITEF("=== Teste 2: Gradiente Suave ===\nInput: [10,20,30; 40,50,60; 70,80,90]\nEsperado: 80\n");
                            vlTOPp->sobel_compute_tb__DOT__pixels_3x3[0U] = 0x3c46505aU;
                            vlTOPp->sobel_compute_tb__DOT__pixels_3x3[1U] = 0x141e2832U;
                            vlTOPp->sobel_compute_tb__DOT__pixels_3x3[2U] = 0xaU;
                            vlTOPp->sobel_compute_tb__DOT__valid_in = 1U;
                            vlTOPp->sobel_compute_tb__DOT__test_phase = 2U;
                        } else {
                            if ((0x10U == vlTOPp->sobel_compute_tb__DOT__cycle_count)) {
                                vlTOPp->sobel_compute_tb__DOT__valid_in = 0U;
                            } else {
                                if (VL_UNLIKELY((0x19U 
                                                 == vlTOPp->sobel_compute_tb__DOT__cycle_count))) {
                                    VL_WRITEF("========================================\nTESTE CONCLU\303\215DO!\n========================================\n");
                                    vlTOPp->sobel_compute_tb__DOT__test_running = 0U;
                                    VL_FINISH_MT("sobel_compute_tb_simple.sv", 153, "");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->sobel_compute_tb__DOT__cycle_count = vlTOPp->__Vdly__sobel_compute_tb__DOT__cycle_count;
    vlTOPp->sobel_compute_tb__DOT__dut__DOT__p[0U] 
        = (0xffU & vlTOPp->sobel_compute_tb__DOT__pixels_3x3[2U]);
    vlTOPp->sobel_compute_tb__DOT__dut__DOT__p[1U] 
        = (0xffU & ((vlTOPp->sobel_compute_tb__DOT__pixels_3x3[2U] 
                     << 8U) | (vlTOPp->sobel_compute_tb__DOT__pixels_3x3[1U] 
                               >> 0x18U)));
    vlTOPp->sobel_compute_tb__DOT__dut__DOT__p[2U] 
        = (0xffU & ((vlTOPp->sobel_compute_tb__DOT__pixels_3x3[2U] 
                     << 0x10U) | (vlTOPp->sobel_compute_tb__DOT__pixels_3x3[1U] 
                                  >> 0x10U)));
    vlTOPp->sobel_compute_tb__DOT__dut__DOT__p[3U] 
        = (0xffU & ((vlTOPp->sobel_compute_tb__DOT__pixels_3x3[2U] 
                     << 0x18U) | (vlTOPp->sobel_compute_tb__DOT__pixels_3x3[1U] 
                                  >> 8U)));
    vlTOPp->sobel_compute_tb__DOT__dut__DOT__p[4U] 
        = (0xffU & vlTOPp->sobel_compute_tb__DOT__pixels_3x3[1U]);
    vlTOPp->sobel_compute_tb__DOT__dut__DOT__p[5U] 
        = (0xffU & ((vlTOPp->sobel_compute_tb__DOT__pixels_3x3[1U] 
                     << 8U) | (vlTOPp->sobel_compute_tb__DOT__pixels_3x3[0U] 
                               >> 0x18U)));
    vlTOPp->sobel_compute_tb__DOT__dut__DOT__p[6U] 
        = (0xffU & ((vlTOPp->sobel_compute_tb__DOT__pixels_3x3[1U] 
                     << 0x10U) | (vlTOPp->sobel_compute_tb__DOT__pixels_3x3[0U] 
                                  >> 0x10U)));
    vlTOPp->sobel_compute_tb__DOT__dut__DOT__p[7U] 
        = (0xffU & ((vlTOPp->sobel_compute_tb__DOT__pixels_3x3[1U] 
                     << 0x18U) | (vlTOPp->sobel_compute_tb__DOT__pixels_3x3[0U] 
                                  >> 8U)));
    vlTOPp->sobel_compute_tb__DOT__dut__DOT__p[8U] 
        = (0xffU & vlTOPp->sobel_compute_tb__DOT__pixels_3x3[0U]);
}

void Vsobel_compute_tb_simple::_eval(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsobel_compute_tb_simple::_eval\n"); );
    Vsobel_compute_tb_simple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
    if (((IData)(vlTOPp->__VinpClk__TOP__sobel_compute_tb__DOT__clk) 
         & (~ (IData)(vlTOPp->__Vclklast__TOP____VinpClk__TOP__sobel_compute_tb__DOT__clk)))) {
        vlTOPp->_sequent__TOP__3(vlSymsp);
    }
    if ((((IData)(vlTOPp->__VinpClk__TOP__sobel_compute_tb__DOT__clk) 
          & (~ (IData)(vlTOPp->__Vclklast__TOP____VinpClk__TOP__sobel_compute_tb__DOT__clk))) 
         | ((~ (IData)(vlTOPp->__VinpClk__TOP__sobel_compute_tb__DOT__rst_n)) 
            & (IData)(vlTOPp->__Vclklast__TOP____VinpClk__TOP__sobel_compute_tb__DOT__rst_n)))) {
        vlTOPp->_sequent__TOP__4(vlSymsp);
    }
    if (((IData)(vlTOPp->__VinpClk__TOP__sobel_compute_tb__DOT__clk) 
         & (~ (IData)(vlTOPp->__Vclklast__TOP____VinpClk__TOP__sobel_compute_tb__DOT__clk)))) {
        vlTOPp->_sequent__TOP__6(vlSymsp);
    }
    // Final
    vlTOPp->__Vclklast__TOP____VinpClk__TOP__sobel_compute_tb__DOT__clk 
        = vlTOPp->__VinpClk__TOP__sobel_compute_tb__DOT__clk;
    vlTOPp->__Vclklast__TOP____VinpClk__TOP__sobel_compute_tb__DOT__rst_n 
        = vlTOPp->__VinpClk__TOP__sobel_compute_tb__DOT__rst_n;
    vlTOPp->__VinpClk__TOP__sobel_compute_tb__DOT__clk 
        = vlTOPp->sobel_compute_tb__DOT__clk;
    vlTOPp->__VinpClk__TOP__sobel_compute_tb__DOT__rst_n 
        = vlTOPp->sobel_compute_tb__DOT__rst_n;
}

VL_INLINE_OPT QData Vsobel_compute_tb_simple::_change_request(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsobel_compute_tb_simple::_change_request\n"); );
    Vsobel_compute_tb_simple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vsobel_compute_tb_simple::_change_request_1(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsobel_compute_tb_simple::_change_request_1\n"); );
    Vsobel_compute_tb_simple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    __req |= ((vlTOPp->sobel_compute_tb__DOT__clk ^ vlTOPp->__Vchglast__TOP__sobel_compute_tb__DOT__clk)
         | (vlTOPp->sobel_compute_tb__DOT__rst_n ^ vlTOPp->__Vchglast__TOP__sobel_compute_tb__DOT__rst_n));
    VL_DEBUG_IF( if(__req && ((vlTOPp->sobel_compute_tb__DOT__clk ^ vlTOPp->__Vchglast__TOP__sobel_compute_tb__DOT__clk))) VL_DBG_MSGF("        CHANGE: sobel_compute_tb_simple.sv:14: sobel_compute_tb.clk\n"); );
    VL_DEBUG_IF( if(__req && ((vlTOPp->sobel_compute_tb__DOT__rst_n ^ vlTOPp->__Vchglast__TOP__sobel_compute_tb__DOT__rst_n))) VL_DBG_MSGF("        CHANGE: sobel_compute_tb_simple.sv:15: sobel_compute_tb.rst_n\n"); );
    // Final
    vlTOPp->__Vchglast__TOP__sobel_compute_tb__DOT__clk 
        = vlTOPp->sobel_compute_tb__DOT__clk;
    vlTOPp->__Vchglast__TOP__sobel_compute_tb__DOT__rst_n 
        = vlTOPp->sobel_compute_tb__DOT__rst_n;
    return __req;
}

#ifdef VL_DEBUG
void Vsobel_compute_tb_simple::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsobel_compute_tb_simple::_eval_debug_assertions\n"); );
}
#endif  // VL_DEBUG
