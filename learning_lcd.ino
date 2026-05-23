
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Create LCD object (address 0x27, 16 chars, 2 lines)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Messages to display
String line1 = "Amritaa Cricket  ";
String line2 = "Analyst 2027";
void setup() {
  lcd.init();       // Initialize I2C LCD
  lcd.backlight();  // Turn on LCD backlight
}

void loop() {
  lcd.clear();

  // Print Line 1 character by character
  lcd.setCursor(0, 0);
  for (int i = 0; i < line1.length(); i++) {
    lcd.print(line1[i]);
    delay(200); // Delay between each character
  }

  // Print Line 2 character by character
  lcd.setCursor(0, 1);
  for (int i = 0; i < line2.length(); i++) {
    lcd.print(line2[i]);
    delay(200); // Delay between each character
  }

  delay(2000); // Pause after message is complete
}
