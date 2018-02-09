
const int trig=7;
const int echo=8;
float duration,cm;
void setup() {
  Serial.begin(9600);
  
 pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}

void loop() {
  
  digitalWrite(trig,LOW);
  delayMicroseconds(2000);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  //duration=pulseIn(echo,HIGH);
  //Serial.println(duration);
  cm=(pulseIn(echo,HIGH)/2)/29.1;
  Serial.println(cm);
  delay(500);
}
