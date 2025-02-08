#include <Servo.h>

// Pin Definitions
#define TRIG_PIN 6       // Ultrasonic Sensor Trigger Pin
#define ECHO_PIN 7       // Ultrasonic Sensor Echo Pin
#define PIR_PIN 2        // PIR Sensor for Motion Detection
#define SERVO_PIN 4      // Servo Motor for Lid
#define BUZZER_PIN 3     // Buzzer
#define LOAD_CELL 8      // Load Sensor for Fullness Detection
#define GAS_SENSOR A0    // Gas Sensor for Odor Detection (Analog Pin)
#define RELAY_PIN 5      // Relay for Motor (if used)

// Initialize Servo
Servo lidServo;

void setup() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(PIR_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LOAD_CELL, INPUT);
    pinMode(GAS_SENSOR, INPUT);
    pinMode(RELAY_PIN, OUTPUT);
    
    lidServo.attach(SERVO_PIN);
    lidServo.write(0); // Keep lid closed at startup

    Serial.begin(9600);
}

void loop() {
    int motionDetected = digitalRead(PIR_PIN);
    float distance = getDistance();
    int wasteLevel = analogRead(LOAD_CELL);
    int odorLevel = analogRead(GAS_SENSOR);

    // Check if person is very close (less than 30 cm)
    if (motionDetected && distance < 30) {
        openLid();
        delay(700);  // Faster operation for running motion
        closeLid();
    }

    // Check if dustbin is full
    if (wasteLevel > 700) {  // Adjust threshold as needed
        alertFull();
    }

    // Check for odor in biodegradable bin
    if (odorLevel > 500) {  // Adjust threshold as needed
        alertOdor();
    }
}

float getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);
    float distance = duration * 0.034 / 2;
    return distance;
}

void openLid() {
    lidServo.write(90);  // Open lid
}

void closeLid() {
    lidServo.write(0);   // Close lid
}

void alertFull() {
    for (int i = 0; i < 3; i++) {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(500);
        digitalWrite(BUZZER_PIN, LOW);
        delay(500);
    }
}

void alertOdor() {
    for (int i = 0; i < 2; i++) {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(200);
        digitalWrite(BUZZER_PIN, LOW);
        delay(200);
    }
}
