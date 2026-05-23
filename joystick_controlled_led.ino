// Pin definitions
#define VRX_PIN A1    // Joystick X-axis
#define VRY_PIN A0    // Joystick Y-axis
#define SW_PIN  9     // Joystick button
#define rled 2
#define bled 3
#define gled 4
#define wled 5

void setup() {
  Serial.begin(9600);      // Start Serial Monitor
  pinMode(SW_PIN, INPUT_PULLUP); // Use internal pull-up for button
  pinMode(rled,OUTPUT);
  pinMode(bled,OUTPUT);
  pinMode(gled,OUTPUT);
  pinMode(wled,OUTPUT);
  delay(2000);
  Serial.println("AYNOP: Joystick Started");
}

void loop() {
  int xValue = analogRead(VRX_PIN);   // Read X-axis (0–1023)
  int yValue = analogRead(VRY_PIN);   // Read Y-axis (0–1023)
  int buttonState = digitalRead(SW_PIN); // Read button (LOW = pressed)

  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" | Y: ");
  Serial.print(yValue);
  Serial.print(" | Button: ");



  if (yValue < 400) { //up
    digitalWrite(rled,HIGH);
    digitalWrite(bled,LOW);
    digitalWrite(gled,LOW);
    digitalWrite(wled,LOW);
  } 
  if(yValue > 600)
   { //down
    digitalWrite(rled,LOW);
    digitalWrite(bled,HIGH);
    digitalWrite(gled,LOW);
    digitalWrite(wled,LOW);
  }
  if (xValue < 400) { //up
    digitalWrite(gled,HIGH);
    digitalWrite(wled,LOW);
    digitalWrite(rled,LOW);
    digitalWrite(bled,LOW);
  } 
  if(xValue > 600)
   { //down
    digitalWrite(gled,LOW);
    digitalWrite(wled,HIGH);
    digitalWrite(rled,LOW);
    digitalWrite(bled,LOW);
  }

  delay(300); // Small delay for readability
}

