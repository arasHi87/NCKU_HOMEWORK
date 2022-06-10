module SME(clk,reset,chardata,isstring,ispattern,valid,match,match_index);
input clk;
input reset;
input [7:0] chardata;
input isstring;
input ispattern;
output match;
output reg [4:0] match_index;
output reg valid;

reg [7:0] string [0:33];
reg [7:0] pattern [0:8];
reg [7:0] str_cnt, pat_cnt, cal_cnt;
reg [7:0] str_len, pat_len;
reg [7:0] match_tmp;



reg [2:0]state, next_state;
parameter IDLE = 3'b000;
parameter READSTR = 3'b001;
parameter READPAT = 3'b010;
parameter CAL = 3'b011;
parameter OUT = 3'b100;

integer i,j;

always@(posedge clk or posedge reset)begin
    // if(reset)   state <= IDLE;
    // else    state <= next_state;
    state <= (reset ? IDLE : next_state);
end

always@(*)begin
    if(reset)   next_state=IDLE;
    else begin
        case(state)
            IDLE:begin
                // if(isstring == 1)   next_state = READSTR;
                // else next_state = IDLE;
                next_state = (isstring == 1 ? READSTR : IDLE); 
            end
            READSTR:begin
                // if(ispattern == 1)  next_state = READPAT;
                // else next_state = READSTR;
                next_state = (ispattern == 1 ? READPAT : READSTR) ;
            end
            READPAT:begin
                // if(ispattern == 0)  next_state = CAL;
                // else next_state = READPAT;
                next_state = (ispattern == 0 ? CAL : READPAT);
            end
            CAL:begin
                // if(match || cal_cnt == str_len - pat_len + 3)next_state = OUT;
                // else next_state = CAL;
                next_state = (match || cal_cnt == str_len - pat_len + 3 ? OUT : CAL);
            end
            OUT:begin
                // if(isstring == 1) next_state = READSTR;
                // else next_state = READPAT;
                next_state = (isstring == 1 ? READSTR : READPAT);
            end
            default:    next_state = IDLE;
        endcase
    end
end




//str cnt
always@(posedge clk or posedge reset)begin
    // if(reset)begin
    //     str_cnt <= 0;
    // end
    // else if(isstring)
    // begin
    //     str_cnt <= str_cnt + 1; //string -> pattern cnt==0
    // end
    // else begin
    //     str_cnt <= 0;
    // end
    if (isstring) str_cnt <= str_cnt + 1;
    else          str_cnt <= 0;
end

//pat_cnt
always@(posedge clk or posedge reset)begin
    // if(reset)begin
    //     pat_cnt <= 0;
    // end
    // else if(next_state == CAL || next_state == READSTR )
    // begin
    //     pat_cnt <= 0;
    // end
    // else if(next_state == READPAT || next_state == OUT) begin
    //     pat_cnt <= pat_cnt + 1;
    // end
    if (next_state == READPAT || next_state == OUT) pat_cnt <= pat_cnt + 1;
    else          pat_cnt <= 0;
end

//cal cnt
always@(posedge clk or posedge reset)begin
    // if(reset)begin
    //     cal_cnt <= 0;
    // end
    // else if(next_state == CAL || (next_state == READPAT && !ispattern))
    //     cal_cnt <= cal_cnt + 1; //string -> pattern cnt==0
    // else begin
    //     cal_cnt <= 0;
    // end
    if (next_state == CAL || (next_state == READPAT && !ispattern)) cal_cnt <= cal_cnt + 1;
    else cal_cnt <= 0;
end

//str_len
always @(negedge isstring) begin
    str_len <= str_cnt;
end

always @(negedge ispattern) begin
    pat_len <= pat_cnt;
end


//READ DATA STRING
always@(posedge clk or posedge reset)begin
    if(reset)begin
        for(i=0;i<34;i=i+1)
            string[i] <= 8'h20;
    end
    else if(isstring)begin
        string[str_cnt + 1] <= chardata;
        if(str_cnt == 0)begin
            for(i=2;i<34;i=i+1)
                string[i] <= 8'h20;
        end

        // string[0] <= 8'h20;
    end
    // else
    //     string[0] <= 8'h20;
end

//READ DATA PATTERN
always@(posedge clk or posedge reset)begin
    if(reset)begin
        for(j=0;j<8;j=j+1)
            pattern[j] <= 8'h2E;
    end
    else if(ispattern)begin
            pattern[pat_cnt] <= chardata;
        if(pat_cnt == 0)begin
            for(j=1;j<9;j=j+1)
                pattern[j] <= 8'h2E;
        end
    end
end


//match_tmp
always @(posedge clk) begin
    //cnt 0 ~ 26
    if(next_state == CAL)begin
        match_tmp[0] <= ((pattern[0] == 8'h2E) || (pattern[0] == 8'h5E && string[cal_cnt] == 8'h20) ||           (pattern[0] == string[cal_cnt])) ? 1 : 0;
        match_tmp[1] <= ((pattern[1] == 8'h2E) || (pattern[1] == string[cal_cnt+4'd1]) || (pattern[1] == 8'h24 && string[cal_cnt+4'd1] == 8'h20)) ? 1 : 0;
        match_tmp[2] <= ((pattern[2] == 8'h2E) || (pattern[2] == string[cal_cnt+4'd2]) || (pattern[2] == 8'h24 && string[cal_cnt+4'd2] == 8'h20)) ? 1 : 0;
        match_tmp[3] <= ((pattern[3] == 8'h2E) || (pattern[3] == string[cal_cnt+4'd3]) || (pattern[3] == 8'h24 && string[cal_cnt+4'd3] == 8'h20)) ? 1 : 0;
        match_tmp[4] <= ((pattern[4] == 8'h2E) || (pattern[4] == string[cal_cnt+4'd4]) || (pattern[4] == 8'h24 && string[cal_cnt+4'd4] == 8'h20)) ? 1 : 0;
        match_tmp[5] <= ((pattern[5] == 8'h2E) || (pattern[5] == string[cal_cnt+4'd5]) || (pattern[5] == 8'h24 && string[cal_cnt+4'd5] == 8'h20)) ? 1 : 0;
        match_tmp[6] <= ((pattern[6] == 8'h2E) || (pattern[6] == string[cal_cnt+4'd6]) || (pattern[6] == 8'h24 && string[cal_cnt+4'd6] == 8'h20)) ? 1 : 0;
        match_tmp[7] <= ((pattern[7] == 8'h2E) || (pattern[7] == string[cal_cnt+4'd7]) || (pattern[7] == 8'h24 && string[cal_cnt+4'd7] == 8'h20)) ? 1 : 0;
    end
end

assign match = (pattern[8] == 8'h24) ? 0 : &match_tmp && (cal_cnt > 1);
// assign match =  &match_tmp && (cal_cnt > 1);



//output
always @(*) begin
    if(next_state == OUT)begin
        valid = 1'b1;
        match_index = (pattern[0] == 8'h5E) ? cal_cnt[4:0] - 5'd1 : cal_cnt[4:0] - 5'd2;
    end
    else begin
        valid = 0;
        match_index = 0;
    end
end


endmodule