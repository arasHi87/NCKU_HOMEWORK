module FindMaxLessThenAVG(input i1,
                          input i2,
                          input [7:0] v1,
                          input [7:0] v2, 
                          output reg [7:0] t_i,
                          output reg [7:0]  o_v);

wire flag;
assign flag = v1 > v2;

always @(*) begin
    case({i1, i2})
        2'b00: begin
            t_i <= 0;
            if(flag) o_v <= v1;
            else o_v <= v2;
        end
        2'b01: begin
            t_i <= 0;
            o_v <= v1;
        end
        2'b10: begin
            t_i <= 0;
            o_v <= v2;
        end
        default: begin
            t_i <= 1;
            o_v <= 8'bx;
        end
    endcase
end
endmodule

module CS(input [9:0] Y,
          input [7:0] X,
          input reset,
          input clk);

reg  [71:0] data;
reg  [11:0] r_sum;
reg  [8:0]  r_flag;
wire [11:0] sum;
wire [8:0]  flag;
wire [20:0] avg;
wire [7:0]  t_i; // tmp invaild
wire [63:0] t_v; // tmp value
wire [12:0] out;

always @(posedge clk or posedge reset) begin
    if(reset) begin
        data <= 72'b0;
        r_sum <= 0;
        r_flag <= 8'b0;
    end
    else begin
        data <= {data[63:0], X};
        r_sum <= sum;
        r_flag <= flag;
    end
end

assign sum = r_sum - {4'b0, data[71:64]} + {4'b0, X};

// avg = (sum * 512 + sum * 8) - (sum *  64) + (sum / 512 + sum * 8) - sum
// avg = sum * (512 - 64 + 8 - 1 + 1/8 + 1/512 = 455 + 65/512 = 455.126953125 ≒ 4096/9)
// avg = sum * (4096 / 9)
assign avg = {sum, sum[11:3]} - {2'b0, sum, 6'b0} + {5'b0, sum, sum[11:9]} - {8'b0, sum};

assign flag[0] = data[63:56] > avg[19:12];
assign flag[1] = data[55:48] > avg[19:12];
assign flag[2] = data[47:40] > avg[19:12];
assign flag[3] = data[39:32] > avg[19:12];
assign flag[4] = data[31:24] > avg[19:12];
assign flag[5] = data[23:16] > avg[19:12];
assign flag[6] = data[15:8] > avg[19:12];
assign flag[7] = data[7:0] > avg[19:12];
assign flag[8] = X > avg[19:12];

FindMaxLessThenAVG f11(r_flag[0], r_flag[1], data[71:64], data[63:56], t_i[0], t_v[7:0]);
FindMaxLessThenAVG f12(r_flag[2], r_flag[3], data[55:48], data[47:40], t_i[1], t_v[15:8]);
FindMaxLessThenAVG f13(r_flag[4], r_flag[5], data[39:32], data[31:24], t_i[2], t_v[23:16]);
FindMaxLessThenAVG f14(r_flag[6], r_flag[7], data[23:16], data[15:8], t_i[3], t_v[31:24]);
FindMaxLessThenAVG f21(t_i[0], t_i[1], t_v[7:0], t_v[15:8], t_i[4], t_v[39:32]);
FindMaxLessThenAVG f22(t_i[2], t_i[3], t_v[23:16], t_v[31:24], t_i[5], t_v[47:40]);
FindMaxLessThenAVG f23(t_i[4], t_i[5], t_v[39:32], t_v[47:40], t_i[6], t_v[55:48]);
FindMaxLessThenAVG f24(t_i[6], r_flag[8], t_v[55:48], data[7:0], t_i[7], t_v[63:56]);

assign out = {1'b0, r_sum} + {1'b0, {1'b0, t_v[63:56], 3'b0} + {4'b0, t_v[63:56]}};
assign Y = out[12:3];

endmodule