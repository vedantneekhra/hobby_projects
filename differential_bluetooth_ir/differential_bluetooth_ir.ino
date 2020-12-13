#include <SoftwareSerial.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <IRremote.h>

// pin defination motor
#define pwm_a 3
#define pwm_b 9
#define signal_a1 11
#define signal_a2 10
#define signal_b1 8
#define signal_b2 7

// pin defination ir
#define ir_recevier 2

// pin defination bluetooth
#define tx 5
#define rx 4

// pin defination switch
#define ir_cal_pin 12
#define mode_detection A1

// variable for ir
uint32_t val_arr[6];
IRrecv ir_rec(ir_recevier);

// bluetooth
SoftwareSerial blue(rx, tx);

// variable for motor
int speed_a = 0, speed_b = 0, base_speed = 100;
bool mode_check;
unsigned long long update_time = 0;

void motor_drive(){
  if(speed_a < 0){
    digitalWrite(signal_a1, HIGH);
    digitalWrite(signal_a2, LOW);
  }
  else{
    digitalWrite(signal_a1, LOW);
    digitalWrite(signal_a2, HIGH);
  }
  if(speed_b < 0){
    digitalWrite(signal_b1, HIGH);
    digitalWrite(signal_b2, LOW);
  }
  else{
    digitalWrite(signal_b1, LOW);
    digitalWrite(signal_b2, HIGH);
  }
  analogWrite(pwm_a, abs(speed_a) < 256?abs(speed_a):255);
  analogWrite(pwm_b, abs(speed_b) < 256?abs(speed_b):255);
}

void setup() {
  Serial.begin(9600);
  blue.begin(9600);
  pinMode(pwm_a, OUTPUT);
  pinMode(pwm_b, OUTPUT);
  pinMode(signal_a1, OUTPUT);
  pinMode(signal_a2, OUTPUT);
  pinMode(signal_b1, OUTPUT);
  pinMode(signal_b2, OUTPUT);

  ir_rec.enableIRIn();
  pinMode(ir_cal_pin, INPUT_PULLUP);
  pinMode(mode_detection, INPUT_PULLUP);
  mode_check = (digitalRead(mode_detection) == HIGH);
  if (mode_check) {
    Serial.println("IR mode!!!!!");
    ir_cal();
  }
}

void loop() {
  if(mode_check){
    ir_drive();
  }
  else{
    bluetooth_drive();
  }
  if(millis() - update_time >= 1000){
    speed_a = 0;
    speed_b = 0;
  }
  Serial.println("Motor A : " + String(speed_a) + ", Motor B : " + String(speed_b));
  motor_drive();
}
