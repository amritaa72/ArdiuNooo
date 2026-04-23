const int touchsensorpin=2;
const int ledpin=3;
const int buzzer=8;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(touchsensorpin,INPUT);
  pinMode(ledpin,OUTPUT);
  pinMode(touchsensorpin,INPUT);
  pinMode(buzzer,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int touchstate=digitalRead(touchsensorpin);
  if(touchstate==HIGH)
  {
    Serial.println("The sensor is being touched");
    digitalWrite(ledpin,HIGH);
    tone(buzzer,1000,200);
    delay(1000);
  }
  else
  {
    if(touchstate==LOW)
    {
    Serial.println("The sensor is untouched");
    digitalWrite(ledpin,LOW);
    noTone(buzzer);
    delay(1000);
    }
  }
}
