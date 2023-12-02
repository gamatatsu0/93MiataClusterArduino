// This function takes in the analog input from the voltage divider
// and returns the equivalent voltage to the value
float analogToVoltage(float analog){
  return analog / 41.2;
}

// This function takes in a voltage and returns the amount
// of gallons which are equivalent ot the voltage given
float voltageToGallons(float voltage){
  return voltage / 0.991;
}

// This function takes in a voltage and returns the temperature 
//equivalent ot the voltage given
float voltageToTemp(float voltage){
  return voltage / 0.991;
}

// This function takes in a voltage and returns the PSI
// equivalent ot the voltage given
// This is for the oil pressure gauge
float voltageToPreassure(float voltage){
  return voltage / 0.991;
}


