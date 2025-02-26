// initialize switch actuator
const int RPWM = 8;
const int LPWM = 9;
const int R_EN = 10;
const int L_EN = 11;

// initialize sensor LDR
const int sensorLDRKa = A2;
const int sensorLDRKi = A3;

// initialize sensor value 
int valKa, valKi, Speed;

void setup() {

  // configure motor driver as an output
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(R_EN, OUTPUT);
  pinMode(L_EN, OUTPUT);

  // configure sensor LDR as an input
  pinMode(sensorLDRKa, INPUT);
  pinMode(sensorLDRKi, INPUT);
  
  Serial.begin(9600);

}

void loop() {
  Speed = 100;
  // read value from each ldr sensors
  valKa = analogRead(sensorLDRKa);
  valKi = analogRead(sensorLDRKi);
  analogWrite(R_EN, 500);
  analogWrite(L_EN, 500);

  Serial.println("Timur: " + String(valKa) + "  Barat: " + String(valKi));
  delay(50);

  // comparing the value of LDR Sensors
  if(valKa <100 && valKi < 100){
    if(valKa - valKi < -10){
      analogWrite(RPWM, 0);
      analogWrite(LPWM, Speed);
      Serial.println("Turun");
    } else if (valKa - valKi > 10){
      analogWrite(LPWM, 0);
      analogWrite(RPWM, Speed);
      Serial.println("Naik");
    } else{
      analogWrite(RPWM, 0);
      analogWrite(LPWM, 0);
      delay(600000); // Sleep for 10 minutes
    }
  }else if (valKa >300 && valKi > 300){
      analogWrite(RPWM, 0);
      analogWrite(LPWM, Speed);
      Serial.println("resetting");
      delay(2000);
  } else{
      analogWrite(RPWM, 0);
      analogWrite(LPWM, 0);
  }
  
  delay(1000);

}
