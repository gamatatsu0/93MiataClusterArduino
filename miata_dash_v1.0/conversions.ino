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

// This function takes in a voltage and returns the temperature 
//equivalent ot the voltage given
float voltageToTemp(float analog){
  float voltage = analogToVoltage(analog);
  float normal_operating_temp = 195;
  float voltage_at_norm_op_temp = 5.13;
  float conversion_rate = (normal_operating_temp * .01)/voltage_at_norm_op_temp; //0.380116959

  
  return (voltage * 100) * conversion_rate;
}

// This function takes in a voltage and returns the PSI
// equivalent ot the voltage given
// This is for the oil pressure gauge
float voltageToPreassure(float analog){
  float voltage = analogToVoltage(analog);
  return voltage / 0.991;
}
