module traffic_light (
    input  clk,
    input  rst,
    input  pass,
    output reg R,
    output reg G,
    output reg Y
);

reg [10:0] cnt;

initial begin
    cnt = 8'b00000000;
end

always @(posedge clk) begin
    if (rst) begin
        cnt <= 0;
    end
    else if (pass) begin
        if (cnt > 510) begin
            cnt <= 0;
        end
        else begin
            cnt <= cnt + 1;
        end
    end
    else begin
        if (cnt == 1535) begin
            cnt <= 0;
        end
        else begin
            cnt <= cnt + 1;
        end
    end
end

always @(negedge clk or posedge pass or negedge cnt) begin
    if (rst || pass || (cnt >= 0 && cnt <= 510) || (cnt >= 575 && cnt <= 638) || (cnt >= 703 && cnt <= 766)) begin
        R <= 0;
        G <= 1;
        Y <= 0;
    end
    else if (cnt >= 767 && cnt <= 1022) begin
        R <= 0;
        G <= 0;
        Y <= 1;
    end
    else if (cnt >= 1023 && cnt <= 1534) begin
        R <= 1;
        G <= 0;
        Y <= 0;
    end
    else begin
        R <= 0;
        G <= 0;
        Y <= 0;
    end
end

endmodule