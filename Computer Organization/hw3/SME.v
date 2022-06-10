module SME (
    input            clk,
    input            reset,
    input      [7:0] chardata,
    input            isstring,
    input            ispattern,
    output           match,
    output reg [4:0] match_index,
    output reg       valid
);

/*
    s_len => string length
    s_cnt => string count
    p_len => patteren length
    p_cnt => patteren count
    m_len => match length
    m_arr => match array
*/

integer i, j, k;
reg [7:0] string  [0:33];
reg [7:0] pattern [0:8];
reg [7:0] s_len, p_len, s_cnt, p_cnt, m_len, m_arr;
reg [2:0] state, nxt_state;

parameter MAT   = 3'b000; // try to match
parameter OUT   = 3'b001; // output
parameter IDLE  = 3'b010; // IDLE
parameter R_STR = 3'b011; // read string
parameter R_PAT = 3'b100; // read patteren

/* --------------------- state middleware --------------------- */
always @(posedge clk or posedge reset) begin
    state <= (reset ? IDLE : nxt_state);
end

always @(*) begin
    if (reset) nxt_state = IDLE;
    else begin
        case (state)
            MAT: nxt_state     = ((match || m_len + p_len == s_len + 3) ? OUT : MAT);
            OUT: nxt_state     = (isstring == 1 ? R_STR : R_PAT);
            IDLE: nxt_state    = (isstring == 1 ? R_STR : IDLE);
            R_STR: nxt_state   = (ispattern == 1 ? R_PAT : R_STR);
            R_PAT: nxt_state   = (ispattern == 0 ? MAT : R_PAT);
            default: nxt_state = IDLE;
        endcase
    end
end
/* ------------------------------------------------------------ */

/* ---------------- count string and assign it ---------------- */
always @(posedge clk or posedge reset) begin
    s_cnt <= (isstring ? s_cnt + 1 : 0);
end

always @(negedge isstring) begin
    s_len <= s_cnt;
end
/* ------------------------------------------------------------ */

/* --------------- count patteren and assign it --------------- */
always @(posedge clk or posedge reset) begin
    p_cnt <= ((nxt_state == R_PAT || nxt_state == OUT) ? p_cnt + 1 : 0);
end

always @(negedge ispattern) begin
    p_len <= p_cnt;
end
/* ------------------------------------------------------------ */

/* ----------------------- count match ------------------------ */
always @(posedge clk or posedge reset) begin
    m_len <= (((nxt_state == MAT) || (nxt_state == R_PAT && !ispattern)) ? m_len + 1 : 0);
end
/* ------------------------------------------------------------ */

/* ----------------------- read string ------------------------ */
always @(posedge clk or posedge reset) begin
    if (reset) begin
        for (i = 0; i < 34; i = i + 1)
            string[i] <= 8'h20;
    end
    else if (isstring) begin
        string[s_cnt + 1] <= chardata;
        if (!s_cnt) begin
            for (i = 2; i < 34; i = i + 1)
                string[i] <= 8'h20;
        end
    end
end
/* ------------------------------------------------------------ */

/* ----------------------- read patteren ---------------------- */
always @(posedge clk or posedge reset) begin
    if (reset) begin
        for (j = 0; j < 8; j = j + 1)
            pattern[j] <= 8'h2E;
    end
    else if (ispattern) begin
        pattern[p_cnt] <= chardata;
        if (!p_cnt) begin
            for (j = 1; j < 9; j = j + 1)
                pattern[j] <= 8'h2E;
        end
    end
end
/* ------------------------------------------------------------ */

/* ------------------------- try match ------------------------ */
always @(posedge clk) begin
    if (nxt_state == MAT) begin
        m_arr[0] <= ((pattern[0] == 8'h2E) || (pattern[0] == 8'h5E && string[m_len] == 8'h20) || (pattern[0] == string[m_len])) ? 1 : 0;
        for (k = 1; k <= 7; k = k + 1)
           m_arr[k] <= ((pattern[k] == 8'h2E) || (pattern[k] == string[m_len + k]) || (pattern[k] == 8'h24 && string[m_len + k] == 8'h20)) ? 1 : 0; 
    end
end

assign match = (pattern[8] == 8'h24) ? 0 : &m_arr && (m_len > 1);
/* ------------------------------------------------------------ */

/* -------------------------- output -------------------------- */
always @(*) begin
    if (nxt_state == OUT) begin
        valid = 1'b1;
        match_index = (pattern[0] == 8'h5E) ? m_len[4:0] - 5'd1 : m_len[4:0] - 5'd2;
    end
    else begin
        valid = 0;
        match_index = 0;
    end
end
/* ------------------------------------------------------------ */
endmodule