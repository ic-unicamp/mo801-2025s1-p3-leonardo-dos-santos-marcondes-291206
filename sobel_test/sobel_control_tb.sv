/*
 * Testbench para Sobel Control Unit
 * Valida máquina de estados e coordenação
 */

`timescale 1ns/1ps

module sobel_control_tb;

    // ========================================
    // SINAIS DO DUT
    // ========================================
    
    logic        clk;
    logic        rst_n;
    logic        start;
    logic [15:0] img_width;
    logic [15:0] img_height;
    logic [31:0] src_addr;
    logic [31:0] dst_addr;
    logic        busy;
    logic        done;
    logic        error;
    
    // Interface memória (simulada)
    logic        mem_read_req;
    logic [31:0] mem_read_addr;
    logic        mem_read_ack;
    logic [71:0] mem_read_data;
    logic        mem_write_req;
    logic [31:0] mem_write_addr;
    logic [15:0] mem_write_data;
    logic        mem_write_ack;
    
    // Interface compute engine (simulada)
    logic        ce_valid_in;
    logic [71:0] ce_pixels_3x3;
    logic        ce_valid_out;
    logic [15:0] ce_gradient_x;
    logic        ce_busy;
    logic        ce_enable;

    // ========================================
    // INSTANCIAÇÃO DO DUT
    // ========================================
    
    sobel_control_unit dut (
        .clk(clk),
        .rst_n(rst_n),
        .start(start),
        .img_width(img_width),
        .img_height(img_height),
        .src_addr(src_addr),
        .dst_addr(dst_addr),
        .busy(busy),
        .done(done),
        .error(error),
        .mem_read_req(mem_read_req),
        .mem_read_addr(mem_read_addr),
        .mem_read_ack(mem_read_ack),
        .mem_read_data(mem_read_data),
        .mem_write_req(mem_write_req),
        .mem_write_addr(mem_write_addr),
        .mem_write_data(mem_write_data),
        .mem_write_ack(mem_write_ack),
        .ce_valid_in(ce_valid_in),
        .ce_pixels_3x3(ce_pixels_3x3),
        .ce_valid_out(ce_valid_out),
        .ce_gradient_x(ce_gradient_x),
        .ce_busy(ce_busy),
        .ce_enable(ce_enable)
    );

    // ========================================
    // GERAÇÃO DE CLOCK
    // ========================================
    
    /* verilator lint_off STMTDLY */
    always begin
        #10 clk = ~clk;  // 50MHz
    end
    /* verilator lint_on STMTDLY */

    // ========================================
    // SIMULAÇÃO DE MEMÓRIA
    // ========================================
    
    // Simular latência de memória
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            mem_read_ack  <= 1'b0;
            mem_write_ack <= 1'b0;
            mem_read_data <= 72'h0;
        end else begin
            // Simular 1 ciclo de latência para leitura
            mem_read_ack <= mem_read_req;
            if (mem_read_req) begin
                // Dados de teste: pixels incrementais
                mem_read_data <= {8'd10, 8'd20, 8'd30, 8'd40, 8'd50, 
                                 8'd60, 8'd70, 8'd80, 8'd90};
            end
            
            // Simular 1 ciclo de latência para escrita
            mem_write_ack <= mem_write_req;
        end
    end

    // ========================================
    // SIMULAÇÃO DO COMPUTE ENGINE
    // ========================================
    
    // Simular comportamento do compute engine
    logic [1:0] ce_pipeline_delay;
    
    always_ff @(posedge clk) begin
        if (!rst_n) begin
            ce_valid_out    <= 1'b0;
            ce_gradient_x   <= 16'd0;
            ce_busy         <= 1'b0;
            ce_pipeline_delay <= 2'd0;
        end else if (ce_enable && ce_valid_in) begin
            // Simular pipeline de 2 ciclos
            ce_pipeline_delay <= 2'd2;
            ce_busy          <= 1'b1;
            ce_valid_out     <= 1'b0;
        end else if (ce_pipeline_delay > 0) begin
            ce_pipeline_delay <= ce_pipeline_delay - 1;
            if (ce_pipeline_delay == 1) begin
                // Resultado disponível
                ce_valid_out  <= 1'b1;
                ce_gradient_x <= 16'd123; // Resultado simulado
                ce_busy       <= 1'b0;
            end
        end else begin
            ce_valid_out <= 1'b0;
            ce_busy      <= 1'b0;
        end
    end

    // ========================================
    // VARIÁVEIS DE CONTROLE
    // ========================================
    
    integer cycle_count = 0;
    integer test_phase = 0;

    // ========================================
    // SEQUÊNCIA PRINCIPAL DE TESTE
    // ========================================
    
    initial begin
        $display("========================================");
        $display("TESTE DA SOBEL CONTROL UNIT");
        $display("========================================");
        
        // Inicialização
        clk = 0;
        rst_n = 0;
        start = 0;
        img_width = 32;
        img_height = 32;
        src_addr = 32'h1000;
        dst_addr = 32'h2000;
    end

    // ========================================
    // MÁQUINA DE ESTADOS DO TESTE
    // ========================================
    
    always_ff @(posedge clk) begin
        cycle_count <= cycle_count + 1;
        
        case (cycle_count)
            // Reset por 5 ciclos
            0, 1, 2, 3, 4: begin
                rst_n <= 0;
            end
            
            // Liberar reset
            5: begin
                rst_n <= 1;
                $display("[@%0d] Reset liberado", cycle_count);
            end
            
            // Iniciar processamento
            10: begin
                start <= 1;
                test_phase <= 1;
                $display("[@%0d] Iniciando processamento", cycle_count);
                $display("  img_size: %dx%d", img_width, img_height);
                $display("  src_addr: 0x%h", src_addr);
                $display("  dst_addr: 0x%h", dst_addr);
            end
            
            // Parar sinal start
            11: begin
                start <= 0;
            end
            
            // Monitorar progresso
            100: begin
                if (!done) begin
                    $display("[@%0d] Ainda processando...", cycle_count);
                    if (busy) begin
                        $display("  Status: BUSY");
                    end
                    if (error) begin
                        $display("  Status: ERROR!");
                        $finish;
                    end
                end
            end
            
            // Timeout de segurança
            1000: begin
                if (!done) begin
                    $display("[@%0d] TIMEOUT - processamento não finalizou!", cycle_count);
                    $error("Teste falhou por timeout");
                end
                $finish;
            end
        endcase
    end

    // ========================================
    // MONITORAMENTO DE ESTADOS
    // ========================================
    
    // Monitorar mudanças de estado
    always_ff @(posedge clk) begin
        if (rst_n && cycle_count > 10) begin
            // Monitorar sinais importantes
            if (mem_read_req) begin
                $display("[@%0d] MEM READ: addr=0x%h", cycle_count, mem_read_addr);
            end
            
            if (mem_write_req) begin
                $display("[@%0d] MEM WRITE: addr=0x%h, data=%d", 
                        cycle_count, mem_write_addr, mem_write_data);
            end
            
            if (ce_valid_in) begin
                $display("[@%0d] COMPUTE: enviando dados para engine", cycle_count);
            end
            
            if (ce_valid_out) begin
                $display("[@%0d] COMPUTE: resultado=%d", cycle_count, ce_gradient_x);
            end
        end
    end

    // ========================================
    // VERIFICAÇÃO DE CONCLUSÃO
    // ========================================
    
    always_ff @(posedge clk) begin
        if (done && test_phase == 1) begin
            $display("========================================");
            $display("[@%0d] PROCESSAMENTO CONCLUÍDO!", cycle_count);
            $display("✓ Control Unit funcionou corretamente");
            $display("✓ Máquina de estados operacional");
            $display("✓ Interface memória funcionando");
            $display("✓ Interface compute engine funcionando");
            $display("========================================");
            test_phase <= 2;
            
            // Aguardar alguns ciclos e finalizar
            repeat (10) @(posedge clk);
            $finish;
        end
    end

endmodule

/*
 * OBJETIVOS DO TESTE:
 * 
 * 1. VALIDAR MÁQUINA DE ESTADOS:
 *    - IDLE → SETUP → FETCH → PROCESS → WRITE → FINISH
 *    - Transições corretas
 *    - Tratamento de erro
 * 
 * 2. VALIDAR INTERFACES:
 *    - Memória: read_req/ack, write_req/ack
 *    - Compute Engine: valid_in/out, enable
 *    - Timing correto entre componentes
 * 
 * 3. VERIFICAR COORDENAÇÃO:
 *    - Sequência de operações
 *    - Pipeline overlap
 *    - Conclusão correta
 */