int redled=12;
int blueled=11;
int buzzer=10;
int smokeao=A5;
int smokethres=400;

void setup() {
  // put your setup code here, to run once:
  pinMode(redled,OUTPUT);
  pinMode(blueled,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(smokeao,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int analogsensor=analogRead(smokeao);
  Serial.print("Pin A0");
  Serial.println(analogsensor);
  if(analogsensor>smokethres)
  {
    digitalWrite(redled,HIGH);
    digitalWrite(blueled,LOW);
    tone(buzzer,1000,200);
  }
  else
  {
    digitalWrite(redled,LOW);
    digitalWrite(blueled,HIGH);
    noTone(buzzer);
  }
  delay(1000);
}
