const int DAC_PIN = DAC0; // Define the DAC pin

//Sleep period
float total_time = 1000*60*6; //whole program period (ms)
float time_on = 1000*60*5; //period during which we have pulsed light (ms)
// dutycyle
float dutycycle = 0.5; //percentage of dutycycle
float frequence = 1; // frequency in Hz
float period_ms = (1/frequence)*1000; //(period in ms)

//Compute the analog voltage value between 0 and 3.3V (0-255)
float prop = 0.5/5; // percentage of the max voltage used
int v_val = ceil(prop * 255); //rounded value of voltage (0-255) 

void setup() {
  //Define transmission speed
  Serial.begin(9600);
}

void loop() {
  unsigned long startTime = millis(); //Get the starting time
  
  //Program on
  while((millis() - startTime) < time_on) {
    //Pulsed light
    //Set Voltage using DAC
    analogWrite(DAC_PIN, v_val);
    delay(dutycycle * period_ms); //Period at which voltage is up 
    analogWrite(DAC_PIN, 0);
    delay(period_ms - dutycycle * period_ms); // Period at which voltage is down
  }

	// Program off
  analogWrite(DAC_PIN, 0); //ensure the voltage is at 0
  delay(total_time - time_on);

  }