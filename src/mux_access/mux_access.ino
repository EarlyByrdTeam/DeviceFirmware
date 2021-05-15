#define MUX_RX1_IN A1
#define MUX_ENn 2
//Controls
#define MUX_RX1_S0 7
#define MUX_RX1_S1 6
#define MUX_RX1_S2 5
#define MUX_RX1_S3 6

void setup() {
  Serial.begin(9600);

  pinMode(MUX_ENn, OUTPUT);
  
  pinMode(MUX_RX1_S0, OUTPUT);
  pinMode(MUX_RX1_S1, OUTPUT);
  pinMode(MUX_RX1_S2, OUTPUT);
  pinMode(MUX_RX1_S3, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT); //Status LED

  //Reset Multiplexers
  enable_mux(1); //Disable (active low signal)
  delay(100);
//  enable_mux(0); //Enable
  
  digitalWrite(LED_BUILTIN, HIGH);   

}

void loop() {
  delay(1000);
  enable_mux(0); //Enable
//  float elecValue = read_mux_pin(15);
  set_mux_pin(15); //Select MUX pin to read
//  delay(5);
  int pinValue = analogRead(MUX_RX1_IN);
  float voltage = pinValue * (5.0/1023.0);
//  return voltage;
  Serial.print("Electrode value (V): "); Serial.println(voltage);
  delay(15);
   set_mux_pin(0); //Select MUX pin to read
//  delay(5);
  pinValue = analogRead(MUX_RX1_IN);
  voltage = pinValue * (5.0/1023.0);
//  return voltage;
  Serial.print("Electrode value (V): "); Serial.println(voltage);
//  delay(250);
//  elecValue = read_mux_pin(14);
//  Serial.print("Electrode value (V): "); Serial.println(elecValue);
//  delay(250);
//  elecValue = read_mux_pin(0);
//  Serial.print("Electrode value (V): "); Serial.println(elecValue);
  Serial.print("\n\n");

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

void set_mux_pin(int muxPin){
  switch(muxPin){
    case 0:
      digitalWrite(MUX_RX1_S0, LOW);
      digitalWrite(MUX_RX1_S1, LOW);
      digitalWrite(MUX_RX1_S2, LOW);
      digitalWrite(MUX_RX1_S3, LOW);
      break;
    case 14:
      digitalWrite(MUX_RX1_S0, HIGH);
      digitalWrite(MUX_RX1_S1, LOW);
      digitalWrite(MUX_RX1_S2, LOW);
      digitalWrite(MUX_RX1_S3, LOW);
      break;
    case 15:
      digitalWrite(MUX_RX1_S0, HIGH);
      digitalWrite(MUX_RX1_S1, HIGH);
      digitalWrite(MUX_RX1_S2, HIGH);
      digitalWrite(MUX_RX1_S3, HIGH);
      break;
  }
}
