

// Declara trig e echo do primeiro sensor (Frequência)
#define trigPin1 4 // Declara constante trigPin
#define echoPin1 2 // Declara constante como echoPin

// Declara trig e echo do segundo sensor (Volume)
#define trigPin2 7 // Declara constante trigPin
#define echoPin2 8 // Declara constante como echoPin

int frequencia = 0; // Inicializa variável de frequência em 0
int Buzzer = 3; // Inicializa buzzer no pino 13
int duration1, distance1 ; // Inicializa variável de distância e tempo
int duration2, distance2 ; // Inicializa variável de distância e tempo

void setup() {
 Serial.begin (9600);
 pinMode(trigPin1, OUTPUT);
 pinMode(echoPin1, INPUT);
 
 pinMode(trigPin2, OUTPUT);
 pinMode(echoPin2, INPUT);
 
 pinMode(Buzzer, OUTPUT);
}

void loop() {
 digitalWrite(trigPin1, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin1, LOW);
 duration1 = pulseIn(echoPin1, HIGH);
 distance1 = (duration1 / 2) / 29.1; // Define base do cálculo de conversão
 
 if (distance1 >= 40 || distance1 <= 0) { // Define as distâncias bases de verificação
  Serial.print(" | D1 = ");
  Serial.print(distance1);
  Serial.print(" range 5 de frequencia");
  noTone(Buzzer);
 }
 else if (distance1>= 30 && distance1<= 40 ) { // Define as distâncias bases de verificação
  Serial.print(" | D1 = ");
  Serial.print(distance1);
  Serial.print(" range 4 de frequencia");
  tone(Buzzer, 150);
 }
 else if (distance1>= 20 && distance1<= 30 ) { // Define as distâncias bases de verificação
  Serial.print(" | D1 = ");
  Serial.print(distance1);
  Serial.print(" range 3 de frequencia");
  tone(Buzzer, 100);
 }
 else if (distance1>= 10 && distance1<= 20 ) { // Define as distâncias bases de verificação
  Serial.print(" | D1 = ");
  Serial.print(distance1);
  Serial.print(" range 2 de frequencia");
  tone(Buzzer, 50);
 }
 else { // Define as distâncias bases de verificação
  Serial.print(" | D1 = ");
  Serial.print(distance1);
  Serial.print(" range 1 de frequencia");
  tone(Buzzer, 10);
 }

 delay(100);

 digitalWrite(trigPin2, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin2, LOW);
 duration2 = pulseIn(echoPin2, HIGH);

 distance2 = (duration2 / 2) / 29.1;
  
 //Controle de Volume
 int pwm = map(distance2, 0, 40, 0, 255); //define valores pwm (0 a 255)o
 Serial.print(" D2 = ");
 Serial.print(distance2);
 Serial.print(" | PWM = ");
 Serial.println(pwm);

 analogWrite(Buzzer, pwm);

 delay(300);
 
}
