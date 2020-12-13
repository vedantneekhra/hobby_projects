void bluetooth_drive(){
  if(blue.available()){
    switch(blue.read()){
      case 52:
            speed_a = base_speed, speed_b = base_speed;
            break;
      case 51:
            speed_a = -1*base_speed, speed_b = base_speed;
            break;
      case 54:
            speed_a = -1*base_speed, speed_b = -1*base_speed;
            break;
      case 53:
            speed_a = base_speed, speed_b = -1*base_speed;
            break;
      case 'I':
            base_speed = min(255, base_speed+10);
            
            break;
      case 'D':
            base_speed = max(0, base_speed-10);
            break;
    }
    update_time = millis();
  }
}
