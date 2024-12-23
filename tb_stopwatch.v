`timescale 1ns/1ps

module tb_stopwatch;
    reg clk;           // Clock
    reg reset;         // Reset signal
    reg start_stop;    // Start/Stop toggle button
    wire [3:0] sec_ones, sec_tens, min_ones, min_tens;  // Outputs

    // Instantiate the stopwatch module
    stopwatch uut (
        .clk(clk),
        .reset(reset),
        .start_stop(start_stop),
        .sec_ones(sec_ones),
        .sec_tens(sec_tens),
        .min_ones(min_ones),
        .min_tens(min_tens)
    );

    // Clock generation (50 MHz)
    always #10 clk = ~clk;

    // Testbench sequence
    initial begin
        // Initialize signals
        clk = 0;
        reset = 1;
        start_stop = 0;

        #50;  // Hold reset for 50 ns
        reset = 0;

        #50;  // Wait for 50 ns
        start_stop = 1;  // Start the stopwatch

        #100000000;  // Simulate for a while (1 second in real time)
        start_stop = 0;  // Stop the stopwatch

        #50000;  // Wait for some time
        reset = 1;  // Reset the stopwatch

        #100;  // Hold reset
        reset = 0;

        #1000000;  // Simulate more time
        $stop;  // End simulation
    end
endmodule
