#!/bin/bash

echo "🔧 Correção Final - Compatibilidade Verilator"
echo "=============================================="
echo ""

# Verificar se estamos no diretório correto
if [ ! -f ".gitattributes" ]; then
    echo "❌ Execute este script na raiz do projeto"
    exit 1
fi

echo "📋 Aplicando correção final para Verilator..."
echo ""

# Substituir testbench por versão totalmente compatível
echo "1. Criando testbench compatível com Verilator..."

cat > sobel_test/sobel_compute_tb_simple.sv << 'EOF'
/*
 * Testbench para Sobel Compute Engine
 * TOTALMENTE COMPATÍVEL COM VERILATOR
 */

`timescale 1ns/1ps

module sobel_compute_tb_simple;

    // ========================================
    // SINAIS DO DUT
    // ========================================
    
    logic        clk;
    logic        rst_n;
    logic        valid_in;
    logic [71:0] pixels_3x3;
    logic        valid_out;
    logic [15:0] gradient_x;
    logic        enable;
    logic        busy;

    // ========================================
    // INSTANCIAÇÃO DO DUT
    // ========================================
    
    sobel_compute_engine dut (
        .clk(clk),
        .rst_n(rst_n),
        .valid_in(valid_in),
        .pixels_3x3(pixels_3x3),
        .valid_out(valid_out),
        .gradient_x(gradient_x),
        .enable(enable),
        .busy(busy)
    );

    // ========================================
    // VARIÁVEIS DE CONTROLE
    // ========================================
    
    integer cycle_count = 0;
    integer test_phase = 0;
    logic test_running = 0;

    // ========================================
    // GERAÇÃO DE CLOCK
    // ========================================
    
    always #10 clk = ~clk;

    // ========================================
    // DADOS DE TESTE
    // ========================================
    
    // Teste 1: Borda vertical nítida
    logic [71:0] test_case_1 = {8'd0, 8'd0, 8'd255, 8'd0, 8'd0, 8'd255, 8'd0, 8'd0, 8'd255};
    logic [15:0] expected_1 = 16'd765;
    
    // Teste 2: Gradiente suave 
    logic [71:0] test_case_2 = {8'd10, 8'd20, 8'd30, 8'd40, 8'd50, 8'd60, 8'd70, 8'd80, 8'd90};
    logic [15:0] expected_2 = 16'd80;

    // ========================================
    // MÁQUINA DE ESTADOS DO TESTE
    // ========================================
    
    typedef enum logic [3:0] {
        INIT,
        RESET,
        SETUP,
        TEST1_SEND,
        TEST1_WAIT,
        TEST1_CHECK,
        TEST2_SEND,
        TEST2_WAIT, 
        TEST2_CHECK,
        FINISH
    } test_state_t;
    
    test_state_t state = INIT;
    integer wait_counter = 0;

    // ========================================
    // SEQUÊNCIA PRINCIPAL DE TESTE
    // ========================================
    
    always_ff @(posedge clk) begin
        case (state)
            INIT: begin
                rst_n <= 0;
                enable <= 0;
                valid_in <= 0;
                pixels_3x3 <= 72'h0;
                test_phase <= 0;
                wait_counter <= 0;
                state <= RESET;
                
                $display("========================================");
                $display("TESTE SIMPLIFICADO DO SOBEL COMPUTE ENGINE");
                $display("========================================");
            end
            
            RESET: begin
                if (wait_counter < 5) begin
                    wait_counter <= wait_counter + 1;
                end else begin
                    rst_n <= 1;
                    enable <= 1;
                    wait_counter <= 0;
                    state <= SETUP;
                    $display("Reset liberado, engine habilitado");
                end
            end
            
            SETUP: begin
                if (wait_counter < 2) begin
                    wait_counter <= wait_counter + 1;
                end else begin
                    wait_counter <= 0;
                    state <= TEST1_SEND;
                end
            end
            
            TEST1_SEND: begin
                $display("=== Teste 1: Borda Vertical ===");
                $display("Input: [0,0,255; 0,0,255; 0,0,255]");
                $display("Esperado: %0d", expected_1);
                
                pixels_3x3 <= test_case_1;
                valid_in <= 1;
                test_phase <= 1;
                state <= TEST1_WAIT;
            end
            
            TEST1_WAIT: begin
                valid_in <= 0;
                if (valid_out) begin
                    state <= TEST1_CHECK;
                end else if (wait_counter > 100) begin
                    $display("TIMEOUT no teste 1!");
                    state <= FINISH;
                end else begin
                    wait_counter <= wait_counter + 1;
                end
            end
            
            TEST1_CHECK: begin
                $display("Resultado obtido: %0d", $signed(gradient_x));
                
                if (gradient_x == expected_1) begin
                    $display("✓ TESTE 1 PASSOU!");
                end else begin
                    $display("✗ TESTE 1 FALHOU! Esperado: %0d, Obtido: %0d", 
                            expected_1, gradient_x);
                end
                
                wait_counter <= 0;
                state <= TEST2_SEND;
            end
            
            TEST2_SEND: begin
                if (wait_counter < 3) begin
                    wait_counter <= wait_counter + 1;
                end else begin
                    $display("=== Teste 2: Gradiente Suave ===");
                    $display("Input: [10,20,30; 40,50,60; 70,80,90]");
                    $display("Esperado: %0d", expected_2);
                    
                    pixels_3x3 <= test_case_2;
                    valid_in <= 1;
                    test_phase <= 2;
                    wait_counter <= 0;
                    state <= TEST2_WAIT;
                end
            end
            
            TEST2_WAIT: begin
                valid_in <= 0;
                if (valid_out) begin
                    state <= TEST2_CHECK;
                end else if (wait_counter > 100) begin
                    $display("TIMEOUT no teste 2!");
                    state <= FINISH;
                end else begin
                    wait_counter <= wait_counter + 1;
                end
            end
            
            TEST2_CHECK: begin
                $display("Resultado obtido: %0d", $signed(gradient_x));
                
                if (gradient_x == expected_2) begin
                    $display("✓ TESTE 2 PASSOU!");
                end else begin
                    $display("✗ TESTE 2 FALHOU! Esperado: %0d, Obtido: %0d", 
                            expected_2, gradient_x);
                end
                
                wait_counter <= 0;
                state <= FINISH;
            end
            
            FINISH: begin
                if (wait_counter < 5) begin
                    wait_counter <= wait_counter + 1;
                end else begin
                    $display("========================================");
                    $display("TESTE CONCLUÍDO!");
                    $display("========================================");
                    test_running <= 0;
                    $finish;
                end
            end
            
            default: begin
                state <= FINISH;
            end
        endcase
    end

    // ========================================
    // INICIALIZAÇÃO
    // ========================================
    
    initial begin
        clk = 0;
        test_running = 1;
    end

    // ========================================
    // TIMEOUT DE SEGURANÇA
    // ========================================
    
    initial begin
        #50000;  // 50µs timeout
        $display("TIMEOUT GERAL - Forçando finalização");
        $finish;
    end

endmodule
EOF

echo "✅ Testbench substituído por versão compatível"

# Verificar sintaxe
echo "2. Verificando sintaxe do novo testbench..."
cd sobel_test

if verilator --lint-only sobel_compute_tb_simple.sv sobel_compute_engine.sv 2>/dev/null; then
    echo "✅ Sintaxe verificada: OK"
else
    echo "❌ Ainda há problemas de sintaxe"
    echo "Executando verificação detalhada..."
    verilator --lint-only sobel_compute_tb_simple.sv sobel_compute_engine.sv
fi

cd ..

echo ""
echo "3. Testando compilação completa..."
cd sobel_test

# Limpar arquivos antigos
rm -rf obj_dir

# Tentar compilação simples (apenas RTL, sem testbench por enquanto)
if verilator --cc sobel_compute_engine.sv 2>/dev/null; then
    echo "✅ sobel_compute_engine.sv compila OK"
else
    echo "❌ Problema no sobel_compute_engine.sv"
fi

# Tentar compilação do testbench
if verilator --cc sobel_compute_tb_simple.sv sobel_compute_engine.sv 2>/dev/null; then
    echo "✅ Testbench compila OK"
else
    echo "❌ Problema no testbench"
    echo "Detalhes do erro:"
    verilator --cc sobel_compute_tb_simple.sv sobel_compute_engine.sv
fi

cd ..

echo ""
echo "🎯 CORREÇÃO APLICADA!"
echo ""
echo "Próximos passos:"
echo "1. Execute: ./run_projeto3.sh"
echo "2. Se ainda houver erros, verifique:"
echo "   - results/hardware_build.log"
echo "   - Versão do Verilator: $(verilator --version | head -1)"
echo ""
echo "Versão do testbench:"
echo "- ✅ Sem wait statements"  
echo "- ✅ Sem múltiplos @(posedge clk)"
echo "- ✅ Apenas máquina de estados"
echo "- ✅ Uma lógica always_ff"