const int touchsensorpin1=2;
const int ledpin1=3;
const int touchsensorpin2=12;
const int ledpin2=11;

#include <TM1637Display.h>

#define CLK_PIN 6
#define DIO_PIN 7
//const int buzzer=8;
int number=0;
TM1637Display display(CLK_PIN, DIO_PIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(touchsensorpin1,INPUT);
  pinMode(ledpin1,OUTPUT);
  pinMode(touchsensorpin1,INPUT);

  Serial.begin(touchsensorpin2,INPUT);
  pinMode(ledpin2,OUTPUT);
  pinMode(touchsensorpin2,INPUT);
  //pinMode(buzzer,OUTPUT);
  display.setBrightness(5);   // Brightness level (0–7)
  display.clear(); 
}

void loop()
{
  // put your main code here, to run repeatedly:
  int touchstate1=digitalRead(touchsensorpin1);
  int touchstate2=digitalRead(touchsensorpin2);
  if(touchstate1==HIGH||touchstate2==HIGH)
  {
    if (touchstate1==HIGH)
    {
    Serial.println("The sensor 1 is being touched");
    digitalWrite(ledpin1,HIGH);
    //tone(buzzer,1000,200);
    delay(1000);
    number++;
    }
    if (touchstate2==HIGH)
    {
    Serial.println("The sensor 1 is being touched");
    digitalWrite(ledpin2,HIGH);
    //tone(buzzer,1000,200);
    delay(1000);
    number++;
    }
  }
  else
  {
    if(touchstate1==LOW)
    {
    Serial.println("The sensor 1 is untouched");
    digitalWrite(ledpin1,LOW);
    digitalWrite(ledpin2,LOW);
    //noTone(buzzer);
    delay(1000);
    }
    if(touchstate2==LOW)
    {
    Serial.println("The sensor 2 is untouched");
    digitalWrite(ledpin1,LOW);
    digitalWrite(ledpin2,LOW);
    //noTone(buzzer);
    delay(1000);
    }
  }

  display.showNumberDec(number); // Display number
  //delay(1000);  
}
