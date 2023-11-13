/* baud rate of ***** 115200 ******
 *  The functions in this file are made to asist in the process of transfering data from the arduino
 *  over to the raspberry pi connected of serial connection(USB).
 *
 *  1. The printLights function will use println to print the data gathered by the arduino in the form of an array
 *  in the JSON format. This array will be read by the raspberry pi through a serial connection. 
 *  On the side of the raspberry pi the data will have to be read as JSON with a baud rate of (115200), 
 *  once data is read it the status and values for each one of the lights or gauges will have to accessed as a dictionary.  
 *  
 *  2. Check lights will use the read functions to access the current values for each light or gauge  coming from the the cluster board. 
 *  The result of the from reading data will than beassigned to an index in an array. 
*/
// ........................................Function to Manage Data........................................
void printLights(int lightsArray[]) {
  //  Funtion needs to receive an array of the results of HIGH or LOW Regarding the lights
  
  Serial.println("{\"Fuel\":" + String(lightsArray[0]) + 
  ","+ "\"Temp\":" + String(lightsArray[1]) +
  ","+ "\"Tack\":" + String(lightsArray[2]) + 
  ","+ "\"Oil_psi\":" + String(lightsArray[3]) + 
  ","+ "\"Turn_Left\":" + String(lightsArray[4]) + 
  ","+ "\"Turn_Right\":" + String(lightsArray[5]) + 
  ","+ "\"Hold\":" + String(lightsArray[6]) + 
  ","+ "\"Air_Bag\":" + String(lightsArray[7]) + 
  ","+ "\"Retract\":" + String(lightsArray[8]) + 
  ","+ "\"ABS\":" + String(lightsArray[0])+
  ","+ "\"Washer\":" + String(lightsArray[10])+
  ","+ "\"Beam\":" + String(lightsArray[11])+
  ","+ "\"Bealts\":" + String(lightsArray[12])+
  ","+ "\"Break\":" + String(lightsArray[13])+
  ","+ "\"Charge\":" + String(lightsArray[14])+
  ","+ "\"Check_Heat\":" + String(lightsArray[15])+
  "}" ); 
  // Serial.println("..................................................");
}

 
// This will get the input from the warning lights.
// It will need to go into a diffferent file for ease of use.
int *checkLights() {
  // **** Gauges **** 4
  float Read_Fuel = voltageToGallons(analogToVoltage(analogRead(Fuel))); 
  float Read_TEMP = analogToVoltage(analogRead(TEMP)); 
  float Read_Tack = frq; 
  float Read_Oil_Temp = analogToVoltage(analogRead(Oil_Temp)); 

  
  //  **** Top Center **** 2
  int Read_TurnLeft = digitalRead(TurnLeft);
  int Read_TurnRight = digitalRead(TurnRight);


  // **** Tack Gauge ****
  int Read_HOLD = digitalRead(HOLD);
  int Read_AirBag = digitalRead(AirBag);
  int Read_Retract = digitalRead(Retract);

  
  // **** Middle Center **** 7
  int Read_ABS = digitalRead(ABS);
  int Read_Washer = digitalRead(Washer);
  int Read_Beam = digitalRead(Beam);
  int Read_Belts = digitalRead(Belts);
  int Read_Break = digitalRead(Break);
  int Read_Charge = digitalRead(Charge);
  int Read_Check_Heat = digitalRead(Check_Engine);


  //...........................................................................
  //  Adding the data from the lights to the JSON
  
  // **** Gauges **** 4
  Read_Lights_Results[0] = Read_Fuel;
  Read_Lights_Results[1] = convertVoltsToPercent( Read_TEMP, 350);
  Read_Lights_Results[2] = Read_Tack;
  Read_Lights_Results[3] = Read_Oil_Temp;

  //  **** Top Center **** 2
  Read_Lights_Results[4] = Read_TurnLeft;
  Read_Lights_Results[5] = Read_TurnRight;

  // **** Tack Gauge ****
  Read_Lights_Results[6] = Read_HOLD;
  Read_Lights_Results[7] = Read_AirBag;
  Read_Lights_Results[8] = Read_Retract;

  // **** Middle Center **** 7
  Read_Lights_Results[9] = Read_ABS;
  Read_Lights_Results[10] = Read_Washer;
  Read_Lights_Results[11] = Read_Beam;
  Read_Lights_Results[12] = Read_Belts;
  Read_Lights_Results[13] = Read_Break;
  Read_Lights_Results[14] = Read_Charge;
  Read_Lights_Results[15] = Read_Check_Heat;

  printLights(Read_Lights_Results);

  return Read_Lights_Results;
};
