#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define Ultrasonic Sensor Pins
const int trigPin1 = 2;  // High Reservoir Sensor
const int echoPin1 = 3;  
const int trigPin2 = 4;  // Low Reservoir Sensor
const int echoPin2 = 5;  

// Define LED and Buzzer Pins
int ledA = 13;  // RED LED 1
int ledB = 12;  // BLUE LED 1
int buzzerPin1 = 11;  
int ledC = 10;  // RED LED 2
int ledD = 9;   // BLUE LED 2
int buzzerPin2 = 8;  

// Threshold values for high reservoir
const int a = 27;   
const int b = 28;  
const int c = 31;  

// Threshold values for low reservoir
const int d = 37;  
const int e = 40;  
const int f = 50;  

// LCD object
LiquidCrystal_I2C lcd(0x27, 16, 2);

long previousDistance1 = 0, previousDistance2 = 0;
unsigned long previousTime = 0;
unsigned long startTime = 0;
bool isSleeping = false;

void setup() {
    Serial.begin(9600);

    // Initialize Pins
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    
    pinMode(ledA, OUTPUT);
    pinMode(ledB, OUTPUT);
    pinMode(buzzerPin1, OUTPUT);
    pinMode(ledC, OUTPUT);
    pinMode(ledD, OUTPUT);
    pinMode(buzzerPin2, OUTPUT);

    // Reset Outputs
    resetOutputs1();
    resetOutputs2();

    // Initialize LCD
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Flood Monitor");
    delay(1500);
    lcd.clear();

    startTime = millis();  // Start the timer
}

void loop() {
    unsigned long currentTime = millis();
    unsigned long elapsedTime = (currentTime - startTime) / 1000;  // Convert to seconds

    // Sleep Condition: Only sleep if no alerts are active
    if (elapsedTime >= 45 && !isSleeping && !isAlertActive()) {
        isSleeping = true;
        resetOutputs1();
        resetOutputs2();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Sleeping...");
        delay(15000); // Sleep for 15s
        startTime = millis();  // Restart the timer
        isSleeping = false;
        lcd.clear();
    }

    if (!isSleeping) {
        float timeDiff = (currentTime - previousTime) / 1000.0;  // Convert to seconds

        long distance1 = getDistance(trigPin1, echoPin1);
        long distance2 = getDistance(trigPin2, echoPin2);

        float rateOfChange1 = (previousTime != 0) ? (distance1 - previousDistance1) / timeDiff : 0;
        float rateOfChange2 = (previousTime != 0) ? (distance2 - previousDistance2) / timeDiff : 0;

        // Update LCD
        lcd.setCursor(0, 0);
        lcd.print("D1:");
        lcd.print(distance1);
        lcd.print("cm R:");
        lcd.print(abs(rateOfChange1));
        lcd.print("  ");

        lcd.setCursor(0, 1);
        lcd.print("D2:");
        lcd.print(distance2);
        lcd.print("cm R:");
        lcd.print(abs(rateOfChange2));
        lcd.print("  ");

        // High Reservoir Alert Logic
        if (distance1 <= a || rateOfChange1 >= 25 ) {
            activateBuzzer1();
        } else if (distance1 <= b) {
            activateLedB();
        } else if (distance1 <= c) {
            activateLedA();
        } else {
            resetOutputs1();
        }

        // Low Reservoir Alert Logic
        if (distance2 <= d || rateOfChange1 >= 25 ) {
            activateBuzzer2();
        } else if (distance2 <= e) {
            activateLedD();
        } else if (distance2 <= f) {
            activateLedC();
        } else {
            resetOutputs2();
        }

        // Update previous values
        previousDistance1 = distance1;
        previousDistance2 = distance2;
        previousTime = currentTime;
    }

    delay(250);
}

// Function to get distance from ultrasonic sensor
long getDistance(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 20000);
    if (duration == 0) return -1;  // Return -1 if no valid pulse detected
    return duration / 58;  // Convert to cm
}

// Function to check if any alert is active
bool isAlertActive() {
    long distance1 = getDistance(trigPin1, echoPin1);
    long distance2 = getDistance(trigPin2, echoPin2);

    float rateOfChange1 = (previousTime != 0) ? (distance1 - previousDistance1) / ((millis() - previousTime) / 1000.0) : 0;
    float rateOfChange2 = (previousTime != 0) ? (distance2 - previousDistance2) / ((millis() - previousTime) / 1000.0) : 0;

    return (distance1 <= a || distance1 <= b || distance1 <= c || rateOfChange1 >= 25 ||
            distance2 <= d || distance2 <= e || distance2 <= f || rateOfChange2 >= 25);
}

// High Reservoir Control
void activateLedA() {
    digitalWrite(ledA, HIGH);
    digitalWrite(ledB, LOW);
    digitalWrite(buzzerPin1, LOW);
}

void activateLedB() {
    digitalWrite(ledA, LOW);
    digitalWrite(ledB, HIGH);
    digitalWrite(buzzerPin1, LOW);
}

void activateBuzzer1() {
    digitalWrite(ledA, LOW);
    digitalWrite(ledB, LOW);
    digitalWrite(buzzerPin1, HIGH);
}

void resetOutputs1() {
    digitalWrite(ledA, LOW);
    digitalWrite(ledB, LOW);
    digitalWrite(buzzerPin1, LOW);
}

// Low Reservoir Control
void activateLedC() {
    digitalWrite(ledC, HIGH);
    digitalWrite(ledD, LOW);
    digitalWrite(buzzerPin2, LOW);
}

void activateLedD() {
    digitalWrite(ledC, LOW);
    digitalWrite(ledD, HIGH);
    digitalWrite(buzzerPin2, LOW);
}

void activateBuzzer2() {
    digitalWrite(ledC, LOW);
    digitalWrite(ledD, LOW);
    digitalWrite(buzzerPin2, HIGH);
}

void resetOutputs2() {
    digitalWrite(ledC, LOW);
    digitalWrite(ledD, LOW);
    digitalWrite(buzzerPin2, LOW);
}
