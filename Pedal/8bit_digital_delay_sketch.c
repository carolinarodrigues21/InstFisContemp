/*****************************************************************************************************************************
  echoTrek - 8Bit Digital Delay / LO-FI Bitcrusher / Reverse Speech DSP Pedal Effects for Guitar, Voice, Synths, etc.
  Works with Arduino UNO R3 / NANO / PRO MINI - See the schematics for wiring details. By J. CesarSound - ver 1.0 - Jan/2021.
******************************************************************************************************************************/

#define audio_in A0
#define time_selector A3

const unsigned int d_size = 1900; //Delay memory buffer size
unsigned int val, d_val, d_time;
int i, j;
byte count = 2;
bool rev = 0;
char delay_data[d_size + 1] = { NULL };  //Delay memory buffer
char delay_data_1[d_size + 1] = { NULL };  //Delay memory buffer
 

void setup() {
  pinMode(time_selector, INPUT_PULLUP);
  DDRD = B00000010;
  DDRB = B11100000;
  InitTimer1();           //Set up timer 1 for 16.384kHz
  setPwmFrequency(5, 1);  //function for setting PWM High frequency 62.475kHz on pin D5
  analogReference(INTERNAL);   //Use 1.1v aref voltage.
  up_time();
}

void loop() {
  if (digitalRead(time_selector) == LOW) {
    up_time();
    PORTB = B11100000;   //make pin 13 high and power on the led when pushbutton is pressed
    while (digitalRead(time_selector) == LOW);
  } else PORTB = B11000000;   //make pin 13 low and power off the led pushbutton is released
  if (rev) PORTD = B00000000; else PORTD = B00000010;   //Reverse speech sampler indication TX Led power on
}

void sampling() {
  val = map(analogRead(audio_in), 0, 900, 0, 255);
  delay_sound();
  analogWrite(5, d_val);
}

void delay_sound() {
  i = i + 1; if (i > d_time) i = 0;
  delay_data[i] = val;
  if (i == d_time) j = 0;
  delay_data_1[i] = delay_data[i];
  j = j + 1; if (j > d_time) j = 0;
  if (!rev) d_val = delay_data_1[j];
  if (rev) d_val = delay_data_1[d_time - j];
}

void up_time() {
  noInterrupts();
  count++;
  if (count > 7)
    count = 1;
  delay(20);

  switch (count)  {
    case 1:
      d_time = 400; rev = 0; //63ms
      break;
    case 2:
      d_time = 700; //110ms
      break;
    case 3:
      d_time = 1000; //158ms
      break;
    case 4:
      d_time = 1300; //205ms
      break;
    case 5:
      d_time = 1600; //253ms
      break;
    case 6:
      d_time = 1900; //300ms
      break;
    case 7:
      d_time = 1500; rev = 1; //Reverse speech
      break;
  } interrupts();
}

//Set up timer 1 for 16.384kHz (975)
void InitTimer1() {
  cli(); //Disable global interrupts
  TCCR1A = 0; //Reset Timer 1 Counter Control Register A
  TCCR1B = 0; //Reset Timer 1 Counter Control Register B
  TCNT1  = 0; //initialize counter value to 0
  OCR1A = 975; //Set Timer 1 to desired frequency: 16384Hz (16,000,000 / 16384) - 1 = 975
  //Turn on CTC (clear timer on compare match) mode:
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS10); //CS10 Prescalar = 1 (no prescalar used); CS11 Prescalar = 8
  TIMSK1 |= (1 << OCIE1A); //Enable timer interrupt
  sei(); //Enable interrupts
}

ISR(TIMER1_COMPA_vect) {
  sampling();
}

//PWM 62.475kHz high frequency DAC for pins 5 & 6 (others are 32k)
void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if (pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch (divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if (pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if (pin == 3 || pin == 11) {
    switch (divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}