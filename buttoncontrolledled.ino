const int buttonPin = 2;   // Pushbutton connected to digital pin 2
const int ledPin    = 13;  // LED connected to digital pin 13 (onboard LED)

// Variable to store the button state
int buttonState = 0;

void setup() {
  // Set LED pin as OUTPUT
  pinMode(ledPin, OUTPUT);

  // Set button pin as INPUT (external pull-down resistor required)
  pinMode(buttonPin, INPUT);
}

void loop() {
  // Read the state of the pushbutton
  buttonState = digitalRead(buttonPin);

  // Check if the pushbutton is pressed
  if (buttonState == HIGH) {
    // Turn LED ON when button is pressed
    digitalWrite(ledPin, HIGH);
  } else {
    // Turn LED OFF when button is released
    digitalWrite(ledPin, LOW);
  }
}
