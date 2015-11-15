void stringMotorAxis() {
  Serial.println("visaRead : " + visaRead);
  
  int comma1 = visaRead.indexOf(',');
  int comma2 = visaRead.indexOf(',', comma1+1);
  int comma3 = visaRead.indexOf(',', comma2+1);
  int comma4 = visaRead.indexOf(',', comma3+1);
  
  String sTemp1 = visaRead.substring(0, comma1);
  String sTemp2 = visaRead.substring(comma1+1,comma2);
  String sTemp3 = visaRead.substring(comma2+1,comma3);
  
  char cTemp1[sTemp1.length()+1];
  char cTemp2[sTemp2.length()+1];
  char cTemp3[sTemp3.length()+1];
  
  sTemp1.substring(0).toCharArray(cTemp1, sTemp1.length()+1);
  sTemp2.substring(0).toCharArray(cTemp2, sTemp2.length()+1);
  sTemp3.substring(0).toCharArray(cTemp3, sTemp3.length()+1);
  
  if((cTemp1[0] == 'L') || (cTemp1[0] == 'l')) {
    Axis_Temp[Motor_L] = strtol(cTemp1+1, NULL, 10);
    Axis_Revision(Motor_L);
  }
  if((cTemp1[0] == 'M') || (cTemp1[0] == 'm')) {
    Axis_Temp[Motor_M] = strtol(cTemp1+1, NULL, 10);
    Axis_Revision(Motor_M);
  }
  if((cTemp1[0] == 'R') || (cTemp1[0] == 'r')) {
    Axis_Temp[Motor_R] = strtol(cTemp1+1, NULL, 10);
    Axis_Revision(Motor_R);
  }
  
  if((cTemp2[0] == 'L') || (cTemp2[0] == 'l')) {
    Axis_Temp[Motor_L] = strtol(cTemp2+1, NULL, 10);
    Axis_Revision(Motor_L);
  }
  if((cTemp2[0] == 'M') || (cTemp2[0] == 'm')) {
    Axis_Temp[Motor_M] = strtol(cTemp2+1, NULL, 10);
    Axis_Revision(Motor_M);
  }
  if((cTemp2[0] == 'R') || (cTemp2[0] == 'r')) {
    Axis_Temp[Motor_R] = strtol(cTemp2+1, NULL, 10);
    Axis_Revision(Motor_R);
  }
  
  if((cTemp3[0] == 'L') || (cTemp3[0] == 'l')) {
    Axis_Temp[Motor_L] = strtol(cTemp3+1, NULL, 10);
    Axis_Revision(Motor_L);
  }
  if((cTemp3[0] == 'R') || (cTemp3[0] == 'r')) {
    Axis_Temp[Motor_R] = strtol(cTemp3+1, NULL, 10);
    Axis_Revision(Motor_R);
  }
  if((cTemp3[0] == 'M') || (cTemp3[0] == 'm')) {
    Axis_Temp[Motor_M] = strtol(cTemp3+1, NULL, 10);
    Axis_Revision(Motor_M);
  }

  visaRead = "";
}

void Axis_Revision(int PORT) {
  if(PORT == Motor_L) Axis_Data[Motor_L] = map(constrain(Axis_Temp[Motor_L], Min, Axis_Max), Min, Axis_Max, Min, Motor_Max);
  if(PORT == Motor_R) Axis_Data[Motor_R] = map(constrain(Axis_Temp[Motor_R], Min, Axis_Max), Min, Axis_Max, Min, Motor_Max);
  if(PORT == Motor_M) Axis_Data[Motor_M] = map(constrain(Axis_Temp[Motor_M], Min, Axis_Max), Min, Axis_Max, Min, Motor_Max);
}

void SerialShow() {
  Serial.print("Axis");
  Serial.print(" : ");
  for(char i=0; i<3; i++) {
    Serial.print(Axis_Data[i]);
    Serial.print("  ");
  }
  Serial.print("     ");
  
  Serial.print("Move");
  Serial.print(" : ");
  for(char i=0; i<3; i++) {
    Serial.print(Axis_Move[i]);
    Serial.print(" ");
  }
  Serial.print("     ");
  
  Serial.print("Enc");
  Serial.print(" : ");
  for(char i=0; i<3; i++) {
    Serial.print(Encoder_Data[i]);
    Serial.print(" ");
  }
  Serial.print("     ");
  
  Serial.print("     ");
  Serial.print("EnA");
  Serial.print(" : ");
  for(char i=0; i<3; i++) {
    Serial.print(EncoderA_Temp[i]);
    Serial.print(" ");
  }
  Serial.print("     ");
  
  Serial.print("EnB");
  Serial.print(" : ");
  for(char i=0; i<3; i++) {
    Serial.print(EncoderB_Temp[i]);
    Serial.print(" ");
  }
  Serial.print("\n");
}

