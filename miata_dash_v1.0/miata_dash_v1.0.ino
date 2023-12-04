// Last edited September 06 2023

#include <ArduinoJson.h>
#include <Smoothed.h>  //Data Smoothing Library


// Measures the HIGH width, LOW width, frequency, and duty-cycle of a pulse train
// on Arduino UNO Pin 8 (ICP1 pin).

// Note: Since this uses Timer1, Pin 9 and Pin 10 can't be used for
// analogWrite().

// ........................................Pins numbers for Input........................................

// these are checked for in the main program
volatile unsigned long timerCounts;
volatile boolean counterReady;

// internal to counting routine
unsigned long overflowCount;
unsigned int timerTicks;
unsigned int timerPeriod;

float frq;



// **** Gauges **** 4
// Max Voltage for the analog inputs should be 0 - 3.75V.

int Fuel = A0;      // Analog signal will be used to read the level of the gas tank
int TEMP = A1;      // Analog
int Tack;           // Analog signal will come in throug D5
int Oil_Temp = A2;  // Analog

//  **** Top Center **** 2
int TurnLeft = 26;   // Top Center
int TurnRight = 27;  // Top Center
int Ground;

//
int HOLD = 35;
int AirBag = 24;   // On Tack Gauge
int Retract = 31;  // On Tack Gauge


// **** Middle Center **** 7
int ABS = 28;           //Middle Center
int Washer = 29;        // Middle Center
int Beam = 33;          // Middle Center
int Belts = 25;         // Middle Center
int Break = 23;         // Middle Center
int Charge = 22;        // Middle Center
int Check_Engine = 29;  // Middle Center


int Read_Fuel = 50;


Smoothed<int> tempSensor;

// ........................................Some Globals...................................................
// Array used to values for testing * Will need to delete
int Read_Lights_Results[16];

////  Will use to send data to the Pi
const int capacity = JSON_OBJECT_SIZE(18);
StaticJsonDocument<capacity> carData;


void setup() {
  Serial.begin(115200);

  // For testing, uncomment one of these lines and connect
  // Pin 3 or Pin 5 to Pin 8

  //   analogWrite(3, 64);  // 512.00, 1528.00, 2040.00, 25.10%, 490.20 Hz
  //analogWrite(5, 64);  // 260.00, 764.00, 1024.00, 25.39%, 976.56 Hz

  //  This inputs are for the warning lights they will need to be passed to the
  // "checkLights" function.

  // **** Gauges **** 4
  pinMode(Fuel, INPUT);
  pinMode(TEMP, INPUT);
  pinMode(Tack, INPUT);
  pinMode(Oil_Temp, INPUT);

  //  **** Top Center **** 2
  pinMode(TurnLeft, INPUT);
  pinMode(TurnRight, INPUT);

  // **** Tack Gauge ****
  pinMode(Retract, INPUT);
  pinMode(AirBag, INPUT);
  pinMode(HOLD, INPUT);

  // **** Middle Center **** 7
  pinMode(ABS, INPUT);
  pinMode(Washer, INPUT);
  pinMode(Beam, INPUT);
  pinMode(Belts, INPUT);
  pinMode(Break, INPUT);
  pinMode(Charge, INPUT);
  pinMode(Check_Engine, INPUT);

  // Initialise the sensor value store. We want this one to be a simple linear recursive exponential filter.
  // We set the filter level to 10. Higher numbers will result in less filtering/smoothing. Lower number result in more filtering/smoothing
  tempSensor.begin(SMOOTHED_EXPONENTIAL, 50);
}

void loop() {
  // Read_Fuel = analogRead(Fuel);
  // Serial.print(Read_Fuel);
  // tempSensor.add(Read_Fuel);
  //  int smoothedFuelValueExp = tempSensor.get();

  // stop Timer 0 interrupts from throwing the count out
  byte oldTCCR0A = TCCR0A;
  byte oldTCCR0B = TCCR0B;
  TCCR0A = 0;  // stop timer 0
  TCCR0B = 0;

  startCounting(500);  // how many ms to count for

  while (!counterReady) {}  // loop until count over

  // adjust counts by counting interval to give frequency in Hz
  frq = (timerCounts * 1000.0) / timerPeriod;


  // restart timer 0
  TCCR0A = oldTCCR0A;
  TCCR0B = oldTCCR0B;

  // let serial stuff finish
  //  delay(200);
  checkLights();
}
