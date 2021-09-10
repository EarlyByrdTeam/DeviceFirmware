#define MUX_RX1_IN A0    // Common I/O
#define MUX_ENn 7        // Enable Pin
//Controls
#define MUX_RX1_S0 3
#define MUX_RX1_S1 4
#define MUX_RX1_S2 5
#define MUX_RX1_S3 6
int pin = 0;

void setup() {
  Serial.begin(9600);

  pinMode(MUX_ENn, OUTPUT);
  
  pinMode(MUX_RX1_S0, OUTPUT);
  pinMode(MUX_RX1_S1, OUTPUT);
  pinMode(MUX_RX1_S2, OUTPUT);
  pinMode(MUX_RX1_S3, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT); //Status LED
  pinMode(22, OUTPUT);
  //pinMode(23, OUTPUT);
  //pinMode(24, OUTPUT);
  //pinMode(25, OUTPUT);
  //pinMode(26, OUTPUT);
  //pinMode(27, OUTPUT);
  //pinMode(28, OUTPUT);
  //pinMode(29, OUTPUT);
    
  //Reset Multiplexers
  enable_mux(1); //Disable (active low signal)
  digitalWrite(LED_BUILTIN, LOW);

}

void loop() {
  
  delay(1000);
  enable_mux(0); // Enable
  //digitalWrite(28, HIGH);
  digitalWrite(22, HIGH);
  //digitalWrite(23, HIGH);
  
  pin = 8;
  set_mux_pin(pin); //Select MUX pin to read
  int pinValue = analogRead(MUX_RX1_IN);
  float voltage = pinValue * (5.0/1023.0);
  Serial.print("Reading Pin: "); Serial.println(pin);
  Serial.print("Electrode value (V): "); Serial.println(voltage);
}

void enable_mux(int en){
  digitalWrite(MUX_ENn, en);
}

float read_mux_pin(int pin){
  Serial.print("Reading MUX pin: ");Serial.println(pin);
  set_mux_pin(pin); //Select MUX pin to read
  delay(5);
  int pinValue = analogRead(MUX_RX1_IN);
  float voltage = pinValue * (5.0/1023.0);
  return voltage;
}

// Implementing pair drive 
numSamples = 250;
numElectrodes = 16;
n=0;
m=0;
Serial.print("Starting Pair Drive.")
while (n = 0, n < 16, n++){
  if (n = 15) {
    inject_current(n,0)}; 
  else {
    inject_current(n, n+1);
  }
  el1 = mod(n+2,15);   // electrodes to begin reading voltage from
  el2 = mod(n+3,15); 
  // Read potential difference from adjacent pairs of electrodes
  while (m=0, m<12, m++){
    read_voltage_from(el1, el2);
    take_k_samples;
    average_vector;
    send_value_to_serial;
    deselect_pair;
    el1 += 1; // move to next adjacent pair of electrodes
    el2 += 1;
  }
  if (n = 15) {
    stop_inject_current(n,0);
  }
  else {
    stop_inject_current(n,n+1);
  }
 Serial.print("Pair drive complete.")
}

void set_mux_pin(int muxPin){
  switch(muxPin){
    case 0:
      digitalWrite(MUX_RX1_S0, LOW);
      digitalWrite(MUX_RX1_S1, LOW);
      digitalWrite(MUX_RX1_S2, LOW);
      digitalWrite(MUX_RX1_S3, LOW);
      break;
    case 1:
      digitalWrite(MUX_RX1_S0, HIGH);
      digitalWrite(MUX_RX1_S1, LOW);
      digitalWrite(MUX_RX1_S2, LOW);
      digitalWrite(MUX_RX1_S3, LOW);
      break;
    case 2:
      digitalWrite(MUX_RX1_S0, LOW);
      digitalWrite(MUX_RX1_S1, HIGH);
      digitalWrite(MUX_RX1_S2, LOW);
      digitalWrite(MUX_RX1_S3, LOW);
      break;
    case 3:
      digitalWrite(MUX_RX1_S0, HIGH);
      digitalWrite(MUX_RX1_S1, HIGH);
      digitalWrite(MUX_RX1_S2, LOW);
      digitalWrite(MUX_RX1_S3, LOW);
      break;
    case 4:
      digitalWrite(MUX_RX1_S0, LOW);
      digitalWrite(MUX_RX1_S1, LOW);
      digitalWrite(MUX_RX1_S2, HIGH);
      digitalWrite(MUX_RX1_S3, LOW);
      break;
    case 5:
      digitalWrite(MUX_RX1_S0, HIGH);
      digitalWrite(MUX_RX1_S1, LOW);
      digitalWrite(MUX_RX1_S2, HIGH);
      digitalWrite(MUX_RX1_S3, LOW);
      break;
    case 6:
      digitalWrite(MUX_RX1_S0, LOW);
      digitalWrite(MUX_RX1_S1, HIGH);
      digitalWrite(MUX_RX1_S2, HIGH);
      digitalWrite(MUX_RX1_S3, LOW);
      break;
    case 7:
      digitalWrite(MUX_RX1_S0, HIGH);
      digitalWrite(MUX_RX1_S1, HIGH);
      digitalWrite(MUX_RX1_S2, HIGH);
      digitalWrite(MUX_RX1_S3, LOW);
      break;
    case 8:
      digitalWrite(MUX_RX1_S0, LOW);
      digitalWrite(MUX_RX1_S1, LOW);
      digitalWrite(MUX_RX1_S2, LOW);
      digitalWrite(MUX_RX1_S3, HIGH);
      break;
    case 9:
      digitalWrite(MUX_RX1_S0, HIGH);
      digitalWrite(MUX_RX1_S1, LOW);
      digitalWrite(MUX_RX1_S2, LOW);
      digitalWrite(MUX_RX1_S3, HIGH);
      break;
    case 10:
      digitalWrite(MUX_RX1_S0, LOW);
      digitalWrite(MUX_RX1_S1, HIGH);
      digitalWrite(MUX_RX1_S2, LOW);
      digitalWrite(MUX_RX1_S3, HIGH);
      break;
    case 11:
      digitalWrite(MUX_RX1_S0, HIGH);
      digitalWrite(MUX_RX1_S1, HIGH);
      digitalWrite(MUX_RX1_S2, LOW);
      digitalWrite(MUX_RX1_S3, HIGH);
      break;
    case 12:
      digitalWrite(MUX_RX1_S0, LOW);
      digitalWrite(MUX_RX1_S1, LOW);
      digitalWrite(MUX_RX1_S2, HIGH);
      digitalWrite(MUX_RX1_S3, HIGH);
      break;
    case 13:
      digitalWrite(MUX_RX1_S0, HIGH);
      digitalWrite(MUX_RX1_S1, LOW);
      digitalWrite(MUX_RX1_S2, HIGH);
      digitalWrite(MUX_RX1_S3, HIGH);
      break;
    case 14:
      digitalWrite(MUX_RX1_S0, LOW);
      digitalWrite(MUX_RX1_S1, HIGH);
      digitalWrite(MUX_RX1_S2, HIGH);
      digitalWrite(MUX_RX1_S3, HIGH);
      break;
    case 15:
      digitalWrite(MUX_RX1_S0, HIGH);
      digitalWrite(MUX_RX1_S1, HIGH);
      digitalWrite(MUX_RX1_S2, HIGH);
      digitalWrite(MUX_RX1_S3, HIGH);
      break;
  }
}
