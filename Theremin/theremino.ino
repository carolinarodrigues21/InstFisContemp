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

int freq1 = 100;
int freq2 = 200;
int freq3 = 300;
int freq4 = 400;

int LED1 = 13;
int LED2 = 12;
int LED3 = 9;
int LED4 = 3;

void setup() {
 Serial.begin (9600);
 pinMode(trigPin1, OUTPUT);
 pinMode(echoPin1, INPUT);
 
 pinMode(trigPin2, OUTPUT);
 pinMode(echoPin2, INPUT);

 pinMode(Speaker,OUTPUT);

 pinMode(LED1,OUTPUT);
 pinMode(LED2,OUTPUT);
 pinMode(LED3,OUTPUT);
 pinMode(LED4,OUTPUT);

 vol.begin();
 
}

void controleVolume(int frequencia){
 digitalWrite(trigPin2, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin2, LOW);
 duration2 = pulseIn(echoPin2, HIGH);

 distance2 = (duration2 / 2) / 29.1;
 //Controle de Volume
 byte volumes[4] = {255, 127, 12, 0};   // List of volumes: 100% Volume, 50% Volume, 5% Volume, 0% Volume
 int mapeamento = map(distance2, 0, 40, volumes[3], volumes[0]); //define valores pwm (0 a 255)
  
 Serial.print("D2 = ");
 Serial.print(distance2);
 Serial.print(" | MAP = ");
 Serial.println(mapeamento);
 vol.tone(frequencia, mapeamento);
 delay(100);
}

void loop() {
 digitalWrite(trigPin1, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin1, LOW);
 duration1 = pulseIn(echoPin1, HIGH);
 distance1 = (duration1 / 2) / 29.1; // Define base do cálculo de conversão
 
 if (distance1 >= 25 || distance1 <= 0) { // Define as distâncias bases de verificação
  frequencia = 0;
  Serial.print(" | D1 = ");
  Serial.print(distance1);
  Serial.print(" range 5 de frequencia \n");
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  digitalWrite(LED4,LOW);
  noTone(Speaker);
 }
 else if (distance1>= 20 && distance1<= 25 ) { // Define as distâncias bases de verificação
  frequencia = freq4;
  Serial.print(" | D1 = ");
  Serial.print(distance1);
  Serial.print(" range 4 de frequencia");
  digitalWrite(LED4,HIGH);
  digitalWrite(LED3,HIGH);
  digitalWrite(LED2,HIGH);
  digitalWrite(LED1,HIGH);
  controleVolume(freq4);
  //tone(Speaker, freq4);
 }
 else if (distance1>= 15 && distance1<= 20) { // Define as distâncias bases de verificação
  frequencia = freq3;
  digitalWrite(LED4,LOW);
  digitalWrite(LED3,HIGH);
  digitalWrite(LED2,HIGH);
  digitalWrite(LED1,HIGH);
  Serial.print(" | D1 = ");
  Serial.print(distance1);
  Serial.print(" range 3 de frequencia \n");
  controleVolume(freq3);
  //tone(Speaker, freq3);
 }
 else if (distance1>= 10 && distance1<= 15 ) { // Define as distâncias bases de verificação
  frequencia = freq2;
  digitalWrite(LED4,LOW);
  digitalWrite(LED3,LOW);
  digitalWrite(LED2,HIGH);
  digitalWrite(LED1,HIGH);
  Serial.print(" | D1 = ");
  Serial.print(distance1);
  Serial.print(" range 2 de frequencia \n");
  controleVolume(freq2);
  //tone(Speaker, freq2);
 }
 else { // Define as distâncias bases de verificação
  frequencia = freq1;
  digitalWrite(LED1,HIGH);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  digitalWrite(LED4,LOW);
  Serial.print(" | D1 = ");
  Serial.print(distance1);
  Serial.print(" range 1 de frequencia \n");
  controleVolume(freq1);
  //tone(Speaker, freq1);
 }

 delay(100);
 
}
