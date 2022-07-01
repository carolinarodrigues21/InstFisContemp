#include "Volume.h" // Include the Volume library
#define trigPin 7 // Declara constante trigPin
#define echoPin 8 // Declara constante como echoPin
int duration, distance; // Inicializa variável de distância e tempo

// speaker connected to digital pin 5

Volume vol; // Plug your speaker into the default pin for your board type:
// https://github.com/connornishijima/arduino-volume1#supported-pins

void setup() {
  vol.begin();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}
 
void loop(){
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1; // Define base do cálculo de conversão

  byte volumes[4] = {255, 127, 12, 0};   // List of volumes: 100% Volume, 50% Volume, 5% Volume, 0% Volume
  int mapeamento = map(distance, 0, 40, volumes[3], volumes[0]); //define valores pwm (0 a 255)o
  
  Serial.print("D = ");
  Serial.print(distance);
  Serial.print(" | MAP = ");
  Serial.println(mapeamento);
  vol.tone(440, mapeamento);
  delay(100);
     
}
