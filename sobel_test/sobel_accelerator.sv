/*
 * Sobel Accelerator - Módulo Completo
 * Integra Control Unit + Compute Engine
 */

module sobel_accelerator (
    input  logic        clk,
    input  logic        rst_n,
    
    // ========================================
    // INTERFACE AXI4-LITE (Registradores)
    // ========================================
    
    // Registrador de Controle (0x00)
    input  logic [31:0] reg_ctrl,
    output logic [31:0] reg_status,
    
    // Configuração da Imagem (0x08)
    input  logic [31:0] reg_img_size,   // [31:16]=height, [15:0]=width
    
    // Endereços (0x0C, 0x10)
    input  logic [31:0] reg_src_addr,
    input  logic [31:0] reg_dst_addr,
    
    // ========================================
    // INTERFACE DE MEMÓRIA (AXI4 ou Wishbone)
    // ========================================
    
    // Leitura
    output logic        mem_read_req,
    output logic [31:0] mem_read_addr,
    input  logic        mem_read_ack,
    input  logic [71:0] mem_read_data,
    
    // Escrita
    output logic        mem_write_req,
    output logic [31:0] mem_write_addr,
    output logic [15:0] mem_write_data,
    input  logic        mem_write_ack
);

    // ========================================
    // DECODIFICAÇÃO DOS REGISTRADORES
    // ========================================
    
    // Registrador de Controle (0x00)
    logic start_pulse;
    logic soft_reset;
    
    assign start_pulse = reg_ctrl[0];    // Bit 0: START
    assign soft_reset  = reg_ctrl[1];    // Bit 1: RESET
    
    // Configuração da Imagem (0x08)
    logic [15:0] img_width, img_height;
    assign img_width  = reg_img_size[15:0];
    assign img_height = reg_img_size[31:16];
    
    // ========================================
    // SINAIS INTERNOS
    // ========================================
    
    // Control Unit → Compute Engine
    logic        ce_valid_in;
    logic [71:0] ce_pixels_3x3;
    logic        ce_valid_out;
    logic [15:0] ce_gradient_x;
    logic        ce_busy;
    logic        ce_enable;
    
    // Status da Control Unit
    logic cu_busy, cu_done, cu_error;
    
    // Reset combinado
    logic internal_rst_n;
    assign internal_rst_n = rst_n && !soft_reset;

    // ========================================
    // INSTANCIAÇÃO DA CONTROL UNIT
    // ========================================
    
    sobel_control_unit control_unit (
        .clk(clk),
        .rst_n(internal_rst_n),
        
        // Interface de controle
        .start(start_pulse),
        .img_width(img_width),
        .img_height(img_height),
        .src_addr(reg_src_addr),
        .dst_addr(reg_dst_addr),
        
        .busy(cu_busy),
        .done(cu_done),
        .error(cu_error),
        
        // Interface com memória (pass-through)
        .mem_read_req(mem_read_req),
        .mem_read_addr(mem_read_addr),
        .mem_read_ack(mem_read_ack),
        .mem_read_data(mem_read_data),
        
        .mem_write_req(mem_write_req),
        .mem_write_addr(mem_write_addr),
        .mem_write_data(mem_write_data),
        .mem_write_ack(mem_write_ack),
        
        // Interface com compute engine
        .ce_valid_in(ce_valid_in),
        .ce_pixels_3x3(ce_pixels_3x3),
        .ce_valid_out(ce_valid_out),
        .ce_gradient_x(ce_gradient_x),
        .ce_busy(ce_busy),
        .ce_enable(ce_enable)
    );

    // ========================================
    // INSTANCIAÇÃO DO COMPUTE ENGINE
    // ========================================
    
    sobel_compute_engine compute_engine (
        .clk(clk),
        .rst_n(internal_rst_n),
        
        .valid_in(ce_valid_in),
        .pixels_3x3(ce_pixels_3x3),
        .valid_out(ce_valid_out),
        .gradient_x(ce_gradient_x),
        .enable(ce_enable),
        .busy(ce_busy)
    );

    // ========================================
    // REGISTRADOR DE STATUS (0x04)
    // ========================================
    
    always_comb begin
        reg_status = 32'h0;
        reg_status[0] = cu_busy;    // Bit 0: BUSY
        reg_status[1] = cu_done;    // Bit 1: DONE
        reg_status[2] = cu_error;   // Bit 2: ERROR
        reg_status[3] = ce_busy;    // Bit 3: COMPUTE_BUSY
        
        // Bits informativos (read-only)
        reg_status[31:16] = 16'h0001; // Versão 0.1
    end

    // ========================================
    // PERFORMANCE COUNTERS (OPCIONAL)
    // ========================================
    
    logic [31:0] cycle_counter;
    logic [15:0] pixel_counter;
    
    always_ff @(posedge clk or negedge internal_rst_n) begin
        if (!internal_rst_n) begin
            cycle_counter <= 32'd0;
            pixel_counter <= 16'd0;
        end else begin
            if (cu_busy) begin
                cycle_counter <= cycle_counter + 1;
            end
            
            if (ce_valid_out) begin
                pixel_counter <= pixel_counter + 1;
            end
            
            if (cu_done) begin
                // Reset counters quando terminar
                cycle_counter <= 32'd0;
                pixel_counter <= 16'd0;
            end
        end
    end

endmodule

/*
 * INTERFACE DE REGISTRADORES:
 * 
 * 0x00: CTRL
 *   [0] START  - Iniciar processamento (write-only, auto-clear)
 *   [1] RESET  - Reset do acelerador
 * 
 * 0x04: STATUS (read-only)
 *   [0] BUSY        - Processamento em andamento
 *   [1] DONE        - Processamento concluído
 *   [2] ERROR       - Erro durante processamento
 *   [3] COMPUTE_BUSY - Compute engine ocupado
 *   [31:16] VERSION - Versão do acelerador (0x0001)
 * 
 * 0x08: IMG_SIZE
 *   [15:0]  WIDTH  - Largura da imagem
 *   [31:16] HEIGHT - Altura da imagem
 * 
 * 0x0C: SRC_ADDR
 *   [31:0] - Endereço da imagem fonte
 * 
 * 0x10: DST_ADDR  
 *   [31:0] - Endereço dos resultados
 * 
 * EXEMPLO DE USO:
 * 
 * // Configurar acelerador
 * write32(SOBEL_BASE + 0x08, (32 << 16) | 32);     // 32x32 pixels
 * write32(SOBEL_BASE + 0x0C, 0x10000000);          // src_addr
 * write32(SOBEL_BASE + 0x10, 0x20000000);          // dst_addr
 * 
 * // Iniciar processamento
 * write32(SOBEL_BASE + 0x00, 0x01);                // START
 * 
 * // Aguardar conclusão
 * while (read32(SOBEL_BASE + 0x04) & 0x01);        // Enquanto BUSY
 * 
 * // Verificar resultado
 * uint32_t status = read32(SOBEL_BASE + 0x04);
 * if (status & 0x02) printf("Concluído!\n");       // DONE
 * if (status & 0x04) printf("Erro!\n");            // ERROR
 */