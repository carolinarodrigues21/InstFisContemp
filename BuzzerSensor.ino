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
  noTone(Buzzer);
 }

 else {
 Serial.print(distance); // Imprime o valor da distância no Monitor Serial
 Serial.print("\n");
 tone(Buzzer, 10);
 }
 delay(100);
}
