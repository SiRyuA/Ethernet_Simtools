void splitString(char* data) {
  char* parameter;
  parameter = strtok(data, "n");
  while(parameter != NULL) {
    Command(parameter);
    parameter = strtok (NULL, "nn");
  }
  
  //버퍼 초기화
  for(int x = 0; x < Buffer_Size; x++) {
    buffers[x] = '\0';
  }
  Serial.flush();
}

void String_println() {
  stringWrite = "A";
  stringWrite.concat(Encoder_Data[Motor_L]);
  stringWrite.concat("B");
  stringWrite.concat(Encoder_Data[Motor_M]);
  stringWrite.concat("C");
  stringWrite.concat(Encoder_Data[Motor_R]);
  stringWrite.concat("L");
  stringWrite.concat(map(AxisData[Motor_L], Axis_Min, Axis_Max, Motor_Min, Motor_Max));
  stringWrite.concat("M");
  stringWrite.concat(map(AxisData[Motor_M], Axis_Min, Axis_Max, Motor_Min, Motor_Max));
  stringWrite.concat("R");
  stringWrite.concat(map(AxisData[Motor_R], Axis_Min, Axis_Max, Motor_Min, Motor_Max));
  stringWrite.concat(AxisControl);
  
  Serial.print(stringWrite + "\n");
  
  stringWrite="";
}

void Command(char* data) {
  if((data[0] == 'L') || (data[0] == 'l')) {
    AxisRead = strtol(data+1, NULL, 10);
    AxisRead = constrain(AxisRead, 0, 255);

    AxisData[Motor_L] = AxisRead;
  }
  
  if((data[0] == 'R') || (data[0] == 'r')) {
    AxisRead = strtol(data+1, NULL, 10);
    AxisRead = constrain(AxisRead, 0, 255);

    AxisData[Motor_R] = AxisRead;
  }
  
  if((data[0] == 'M') || (data[0] == 'm')) {
    AxisRead = strtol(data+1, NULL, 10);
    AxisRead = constrain(AxisRead, 0, 255);

    AxisData[Motor_M] = AxisRead;
  }
  
  if((data[0] == 'V') || (data[0] == 'v')) AxisControl = 0;
  if((data[0] == 'W') || (data[0] == 'w')) AxisControl = 'w';
  if((data[0] == 'X') || (data[0] == 'x')) AxisControl = 'x';
  if((data[0] == 'Y') || (data[0] == 'y')) AxisControl = 'y';
  if((data[0] == 'Z') || (data[0] == 'z')) AxisControl = 'z';
}

void Move(){
  if((AxisControl == 'w') || (AxisControl == 'x') || (AxisControl == 'y') || (AxisControl == 'z')) {
    if(AxisControl == 'w') Motor_START();
    if(AxisControl == 'x') Motor_FULLUP();
    if(AxisControl == 'y') Motor_FULLDW();
    if(AxisControl == 'z') Motor_RST(); 
  }else {
    if(map(AxisData[Motor_M], Axis_Min, Axis_Max, Motor_Min, Motor_Max) > Encoder_Data[Motor_M]) Motor_UP(Motor_M);
    if(map(AxisData[Motor_M], Axis_Min, Axis_Max, Motor_Min, Motor_Max) < Encoder_Data[Motor_M]) Motor_DW(Motor_M);
    if(map(AxisData[Motor_M], Axis_Min, Axis_Max, Motor_Min, Motor_Max) == Encoder_Data[Motor_M]) Motor_ST(Motor_M);
    
    if(map(AxisData[Motor_R], Axis_Min, Axis_Max, Motor_Min, Motor_Max) > Encoder_Data[Motor_L]) Motor_UP(Motor_L);
    if(map(AxisData[Motor_R], Axis_Min, Axis_Max, Motor_Min, Motor_Max) < Encoder_Data[Motor_L]) Motor_DW(Motor_L);
    if(map(AxisData[Motor_R], Axis_Min, Axis_Max, Motor_Min, Motor_Max) == Encoder_Data[Motor_L]) Motor_ST(Motor_L);
  
    if(map(AxisData[Motor_R], Axis_Min, Axis_Max, Motor_Min, Motor_Max) > Encoder_Data[Motor_R]) Motor_UP(Motor_R);
    if(map(AxisData[Motor_R], Axis_Min, Axis_Max, Motor_Min, Motor_Max) < Encoder_Data[Motor_R]) Motor_DW(Motor_R);
    if(map(AxisData[Motor_R], Axis_Min, Axis_Max, Motor_Min, Motor_Max) == Encoder_Data[Motor_R]) Motor_ST(Motor_R);
  }
}

