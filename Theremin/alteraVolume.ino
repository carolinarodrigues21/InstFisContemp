const int pinPot = A4; // Indica a porta analógica ligada ao potenciômetro
const int pinBuzzer = 3; // Indica a porta digital ligada ao buzzer (PWM)
#define trigPin 7 // Declara constante trigPin
#define echoPin 8 // Declara constante como echoPin
int duration, distance; // Inicializa variável de distância e tempo

void setup(){
  pinMode(pinBuzzer, OUTPUT);
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
  
  int pwm = map(distance, 0, 40, 0, 255); //define valores pwm (0 a 255)o
  
  Serial.print("D = ");
  Serial.print(distance);
  Serial.print(" | PWM = ");
  Serial.println(pwm);

  analogWrite(pinBuzzer, pwm);
     
}