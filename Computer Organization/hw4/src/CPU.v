module CPU(
    input             clk,
    input             rst,
    input      [31:0] data_out,
    input      [31:0] instr_out,
    output            instr_read,
    output            data_read,
    output reg [31:0] instr_addr,
    output reg [31:0] data_addr,
    output reg [3:0]  data_write,
    output reg [31:0] data_in
);

reg	[2:0] CurrentState;
reg	[2:0] NextState;

reg	[31:0] Register[31:0];
reg	[31:0] Immediate;
reg [31:0] Tmp;

reg	Instruction_Fetch;
reg	Instruction_Decode;
reg	Execute;
reg	Memory_Access;
reg	Write_Back;

integer i;

parameter 	Idle_state = 3'h0,
			Instruction_Fetch_state = 3'h1,
			Instruction_Decode_state = 3'h2,
			Execute_state = 3'h3,
			Memory_Access_state = 3'h4,
			Write_Back_state = 3'h5,
			Finish_state = 3'h6;

wire [6:0]	opcode;
wire [4:0]	rd;
wire [2:0]	funct3;
wire [4:0]	rs1;
wire [4:0]	rs2;
wire [4:0]	shamt;
wire [6:0]	funct7;

assign instr_read = 1;
assign data_read = 1;

assign opcode = instr_out[ 6: 0];
assign rd = 	instr_out[11: 7];
assign funct3 = instr_out[14:12];
assign rs1 = 	instr_out[19:15];
assign rs2 = 	instr_out[24:20];
assign shamt = 	instr_out[24:20];
assign funct7 = instr_out[31:25];

////////////////////////////////////////////////
//Immediate
always@(posedge clk or posedge rst)begin
	if(rst)
		Immediate <= 32'h0;
	else if(Instruction_Decode)begin
		case(opcode)
			7'b0010011:begin//I-type
				/*add your code*/
				Immediate[11:0]  <= instr_out[31:20];
				Immediate[31:12] <= { 20{instr_out[31]} };
			end
			7'b0100011:begin//S-type
				/*add your code*/
				Immediate[11:5]  <= instr_out[31:25];
				Immediate[4:0]   <= instr_out[11:7];
				Immediate[31:12] <= { 20{instr_out[31]} };
			end
			7'b0110111:begin//LUI
				Immediate[31:12] <= instr_out[31:12];
				Immediate[11:0] <= 12'h0;
			end
		endcase
	end
end
////////////////////////////////////////////////

////////////////////////////////////////////////
//Register_Files
always@(posedge clk or posedge rst)begin
	if(rst)begin
		for(i = 0; i < 32; i = i + 1)
			Register[i] <= 32'h0;
	end
	else if(Write_Back)begin
		case(opcode)
			7'b0110011:begin//R-type
				case(funct3)
					3'b000:begin
						case(funct7)
							7'b0000000:begin//ADD
								Register[rd] <= Register[rs1] + Register[rs2];
							end
							7'b0100000:begin//SUB
								/*add your code*/
								Register[rd] <= Register[rs1] - Register[rs2];
							end
						endcase
					end
					3'b100:begin
						case(funct7)
							7'b0000000:begin//XOR
								/*add your code*/
								Register[rd] <= Register[rs1] ^ Register[rs2];
							end
						endcase
					end
					3'b110:begin
						case(funct7)
							7'b0000000:begin//OR
								/*add your code*/
								Register[rd] <= Register[rs1] | Register[rs2];
							end
						endcase
					end
					3'b111:begin
						case(funct7)
							7'b0000000:begin//AND
								/*add your code*/
								Register[rd] <= Register[rs1] & Register[rs2];
							end
						endcase
					end
				endcase
			end
			7'b0010011:begin//I-type
				case(funct3)
					3'b000:begin//ADDI
						Register[rd] <= Register[rs1] + $signed(Immediate);
					end
					3'b100:begin//XORI
						/*add your code*/
						Register[rd] <= Register[rs1] ^ $signed(Immediate);
					end
					3'b110:begin//ORI
						/*add your code*/
						Register[rd] <= Register[rs1] | $signed(Immediate);
					end
					3'b111:begin//ANDI
						/*add your code*/
						Register[rd] <= Register[rs1] & $signed(Immediate);
					end
				endcase
			end
			7'b0110111:begin//LUI
				/*add your code*/
				Register[rd] <= { Immediate[31:12], 12'b0 };
			end
		endcase
	end
end
////////////////////////////////////////////////

////////////////////////////////////////////////
//instr_addr == PC
always@(posedge clk or posedge rst)begin
	if(rst) begin
		instr_addr <= 0;
		Tmp <= 0;
	end
	else if(Write_Back)begin//default
		/*add your code*/
		Tmp        <= Tmp + 4;
		instr_addr <= Tmp + 4;
	end
end
////////////////////////////////////////////////

////////////////////////////////////////////////
//data_addr
always@(posedge clk or posedge rst)begin
	if(rst)
		data_addr <= 32'h0;
	else if(Execute)begin
		case(opcode)
			7'b0100011:begin//S-type
				/*add your code*/
				data_addr <= Register[rs1] + $signed(Immediate);
			end
		endcase
	end
end
////////////////////////////////////////////////

////////////////////////////////////////////////
//data_write
always@(posedge clk or posedge rst)begin
	if(rst)
		data_write <= 4'h0;
	else if(Execute)begin
		case(opcode)
			7'b0100011:begin
				case(funct3)
					3'b010:begin//SW
						data_write <= 4'hf;
					end
				endcase
			end
		endcase
	end
	else if(Memory_Access)
		data_write <= 4'h0;
end
////////////////////////////////////////////////

////////////////////////////////////////////////
//data_in
always@(posedge clk or posedge rst)begin
	if(rst)
		data_in <= 0;
	else if(Execute)begin
		case(opcode)
			7'b0100011:begin
				if(Register[rs1][1:0] + Immediate[1:0] == 2'b0)
					data_in <= Register[rs2];
			end
		endcase
	end
end
////////////////////////////////////////////////

////////////////////////////////////////////////
//2C 1S
always@(posedge clk or posedge rst)begin
	if(rst)
		CurrentState <= 0;
	else
		CurrentState <= NextState;
end

always@(*)begin
	case(CurrentState)
		Idle_state: 				NextState = Instruction_Fetch_state;	//Reset
		Instruction_Fetch_state: 	NextState = Instruction_Decode_state;	//Instruction Fetch
		Instruction_Decode_state: 	NextState = Execute_state;				//Instruction Decode
		Execute_state: 				NextState = Memory_Access_state;		//Execute
		Memory_Access_state: 		NextState = Write_Back_state;			//Memory Access
		Write_Back_state: 			NextState = Instruction_Fetch_state;	//Write Back
		default: 					NextState = Finish_state; 				//finish
	endcase
end

always@(*)begin
	case(CurrentState)
		Idle_state:begin//Reset
			Instruction_Fetch = 0;
			Instruction_Decode = 0;
			Execute = 0;
			Memory_Access = 0;
			Write_Back = 0;
        end
        Instruction_Fetch_state:begin//Instruction Fetch
			Instruction_Fetch = 1;
            Instruction_Decode = 0;
            Execute = 0;
            Memory_Access = 0;
            Write_Back = 0;
        end
        Instruction_Decode_state:begin//Instruction Decode
			Instruction_Fetch = 0;
            Instruction_Decode = 1;
            Execute = 0;
            Memory_Access = 0;
            Write_Back = 0;
        end
        Execute_state:begin//Execute
			Instruction_Fetch = 0;
            Instruction_Decode = 0;
            Execute = 1;
            Memory_Access = 0;
            Write_Back = 0;
        end
        Memory_Access_state:begin//Memory Access
			Instruction_Fetch = 0;
            Instruction_Decode = 0;
            Execute = 0;
            Memory_Access = 1;
            Write_Back = 0;
        end
        Write_Back_state:begin//Write Back
			Instruction_Fetch = 0;
            Instruction_Decode = 0;
            Execute = 0;
            Memory_Access = 0;
            Write_Back = 1;
        end
        default: begin//finish
			Instruction_Fetch = 0;
            Instruction_Decode = 0;
            Execute = 0;
            Memory_Access = 0;
            Write_Back = 0;
        end
	endcase
end
////////////////////////////////////////////////

endmodule
