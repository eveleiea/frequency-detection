#include "autocorrelatefrequency.h"

#define PRESCALER 64
#define N_VALUE 6
#define SAMPLING_FREQUENCY (F_CPU)
#define NUM_SAMPLES 512
#define SAMPLING_FREQUENCY (((float)F_CPU)/(PRESCALER*(1+N_VALUE)))

volatile char sample[NUM_SAMPLES];
volatile uint16_t sampleCount;


void setup() {
  // put your setup code here, to run once:
  setupTimer();
  setupPins();
  
  Serial.begin(115200);
}

float freq;
void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(13,HIGH);
  startSampling();
  while(sampleCount < NUM_SAMPLES);
  stopSampling();
  freq = autoCorrelateFrequencyBetter((char*)sample, NUM_SAMPLES, SAMPLING_FREQUENCY);
  
  Serial.print(freq);
  Serial.print('\n');
  //digitalWrite(13,HIGH);
}

// https://www.arduino.cc/en/Reference/PortManipulation
void setupPins() {
  // set Arduino pin 7 as an input
  // it is bit 7 of PORT B
  PORTD &= ~_BV(PD7); // disable pull up on pin 7
  DDRD &= ~_BV(PD7); // clear bit 7 to make it an input

  // set Arduino pin 13 as output (L LED)
  PORTB &= ~_BV(PB5); // set output as LOW by default.
  DDRB |= _BV(5);

}

/* configure initial settings for 8-bit Timer0 */
void setupTimer() {
  // disable interrupts while we are configuring things
  cli();
  
  // set Timer1 to act in CTC mode, prescaler fIO/64
  // toggle OCR0A (Arduino pin 6) on compare match
  // set COM0A = 01, COM0B = 00, WGM0 = 010 and CS0 = 010
  TCCR0A = _BV(COM0A0) | _BV(WGM01);
  TCCR0B = _BV(CS00) | _BV(CS01);

  // frequency of interrupt is equal to
  // f_int = f_cpu / (N*(1+OCR1A))
  OCR0A = N_VALUE;
  // OCR0A is pin 6 on arduino
  // set Arduino pin 6 as output 
  PORTD &= ~_BV(PD6); // low as default
  DDRD |= _BV(PD6);

  // disable overflow interrupt
  TIMSK0 &= ~_BV(OCIE0A);

  // Kill Arduino environment timer interrupts
  TIMSK1 = 0;
  TIMSK2 = 0;
  
  // enable interrupts once again
  sei();
}

void startSampling() {
  cli();
  sampleCount = 0;
  
  // clear any previous compare match interrupt
  TIFR0 |= _BV(OCF0A);
  // enable overflow interrupt
  TIMSK0 |= _BV(OCIE0A);
  // clear timer
  TCNT0 = 0;
  sei();
}

inline void stopSampling() {
  // disable overflow interrupt
  TIMSK0 &= ~_BV(OCIE0A);
}

/* take a sample from the source */
inline char takeSample() {
  return ((PIND&_BV(PD7)) != 0)?1:0;//digitalRead(7);
}

char temp;
volatile byte state;
ISR(TIMER0_COMPA_vect) {
  temp = takeSample();
  
  state++;
  digitalWrite(13,state&1);
  //PORTB &= ~_BV(PB5);
  //PORTB |= (state&1)<<5;
  
  if(sampleCount < NUM_SAMPLES) {
    sample[sampleCount] = temp;
    sampleCount++;
  }
}


