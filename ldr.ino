
const int ldrPin = A0;   // LDR voltage divider output → A0
const int ledPin = 13;   // Onboard LED

// Simple threshold (tune after testing): lower value = darker
int darkThreshold = 350; // Try 350; adjust to your room lighting

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  Serial.println(" LDR Light Meter");
  Serial.println("-------------------------------");
}

void loop() {
  // Read the LDR once (0..1023 from 10-bit ADC)
  int sensorValue = analogRead(ldrPin);

  // Convert to a rough percentage (0 = dark, 100 = bright)
  int lightPercent = map(sensorValue, 0, 1023, 0, 100);
  if (lightPercent < 0)   lightPercent = 0;
  if (lightPercent > 100) lightPercent = 100;

  // Simple LED indicator: ON when it's dark
  if (sensorValue < darkThreshold) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  // Print result
  Serial.print("Raw: ");
  Serial.print(sensorValue);
  Serial.print("   Light: ");
  Serial.print(lightPercent);
  Serial.println("%");

  delay(300); // Update about 3 times per second
}
