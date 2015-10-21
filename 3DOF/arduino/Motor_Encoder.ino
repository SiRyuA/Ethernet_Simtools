void Motor_Encoder(int PORT) { 
  if(digitalRead(Encoder[PORT]) == HIGH) {
    if(Motor_way[PORT] == 1) Encoder_Data[PORT]++;
    else if(Motor_way[PORT] == -1) Encoder_Data[PORT]--;
  }
  
  if(Encoder_Data[PORT] < Motor_Min) {
    Encoder_Data[PORT] = Motor_Min;
    Motor_ST(PORT);
  }
  
  if(Encoder_Data[PORT] > Motor_Max) {
    Encoder_Data[PORT] = Motor_Max;
    Motor_ST(PORT);
  }
  
  Encoder_Save[PORT] = Encoder_Data[PORT];
  
  if(Only_Arduino == 1) {
    Serial.print("Motor ");
    Serial.print(PORT);
    Serial.print(" : ");
    Serial.println(Encoder_Data[PORT], DEC);
  }
}

void Motor_UP(int PORT){
  Encoder_Data[PORT] = Encoder_Save[PORT];
  Motor_work[PORT] = 1;
  Motor_way[PORT] = 1;

  if(Only_Arduino == 1) {
    Serial.print("Motor");
    Serial.print(PORT);
    Serial.println(" UP");
  }
  
  digitalWrite(Motor_CW[PORT], HIGH);
  digitalWrite(Motor_CCW[PORT], LOW);
}

void Motor_ST(int PORT){
  Motor_work[PORT] = 0;
  Motor_way[PORT] = 1;

  if(Only_Arduino == 1) {
    Serial.print("Motor");
    Serial.print(PORT);
    Serial.println(" STOP");
  }
  
  digitalWrite(Motor_CW[PORT], LOW);
  digitalWrite(Motor_CCW[PORT], LOW);
}

void Motor_DW(int PORT){
  Encoder_Data[PORT] = Encoder_Save[PORT];
  Motor_work[PORT] = 1;
  Motor_way[PORT] = -1;

  if(Only_Arduino == 1) {
    Serial.print("Motor");
    Serial.print(PORT);
    Serial.println(" DOWN");
  }
  
  digitalWrite(Motor_CW[PORT], LOW);
  digitalWrite(Motor_CCW[PORT], HIGH);
}

void Motor_FULLUP(){
  for(char i=0; i<3; i++) Motor_way[i] = 0;
  
  if(Only_Arduino == 1) Serial.println("Motor FULL UP");

  for(char i=0; i<3; i++) {
    digitalWrite(Motor_CW[i], HIGH);
    digitalWrite(Motor_CCW[i], LOW);
  }
  Serial.flush();
}

void Motor_FULLDOWN(){
  for(char i=0; i<3; i++) Motor_way[i] = 0;
  
  if(Only_Arduino == 1) Serial.println("Motor FULL DOWN");

  for(char i=0; i<3; i++) {
    digitalWrite(Motor_CW[i], LOW);
    digitalWrite(Motor_CCW[i], HIGH);
  }
  Serial.flush();
}

void Motor_RESET(){
  for(char i=0; i<3; i++) {
    Encoder_Data[i] = 0;
    Encoder_Save[i] = 0;
    Motor_work[i] = 0;
    Motor_way[i] = 0;
  }

  if(Only_Arduino == 1) Serial.println("Motor FULL RESET");
  
  for(char i=0; i<3; i++) {
    digitalWrite(Motor_CW[i], LOW);
    digitalWrite(Motor_CCW[i], LOW);
    digitalWrite(Encoder[i], HIGH);
  }
  Serial.flush();
}
