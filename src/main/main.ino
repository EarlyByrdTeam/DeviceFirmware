#include <Wire.h>

#include <AD5933_EB.h>


AD5933_EB AD5933;

int start;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("EB Custom AD5933 code started!");
  main();
}

int main() {
  start = 1;
  while (1) {
    if (start) {
      if (!AD5933.reset()) {
        Serial.println("Unsuccessful reset");
      } else {
        Serial.println("Good reset!");
      }
      delay(500);

      if (!AD5933.set_freq_start(1950)) {
        Serial.println("Unsuccessful set freq start");
      } else {
        Serial.println("Good set freq start");
      }
      delay(500);
      if (!AD5933.set_freq_delta(975)) {
        Serial.println("Unsuccessful set freq delta");
      } else {
        Serial.println("Good set freq delta");
      }

      delay(500);
      if (!AD5933.set_incr_num(10)) {
        Serial.println("Unsuccessful set increment num");
      } else {
        Serial.println("Good set increment num");
      }
      delay(500);
      if (!AD5933.set_measurement_delay()) {
        Serial.println("Unsuccessful set measurement del");
      } else {
        Serial.println("Good set measurement del");
      }
      delay(500);
      if (!AD5933.init()) {
        Serial.println("Unsuccessful init");
      } else {
        Serial.println("Good init");
      }
      delay(500);
      if (!AD5933.standby()) {
        Serial.println("Unsuccessful standby");
      } else {
        Serial.println("Good standby");
      }

      if (!AD5933.start_freq_sweep()){
        Serial.println("Failed to start freq sweep");
      }else Serial.println("Freq sweep started!");

      delay(500);
      
      if (AD5933.check_result()){
        Serial.println("Impedance results available!");
      } else {
        Serial.println("Impedance results not available");
//        while (!AD5933.check_result()) //Wait for good result
//        ;
//        delay(500);
      }
      delay(500);
      int real;
      int imag;
      if (!AD5933.read_complex_data(&real, &imag)){
        Serial.println("Failed to read complex data");
      } else {
        Serial.print("Real: ");
        Serial.println(real);
        Serial.print("Imaginary: ");
        Serial.println(imag);
      }
      start = 0;
    }
    return 0;
  }
}

void loop() {

}
//void loop() {
//  // put your main code here, to run repeatedly:
//  if (!AD5933.reset()){
//    Serial.println("Unsuccessful reset");
//  } else {
//    Serial.println("Good reset!");
//  }
//   delay(500);
//   
//   if (!AD5933.set_freq_start(1950)){
//    Serial.println("Unsuccessful set freq start");
//   } else {
//    Serial.println("Good set freq start");
//   }
//   delay(500);
//   if (!AD5933.set_freq_delta(975)){
//    Serial.println("Unsuccessful set freq delta");
//   } else {
//    Serial.println("Good set freq delta");
//   }
//
//   delay(500);
//   if (!AD5933.set_incr_num(10)){
//    Serial.println("Unsuccessful set increment num");
//   } else {
//    Serial.println("Good set increment num");
//   }
//   delay(500);
//   if (!AD5933.set_measurement_delay()){
//    Serial.println("Unsuccessful set measurement del");
//   } else {
//    Serial.println("Good set measurement del");
//   }
//   delay(500);
//   if (!AD5933.init()){
//    Serial.println("Unsuccessful init");
//   } else {
//    Serial.println("Good init");
//   }
//   delay(500);
//   if (!AD5933.standby()){
//    Serial.println("Unsuccessful standby");
//   } else {
//    Serial.println("Good standby");
//   }
//
//}
