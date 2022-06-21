
#define trigPin 7 // Declara constante trigPin
#define echoPin 8 // Declara constante como echoPin

int frequencia = 0; // Inicializa variável de frequência em 0
int Buzzer = 3; // Inicializa buzzer no pino 13
int duration, distance; // Inicializa variável de distância e tempo

void setup() {
 Serial.begin (9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(Buzzer, OUTPUT);
}

void loop() {
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 distance = (duration / 2) / 29.1; // Define base do cálculo de conversão
 
 if (distance >= 40 || distance <= 0) { // Define as distâncias bases de verificação
  Serial.print(distance);
  Serial.print("\n");
  Serial.print("range 5 \n");
  noTone(Buzzer);
 }
 else if (distance>= 30 && distance<= 40 ) { // Define as distâncias bases de verificação
  Serial.print(distance);
  Serial.print("range 4 \n");
  Serial.print("\n");
  tone(Buzzer, 150);
 }
 else if (distance>= 20 && distance<= 30 ) { // Define as distâncias bases de verificação
  Serial.print(distance);
  Serial.print("range 3 \n");
  Serial.print("\n");
  tone(Buzzer, 100);
 }
 else if (distance>= 10 && distance<= 20 ) { // Define as distâncias bases de verificação
  Serial.print(distance);
  Serial.print("range 2 \n");
  Serial.print("\n");
  tone(Buzzer, 50);
 }
 else { // Define as distâncias bases de verificação
  Serial.print(distance);
  Serial.print("range 1 \n");
  Serial.print("\n");
  tone(Buzzer, 10);
 }
 delay(500);
}
