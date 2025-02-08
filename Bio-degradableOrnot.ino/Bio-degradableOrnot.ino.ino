#define MOISTURE_SENSOR A0  // Moisture sensor pin
#define GAS_SENSOR A1       // Gas sensor pin
#define WEIGHT_SENSOR A2    // Load cell for weight detection
#define COLOR_SENSOR A3     // Color sensor (simulated)

void setup() {
    Serial.begin(9600);
    pinMode(MOISTURE_SENSOR, INPUT);
    pinMode(GAS_SENSOR, INPUT);
    pinMode(WEIGHT_SENSOR, INPUT);
    pinMode(COLOR_SENSOR, INPUT);
}

void loop() {
    int moisture = analogRead(MOISTURE_SENSOR);
    int gas = analogRead(GAS_SENSOR);
    int weight = analogRead(WEIGHT_SENSOR);
    int color = analogRead(COLOR_SENSOR); // Simulating color detection

    Serial.print("Moisture: "); Serial.println(moisture);
    Serial.print("Gas Level: "); Serial.println(gas);
    Serial.print("Weight: "); Serial.println(weight);
    Serial.print("Color Value: "); Serial.println(color);

    // Classification Logic
    if (moisture > 500 && gas > 400) {
        Serial.println("Detected: Biodegradable Waste");
    } else if (color > 600) {  
        Serial.println("Detected: Non-Biodegradable Waste (e.g., Plastic)");
    } else {
        Serial.println("Unknown Waste Type - Needs Manual Sorting");
    }
    
    delay(2000);  // Wait before next reading
}
