/*
 * Testbench para Sobel Compute Engine
 * COMPATÍVEL COM VERILATOR v4.038
 */

/* verilator lint_off STMTDLY */
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
    // GERAÇÃO DE CLOCK - SEM DELAY
    // ========================================
    
    always begin
        clk = 0;
        clk = #10 1;
        clk = #10 0;
    end

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
        INIT        = 4'h0,
        RESET       = 4'h1,
        SETUP       = 4'h2,
        TEST1_SEND  = 4'h3,
        TEST1_WAIT  = 4'h4,
        TEST1_CHECK = 4'h5,
        TEST2_SEND  = 4'h6,
        TEST2_WAIT  = 4'h7,
        TEST2_CHECK = 4'h8,
        FINISH      = 4'h9
    } test_state_t;
    
    test_state_t state = INIT;
    integer wait_counter = 0;

    // ========================================
    // SEQUÊNCIA PRINCIPAL DE TESTE
    // ========================================
    
    always_ff @(posedge clk) begin
        case (state)
            INIT: begin
                rst_n <= 1'b0;
                enable <= 1'b0;
                valid_in <= 1'b0;
                pixels_3x3 <= 72'h0;
                test_phase <= 0;
                wait_counter <= 0;
                state <= RESET;
                
                $display("========================================");
                $display("TESTE SOBEL COMPUTE ENGINE");
                $display("========================================");
            end
            
            RESET: begin
                if (wait_counter < 5) begin
                    wait_counter <= wait_counter + 1;
                end else begin
                    rst_n <= 1'b1;
                    enable <= 1'b1;
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
                $display("Esperado: %0d", expected_1);
                
                pixels_3x3 <= test_case_1;
                valid_in <= 1'b1;
                test_phase <= 1;
                wait_counter <= 0;
                state <= TEST1_WAIT;
            end
            
            TEST1_WAIT: begin
                valid_in <= 1'b0;
                if (valid_out) begin
                    state <= TEST1_CHECK;
                end else if (wait_counter > 20) begin
                    $display("TIMEOUT no teste 1!");
                    state <= FINISH;
                end else begin
                    wait_counter <= wait_counter + 1;
                end
            end
            
            TEST1_CHECK: begin
                $display("Resultado: %0d", $signed(gradient_x));
                
                if (gradient_x == expected_1) begin
                    $display("TESTE 1 PASSOU!");
                end else begin
                    $display("TESTE 1 FALHOU! Esperado: %0d, Obtido: %0d", 
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
                    $display("Esperado: %0d", expected_2);
                    
                    pixels_3x3 <= test_case_2;
                    valid_in <= 1'b1;
                    test_phase <= 2;
                    wait_counter <= 0;
                    state <= TEST2_WAIT;
                end
            end
            
            TEST2_WAIT: begin
                valid_in <= 1'b0;
                if (valid_out) begin
                    state <= TEST2_CHECK;
                end else if (wait_counter > 20) begin
                    $display("TIMEOUT no teste 2!");
                    state <= FINISH;
                end else begin
                    wait_counter <= wait_counter + 1;
                end
            end
            
            TEST2_CHECK: begin
                $display("Resultado: %0d", $signed(gradient_x));
                
                if (gradient_x == expected_2) begin
                    $display("TESTE 2 PASSOU!");
                end else begin
                    $display("TESTE 2 FALHOU! Esperado: %0d, Obtido: %0d", 
                            expected_2, gradient_x);
                end
                
                wait_counter <= 0;
                state <= FINISH;
            end
            
            FINISH: begin
                if (wait_counter < 3) begin
                    wait_counter <= wait_counter + 1;
                end else begin
                    $display("========================================");
                    $display("TESTE CONCLUIDO!");
                    $display("========================================");
                    test_running <= 1'b0;
                    $finish;
                end
            end
            
            default: begin
                state <= FINISH;
            end
        endcase
        
        // Contador global de segurança
        cycle_count <= cycle_count + 1;
        if (cycle_count > 1000) begin
            $display("TIMEOUT GERAL!");
            $finish;
        end
    end

    // ========================================
    // INICIALIZAÇÃO
    // ========================================
    
    initial begin
        clk = 1'b0;
        test_running = 1'b1;
        $display("Iniciando teste...");
    end

endmodule
/* verilator lint_on STMTDLY */
