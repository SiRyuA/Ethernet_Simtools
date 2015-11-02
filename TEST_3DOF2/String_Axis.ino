void stringMotorAxis() {
  Serial.println("visaRead : " + visaRead);
  
  int comma1 = visaRead.indexOf(',');
  int comma2 = visaRead.indexOf(',', comma1+1);
  int comma3 = visaRead.indexOf(',', comma2+1);
  int comma4 = visaRead.indexOf(',', comma3+1);
  
  String sTemp1 = visaRead.substring(0, comma1);
  String sTemp2 = visaRead.substring(comma1+1,comma2);
  String sTemp3 = visaRead.substring(comma2+1,comma3);
  
  Serial.println("sTemp1 : " + sTemp1 + "\t sTemp2 : " + sTemp2 + "\t sTemp3 : " + sTemp3);
  
  char cTemp1[sTemp1.length()+1];
  char cTemp2[sTemp2.length()+1];
  char cTemp3[sTemp3.length()+1];
  
  sTemp1.substring(0).toCharArray(cTemp1, sTemp1.length()+1);
  sTemp2.substring(0).toCharArray(cTemp2, sTemp2.length()+1);
  sTemp3.substring(0).toCharArray(cTemp3, sTemp3.length()+1);
  
  Serial.print("cTemp1 : ");Serial.print(cTemp1);Serial.print("\t");
  Serial.print("cTemp2 : ");Serial.print(cTemp2);Serial.print("\t");
  Serial.print("cTemp3 : ");Serial.print(cTemp3);Serial.print("\n");
  
  if((cTemp1[0] == 'L') || (cTemp1[0] == 'l')) {
    Axis_Data[Motor_L] = strtol(cTemp1+1, NULL, 10);
    Axis_Data[Motor_L] = map(constrain(Axis_Data[Motor_L], Min, Axis_Max), Min, Axis_Max, Min, Motor_Max);
    Serial.print("L : ");
    Serial.print(Axis_Data[Motor_L]);
    Serial.print("\t");
  }
  /*if((cTemp1[0] == 'M') || (cTemp1[0] == 'm')) {
    Axis_Data[Motor_M] = strtol(cTemp1+1, NULL, 10);
    Axis_Data[Motor_M] = map(constrain(Axis_Data[Motor_M], Min, Axis_Max), Min, Axis_Max, Min, Motor_Max);
    Serial.print("M : ");
    Serial.print(Axis_Data[Motor_M]);
    Serial.print("\t");
  }
  if((cTemp1[0] == 'R') || (cTemp1[0] == 'r')) {
    Axis_Data[Motor_R] = strtol(cTemp1+1, NULL, 10);
    Axis_Data[Motor_R] = map(constrain(Axis_Data[Motor_R], Min, Axis_Max), Min, Axis_Max, Min, Motor_Max);
    Serial.print("R : ");
    Serial.print(Axis_Data[Motor_R]);
    Serial.print("\t");
  }*/
  
  /*if((cTemp2[0] == 'L') || (cTemp2[0] == 'l')) {
    Axis_Data[Motor_L] = strtol(cTemp2+1, NULL, 10);
    Axis_Data[Motor_L] = map(constrain(Axis_Data[Motor_L], Min, Axis_Max), Min, Axis_Max, Min, Motor_Max);
    Serial.print("L : ");
    Serial.print(Axis_Data[Motor_L]);
    Serial.print("\t");
  }*/
  if((cTemp2[0] == 'M') || (cTemp2[0] == 'm')) {
    Axis_Data[Motor_M] = strtol(cTemp2+1, NULL, 10);
    Axis_Data[Motor_M] = map(constrain(Axis_Data[Motor_M], Min, Axis_Max), Min, Axis_Max, Min, Motor_Max);
    Serial.print("M : ");
    Serial.print(Axis_Data[Motor_M]);
    Serial.print("\t");
  }
  /*if((cTemp2[0] == 'R') || (cTemp2[0] == 'r')) {
    Axis_Data[Motor_R] = strtol(cTemp2+1, NULL, 10);
    Axis_Data[Motor_R] = map(constrain(Axis_Data[Motor_R], Min, Axis_Max), Min, Axis_Max, Min, Motor_Max);
    Serial.print("R : ");
    Serial.print(Axis_Data[Motor_R]);
    Serial.print("\t");
  }*/
  
  /*if((cTemp3[0] == 'L') || (cTemp3[0] == 'l')) {
    Axis_Data[Motor_L] = strtol(cTemp3+1, NULL, 10);
    Axis_Data[Motor_L] = map(constrain(Axis_Data[Motor_L], Min, Axis_Max), Min, Axis_Max, Min, Motor_Max);
    Serial.print("L : ");
    Serial.print(Axis_Data[Motor_L]);
    Serial.print("\n");
  }
  if((cTemp3[0] == 'M') || (cTemp3[0] == 'm')) {
    Axis_Data[Motor_M] = strtol(cTemp3+1, NULL, 10);
    Axis_Data[Motor_M] = map(constrain(Axis_Data[Motor_M], Min, Axis_Max), Min, Axis_Max, Min, Motor_Max);
    Serial.print("M : ");
    Serial.print(Axis_Data[Motor_M]);
    Serial.print("\n");
  }*/
  if((cTemp3[0] == 'R') || (cTemp3[0] == 'r')) {
    Axis_Data[Motor_R] = strtol(cTemp3+1, NULL, 10);
    Axis_Data[Motor_R] = map(constrain(Axis_Data[Motor_R], Min, Axis_Max), Min, Axis_Max, Min, Motor_Max);
    Serial.print("R : ");
    Serial.print(Axis_Data[Motor_R]);
    Serial.print("\n");
  }
}

