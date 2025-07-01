// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsobel_compute_tb_simple.h for the primary calling header

#include "Vsobel_compute_tb_simple.h"
#include "Vsobel_compute_tb_simple__Syms.h"

//==========

VL_CTOR_IMP(Vsobel_compute_tb_simple) {
    Vsobel_compute_tb_simple__Syms* __restrict vlSymsp = __VlSymsp = new Vsobel_compute_tb_simple__Syms(this, name());
    Vsobel_compute_tb_simple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vsobel_compute_tb_simple::__Vconfigure(Vsobel_compute_tb_simple__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-9);
    Verilated::timeprecision(-12);
}

Vsobel_compute_tb_simple::~Vsobel_compute_tb_simple() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vsobel_compute_tb_simple::_initial__TOP__1(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsobel_compute_tb_simple::_initial__TOP__1\n"); );
    Vsobel_compute_tb_simple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->sobel_compute_tb_simple__DOT__clk = 0U;
    VL_WRITEF("Iniciando teste...\n");
    vlTOPp->sobel_compute_tb_simple__DOT__cycle_count = 0U;
    vlTOPp->sobel_compute_tb_simple__DOT__state = 0U;
    vlTOPp->sobel_compute_tb_simple__DOT__wait_counter = 0U;
}

void Vsobel_compute_tb_simple::_settle__TOP__2(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsobel_compute_tb_simple::_settle__TOP__2\n"); );
    Vsobel_compute_tb_simple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->sobel_compute_tb_simple__DOT__clk = 0U;
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

void Vsobel_compute_tb_simple::_eval_initial(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsobel_compute_tb_simple::_eval_initial\n"); );
    Vsobel_compute_tb_simple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_initial__TOP__1(vlSymsp);
    vlTOPp->__Vclklast__TOP__sobel_compute_tb_simple__DOT__clk = 0U;
    vlTOPp->__Vclklast__TOP____VinpClk__TOP__sobel_compute_tb_simple__DOT__rst_n 
        = vlTOPp->__VinpClk__TOP__sobel_compute_tb_simple__DOT__rst_n;
}

void Vsobel_compute_tb_simple::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsobel_compute_tb_simple::final\n"); );
    // Variables
    Vsobel_compute_tb_simple__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vsobel_compute_tb_simple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vsobel_compute_tb_simple::_eval_settle(Vsobel_compute_tb_simple__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsobel_compute_tb_simple::_eval_settle\n"); );
    Vsobel_compute_tb_simple* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
}

void Vsobel_compute_tb_simple::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsobel_compute_tb_simple::_ctor_var_reset\n"); );
    // Body
    sobel_compute_tb_simple__DOT__clk = VL_RAND_RESET_I(1);
    sobel_compute_tb_simple__DOT__rst_n = VL_RAND_RESET_I(1);
    sobel_compute_tb_simple__DOT__valid_in = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(72, sobel_compute_tb_simple__DOT__pixels_3x3);
    sobel_compute_tb_simple__DOT__enable = VL_RAND_RESET_I(1);
    sobel_compute_tb_simple__DOT__cycle_count = VL_RAND_RESET_I(32);
    sobel_compute_tb_simple__DOT__state = VL_RAND_RESET_I(4);
    sobel_compute_tb_simple__DOT__wait_counter = VL_RAND_RESET_I(32);
    { int __Vi0=0; for (; __Vi0<9; ++__Vi0) {
            sobel_compute_tb_simple__DOT__dut__DOT__p[__Vi0] = VL_RAND_RESET_I(8);
    }}
    { int __Vi0=0; for (; __Vi0<6; ++__Vi0) {
            sobel_compute_tb_simple__DOT__dut__DOT__mult_result[__Vi0] = VL_RAND_RESET_I(16);
    }}
    sobel_compute_tb_simple__DOT__dut__DOT__stage1_valid = VL_RAND_RESET_I(1);
    sobel_compute_tb_simple__DOT__dut__DOT__sum_intermediate = VL_RAND_RESET_I(19);
    sobel_compute_tb_simple__DOT__dut__DOT__stage2_valid = VL_RAND_RESET_I(1);
    __Vdly__sobel_compute_tb_simple__DOT__rst_n = VL_RAND_RESET_I(1);
    __Vdly__sobel_compute_tb_simple__DOT__enable = VL_RAND_RESET_I(1);
    __Vdlyvval__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v0 = VL_RAND_RESET_I(16);
    __Vdlyvset__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v0 = 0;
    __Vdlyvval__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v1 = VL_RAND_RESET_I(16);
    __Vdlyvval__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v2 = VL_RAND_RESET_I(16);
    __Vdlyvval__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v3 = VL_RAND_RESET_I(16);
    __Vdlyvval__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v4 = VL_RAND_RESET_I(16);
    __Vdlyvval__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v5 = VL_RAND_RESET_I(16);
    __Vdlyvset__sobel_compute_tb_simple__DOT__dut__DOT__mult_result__v6 = 0;
    __Vdly__sobel_compute_tb_simple__DOT__dut__DOT__stage1_valid = VL_RAND_RESET_I(1);
    __VinpClk__TOP__sobel_compute_tb_simple__DOT__rst_n = VL_RAND_RESET_I(1);
    __Vchglast__TOP__sobel_compute_tb_simple__DOT__rst_n = VL_RAND_RESET_I(1);
}
