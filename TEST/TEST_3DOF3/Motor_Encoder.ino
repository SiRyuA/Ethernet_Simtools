void Motor_Encoder(int PORT) { 
  if(digitalRead(EncoderA[PORT]) == HIGH){
    if(Motor_way[PORT] == 1) EncoderA_Temp[PORT]++;
    else if(Motor_way[PORT] == -1) EncoderA_Temp[PORT]--;
  }else if(digitalRead(EncoderA[PORT]) == LOW) EncoderA_Temp[PORT] = Encoder_Data[PORT];

  if(digitalRead(EncoderB[PORT]) == HIGH) {
    if(Motor_way[PORT] == 1) EncoderB_Temp[PORT]++;
    else if(Motor_way[PORT] == -1) EncoderB_Temp[PORT]--;
  }else if(digitalRead(EncoderB[PORT]) == LOW) EncoderB_Temp[PORT] = Encoder_Data[PORT];

  Encoder_Data[PORT] = (EncoderA_Temp[PORT] + EncoderB_Temp[PORT])/2;
  
  if(Encoder_Data[PORT] < Min) {
    Encoder_Data[PORT] = Min;
    Motor_ST(PORT);
  }
  
  if(Encoder_Data[PORT] > Motor_Max) {
    Encoder_Data[PORT] = Motor_Max;
    Motor_ST(PORT);
  }
}

void Motor_UP(int PORT){
  Motor_work[PORT] = 1;
  Motor_way[PORT] = 1;
  
  digitalWrite(Motor_CW[PORT], HIGH);
  digitalWrite(Motor_CCW[PORT], LOW);
}

void Motor_ST(int PORT){
  Motor_work[PORT] = 0;
  Motor_way[PORT] = 1;

  digitalWrite(Motor_CW[PORT], LOW);
  digitalWrite(Motor_CCW[PORT], LOW);
}

void Motor_DW(int PORT){
  Motor_work[PORT] = 1;
  Motor_way[PORT] = -1;

  digitalWrite(Motor_CW[PORT], LOW);
  digitalWrite(Motor_CCW[PORT], HIGH);
}

void Motor_FULLUP(){
  for(char i=0; i<3; i++) {
    Motor_way[i] = 0;
    digitalWrite(Motor_CW[i], HIGH);
    digitalWrite(Motor_CCW[i], LOW);
  }
  Serial.flush();
}

void Motor_FULLDW(){  
  for(char i=0; i<3; i++) {
     Motor_way[i] = 0;
    digitalWrite(Motor_CW[i], LOW);
    digitalWrite(Motor_CCW[i], HIGH);
  }
  Serial.flush();
}

void Motor_RST(){
  for(char i=0; i<3; i++) {
    Encoder_Data[i] = 0;
    EncoderA_Temp[i] = 0;
    EncoderB_Temp[i] = 0;
    Motor_work[i] = 0;
    Motor_way[i] = 0;
    digitalWrite(Motor_CW[i], LOW);
    digitalWrite(Motor_CCW[i], LOW);
    digitalWrite(EncoderA[i], HIGH);
    digitalWrite(EncoderB[i], HIGH);
  }
  visaRead = "";
  Serial.flush(); 
}

void Motor_START(){
  Serial.println("Motor RESET");
  Motor_FULLUP();
  delay(1000);
  
  Motor_FULLDW();
  delay(16000);

  Motor_FULLUP();
  delay(1000);

  Serial.println("Encoder RESET");  
  Motor_RST();
  for(char i=0; i<3; i++) {
    Axis_Data[i] = 0;
  }

  Serial.println("Serial RESET");  
  visaRead = "";
  Serial.flush();
  BUTTON_Count = 0;

  tone(TONE, 4444);
  delay(100);
  noTone(TONE);
}

void Motor_WORK() {
  if((visaRead == "U") || (visaRead == "u") || (visaRead == "D") || (visaRead == "d") || (visaRead == "S") || (visaRead == "s") || (visaRead == "X") || (visaRead == "x")) {
    if((visaRead == "U") || (visaRead == "u")) Motor_FULLUP();
    if((visaRead == "D") || (visaRead == "d")) Motor_FULLDW();
    if((visaRead == "S") || (visaRead == "s")) Motor_START();
    if((visaRead == "X") || (visaRead == "x")) Motor_RST();
  }else {
    if(Axis_Data[Motor_M]  > Encoder_Data[Motor_M]) Motor_UP(Motor_M);
    if(Axis_Data[Motor_M]  < Encoder_Data[Motor_M]) Motor_DW(Motor_M);
    if(Axis_Data[Motor_M] == Encoder_Data[Motor_M]) Motor_ST(Motor_M);
    
    if(Axis_Data[Motor_L]  > Encoder_Data[Motor_L]) Motor_UP(Motor_L);
    if(Axis_Data[Motor_L]  < Encoder_Data[Motor_L]) Motor_DW(Motor_L);
    if(Axis_Data[Motor_L] == Encoder_Data[Motor_L]) Motor_ST(Motor_L);
  
    if(Axis_Data[Motor_R]  > Encoder_Data[Motor_R]) Motor_UP(Motor_R);
    if(Axis_Data[Motor_R]  < Encoder_Data[Motor_R]) Motor_DW(Motor_R);
    if(Axis_Data[Motor_R] == Encoder_Data[Motor_R]) Motor_ST(Motor_R);
  }
}

