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

char visaRead= 0;
char visaTemp = 0;
String stringCommand = "";
String stringTemp = "";
String stringWrite = "";

void setup()
{                
  Serial.begin(9600);
  Serial.flush();

  Serial.println("contacted.");
  
  delay(100);

  for(char i=0; i<3; i++) {
    pinMode(Motor_CW[i], OUTPUT);
    pinMode(Motor_CCW[i], OUTPUT);
    pinMode(Encoder[i], INPUT);
  }

  Motor_Min = 0;
  Motor_Max = 300;
  delay_time = 100;

  Serial.println("settings.");

  Motor_START();

  Serial.println("start.");
  Serial.flush();
}
  
void loop()                    
{
  if(Motor_work[nL] == 1) Motor_Encoder(nL);
  if(Motor_work[nC] == 1) Motor_Encoder(nC);
  if(Motor_work[nR] == 1) Motor_Encoder(nR);
  
  Command_Read();
  Motor_moveSum();

  stringWrite = "L";
  stringWrite.concat(Encoder_Data[nL]);
  stringWrite.concat("C");
  stringWrite.concat(Encoder_Data[nC]);
  stringWrite.concat("R");
  stringWrite.concat(Encoder_Data[nR]);

  Serial.println(stringWrite);
  delay(delay_time);
  stringWrite="";
}

void Command_Read() {
  stringCommand = "";
  
  while(Serial.available())
  {
    visaRead = Serial.read();
    visaTemp = visaRead;
    stringCommand.concat(visaTemp);
  }
  
  if(stringCommand != "")
  {
    char TempData[4];
  
    stringCommand.substring(1, 4).toCharArray(TempData, 4);
    GAxis_data[nL] = atoi(TempData);
      
    stringCommand.substring(5, 8).toCharArray(TempData, 4);
    GAxis_data[nC] = atoi(TempData);
      
    stringCommand.substring(9, 12).toCharArray(TempData, 4);
    GAxis_data[nR] = atoi(TempData);
    
    Serial.println(stringCommand); 
  }
}

void Motor_moveSum() {
  if((visaRead == 'x') || (visaRead == 'y') || (visaRead == 'r') || (visaRead == 'X') || (visaRead == 'Y') || (visaRead == 'R')){
    if((visaRead == 'x') || (visaRead == 'X')) Motor_FULLUP();
    if((visaRead == 'y') || (visaRead == 'Y')) Motor_FULLDW();
    if((visaRead == 'r') || (visaRead == 'R')) Motor_RESET();
  }
  else {
    if(GAxis_data[nL] > Encoder_Data[nL]) Motor_UP(nL);
    if(GAxis_data[nL] < Encoder_Data[nL]) Motor_DW(nL);
    if(GAxis_data[nL] == Encoder_Data[nL]) Motor_ST(nL);
  
    if(GAxis_data[nR] > Encoder_Data[nR]) Motor_UP(nR);
    if(GAxis_data[nR] < Encoder_Data[nR]) Motor_DW(nR);
    if(GAxis_data[nR] == Encoder_Data[nR]) Motor_ST(nR);

    if(GAxis_data[nC] > Encoder_Data[nC]) Motor_UP(nC);
    if(GAxis_data[nC] < Encoder_Data[nC]) Motor_DW(nC);
    if(GAxis_data[nC] == Encoder_Data[nC]) Motor_ST(nC);
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

void Motor_START(){
  Motor_FULLUP();
  delay(2000);
  Motor_FULLDW();
  delay(4000);
  Motor_RESET();
}

void Motor_FULLUP(){
  for(char i=0; i<3; i++) Motor_ways[i] = 0;

  for(char i=0; i<3; i++) {
    digitalWrite(Motor_CW[i], HIGH);
    digitalWrite(Motor_CCW[i], LOW);
  }
  Serial.flush();
}

void Motor_FULLDW(){
  for(char i=0; i<3; i++) Motor_ways[i] = 0;

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
    Motor_ways[i] = 0;
  }
  
  for(char i=0; i<3; i++) {
    digitalWrite(Motor_CW[i], LOW);
    digitalWrite(Motor_CCW[i], LOW);
    digitalWrite(Encoder[i], HIGH);
  }
  Serial.flush();
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
