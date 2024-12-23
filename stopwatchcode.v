module stopwatch (
    input clk,           // System clock
    input reset,         // Reset signal
    input start_stop,    // Start/Stop toggle button
    output reg [3:0] sec_ones,  // Ones place of seconds
    output reg [3:0] sec_tens,  // Tens place of seconds
    output reg [3:0] min_ones,  // Ones place of minutes
    output reg [3:0] min_tens   // Tens place of minutes
);
    reg running;              // Stopwatch running status
    reg [23:0] clk_divider;   // Clock divider for 1 Hz
    reg tick;                 // 1 Hz clock signal

    // Clock Divider for 1 Hz
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            clk_divider <= 0;
            tick <= 0;
        end else if (clk_divider == 24_999_999) begin
            clk_divider <= 0;
            tick <= 1;
        end else begin
            clk_divider <= clk_divider + 1;
            tick <= 0;
        end
    end

    // Start/Stop Logic
    always @(posedge start_stop or posedge reset) begin
        if (reset)
            running <= 0;
        else
            running <= ~running;
    end

    // Stopwatch Counter Logic
    always @(posedge tick or posedge reset) begin
        if (reset) begin
            sec_ones <= 0;
            sec_tens <= 0;
            min_ones <= 0;
            min_tens <= 0;
        end else if (running) begin
            if (sec_ones == 9) begin
                sec_ones <= 0;
                if (sec_tens == 5) begin
                    sec_tens <= 0;
                    if (min_ones == 9) begin
                        min_ones <= 0;
                        if (min_tens == 5)
                            min_tens <= 0;
                        else
                            min_tens <= min_tens + 1;
                    end else
                        min_ones <= min_ones + 1;
                end else
                    sec_tens <= sec_tens + 1;
            end else
                sec_ones <= sec_ones + 1;
        end
    end
endmodule

