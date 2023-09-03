//This program is to be ran on the test output arduino.. 
//It will mimic the output of the "CAR". It only will mimic some of the 
//tach and mostly warning lights going on an off. 





// Measures the HIGH width, LOW width, frequency, and duty-cycle of a pulse train
// on Arduino UNO Pin 8 (ICP1 pin).

// Note: Since this uses Timer1, Pin 9 and Pin 10 can't be used for
// analogWrite().




// Pins numbers for Input
int Fuel = 0;
int Belts = 2;
int Check_Heat =0;
int Break =0;
int AirBag =0;
int Retract =0;
int Charge =0;
int Tack =8;
int Starter =0;
int Hol=0;
int ABS =0;
int Washer =0;



void setup()
{
  Serial.begin(115200);
  while (!Serial);

  // For testing, uncomment one of these lines and connect
  // Pin 3 or Pin 5 to Pin 8
   analogWrite(3, 64);  // 512.00, 1528.00, 2040.00, 25.10%, 490.20 Hz
  //analogWrite(5, 64);  // 260.00, 764.00, 1024.00, 25.39%, 976.56 Hz




  pinMode(Fuel, OUTPUT);
  pinMode(Belts, OUTPUT);
  pinMode(Check_Heat, OUTPUT);
  pinMode(Break, OUTPUT);
  pinMode(AirBag, OUTPUT);
  pinMode(Retract, OUTPUT);
  pinMode(Charge, OUTPUT);
  pinMode(Tack, OUTPUT);
  pinMode(Starter, OUTPUT);
  pinMode(Hol, INPUT);
  pinMode(ABS, OUTPUT);
  pinMode(Washer, OUTPUT);
  



  noInterrupts ();  // protected code
  // reset Timer 1
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  TIMSK1 = 0;

  TIFR1 |= _BV(ICF1); // clear Input Capture Flag so we don't get a bogus interrupt
  TIFR1 |= _BV(TOV1); // clear Overflow Flag so we don't get a bogus interrupt

  TCCR1B = _BV(CS10) | // start Timer 1, no prescaler
           _BV(ICES1); // Input Capture Edge Select (1=Rising, 0=Falling)

  TIMSK1 |= _BV(ICIE1); // Enable Timer 1 Input Capture Interrupt
  TIMSK1 |= _BV(TOIE1); // Enable Timer 1 Overflow Interrupt
  interrupts ();
}

volatile uint32_t PulseHighTime = 0;
volatile uint32_t PulseLowTime = 0;
volatile uint16_t Overflows = 0;

ISR(TIMER1_OVF_vect)
{
  Overflows++;
}

ISR(TIMER1_CAPT_vect)
{
  static uint32_t firstRisingEdgeTime = 0;
  static uint32_t fallingEdgeTime = 0;
  static uint32_t secondRisingEdgeTime = 0;

  uint16_t overflows = Overflows;

  // If an overflow happened but has not been handled yet
  // and the timer count was close to zero, count the
  // overflow as part of this time.
  if ((TIFR1 & _BV(TOV1)) && (ICR1 < 1024))
    overflows++;

  if (PulseLowTime == 0)
  {
    if (TCCR1B & _BV(ICES1))
    {
      // Interrupted on Rising Edge
      if (firstRisingEdgeTime)  // Already have the first rising edge...
      {
        // ... so this is the second rising edge, ending the low part
        // of the cycle.
        secondRisingEdgeTime = overflows; // Upper 16 bits
        secondRisingEdgeTime = (secondRisingEdgeTime << 16) | ICR1;
        PulseLowTime = secondRisingEdgeTime - fallingEdgeTime;
        firstRisingEdgeTime = 0;
      }
      else
      {
        firstRisingEdgeTime = overflows; // Upper 16 bits
        firstRisingEdgeTime = (firstRisingEdgeTime << 16) | ICR1;
        TCCR1B &= ~_BV(ICES1); // Switch to Falling Edge
      }
    }
    else
    {
      // Interrupted on Falling Edge
      fallingEdgeTime = overflows; // Upper 16 bits
      fallingEdgeTime = (fallingEdgeTime << 16) | ICR1;
      TCCR1B |= _BV(ICES1); // Switch to Rising Edge
      PulseHighTime = fallingEdgeTime - firstRisingEdgeTime;
    }
  }
}

void loop()
{
//  noInterrupts();
//  uint32_t pulseHighTime = PulseHighTime;
//  uint32_t pulseLowTime = PulseLowTime;
//  interrupts();

  int timer = 10;
  while(timer > 0){
    Serial.println("HIGH:.................");
    digitalWrite(Belts, HIGH);
    delay(500);
    timer--;
    }
    timer = 10;

  while(timer > 0){
    Serial.println("LOW:.................");
    digitalWrite(Belts, LOW);
    delay(500);
    timer--;

    }

  // If a sample has been measured
//  if (pulseLowTime)
//  {
//    // Display the pulse length in microseconds
//    Serial.print("High time (microseconds): ");
//    Serial.println(pulseHighTime / 16.0, 2);
//    Serial.print("Low time (microseconds): ");
//    Serial.println(pulseLowTime / 16.0, 2);
//
//    uint32_t cycleTime = pulseHighTime + pulseLowTime;
//    Serial.print("Cycle time (microseconds): ");
//    Serial.println(cycleTime / 16.0, 2);
//
//    float dutyCycle = pulseHighTime / (float)cycleTime;
//    Serial.print("Duty cycle (%): ");
//    Serial.println(dutyCycle * 100.0, 2);

//    float frequency = (float)F_CPU / cycleTime;
//    Serial.print("Frequency (Hz): ");
//    Serial.println(frequency, 2);
//    Serial.println();

////    float RPM = frequency * 60;
//
//    Serial.print("RPM: ");
//    Serial.println(RPM);
//    Serial.println();

//    delay(1000);  // Slow down output

    // Request another sample
//    noInterrupts();
//    PulseLowTime = 0;
//    interrupts();
//  }
}
