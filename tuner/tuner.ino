#define PRESCALER 64
#define N_VALUE 6
#define SAMPLING_FREQUENCY (F_CPU)
#define NUM_SAMPLES 1024
#define SAMPLING_FREQUENCY (((float)F_CPU)/(PRESCALER*(1+N_VALUE)))

volatile char sample[NUM_SAMPLES];

volatile uint16_t sampleCount;

//    FILE: frequencyDSP.ino
//  AUTHOR: rob tillaart (org version akellyirl)
// VERSION: 0.1.03
// PURPOSE: frequency analysis using DSP
//    DATE: 2013-10-27
//     URL: http://www.instructables.com/id/Reliable-Frequency-Detection-Using-DSP-Techniques
float autoCorrelateFrequency(char * sample, int len, float sampleFreq)
{
  long sum = 0;
  long sum_old = 0;
  int thresh = 0;
  byte pd_state = 0;
  int period = 0;  // 0 results in inf

  // Autocorrelation
  for (int i=0; i < len && (pd_state != 3); i++)
  {
    sum_old = sum;
    sum = 0;

    for (int k=0; k <len-i; k++)
    {
      sum += ((sample[k]) & (sample[k+i]))&1;
    }
    sum /= 256;

    // Peak Detect State Machine
    // 0: initial, set threshold
    // 1: detect positive slope
    // 2: detect negative slope
    // 3: peak found
    if (pd_state == 0)
    {
      thresh = sum / 2;
      pd_state = 1;
    } 
    else if (pd_state == 1 && (sum > thresh) && (sum - sum_old) > 0) 
    {
      pd_state = 2;
    }
    else if (pd_state == 2 && (sum - sum_old) <= 0) 
    {
      period = i;
      pd_state = 3;
    } 
  }

  return sampleFreq/period;
}


void setup() {
  // put your setup code here, to run once:
  setupTimer();
  Serial.begin(57600);
  pinMode(12,INPUT);
  TIMSK1 = 0;
  TIMSK2 = 0;

}

int i = 0;
float freq;
void loop() {
  // put your main code here, to run repeatedly:

  //digitalWrite(13,LOW);
  startSampling();
  while(sampleCount < NUM_SAMPLES);
  freq = autoCorrelateFrequency((char*)sample, NUM_SAMPLES, SAMPLING_FREQUENCY);
  
  Serial.print(freq);
  Serial.print('\n');
  //digitalWrite(13,HIGH);
}

/* configure initial settings for 8-bit Timer0 */
volatile int16_t lastTime;
volatile uint8_t ovfCount;
void setupTimer() {
  lastTime = 0;

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
  pinMode(6,OUTPUT);
  //DDRB &= ~_BV(PB0);

  // disable overflow interrupt
  TIMSK0 &= ~_BV(OCIE0A);
  
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

void stopSampling() {
  // disable overflow interrupt
  TIMSK0 &= ~_BV(OCIE0A);
}

/* take a sample from the source */
inline char takeSample() {
  return (PINB>>4)&1;//digitalRead(12);
}

ISR(TIMER0_COMPA_vect) {
  if(sampleCount < NUM_SAMPLES) {
    sample[sampleCount] = takeSample();
    sampleCount++;
  }
}


