//Ticoder Interrupt
void Ticoder_Interrupt() {
  //Ticoder Pulse Make
  if(Interrupt_Pulse == 0) Interrupt_Pulse = 1;
  else if(Interrupt_Pulse == 1) Interrupt_Pulse = 0;

  // Ticoder Work
  if(Motor_Work[Motor_L] == 1) Ticoder(Motor_L);
  if(Motor_Work[Motor_R] == 1) Ticoder(Motor_R);
  if(Motor_Work[Motor_C] == 1) Ticoder(Motor_C);

  if(TEST_Mode == 1) if(Interrupt_Pulse == 1) Serial.println("U");
}

// Ticoder
void Ticoder(int PORT) {
  if(Interrupt_Pulse == 1) { // Ticoder Pulse HIGH
    if(Motor_Ways[PORT] == 1) Ticoder_Temp[PORT]++; // Motor Forword
    else if(Motor_Ways[PORT] == -1) Ticoder_Temp[PORT]--; // Motor Backword
  }else Ticoder_Temp[PORT] = Ticoder_Data[PORT]; // Ticoder Pulse LOW

  Ticoder_Data[PORT] = Ticoder_Temp[PORT]; // Ticoder Save

  // Ticoder Min Limit
  if(Ticoder_Data[PORT] < Motor_Min) {
    Ticoder_Data[PORT] = Motor_Min;
    Motor_STOP(PORT);
  }

  // Ticoder Max Limit
  if(Ticoder_Data[PORT] > Motor_Max) {
    Ticoder_Data[PORT] = Motor_Max;
    Motor_STOP(PORT);
  }
}
