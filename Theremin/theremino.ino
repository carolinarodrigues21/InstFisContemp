#include "Volume.h"

Volume vol;

// Speaker pin 5

int Speaker = 5;

// Declara trig e echo do primeiro sensor (Frequência)
#define trigPin1 4 // Declara constante trigPin
#define echoPin1 2 // Declara constante como echoPin

// Declara trig e echo do segundo sensor (Volume)
#define trigPin2 7 // Declara constante trigPin
#define echoPin2 8 // Declara constante como echoPin

 // Inicializa variável de frequência em 0
int duration1, distance1 ; // Inicializa variável de distância e tempo
int duration2, distance2 ; // Inicializa variável de distância e tempo

int frequencia = 0;

int freq1 = 10;
int freq2 = 50;
int freq3 = 150;
int freq4 = 250;

void setup() {
 Serial.begin (9600);
 pinMode(trigPin1, OUTPUT);
 pinMode(echoPin1, INPUT);
 
 pinMode(trigPin2, OUTPUT);
 pinMode(echoPin2, INPUT);

 pinMode(Speaker,OUTPUT);

 vol.begin();
 
}

void loop() {
 digitalWrite(trigPin1, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin1, LOW);
 duration1 = pulseIn(echoPin1, HIGH);
 distance1 = (duration1 / 2) / 29.1; // Define base do cálculo de conversão
 
 if (distance1 >= 40 || distance1 <= 0) { // Define as distâncias bases de verificação
  frequencia = 0;
  Serial.print(" | D1 = ");
  Serial.print(distance1);
  Serial.print(" range 5 de frequencia");
  noTone(Speaker);
 }
 else if (distance1>= 30 && distance1<= 40 ) { // Define as distâncias bases de verificação
  frequencia = freq4;
  Serial.print(" | D1 = ");
  Serial.print(distance1);
  Serial.print(" range 4 de frequencia");
  tone(Speaker, freq4);
 }
 else if (distance1>= 20 && distance1<= 30 ) { // Define as distâncias bases de verificação
  frequencia = freq3;
  Serial.print(" | D1 = ");
  Serial.print(distance1);
  Serial.print(" range 3 de frequencia");
  tone(Speaker, freq3);
 }
 else if (distance1>= 10 && distance1<= 20 ) { // Define as distâncias bases de verificação
  frequencia = freq2;
  Serial.print(" | D1 = ");
  Serial.print(distance1);
  Serial.print(" range 2 de frequencia");
  tone(Speaker, freq2);
 }
 else { // Define as distâncias bases de verificação
  frequencia = freq1;
  Serial.print(" | D1 = ");
  Serial.print(distance1);
  Serial.print(" range 1 de frequencia");
  tone(Speaker, freq1);
 }

 delay(100);

 digitalWrite(trigPin2, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin2, LOW);
 duration2 = pulseIn(echoPin2, HIGH);

 distance2 = (duration2 / 2) / 29.1;
  
 //Controle de Volume
 byte volumes[4] = {255, 127, 12, 0};   // List of volumes: 100% Volume, 50% Volume, 5% Volume, 0% Volume
 int mapeamento = map(distance2, 0, 40, volumes[3], volumes[0]); //define valores pwm (0 a 255)o
  
 Serial.print("D = ");
 Serial.print(distance2);
 Serial.print(" | MAP = ");
 Serial.println(mapeamento);
 vol.tone(frequencia, mapeamento);
 delay(100);
 
}
