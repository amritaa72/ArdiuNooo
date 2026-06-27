#include <Servo.h>

// ─────────────────────────────────────────
//  SERVO SETUP — Tuned for MG996R
// ─────────────────────────────────────────
// MG996R typically needs a wider pulse range (≈500–2500 µs)
// than the Arduino Servo.h default (544–2400 µs) to hit its
// full 0–180° travel accurately. Adjust these two numbers
// (MIN_PULSE / MAX_PULSE) if your specific units undershoot
// or overshoot the limit angles.
#define MIN_PULSE 500
#define MAX_PULSE 2500

Servo horizontal;
Servo vertical;

int servohori          = 90;   // Start at center
int servohoriLimitHigh = 170;
int servohoriLimitLow  = 10;

int servovert          = 45;   // Start at 45° tilt
int servovertLimitHigh = 90;
int servovertLimitLow  = 10;

// ─────────────────────────────────────────
//  LDR PIN CONNECTIONS (unchanged)
// ─────────────────────────────────────────
int ldrlt = A0;  // Bottom Left  LDR
int ldrrt = A3;  // Bottom Right LDR
int ldrld = A1;  // Top Left     LDR
int ldrrd = A2;  // Top Right    LDR

// ─────────────────────────────────────────
//  TUNING PARAMETERS
// ─────────────────────────────────────────
int tol   = 90;   // Tolerance — raise if motors jitter, lower if too sluggish
int dtime = 15;   // Delay per loop in ms

void setup() {
  Serial.begin(9600);
  Serial.println("==============================");
  Serial.println("   SOLAR TRACKER INITIALIZING");
  Serial.println("   (MG996R servo profile)");
  Serial.println("==============================");

  // IMPORTANT — POWER NOTE FOR MG996R:
  // These are high-torque metal-gear servos that can pull
  // 500mA-2.5A each under load/stall, especially both moving
  // at once. Do NOT power them from the Arduino 5V pin or USB.
  // Use a separate 5-6V supply rated for at least 3A, with the
  // supply GND tied to Arduino GND. A 470-1000µF capacitor
  // across the servo power rails is recommended to smooth
  // inrush current and prevent resets/glitches.

  // Detach first to prevent twitching during boot
  horizontal.detach();
  vertical.detach();
  delay(500);

  // Attach with explicit pulse-width range calibrated for MG996R
  horizontal.attach(9, MIN_PULSE, MAX_PULSE);
  vertical.attach(10, MIN_PULSE, MAX_PULSE);

  horizontal.write(servohori);   // 90° center
  vertical.write(servovert);     // 45° tilt

  Serial.println("Servos initialized:");
  Serial.print("  Horizontal -> "); Serial.print(servohori); Serial.println("°  (center)");
  Serial.print("  Vertical   -> "); Serial.print(servovert); Serial.println("°  (45 tilt)");
  Serial.println("Stabilizing...");
  delay(2500);
  Serial.println("Ready. Starting tracking loop.");
  Serial.println("------------------------------");
}

void loop() {

  // ── Read all 4 LDRs ──────────────────────
  int lt = analogRead(ldrlt);   // Bottom Left
  int rt = analogRead(ldrrt);   // Bottom Right
  int ld = analogRead(ldrld);   // Top Left
  int rd = analogRead(ldrrd);   // Top Right

  // ── Compute averages ─────────────────────
  int avt = (lt + rt) / 2;   // Average Top    (bottom-left + bottom-right)
  int avd = (ld + rd) / 2;   // Average Bottom (top-left   + top-right)
  int avl = (lt + ld) / 2;   // Average Left
  int avr = (rt + rd) / 2;   // Average Right

  // ── Compute differences ──────────────────
  int dvert  = avt - avd;
  int dhoriz = avl - avr;

  // ── Serial Monitor Output ────────────────
  Serial.print("LDR      | BotL="); Serial.print(lt);
  Serial.print("  BotR=");          Serial.print(rt);
  Serial.print("  TopL=");          Serial.print(ld);
  Serial.print("  TopR=");          Serial.println(rd);

  Serial.print("AVG      | Top=");  Serial.print(avt);
  Serial.print("  Bot=");           Serial.print(avd);
  Serial.print("  Left=");          Serial.print(avl);
  Serial.print("  Right=");         Serial.println(avr);

  Serial.print("DIFF     | V=");    Serial.print(dvert);
  Serial.print("  H=");             Serial.println(dhoriz);

  // ── Vertical Tracking ────────────────────
  if (abs(dvert) > tol) {
    if (avt > avd) {
      servovert++;
      if (servovert > servovertLimitHigh) {
        servovert = servovertLimitHigh;
        Serial.println("VERTICAL | Limit reached (MAX)");
      } else {
        Serial.print("VERTICAL | Moving UP   -> "); Serial.println(servovert);
      }
    } else {
      servovert--;
      if (servovert < servovertLimitLow) {
        servovert = servovertLimitLow;
        Serial.println("VERTICAL | Limit reached (MIN)");
      } else {
        Serial.print("VERTICAL | Moving DOWN -> "); Serial.println(servovert);
      }
    }
    vertical.write(servovert);
  } else {
    Serial.println("VERTICAL | Stable (within tolerance)");
  }

  // ── Horizontal Tracking ──────────────────
  if (abs(dhoriz) > tol) {
    if (avl > avr) {
      servohori--;
      if (servohori < servohoriLimitLow) {
        servohori = servohoriLimitLow;
        Serial.println("HORIZONTAL | Limit reached (MIN)");
      } else {
        Serial.print("HORIZONTAL | Moving LEFT  -> "); Serial.println(servohori);
      }
    } else {
      servohori++;
      if (servohori > servohoriLimitHigh) {
        servohori = servohoriLimitHigh;
        Serial.println("HORIZONTAL | Limit reached (MAX)");
      } else {
        Serial.print("HORIZONTAL | Moving RIGHT -> "); Serial.println(servohori);
      }
    }
    horizontal.write(servohori);
  } else {
    Serial.println("HORIZONTAL | Stable (within tolerance)");
  }

  Serial.println("------------------------------");
  delay(dtime);
}
