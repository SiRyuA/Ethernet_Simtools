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
  WORK_Locker = 1;
  for(char i=0; i<3; i++) {
    Motor_way[i] = 0;
    digitalWrite(Motor_CW[i], HIGH);
    digitalWrite(Motor_CCW[i], LOW);
  }
  Serial.flush();
}

void Motor_FULLDW(){
  WORK_Locker = 1;  
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
    Axis_Data[i] = 0;
    Axis_Temp[i] = 0;
    Axis_Move[i] = 0;
    digitalWrite(Motor_CW[i], LOW);
    digitalWrite(Motor_CCW[i], LOW);
    digitalWrite(EncoderA[i], HIGH);
    digitalWrite(EncoderB[i], HIGH);
  }
  visaRead = "";
  WORK_Locker = 0;
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

  MsTimer2::set(20, Encoder);
  MsTimer2::start();
}

void Motor_WORK() {
    Motor_Revision();
    
    if(Axis_Move[Motor_M]  > Encoder_Data[Motor_M]) Motor_UP(Motor_M);
    if(Axis_Move[Motor_M]  < Encoder_Data[Motor_M]) Motor_DW(Motor_M);
    if(Axis_Move[Motor_M] == Encoder_Data[Motor_M]) Motor_ST(Motor_M);
    
    if(Axis_Move[Motor_L]  > Encoder_Data[Motor_L]) Motor_UP(Motor_L);
    if(Axis_Move[Motor_L]  < Encoder_Data[Motor_L]) Motor_DW(Motor_L);
    if(Axis_Move[Motor_L] == Encoder_Data[Motor_L]) Motor_ST(Motor_L);
  
    if(Axis_Move[Motor_R]  > Encoder_Data[Motor_R]) Motor_UP(Motor_R);
    if(Axis_Move[Motor_R]  < Encoder_Data[Motor_R]) Motor_DW(Motor_R);
    if(Axis_Move[Motor_R] == Encoder_Data[Motor_R]) Motor_ST(Motor_R);
}

void Motor_Revision() {
    if(Motor_way[Motor_L] ==  1) Axis_Move[Motor_L] = Axis_Data[Motor_L] - 3;
    if(Motor_way[Motor_L] == -1) Axis_Move[Motor_L] = Axis_Data[Motor_L] - 1;
    if(Motor_way[Motor_R] ==  1) Axis_Move[Motor_R] = Axis_Data[Motor_R] + 5;
    if(Motor_way[Motor_R] == -1) Axis_Move[Motor_R] = Axis_Data[Motor_R] + 1;
    if(Motor_way[Motor_M] ==  1) Axis_Move[Motor_M] = Axis_Data[Motor_M] + 0;
    if(Motor_way[Motor_M] == -1) Axis_Move[Motor_M] = Axis_Data[Motor_M] + 0;  

    if(Axis_Move[Motor_L] <   0) Axis_Move[Motor_L] =   0;
    if(Axis_Move[Motor_L] > 255) Axis_Move[Motor_L] = 255;

    if(Axis_Move[Motor_R] <   0) Axis_Move[Motor_R] =   0;
    if(Axis_Move[Motor_R] > 255) Axis_Move[Motor_R] = 255;

    if(Axis_Move[Motor_M] <   0) Axis_Move[Motor_M] =   0;
    if(Axis_Move[Motor_M] > 255) Axis_Move[Motor_M] = 255;
}

