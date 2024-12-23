// Segment pins
const int segA = 10;
const int segB = 11;
const int segC = 12;
const int segD = 13;
const int segE = A0;
const int segF = A1;
const int segG = A2;
const int segDP = A3;

// Digit control pins
const int digit1 = 6;
const int digit2 = 7;
const int digit3 = 8;
const int digit4 = 9;

// Segment encoding for numbers 0-9 (Common Cathode)
const byte digitSegments[10] = {
    0b0111111, // 0
    0b0000110, // 1
    0b1011011, // 2
    0b1001111, // 3
    0b1100110, // 4
    0b1101101, // 5
    0b1111101, // 6
    0b0000111, // 7
    0b1111111, // 8
    0b1101111  // 9
};

// Variables for stopwatch
unsigned int milliseconds = 0;
unsigned int seconds = 0;
bool running = false;

void setup() {
    // Set segment pins as output
    pinMode(segA, OUTPUT);
    pinMode(segB, OUTPUT);
    pinMode(segC, OUTPUT);
    pinMode(segD, OUTPUT);
    pinMode(segE, OUTPUT);
    pinMode(segF, OUTPUT);
    pinMode(segG, OUTPUT);
    pinMode(segDP, OUTPUT);

    // Set digit pins as output
    pinMode(digit1, OUTPUT);
    pinMode(digit2, OUTPUT);
    pinMode(digit3, OUTPUT);
    pinMode(digit4, OUTPUT);

    // Set digit pins HIGH (turn off digits initially)
    digitalWrite(digit1, HIGH);
    digitalWrite(digit2, HIGH);
    digitalWrite(digit3, HIGH);
    digitalWrite(digit4, HIGH);

    // Start serial communication for start/stop/reset
    Serial.begin(9600);
}

void loop() {
    // Check for serial input commands
    if (Serial.available()) {
        char command = Serial.read();
        if (command == 's') running = !running; // Start/Stop
        if (command == 'r') {                  // Reset
            milliseconds = 0;
            seconds = 0;
        }
    }

    // Update the stopwatch
    if (running) {
        delay(10); // 10ms interval
        milliseconds += 10;
        if (milliseconds >= 1000) {
            milliseconds = 0;
            seconds++;
        }
    }

    // Display the time
    displayTime(seconds);
}

void displayTime(unsigned int time) {
    // Split the time into digits
    int digitValues[4];
    digitValues[0] = (time / 1000) % 10; // Thousands place
    digitValues[1] = (time / 100) % 10;  // Hundreds place
    digitValues[2] = (time / 10) % 10;   // Tens place
    digitValues[3] = time % 10;          // Units place

    // Display each digit sequentially
    for (int i = 0; i < 4; i++) {
        setDigit(i + 1);
        displayDigit(digitValues[i]);
        delay(5); // Persistence of vision
        clearSegments();
    }
}

void setDigit(int digit) {
    // Activate the corresponding digit
    digitalWrite(digit1, digit == 1 ? LOW : HIGH);
    digitalWrite(digit2, digit == 2 ? LOW : HIGH);
    digitalWrite(digit3, digit == 3 ? LOW : HIGH);
    digitalWrite(digit4, digit == 4 ? LOW : HIGH);
}

void displayDigit(int num) {
    // Send the segment data to the display
    byte segments = digitSegments[num];
    digitalWrite(segA, segments & 0b0000001);
    digitalWrite(segB, segments & 0b0000010);
    digitalWrite(segC, segments & 0b0000100);
    digitalWrite(segD, segments & 0b0001000);
    digitalWrite(segE, segments & 0b0010000);
    digitalWrite(segF, segments & 0b0100000);
    digitalWrite(segG, segments & 0b1000000);
}

void clearSegments() {
    // Turn off all segments
    digitalWrite(segA, LOW);
    digitalWrite(segB, LOW);
    digitalWrite(segC, LOW);
    digitalWrite(segD, LOW);
    digitalWrite(segE, LOW);
    digitalWrite(segF, LOW);
    digitalWrite(segG, LOW);
    digitalWrite(segDP, LOW);
}
