// Define constants
const int LM35_PIN = A0; // Analog pin connected to LM35 temperature sensor
const int LED_PIN = 13;  // Digital pin connected to onboard LED

// Function prototypes
float readTemperature();
void blinkLED(int interval);

// Variables to track time
unsigned long previousMillis_LED = 0;
unsigned long previousMillis_Temperature = 0;

// LED blinking interval
const int interval_LED_low = 250; // LED blink interval when temperature is below 30°C
const int interval_LED_high = 500; // LED blink interval when temperature is above or equal to 30°C

void setup() {
  pinMode(LED_PIN, OUTPUT); // Set LED pin as output
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  // Read temperature from LM35 sensor every second
  if (millis() - previousMillis_Temperature >= 1000) {
    previousMillis_Temperature = millis();
    float temperature = readTemperature(); // Read temperature from LM35 sensor
    Serial.print("Temperature: ");
    Serial.println(temperature); // Print temperature to serial monitor
    
    // Control LED blinking based on temperature
    if (temperature < 30) {
      blinkLED(interval_LED_low); // Blink LED every 250 milliseconds if temperature is below 30°C
    } else {
      blinkLED(interval_LED_high); // Blink LED every 500 milliseconds if temperature is above or equal to 30°C
    }
  }
}

// Function to read temperature from LM35 sensor
float readTemperature() {
  int sensorValue = analogRead(LM35_PIN); // Read analog value from LM35 sensor
  float temperature = (sensorValue * 5.0 / 1023.0 * 100.0); // Convert analog value to Celsius
  return temperature; // Return temperature value
}

// Function to blink LED with specified interval
void blinkLED(int interval) {
  if (millis() - previousMillis_LED >= interval / 2) {
    previousMillis_LED = millis();
    digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // Toggle LED state
  }
}
