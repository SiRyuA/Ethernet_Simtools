#define nL 0
#define nC 1
#define nR 2

int Motor_CW[3] = {22, 28, 36};
int Motor_CCW[3] = {27, 12, 37};
int Encoder[3] = {2, 3, 18};

volatile int Encoder_Data[3] = {0, 0, 0};
volatile int Encoder_Save[3] = {0, 0, 0};

int Motor_work[3] = {0, 0, 0};
int Motor_ways[3] = {0, 0, 0};
int GAxis_data[3] = {0, 0, 0};

int Motor_Min = 0;
int Motor_Max = 0;

int delay_time = 100;

char cRead= 0;
char cTemp = 0;
String sCommand = "";
String sTemp = "";

void setup()
{                
  Serial.begin(9600);
  Serial.flush();

  Serial.println("contacted.");
  
  delay(1000);

  for(char i=0; i<3; i++) {
    pinMode(Motor_CW[i], OUTPUT);
    pinMode(Motor_CCW[i], OUTPUT);
    pinMode(Encoder[i], INPUT);
  }

  Motor_Min = 0;
  Motor_Max = 300;
  delay_time = 100;

  Serial.println("settings.");

  delay(1000);

  Serial.println("start.");
  Serial.flush();
}
  
void loop()                    
{
  if(Motor_work[nL] == 1) Motor_Encoder(nL);
  if(Motor_work[nC] == 1) Motor_Encoder(nC);
  if(Motor_work[nR] == 1) Motor_Encoder(nR);
  
  Command();

  if(cRead == 'Y') Motor_FULLUP();
  if(cRead == 'X') Motor_FULLDOWN();
  if(cRead == 'R') Motor_RESET();

  if(GAxis_data[nL] > Encoder_Data[nL]) Motor_UP(nL);
  if(GAxis_data[nL] < Encoder_Data[nL]) Motor_DW(nL);
  if(GAxis_data[nL] == Encoder_Data[nL]) Motor_ST(nL);

  if(GAxis_data[nC] > Encoder_Data[nC]) Motor_UP(nC);
  if(GAxis_data[nC] < Encoder_Data[nC]) Motor_DW(nC);
  if(GAxis_data[nC] == Encoder_Data[nC]) Motor_ST(nC);

  if(GAxis_data[nR] > Encoder_Data[nR]) Motor_UP(nR);
  if(GAxis_data[nR] < Encoder_Data[nR]) Motor_DW(nR);
  if(GAxis_data[nR] == Encoder_Data[nR]) Motor_ST(nR);

  delay(delay_time);
}

void Command(void) {
  sCommand = "";
  
  while(Serial.available())
  {
    cRead = Serial.read();
    cTemp = cRead;
    sCommand.concat(cTemp);
  }
  
  if(sCommand != "")
  {
    char cTempData[4];
  
    sCommand.substring(1, 4).toCharArray(cTempData, 4);
    GAxis_data[nL] = atoi(cTempData);
      
    sCommand.substring(5, 8).toCharArray(cTempData, 4);
    GAxis_data[nC] = atoi(cTempData);
      
    sCommand.substring(9, 12).toCharArray(cTempData, 4);
    GAxis_data[nR] = atoi(cTempData);
    
    Serial.println(sCommand + ": L=" + GAxis_data[nL] + ", C=" + GAxis_data[nC] + ", R=" + GAxis_data[nR] ); 
  }
}

void Motor_Encoder(int PORT) { 
  if(digitalRead(Encoder[PORT]) == HIGH) {
    if(Motor_ways[PORT] == 1) Encoder_Data[PORT]++;
    else if(Motor_ways[PORT] == -1) Encoder_Data[PORT]--;
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
}

void Motor_UP(int PORT){
  Encoder_Data[PORT] = Encoder_Save[PORT];
  Motor_work[PORT] = 1;
  Motor_ways[PORT] = 1;
  
  digitalWrite(Motor_CW[PORT], HIGH);
  digitalWrite(Motor_CCW[PORT], LOW);
}

void Motor_ST(int PORT){
  Motor_work[PORT] = 0;
  Motor_ways[PORT] = 1;
  
  digitalWrite(Motor_CW[PORT], LOW);
  digitalWrite(Motor_CCW[PORT], LOW);
}

void Motor_DW(int PORT){
  Encoder_Data[PORT] = Encoder_Save[PORT];
  Motor_work[PORT] = 1;
  Motor_ways[PORT] = -1;
  
  digitalWrite(Motor_CW[PORT], LOW);
  digitalWrite(Motor_CCW[PORT], HIGH);
}

void Motor_FULLUP(){
  for(char i=0; i<3; i++) Motor_ways[i] = 0;

  for(char i=0; i<3; i++) {
    digitalWrite(Motor_CW[i], HIGH);
    digitalWrite(Motor_CCW[i], LOW);
  }
  Serial.flush();
}

void Motor_FULLDOWN(){
  for(char i=0; i<3; i++) Motor_ways[i] = 0;

  for(char i=0; i<3; i++) {
    digitalWrite(Motor_CW[i], LOW);
    digitalWrite(Motor_CCW[i], HIGH);
  }
  Serial.flush();
}

void Motor_RESET(){
  for(char i=0; i<3; i++) {
    Encoder_Data[i] = 0;X
    Encoder_Save[i] = 0;
    Motor_work[i] = 0;
    Motor_ways[i] = 0;
  }
  
  for(char i=0; i<3; i++) {
    digitalWrite(Motor_CW[i], LOW);
    digitalWrite(Motor_CCW[i], LOW);
    digitalWrite(Encoder[i], HIGH);
  }
  Serial.flush();
}

