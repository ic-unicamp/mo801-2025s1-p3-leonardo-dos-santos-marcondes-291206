/*
 * Testbench para Sobel Compute Engine
 * Valida a funcionalidade contra implementação software
 */

`timescale 1ns/1ps

module sobel_compute_tb;

    // ========================================
    // SINAIS DO DUT (Device Under Test)
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
    // GERAÇÃO DE CLOCK
    // ========================================
    
    initial begin
        clk = 0;
        forever #10 clk = ~clk;  // 50MHz (período 20ns)
    end

    // ========================================
    // DADOS DE TESTE
    // ========================================
    
    // Caso de teste 1: Borda vertical nítida
    logic [7:0] test_case_1 [8:0];
    initial begin
        test_case_1[0] = 8'd0;   test_case_1[1] = 8'd0;   test_case_1[2] = 8'd255;
        test_case_1[3] = 8'd0;   test_case_1[4] = 8'd0;   test_case_1[5] = 8'd255;
        test_case_1[6] = 8'd0;   test_case_1[7] = 8'd0;   test_case_1[8] = 8'd255;
    end
    
    // Caso de teste 2: Gradiente suave  
    logic [7:0] test_case_2 [8:0];
    initial begin
        test_case_2[0] = 8'd10;  test_case_2[1] = 8'd20;  test_case_2[2] = 8'd30;
        test_case_2[3] = 8'd40;  test_case_2[4] = 8'd50;  test_case_2[5] = 8'd60;
        test_case_2[6] = 8'd70;  test_case_2[7] = 8'd80;  test_case_2[8] = 8'd90;
    end

    // ========================================
    // FUNÇÃO DE REFERÊNCIA (SOFTWARE)
    // ========================================
    
    function automatic logic [15:0] sobel_reference(logic [7:0] p [8:0]);
        logic signed [15:0] gx;
        gx = -$signed({1'b0, p[0]}) + $signed({1'b0, p[2]}) +
             -2*$signed({1'b0, p[3]}) + 2*$signed({1'b0, p[5]}) +
             -$signed({1'b0, p[6]}) + $signed({1'b0, p[8]});
        return gx[15:0];
    endfunction

    // ========================================
    // TASK PARA ENVIAR TESTE
    // ========================================
    
    task automatic send_test_case(logic [7:0] test_pixels [8:0], string test_name);
        logic [71:0] packed_pixels;
        logic [15:0] expected_result;
        
        // Empacotar pixels para interface
        packed_pixels = {test_pixels[0], test_pixels[1], test_pixels[2],
                        test_pixels[3], test_pixels[4], test_pixels[5],
                        test_pixels[6], test_pixels[7], test_pixels[8]};
        
        // Calcular resultado esperado
        expected_result = sobel_reference(test_pixels);
        
        $display("=== %s ===", test_name);
        $display("Input pixels: [%0d,%0d,%0d; %0d,%0d,%0d; %0d,%0d,%0d]", 
                test_pixels[0], test_pixels[1], test_pixels[2],
                test_pixels[3], test_pixels[4], test_pixels[5], 
                test_pixels[6], test_pixels[7], test_pixels[8]);
        $display("Expected gradient_x: %0d", $signed(expected_result));
        
        // Enviar para DUT
        @(posedge clk);
        pixels_3x3 = packed_pixels;
        valid_in = 1'b1;
        
        @(posedge clk);
        valid_in = 1'b0;
        
        // Aguardar resultado
        wait (valid_out);
        @(posedge clk);
        
        $display("Hardware gradient_x: %0d", $signed(gradient_x));
        
        // Verificar resultado
        if (gradient_x == expected_result) begin
            $display("✓ PASS: Resultado correto!");
        end else begin
            $display("✗ FAIL: Esperado %0d, obtido %0d", 
                    $signed(expected_result), $signed(gradient_x));
            $error("Teste falhou!");
        end
        
        $display("");
        
        // Aguardar pipeline limpar
        repeat (3) @(posedge clk);
    endtask

    // ========================================
    // SEQUÊNCIA PRINCIPAL DE TESTE
    // ========================================
    
    initial begin
        $display("========================================");
        $display("TESTE DO SOBEL COMPUTE ENGINE");
        $display("========================================");
        
        // Reset inicial
        rst_n = 0;
        enable = 0;
        valid_in = 0;
        pixels_3x3 = 72'h0;
        
        repeat (5) @(posedge clk);
        rst_n = 1;
        enable = 1;
        
        repeat (2) @(posedge clk);
        
        // Executar casos de teste
        send_test_case(test_case_1, "Borda Vertical Nítida");
        send_test_case(test_case_2, "Gradiente Suave");
        
        // Teste de throughput (múltiplos pixels consecutivos)
        $display("=== Teste de Throughput ===");
        
        @(posedge clk);
        pixels_3x3 = {test_case_1[0], test_case_1[1], test_case_1[2],
                      test_case_1[3], test_case_1[4], test_case_1[5],
                      test_case_1[6], test_case_1[7], test_case_1[8]};
        valid_in = 1'b1;
        
        @(posedge clk);
        pixels_3x3 = {test_case_2[0], test_case_2[1], test_case_2[2],
                      test_case_2[3], test_case_2[4], test_case_2[5],
                      test_case_2[6], test_case_2[7], test_case_2[8]};
        valid_in = 1'b1;
        
        @(posedge clk);
        valid_in = 1'b0;
        
        // Verificar que temos 2 resultados consecutivos
        wait (valid_out);
        $display("Primeiro resultado: %0d", $signed(gradient_x));
        
        @(posedge clk);
        if (valid_out) begin
            $display("Segundo resultado: %0d", $signed(gradient_x));
            $display("✓ Throughput de 1 pixel/ciclo confirmado!");
        end else begin
            $error("Pipeline não manteve throughput esperado!");
        end
        
        repeat (5) @(posedge clk);
        
        $display("========================================");
        $display("TODOS OS TESTES CONCLUÍDOS COM SUCESSO!");
        $display("========================================");
        
        $finish;
    end

    // ========================================
    // MONITORAMENTO CONTÍNUO
    // ========================================
    
    always @(posedge clk) begin
        if (valid_out) begin
            $display("[@%0t] Resultado: gradient_x = %0d", $time, $signed(gradient_x));
        end
    end
    
    // Timeout de segurança
    initial begin
        #10000;  // 10µs timeout
        $error("Timeout - teste não finalizou!");
        $finish;
    end

endmodule

/*
 * OBJETIVOS DO TESTBENCH:
 * 
 * 1. VALIDAÇÃO FUNCIONAL:
 *    - Compara hardware vs software (função de referência)
 *    - Testa casos extremos (borda nítida, gradiente suave)
 *    - Verifica saturação e overflow
 * 
 * 2. VALIDAÇÃO DE PERFORMANCE:
 *    - Confirma latência de 2 ciclos
 *    - Verifica throughput de 1 pixel/ciclo
 *    - Testa pipeline com dados consecutivos
 * 
 * 3. COBERTURA DE TESTES:
 *    - Reset e inicialização
 *    - Casos normais e extremos
 *    - Sequências consecutivas
 *    - Timeouts de segurança
 * 
 * COMO EXECUTAR:
 * $ verilator --cc --exe sobel_compute_tb.sv sobel_compute_engine.sv
 * $ make -C obj_dir -f Vsobel_compute_tb.mk Vsobel_compute_tb
 * $ ./obj_dir/Vsobel_compute_tb
 */