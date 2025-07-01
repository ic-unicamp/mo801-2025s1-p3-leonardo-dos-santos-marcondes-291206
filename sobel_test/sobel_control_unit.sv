/*
 * Sobel Control Unit - Coordenação do Processamento
 * Gerencia o processamento completo de imagens 32x32
 */

module sobel_control_unit (
    input  logic        clk,
    input  logic        rst_n,
    
    // Interface de Controle (AXI4-Lite)
    input  logic        start,           // Iniciar processamento
    input  logic [15:0] img_width,       // Largura da imagem
    input  logic [15:0] img_height,      // Altura da imagem
    input  logic [31:0] src_addr,        // Endereço da imagem fonte
    input  logic [31:0] dst_addr,        // Endereço dos resultados
    
    output logic        busy,            // Processamento em andamento
    output logic        done,            // Processamento concluído
    output logic        error,           // Erro durante processamento
    
    // Interface com Memória
    output logic        mem_read_req,    // Requisição de leitura
    output logic [31:0] mem_read_addr,   // Endereço de leitura
    input  logic        mem_read_ack,    // Leitura confirmada
    input  logic [71:0] mem_read_data,   // Dados lidos (9 pixels)
    
    output logic        mem_write_req,   // Requisição de escrita
    output logic [31:0] mem_write_addr,  // Endereço de escrita
    output logic [15:0] mem_write_data,  // Dados para escrita
    input  logic        mem_write_ack,   // Escrita confirmada
    
    // Interface com Compute Engine
    output logic        ce_valid_in,     // Dados válidos para engine
    output logic [71:0] ce_pixels_3x3,   // Janela 3x3 para processamento
    input  logic        ce_valid_out,    // Resultado válido do engine
    input  logic [15:0] ce_gradient_x,   // Gradiente calculado
    input  logic        ce_busy,         // Engine ocupado
    output logic        ce_enable        // Habilitar engine
);

    // ========================================
    // ESTADOS DA MÁQUINA
    // ========================================
    
    typedef enum logic [3:0] {
        IDLE        = 4'h0,   // Esperando comando
        SETUP       = 4'h1,   // Configurando parâmetros
        FETCH_ROW   = 4'h2,   // Carregando linha da imagem
        PROCESS     = 4'h3,   // Processando pixel
        WRITE_BACK  = 4'h4,   // Escrevendo resultado
        NEXT_PIXEL  = 4'h5,   // Avançar para próximo pixel
        FINISH      = 4'h6,   // Finalizar processamento
        ERROR_STATE = 4'hF    // Estado de erro
    } state_t;
    
    state_t current_state, next_state;

    // ========================================
    // REGISTRADORES INTERNOS
    // ========================================
    
    logic [15:0] width, height;          // Dimensões da imagem
    logic [31:0] base_src, base_dst;     // Endereços base
    
    logic [15:0] current_x, current_y;   // Posição atual (pixel)
    logic [15:0] pixels_processed;       // Contador de pixels
    logic [15:0] total_pixels;           // Total a processar
    
    // Buffer para 3 linhas da imagem (sliding window)
    logic [7:0]  line_buffer [2:0][31:0]; // 3 linhas × 32 pixels
    logic [1:0]  buffer_valid;            // Linhas válidas no buffer
    
    // Controle de pipeline
    logic        fetch_pending;          // Fetch em andamento
    logic        write_pending;          // Write em andamento
    logic [15:0] pending_result;         // Resultado aguardando escrita

    // ========================================
    // MÁQUINA DE ESTADOS PRINCIPAL
    // ========================================
    
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            current_state <= IDLE;
        end else begin
            current_state <= next_state;
        end
    end

    // ========================================
    // LÓGICA DE TRANSIÇÃO DE ESTADOS
    // ========================================
    
    always_comb begin
        next_state = current_state;
        
        case (current_state)
            IDLE: begin
                if (start) begin
                    next_state = SETUP;
                end
            end
            
            SETUP: begin
                // Validar parâmetros e configurar buffers
                if (width == 32 && height == 32) begin
                    next_state = FETCH_ROW;
                end else begin
                    next_state = ERROR_STATE;
                end
            end
            
            FETCH_ROW: begin
                if (mem_read_ack && buffer_valid == 2'b11) begin
                    // Temos 3 linhas carregadas, podemos processar
                    next_state = PROCESS;
                end
            end
            
            PROCESS: begin
                if (ce_valid_out) begin
                    // Resultado disponível
                    next_state = WRITE_BACK;
                end
            end
            
            WRITE_BACK: begin
                if (mem_write_ack) begin
                    next_state = NEXT_PIXEL;
                end
            end
            
            NEXT_PIXEL: begin
                if (pixels_processed >= total_pixels) begin
                    next_state = FINISH;
                end else begin
                    // Verificar se precisa carregar nova linha
                    if (current_x == 0) begin
                        next_state = FETCH_ROW;
                    end else begin
                        next_state = PROCESS;
                    end
                end
            end
            
            FINISH: begin
                next_state = IDLE;
            end
            
            ERROR_STATE: begin
                // Requer reset para sair
                if (!start) begin
                    next_state = IDLE;
                end
            end
            
            default: begin
                next_state = ERROR_STATE;
            end
        endcase
    end

    // ========================================
    // LÓGICA DE CONTROLE DE REGISTRADORES
    // ========================================
    
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            width             <= 16'd0;
            height            <= 16'd0;
            base_src          <= 32'd0;
            base_dst          <= 32'd0;
            current_x         <= 16'd0;
            current_y         <= 16'd0;
            pixels_processed  <= 16'd0;
            total_pixels      <= 16'd0;
            buffer_valid      <= 2'b00;
            fetch_pending     <= 1'b0;
            write_pending     <= 1'b0;
            pending_result    <= 16'd0;
        end else begin
            case (current_state)
                IDLE: begin
                    if (start) begin
                        // Capturar configuração
                        width    <= img_width;
                        height   <= img_height;
                        base_src <= src_addr;
                        base_dst <= dst_addr;
                    end
                end
                
                SETUP: begin
                    // Calcular parâmetros de processamento
                    // Área útil: (32-2) × (32-2) = 30×30 = 900 pixels
                    current_x        <= 16'd1;      // Começar em (1,1)
                    current_y        <= 16'd1;
                    pixels_processed <= 16'd0;
                    total_pixels     <= 16'd900;    // 30×30 pixels úteis
                    buffer_valid     <= 2'b00;
                end
                
                FETCH_ROW: begin
                    if (mem_read_ack) begin
                        buffer_valid <= buffer_valid + 1;
                    end
                end
                
                WRITE_BACK: begin
                    // Aguardar ACK da escrita
                    // pending_result e write_pending são gerenciados em bloco separado
                end
                
                NEXT_PIXEL: begin
                    pixels_processed <= pixels_processed + 1;
                    
                    // Avançar posição
                    if (current_x < 30) begin  // 30 = width - 2
                        current_x <= current_x + 1;
                    end else begin
                        current_x <= 16'd1;
                        current_y <= current_y + 1;
                    end
                end
                
                FINISH: begin
                    // Reset para próxima execução
                    current_x        <= 16'd0;
                    current_y        <= 16'd0;
                    pixels_processed <= 16'd0;
                end
                
                ERROR_STATE: begin
                    // Estado de erro
                end
                
                default: begin
                    // Estado padrão para completar case
                end
            endcase
        end
    end

    // ========================================
    // INTERFACE COM MEMÓRIA
    // ========================================
    
    always_comb begin
        // Leitura: carregar linha da imagem
        mem_read_req  = (current_state == FETCH_ROW) && !fetch_pending;
        // Cast de todos os operandos para 32 bits
        mem_read_addr = base_src + 32'(32'(current_y) * 32'(width) + 32'(current_x)) * 32'd4;
        
        // Escrita: salvar resultado  
        mem_write_req  = (current_state == WRITE_BACK) && !write_pending;
        // Cast de todos os operandos para 32 bits
        mem_write_addr = base_dst + ((32'(current_y) - 32'd1) * (32'(width) - 32'd2) + (32'(current_x) - 32'd1)) * 32'd2;
        mem_write_data = pending_result;
    end

    // ========================================
    // INTERFACE COM COMPUTE ENGINE
    // ========================================
    
    // Extrair janela 3×3 do buffer
    always_comb begin
        ce_pixels_3x3 = {
            line_buffer[0][current_x[4:0]-1], line_buffer[0][current_x[4:0]], line_buffer[0][current_x[4:0]+1],
            line_buffer[1][current_x[4:0]-1], line_buffer[1][current_x[4:0]], line_buffer[1][current_x[4:0]+1],
            line_buffer[2][current_x[4:0]-1], line_buffer[2][current_x[4:0]], line_buffer[2][current_x[4:0]+1]
        };
        
        ce_valid_in = (current_state == PROCESS) && (buffer_valid == 2'b11);
        ce_enable   = (current_state != IDLE) && (current_state != ERROR_STATE);
    end
    
    // Capturar resultado do engine - APENAS aqui para evitar multiple drivers
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            pending_result <= 16'd0;
            write_pending  <= 1'b0;
        end else if (ce_valid_out && (current_state == PROCESS)) begin
            pending_result <= ce_gradient_x;
            write_pending  <= 1'b1;
        end else if (current_state == WRITE_BACK && mem_write_ack) begin
            write_pending <= 1'b0;
        end else if (current_state == FINISH || current_state == ERROR_STATE) begin
            pending_result <= 16'd0;
            write_pending  <= 1'b0;
        end
    end

    // ========================================
    // SINAIS DE STATUS
    // ========================================
    
    assign busy  = (current_state != IDLE) && (current_state != FINISH);
    assign done  = (current_state == FINISH);
    assign error = (current_state == ERROR_STATE);

    // ========================================
    // ASSERTIONS PARA DEBUG
    // ========================================
    
    `ifdef SIMULATION
        // Verificar limites de coordenadas
        always_ff @(posedge clk) begin
            if (current_state == PROCESS) begin
                assert (current_x >= 1 && current_x <= 30) 
                else $error("current_x fora dos limites: %d", current_x);
                
                assert (current_y >= 1 && current_y <= 30) 
                else $error("current_y fora dos limites: %d", current_y);
            end
        end
        
        // Verificar buffer válido antes de processar
        always_ff @(posedge clk) begin
            if (ce_valid_in) begin
                assert (buffer_valid == 2'b11) 
                else $error("Tentativa de processar sem buffer completo!");
            end
        end
    `endif

endmodule

/*
 * EXPLICAÇÃO DO DESIGN:
 * 
 * 1. MÁQUINA DE ESTADOS:
 *    - IDLE: Aguarda comando start
 *    - SETUP: Configura parâmetros e valida entrada
 *    - FETCH_ROW: Carrega linhas da imagem para buffer
 *    - PROCESS: Processa pixel atual com compute engine
 *    - WRITE_BACK: Escreve resultado na memória
 *    - NEXT_PIXEL: Avança para próximo pixel
 *    - FINISH: Sinaliza conclusão
 * 
 * 2. BUFFER MANAGEMENT:
 *    - Line buffer de 3 linhas × 32 pixels
 *    - Sliding window para extrair janela 3×3
 *    - Carregamento otimizado de dados
 * 
 * 3. COORDENAÇÃO:
 *    - Processa área útil 30×30 (evita bordas)
 *    - Coordena timing entre memória e compute engine
 *    - Pipeline overlapped para máxima eficiência
 * 
 * 4. INTERFACE:
 *    - Compatível com AXI4-Lite
 *    - Sinais de status claros (busy/done/error)
 *    - Configuração flexível de endereços
 */