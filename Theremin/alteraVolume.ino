//Ultrasonic echo to 12 and trig to 13
//DigiPot pin 1 to 2, pin 2 to 3 and pin 7 to 4


const int pot = A4;
const int buzzer = 3;
const int trigPin=7, echoPin=8;
int current_value=0, prev_value=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pot, INPUT); 
  pinMode(buzzer, OUTPUT); 
  for(int j=0; j<100; j++)
  {
    Serial.print("potenciometro diminui 1");
    analogWrite(buzzer, current_value);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, distance;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(trigPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);

  current_value=map(distance, 0, 200, 0, 100);  //change this to your project's maximum possible distance
  Serial.print("  ");
  Serial.println(current_value);
  if(current_value>prev_value)
  {
    for(int i=0; i<(current_value-prev_value); i++)
    {
      Serial.print("potenciometro aumenta 1");
      analogWrite(buzzer, current_value);
    }
  }
  else
  {
    for(int i=0; i<=(prev_value-current_value); i++)
    {
      Serial.print("potenciometro diminui 1");
      analogWrite(buzzer, current_value);
    }
  }

  prev_value=current_value;
  delay(100);
}

