void ir_cal(){
  while(digitalRead(ir_cal_pin)!=HIGH){
    continue;
  }
  delay(200);
  for(int i = 0; i<6; i++){
    while(digitalRead(ir_cal_pin)!=LOW){
      continue;
    }
    delay(200);
    while(digitalRead(ir_cal_pin)!=HIGH){
      if(ir_rec.decode()){
        Serial.println("IR_val : " + String(ir_rec.results.value));
        val_arr[i] = ir_rec.results.value;
        ir_rec.resume();
      }
    }
    delay(200);
  }
  Serial.println("Calibartion Comptele!!!");
}

void ir_drive(){
  if(ir_rec.decode()){
    if(ir_rec.results.value == val_arr[0]){
      speed_a = base_speed, speed_b = base_speed;
      update_time = millis();
    }
    else if(ir_rec.results.value == val_arr[1]){
      speed_a = -1*base_speed, speed_b = -1*base_speed;
      update_time = millis();
    }
    else if(ir_rec.results.value == val_arr[2]){
      speed_a = -1*base_speed, speed_b = base_speed;
      update_time = millis();
    }
    else if(ir_rec.results.value == val_arr[3]){
      speed_a = base_speed, speed_b = -1*base_speed;
      update_time = millis();
    }
    else if(ir_rec.results.value == val_arr[4]){
      base_speed = min(255, base_speed+10);
    }
    else if(ir_rec.results.value == val_arr[5]){
      base_speed = max(0, base_speed-10);
    }
    ir_rec.resume();
  }
}
