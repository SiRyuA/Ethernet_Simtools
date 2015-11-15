void stringMotorAxis() {
  char visaTemp[visaRead.length()+1];

  visaRead.substring(0).toCharArray(visaTemp, visaRead.length()+1);
  
  if((visaTemp[0] == 'R') || (visaTemp[0] == 'r')) {
    Axis_Data[Motor_R] = strtol(visaTemp+1, NULL, 10);
    Axis_Data[Motor_R] = map(constrain(Axis_Data[Motor_R]-Motor_R_Revision, Min, Axis_Max), Min, Axis_Max, Min, Motor_Max);
    //Serial.print("R : ");
    //Serial.print(Axis_Data[Motor_R]);
    //Serial.print("\t");
  }

  if((visaTemp[0] == 'L') || (visaTemp[0] == 'l')) {
    Axis_Data[Motor_L] = strtol(visaTemp+1, NULL, 10);
    Axis_Data[Motor_L] = map(constrain(Axis_Data[Motor_L]-Motor_L_Revision, Min, Axis_Max), Min, Axis_Max, Min, Motor_Max);
    //Serial.print("L : ");
    //Serial.print(Axis_Data[Motor_L]);
    //Serial.print("\t");
  }

  if((visaTemp[0] == 'M') || (visaTemp[0] == 'm')) {
    Axis_Data[Motor_M] = strtol(visaTemp+1, NULL, 10);
    Axis_Data[Motor_M] = map(constrain(Axis_Data[Motor_M]-Motor_M_Revision, Min, Axis_Max), Min, Axis_Max, Min, Motor_Max);
    //Serial.print("M : ");
    //Serial.print(Axis_Data[Motor_M]);
    //Serial.print("\t");
  }

  
  visaRead = "";
}

void SerialShow() {
  Serial.print("Axis");
  Serial.print(" : ");
  for(char i=0; i<3; i++) {
    Serial.print(Axis_Data[i]);
    Serial.print("  ");
  }
  Serial.print("     ");
  
  Serial.print("Data");
  Serial.print(" : ");
  for(char i=0; i<3; i++) {
    Serial.print(Encoder_Data[i]);
    Serial.print(" ");
  }
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

