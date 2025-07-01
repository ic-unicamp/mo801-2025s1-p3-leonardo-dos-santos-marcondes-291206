/*
 * Testbench Simplificado para Sobel Compute Engine
 * Compatível com Verilator
 */

`timescale 1ns/1ps

module sobel_compute_tb;

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
    logic [15:0] expected_result;
    logic test_running = 0;

    // ========================================
    // GERAÇÃO DE CLOCK
    // ========================================
    
    /* verilator lint_off STMTDLY */
    always begin
        #10 clk = ~clk;  // 50MHz
    end
    /* verilator lint_on STMTDLY */

    // ========================================
    // DADOS DE TESTE
    // ========================================
    
    // Teste 1: Borda vertical nítida
    // Pixels: [0,0,255; 0,0,255; 0,0,255]
    // Esperado: -0 + 255 + (-2*0) + (2*255) + (-0) + 255 = 765
    logic [71:0] test_case_1 = {8'd0, 8'd0, 8'd255, 8'd0, 8'd0, 8'd255, 8'd0, 8'd0, 8'd255};
    logic [15:0] expected_1 = 16'd765;
    
    // Teste 2: Gradiente suave 
    // Pixels: [10,20,30; 40,50,60; 70,80,90]
    // Esperado: -10 + 30 + (-2*40) + (2*60) + (-70) + 90 = -10+30-80+120-70+90 = 80
    logic [71:0] test_case_2 = {8'd10, 8'd20, 8'd30, 8'd40, 8'd50, 8'd60, 8'd70, 8'd80, 8'd90};
    logic [15:0] expected_2 = 16'd80;

    // ========================================
    // SEQUÊNCIA PRINCIPAL DE TESTE
    // ========================================
    
    initial begin
        // Inicialização
        clk = 0;
        rst_n = 0;
        enable = 0;
        valid_in = 0;
        pixels_3x3 = 72'h0;
        test_running = 1;
        
        $display("========================================");
        $display("TESTE SIMPLIFICADO DO SOBEL COMPUTE ENGINE");
        $display("========================================");
    end

    // ========================================
    // MÁQUINA DE ESTADOS DO TESTE
    // ========================================
    
    always_ff @(posedge clk) begin
        if (!test_running) begin
            // Teste finalizado
        end else begin
            cycle_count <= cycle_count + 1;
            
            case (cycle_count)
                // Ciclos 0-4: Reset
                0, 1, 2, 3, 4: begin
                    rst_n <= 0;
                    enable <= 0;
                end
                
                // Ciclo 5: Liberar reset
                5: begin
                    rst_n <= 1;
                    enable <= 1;
                    $display("Reset liberado, engine habilitado");
                end
                
                // Ciclo 7: Teste 1 - Borda vertical
                7: begin
                    pixels_3x3 <= test_case_1;
                    valid_in <= 1;
                    expected_result <= expected_1;
                    test_phase <= 1;
                    $display("=== Teste 1: Borda Vertical ===");
                    $display("Input: [0,0,255; 0,0,255; 0,0,255]");
                    $display("Esperado: %0d", expected_1);
                end
                
                // Ciclo 8: Parar valid_in
                8: begin
                    valid_in <= 0;
                end
                
                // Ciclo 15: Teste 2 - Gradiente suave
                15: begin
                    pixels_3x3 <= test_case_2;
                    valid_in <= 1;
                    expected_result <= expected_2;
                    test_phase <= 2;
                    $display("=== Teste 2: Gradiente Suave ===");
                    $display("Input: [10,20,30; 40,50,60; 70,80,90]");
                    $display("Esperado: %0d", expected_2);
                end
                
                // Ciclo 16: Parar valid_in
                16: begin
                    valid_in <= 0;
                end
                
                // Ciclo 25: Finalizar
                25: begin
                    $display("========================================");
                    $display("TESTE CONCLUÍDO!");
                    $display("========================================");
                    test_running <= 0;
                    $finish;
                end
            endcase
        end
    end

    // ========================================
    // VERIFICAÇÃO DE RESULTADOS
    // ========================================
    
    always_ff @(posedge clk) begin
        if (valid_out && test_running) begin
            $display("[@%0d] Resultado obtido: %0d", cycle_count, $signed(gradient_x));
            
            if (test_phase == 1) begin
                if (gradient_x == expected_1) begin
                    $display("✓ TESTE 1 PASSOU!");
                end else begin
                    $display("✗ TESTE 1 FALHOU! Esperado: %0d, Obtido: %0d", 
                            expected_1, gradient_x);
                end
            end else if (test_phase == 2) begin
                if (gradient_x == expected_2) begin
                    $display("✓ TESTE 2 PASSOU!");
                end else begin
                    $display("✗ TESTE 2 FALHOU! Esperado: %0d, Obtido: %0d", 
                            expected_2, gradient_x);
                end
            end
        end
    end

    // ========================================
    // MONITORAMENTO DE SINAIS
    // ========================================
    
    always_ff @(posedge clk) begin
        if (test_running && cycle_count > 5) begin
            $display("[@%0d] valid_in=%b, valid_out=%b, busy=%b, gradient_x=%0d", 
                    cycle_count, valid_in, valid_out, busy, $signed(gradient_x));
        end
    end

    // ========================================
    // TIMEOUT DE SEGURANÇA
    // ========================================
    
    always_ff @(posedge clk) begin
        if (cycle_count > 100) begin
            $display("TIMEOUT - Forçando finalização");
            $finish;
        end
    end

endmodule

/*
 * DIFERENÇAS DESTA VERSÃO:
 * 
 * 1. SEM WAIT STATEMENTS: Usa contador de ciclos
 * 2. SEM MÚLTIPLOS @: Uma máquina de estados simples
 * 3. SEM TASKS COMPLEXAS: Lógica linear
 * 4. COMPATÍVEL VERILATOR: Apenas construtos suportados
 * 
 * COMO TESTAR:
 * $ verilator --cc --exe --build sobel_compute_tb_simple.sv sobel_compute_engine.sv
 * $ ./obj_dir/Vsobel_compute_tb_simple
 */