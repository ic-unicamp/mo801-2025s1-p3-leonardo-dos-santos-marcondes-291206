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
            VL_FATAL_MT("sobel_compute_tb_simple.sv", 9, "",
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
            VL_FATAL_MT("sobel_compute_tb_simple.sv", 9, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vsobel_compute_tb_simple::_sequent__TOP__3(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsobel_compute_tb_simple::_sequent__TOP__3\n"); );
    Vsobel_compute_tb_simple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vdly__sobel_compute_tb_simple__DOT__dut__DOT__stage1_valid 
        = vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__stage1_valid;
    vlTOPp->__Vdlyvset__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v0 = 0U;
    vlTOPp->__Vdlyvset__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v6 = 0U;
    vlTOPp->__Vdly__sobel_compute_tb_simple__DOT__dut__DOT__stage1_valid 
        = ((IData)(vlTOPp->sobel_compute_tb_simple__DOT__rst_n) 
           & ((IData)(vlTOPp->sobel_compute_tb_simple__DOT__enable) 
              & (IData)(vlTOPp->sobel_compute_tb_simple__DOT__valid_in)));
    if (vlTOPp->sobel_compute_tb_simple__DOT__rst_n) {
        if (((IData)(vlTOPp->sobel_compute_tb_simple__DOT__enable) 
             & (IData)(vlTOPp->sobel_compute_tb_simple__DOT__valid_in))) {
            vlTOPp->__Vdlyvval__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v0 
                = (0xffffU & VL_MULS_III(16,16,16, (IData)(0xffffU), 
                                         vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__p
                                         [0U]));
            vlTOPp->__Vdlyvset__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v0 = 1U;
            vlTOPp->__Vdlyvval__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v1 
                = vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__p
                [2U];
            vlTOPp->__Vdlyvval__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v2 
                = (0xffffU & VL_MULS_III(16,16,16, (IData)(0xfffeU), 
                                         vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__p
                                         [3U]));
            vlTOPp->__Vdlyvval__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v3 
                = (0xffffU & VL_MULS_III(16,16,16, (IData)(2U), 
                                         vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__p
                                         [5U]));
            vlTOPp->__Vdlyvval__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v4 
                = (0xffffU & VL_MULS_III(16,16,16, (IData)(0xffffU), 
                                         vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__p
                                         [6U]));
            vlTOPp->__Vdlyvval__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v5 
                = vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__p
                [8U];
        }
    } else {
        vlTOPp->__Vdlyvset__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v6 = 1U;
    }
}

VL_INLINE_OPT void Vsobel_compute_tb_simple::_sequent__TOP__4(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsobel_compute_tb_simple::_sequent__TOP__4\n"); );
    Vsobel_compute_tb_simple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*3:0*/ __Vdly__sobel_compute_tb_simple__DOT__state;
    IData/*31:0*/ __Vdly__sobel_compute_tb_simple__DOT__wait_counter;
    IData/*31:0*/ __Vdly__sobel_compute_tb_simple__DOT__cycle_count;
    // Body
    vlTOPp->__Vdly__sobel_compute_tb_simple__DOT__rst_n 
        = vlTOPp->sobel_compute_tb_simple__DOT__rst_n;
    vlTOPp->__Vdly__sobel_compute_tb_simple__DOT__enable 
        = vlTOPp->sobel_compute_tb_simple__DOT__enable;
    __Vdly__sobel_compute_tb_simple__DOT__cycle_count 
        = vlTOPp->sobel_compute_tb_simple__DOT__cycle_count;
    __Vdly__sobel_compute_tb_simple__DOT__wait_counter 
        = vlTOPp->sobel_compute_tb_simple__DOT__wait_counter;
    __Vdly__sobel_compute_tb_simple__DOT__state = vlTOPp->sobel_compute_tb_simple__DOT__state;
    if ((8U & (IData)(vlTOPp->sobel_compute_tb_simple__DOT__state))) {
        if ((4U & (IData)(vlTOPp->sobel_compute_tb_simple__DOT__state))) {
            __Vdly__sobel_compute_tb_simple__DOT__state = 9U;
        } else {
            if ((2U & (IData)(vlTOPp->sobel_compute_tb_simple__DOT__state))) {
                __Vdly__sobel_compute_tb_simple__DOT__state = 9U;
            } else {
                if (VL_LIKELY((1U & (IData)(vlTOPp->sobel_compute_tb_simple__DOT__state)))) {
                    if (VL_LIKELY(VL_GTS_III(1,32,32, 3U, vlTOPp->sobel_compute_tb_simple__DOT__wait_counter))) {
                        __Vdly__sobel_compute_tb_simple__DOT__wait_counter 
                            = ((IData)(1U) + vlTOPp->sobel_compute_tb_simple__DOT__wait_counter);
                    } else {
                        VL_WRITEF("========================================\nTESTE CONCLUIDO!\n========================================\n");
                        VL_FINISH_MT("sobel_compute_tb_simple.sv", 216, "");
                    }
                } else {
                    VL_WRITEF("Resultado: %0d\n",16,
                              (VL_LTS_III(1,19,19, 0x7fffU, vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__sum_intermediate)
                                ? 0x7fffU : (VL_GTS_III(1,19,19, 0x78000U, vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__sum_intermediate)
                                              ? 0x8000U
                                              : (0xffffU 
                                                 & vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__sum_intermediate))));
                    if ((0x50U == (VL_LTS_III(1,19,19, 0x7fffU, vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__sum_intermediate)
                                    ? 0x7fffU : (VL_GTS_III(1,19,19, 0x78000U, vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__sum_intermediate)
                                                  ? 0x8000U
                                                  : 
                                                 (0xffffU 
                                                  & vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__sum_intermediate))))) {
                        VL_WRITEF("TESTE 2 PASSOU!\n");
                    } else {
                        VL_WRITEF("TESTE 2 FALHOU! Esperado: 80, Obtido: %0#\n",
                                  16,(VL_LTS_III(1,19,19, 0x7fffU, vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__sum_intermediate)
                                       ? 0x7fffU : 
                                      (VL_GTS_III(1,19,19, 0x78000U, vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__sum_intermediate)
                                        ? 0x8000U : 
                                       (0xffffU & vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__sum_intermediate))));
                    }
                    __Vdly__sobel_compute_tb_simple__DOT__wait_counter = 0U;
                    __Vdly__sobel_compute_tb_simple__DOT__state = 9U;
                }
            }
        }
    } else {
        if ((4U & (IData)(vlTOPp->sobel_compute_tb_simple__DOT__state))) {
            if ((2U & (IData)(vlTOPp->sobel_compute_tb_simple__DOT__state))) {
                if ((1U & (IData)(vlTOPp->sobel_compute_tb_simple__DOT__state))) {
                    vlTOPp->sobel_compute_tb_simple__DOT__valid_in = 0U;
                    if (vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__stage2_valid) {
                        __Vdly__sobel_compute_tb_simple__DOT__state = 8U;
                    } else {
                        if (VL_UNLIKELY(VL_LTS_III(1,32,32, 0x14U, vlTOPp->sobel_compute_tb_simple__DOT__wait_counter))) {
                            VL_WRITEF("TIMEOUT no teste 2!\n");
                            __Vdly__sobel_compute_tb_simple__DOT__state = 9U;
                        } else {
                            __Vdly__sobel_compute_tb_simple__DOT__wait_counter 
                                = ((IData)(1U) + vlTOPp->sobel_compute_tb_simple__DOT__wait_counter);
                        }
                    }
                } else {
                    if (VL_LIKELY(VL_GTS_III(1,32,32, 3U, vlTOPp->sobel_compute_tb_simple__DOT__wait_counter))) {
                        __Vdly__sobel_compute_tb_simple__DOT__wait_counter 
                            = ((IData)(1U) + vlTOPp->sobel_compute_tb_simple__DOT__wait_counter);
                    } else {
                        VL_WRITEF("=== Teste 2: Gradiente Suave ===\nEsperado: 80\n");
                        vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[0U] = 0x3c46505aU;
                        vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[1U] = 0x141e2832U;
                        vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[2U] = 0xaU;
                        vlTOPp->sobel_compute_tb_simple__DOT__valid_in = 1U;
                        __Vdly__sobel_compute_tb_simple__DOT__wait_counter = 0U;
                        __Vdly__sobel_compute_tb_simple__DOT__state = 7U;
                    }
                }
            } else {
                if (VL_UNLIKELY((1U & (IData)(vlTOPp->sobel_compute_tb_simple__DOT__state)))) {
                    VL_WRITEF("Resultado: %0d\n",16,
                              (VL_LTS_III(1,19,19, 0x7fffU, vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__sum_intermediate)
                                ? 0x7fffU : (VL_GTS_III(1,19,19, 0x78000U, vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__sum_intermediate)
                                              ? 0x8000U
                                              : (0xffffU 
                                                 & vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__sum_intermediate))));
                    if ((0x2fdU == (VL_LTS_III(1,19,19, 0x7fffU, vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__sum_intermediate)
                                     ? 0x7fffU : (VL_GTS_III(1,19,19, 0x78000U, vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__sum_intermediate)
                                                   ? 0x8000U
                                                   : 
                                                  (0xffffU 
                                                   & vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__sum_intermediate))))) {
                        VL_WRITEF("TESTE 1 PASSOU!\n");
                    } else {
                        VL_WRITEF("TESTE 1 FALHOU! Esperado: 765, Obtido: %0#\n",
                                  16,(VL_LTS_III(1,19,19, 0x7fffU, vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__sum_intermediate)
                                       ? 0x7fffU : 
                                      (VL_GTS_III(1,19,19, 0x78000U, vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__sum_intermediate)
                                        ? 0x8000U : 
                                       (0xffffU & vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__sum_intermediate))));
                    }
                    __Vdly__sobel_compute_tb_simple__DOT__wait_counter = 0U;
                    __Vdly__sobel_compute_tb_simple__DOT__state = 6U;
                } else {
                    vlTOPp->sobel_compute_tb_simple__DOT__valid_in = 0U;
                    if (vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__stage2_valid) {
                        __Vdly__sobel_compute_tb_simple__DOT__state = 5U;
                    } else {
                        if (VL_UNLIKELY(VL_LTS_III(1,32,32, 0x14U, vlTOPp->sobel_compute_tb_simple__DOT__wait_counter))) {
                            VL_WRITEF("TIMEOUT no teste 1!\n");
                            __Vdly__sobel_compute_tb_simple__DOT__state = 9U;
                        } else {
                            __Vdly__sobel_compute_tb_simple__DOT__wait_counter 
                                = ((IData)(1U) + vlTOPp->sobel_compute_tb_simple__DOT__wait_counter);
                        }
                    }
                }
            }
        } else {
            if ((2U & (IData)(vlTOPp->sobel_compute_tb_simple__DOT__state))) {
                if (VL_UNLIKELY((1U & (IData)(vlTOPp->sobel_compute_tb_simple__DOT__state)))) {
                    VL_WRITEF("=== Teste 1: Borda Vertical ===\nEsperado: 765\n");
                    vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[0U] = 0xff0000ffU;
                    vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[1U] = 0xff0000U;
                    vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[2U] = 0U;
                    vlTOPp->sobel_compute_tb_simple__DOT__valid_in = 1U;
                    __Vdly__sobel_compute_tb_simple__DOT__wait_counter = 0U;
                    __Vdly__sobel_compute_tb_simple__DOT__state = 4U;
                } else {
                    if (VL_GTS_III(1,32,32, 2U, vlTOPp->sobel_compute_tb_simple__DOT__wait_counter)) {
                        __Vdly__sobel_compute_tb_simple__DOT__wait_counter 
                            = ((IData)(1U) + vlTOPp->sobel_compute_tb_simple__DOT__wait_counter);
                    } else {
                        __Vdly__sobel_compute_tb_simple__DOT__wait_counter = 0U;
                        __Vdly__sobel_compute_tb_simple__DOT__state = 3U;
                    }
                }
            } else {
                if (VL_LIKELY((1U & (IData)(vlTOPp->sobel_compute_tb_simple__DOT__state)))) {
                    if (VL_LIKELY(VL_GTS_III(1,32,32, 5U, vlTOPp->sobel_compute_tb_simple__DOT__wait_counter))) {
                        __Vdly__sobel_compute_tb_simple__DOT__wait_counter 
                            = ((IData)(1U) + vlTOPp->sobel_compute_tb_simple__DOT__wait_counter);
                    } else {
                        VL_WRITEF("Reset liberado, engine habilitado\n");
                        vlTOPp->__Vdly__sobel_compute_tb_simple__DOT__rst_n = 1U;
                        vlTOPp->__Vdly__sobel_compute_tb_simple__DOT__enable = 1U;
                        __Vdly__sobel_compute_tb_simple__DOT__wait_counter = 0U;
                        __Vdly__sobel_compute_tb_simple__DOT__state = 2U;
                    }
                } else {
                    VL_WRITEF("========================================\nTESTE SOBEL COMPUTE ENGINE\n========================================\n");
                    vlTOPp->__Vdly__sobel_compute_tb_simple__DOT__rst_n = 0U;
                    vlTOPp->__Vdly__sobel_compute_tb_simple__DOT__enable = 0U;
                    vlTOPp->sobel_compute_tb_simple__DOT__valid_in = 0U;
                    vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[0U] = 0U;
                    vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[1U] = 0U;
                    vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[2U] = 0U;
                    __Vdly__sobel_compute_tb_simple__DOT__wait_counter = 0U;
                    __Vdly__sobel_compute_tb_simple__DOT__state = 1U;
                }
            }
        }
    }
    __Vdly__sobel_compute_tb_simple__DOT__cycle_count 
        = ((IData)(1U) + vlTOPp->sobel_compute_tb_simple__DOT__cycle_count);
    if (VL_UNLIKELY(VL_LTS_III(1,32,32, 0x3e8U, vlTOPp->sobel_compute_tb_simple__DOT__cycle_count))) {
        VL_WRITEF("TIMEOUT GERAL!\n");
        VL_FINISH_MT("sobel_compute_tb_simple.sv", 229, "");
    }
    vlTOPp->sobel_compute_tb_simple__DOT__state = __Vdly__sobel_compute_tb_simple__DOT__state;
    vlTOPp->sobel_compute_tb_simple__DOT__wait_counter 
        = __Vdly__sobel_compute_tb_simple__DOT__wait_counter;
    vlTOPp->sobel_compute_tb_simple__DOT__cycle_count 
        = __Vdly__sobel_compute_tb_simple__DOT__cycle_count;
    vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__p[0U] 
        = (0xffU & vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[2U]);
    vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__p[1U] 
        = (0xffU & ((vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[2U] 
                     << 8U) | (vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[1U] 
                               >> 0x18U)));
    vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__p[2U] 
        = (0xffU & ((vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[2U] 
                     << 0x10U) | (vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[1U] 
                                  >> 0x10U)));
    vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__p[3U] 
        = (0xffU & ((vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[2U] 
                     << 0x18U) | (vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[1U] 
                                  >> 8U)));
    vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__p[4U] 
        = (0xffU & vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[1U]);
    vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__p[5U] 
        = (0xffU & ((vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[1U] 
                     << 8U) | (vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[0U] 
                               >> 0x18U)));
    vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__p[6U] 
        = (0xffU & ((vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[1U] 
                     << 0x10U) | (vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[0U] 
                                  >> 0x10U)));
    vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__p[7U] 
        = (0xffU & ((vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[1U] 
                     << 0x18U) | (vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[0U] 
                                  >> 8U)));
    vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__p[8U] 
        = (0xffU & vlTOPp->sobel_compute_tb_simple__DOT__pixels_3x3[0U]);
}

VL_INLINE_OPT void Vsobel_compute_tb_simple::_sequent__TOP__5(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsobel_compute_tb_simple::_sequent__TOP__5\n"); );
    Vsobel_compute_tb_simple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__stage2_valid 
        = ((IData)(vlTOPp->sobel_compute_tb_simple__DOT__rst_n) 
           & ((IData)(vlTOPp->sobel_compute_tb_simple__DOT__enable) 
              & (IData)(vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__stage1_valid)));
    if (vlTOPp->sobel_compute_tb_simple__DOT__rst_n) {
        if (((IData)(vlTOPp->sobel_compute_tb_simple__DOT__enable) 
             & (IData)(vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__stage1_valid))) {
            vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__sum_intermediate 
                = (0x7ffffU & (((((VL_EXTENDS_II(19,16, 
                                                 vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__mult_result
                                                 [0U]) 
                                   + VL_EXTENDS_II(19,16, 
                                                   vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__mult_result
                                                   [1U])) 
                                  + VL_EXTENDS_II(19,16, 
                                                  vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__mult_result
                                                  [2U])) 
                                 + VL_EXTENDS_II(19,16, 
                                                 vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__mult_result
                                                 [3U])) 
                                + VL_EXTENDS_II(19,16, 
                                                vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__mult_result
                                                [4U])) 
                               + VL_EXTENDS_II(19,16, 
                                               vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__mult_result
                                               [5U])));
        }
    } else {
        vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__sum_intermediate = 0U;
    }
    vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__stage1_valid 
        = vlTOPp->__Vdly__sobel_compute_tb_simple__DOT__dut__DOT__stage1_valid;
    if (vlTOPp->__Vdlyvset__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v0) {
        vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__mult_result[0U] 
            = vlTOPp->__Vdlyvval__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v0;
        vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__mult_result[1U] 
            = vlTOPp->__Vdlyvval__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v1;
        vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__mult_result[2U] 
            = vlTOPp->__Vdlyvval__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v2;
        vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__mult_result[3U] 
            = vlTOPp->__Vdlyvval__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v3;
        vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__mult_result[4U] 
            = vlTOPp->__Vdlyvval__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v4;
        vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__mult_result[5U] 
            = vlTOPp->__Vdlyvval__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v5;
    }
    if (vlTOPp->__Vdlyvset__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v6) {
        vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__mult_result[0U] = 0U;
        vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__mult_result[1U] = 0U;
        vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__mult_result[2U] = 0U;
        vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__mult_result[3U] = 0U;
        vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__mult_result[4U] = 0U;
        vlTOPp->sobel_compute_tb_simple__DOT__dut__DOT__mult_result[5U] = 0U;
    }
}

VL_INLINE_OPT void Vsobel_compute_tb_simple::_sequent__TOP__6(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsobel_compute_tb_simple::_sequent__TOP__6\n"); );
    Vsobel_compute_tb_simple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->sobel_compute_tb_simple__DOT__rst_n = vlTOPp->__Vdly__sobel_compute_tb_simple__DOT__rst_n;
    vlTOPp->sobel_compute_tb_simple__DOT__enable = vlTOPp->__Vdly__sobel_compute_tb_simple__DOT__enable;
}

void Vsobel_compute_tb_simple::_eval(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsobel_compute_tb_simple::_eval\n"); );
    Vsobel_compute_tb_simple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((((IData)(vlTOPp->sobel_compute_tb_simple__DOT__clk) 
          & (~ (IData)(vlTOPp->__Vclklast__TOP__sobel_compute_tb_simple__DOT__clk))) 
         | ((~ (IData)(vlTOPp->__VinpClk__TOP__sobel_compute_tb_simple__DOT__rst_n)) 
            & (IData)(vlTOPp->__Vclklast__TOP____VinpClk__TOP__sobel_compute_tb_simple__DOT__rst_n)))) {
        vlTOPp->_sequent__TOP__3(vlSymsp);
    }
    if (((IData)(vlTOPp->sobel_compute_tb_simple__DOT__clk) 
         & (~ (IData)(vlTOPp->__Vclklast__TOP__sobel_compute_tb_simple__DOT__clk)))) {
        vlTOPp->_sequent__TOP__4(vlSymsp);
    }
    if ((((IData)(vlTOPp->sobel_compute_tb_simple__DOT__clk) 
          & (~ (IData)(vlTOPp->__Vclklast__TOP__sobel_compute_tb_simple__DOT__clk))) 
         | ((~ (IData)(vlTOPp->__VinpClk__TOP__sobel_compute_tb_simple__DOT__rst_n)) 
            & (IData)(vlTOPp->__Vclklast__TOP____VinpClk__TOP__sobel_compute_tb_simple__DOT__rst_n)))) {
        vlTOPp->_sequent__TOP__5(vlSymsp);
    }
    if (((IData)(vlTOPp->sobel_compute_tb_simple__DOT__clk) 
         & (~ (IData)(vlTOPp->__Vclklast__TOP__sobel_compute_tb_simple__DOT__clk)))) {
        vlTOPp->_sequent__TOP__6(vlSymsp);
    }
    // Final
    vlTOPp->__Vclklast__TOP__sobel_compute_tb_simple__DOT__clk 
        = vlTOPp->sobel_compute_tb_simple__DOT__clk;
    vlTOPp->__Vclklast__TOP____VinpClk__TOP__sobel_compute_tb_simple__DOT__rst_n 
        = vlTOPp->__VinpClk__TOP__sobel_compute_tb_simple__DOT__rst_n;
    vlTOPp->__VinpClk__TOP__sobel_compute_tb_simple__DOT__rst_n 
        = vlTOPp->sobel_compute_tb_simple__DOT__rst_n;
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
    __req |= ((vlTOPp->sobel_compute_tb_simple__DOT__rst_n ^ vlTOPp->__Vchglast__TOP__sobel_compute_tb_simple__DOT__rst_n));
    VL_DEBUG_IF( if(__req && ((vlTOPp->sobel_compute_tb_simple__DOT__rst_n ^ vlTOPp->__Vchglast__TOP__sobel_compute_tb_simple__DOT__rst_n))) VL_DBG_MSGF("        CHANGE: sobel_compute_tb_simple.sv:16: sobel_compute_tb_simple.rst_n\n"); );
    // Final
    vlTOPp->__Vchglast__TOP__sobel_compute_tb_simple__DOT__rst_n 
        = vlTOPp->sobel_compute_tb_simple__DOT__rst_n;
    return __req;
}

#ifdef VL_DEBUG
void Vsobel_compute_tb_simple::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsobel_compute_tb_simple::_eval_debug_assertions\n"); );
}
#endif  // VL_DEBUG
