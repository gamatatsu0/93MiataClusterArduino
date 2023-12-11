// This function takes in the analog input from the voltage divider
// and returns the equivalent voltage to the value
float analogToVoltage(float analog){
  return analog / 41.2;
}

// This function takes in a voltage and returns the amount
// of gallons which are equivalent ot the voltage given
float voltageToGallons(float analog){
  float voltage = analogToVoltage(analog);
  return voltage / 0.991;
}

// This function takes in a the analog signal and returns the temperature 
//equivalent ot the voltage given
int voltageToTemp(float analog){
// to find the temperature vaue given the voltage I used a exponential decay model
  double voltage = analogToVoltage(analog);
  double e = 2.71828;
  int ans = 571.39 * pow(e,(-0.17 * 6.65));
  return ans;
}

// This function takes in a voltage and returns the PSI
// equivalent ot the voltage given
// This is for the oil pressure gauge
int voltageToPreassure(float analog){
  double voltage = analogToVoltage(analog);
  double e = 2.71828;
  int ans = 571.39 * pow(e,(-0.17 * 6.65));
  return ans;
}
