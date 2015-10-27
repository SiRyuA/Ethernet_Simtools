int Motor_CW[3] = {22,28,36};
int Motor_CCW[3] = {27,12,37};
int Encoder[3] = {2,3,18};

volatile int Encoder_Data[3] = {0,0,0};
volatile int Encoder_Save[3] = {0,0,0};

int Motor_work[3] = {0,0,0};
int Motor_way[3] = {0,0,0};

int Motor_Min = 0;
int Motor_Max = 0;
int delay_time = 100;

int AxisRead = 0;
int AxisData[3] = {0,0,0};
char AxisControl = 0;

char buffers[18];
String stringWrite ="";


void setup() {
  // put your setup code here, to run once:
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
  delay_time = 20;

  Serial.println("settings.");

  Motor_START();

  Serial.println("start.");
  Serial.flush();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Motor_work[0] == 1) Motor_Encoder(0);
  if(Motor_work[1] == 1) Motor_Encoder(1);
  if(Motor_work[2] == 1) Motor_Encoder(2);
  
  while(Serial.available()) {
    int index = 0;
    int numChar = Serial.available();

    if(numChar > 18) numChar = 18;
    while(numChar--) buffers[index++] = Serial.read();

    splitString(buffers);
  }

  Move();

  stringWrite = "L";
  stringWrite.concat(map(Encoder_Data[0], Motor_Min, Motor_Max, 0, 255));
  stringWrite.concat("C");
  stringWrite.concat(map(Encoder_Data[1], Motor_Min, Motor_Max, 0, 255));
  stringWrite.concat("R");
  stringWrite.concat(map(Encoder_Data[2], Motor_Min, Motor_Max, 0, 255));

  Serial.print(stringWrite);
  Serial.print("\t");
  Serial.print(AxisControl);
  Serial.print("\t");
  Serial.print(AxisData[0]);
  Serial.print("\t");
  Serial.print(AxisData[1]);
  Serial.print("\t");
  Serial.print(AxisData[2]);
  Serial.println("");
  delay(delay_time);
  stringWrite="";
}

void splitString(char* data) {
  char* parameter;
  parameter = strtok(data, ","); // "," 기준 데이터 값 잘라내기
  while(parameter != NULL) { // 아닐경우 다시 ","기준 재기
    Command(parameter);
    parameter = strtok (NULL, ",");
  }
  
  //버퍼 초기화
  for(int x = 0; x < 18; x++) {
    buffers[x] = '\0';
  }
  Serial.flush();
}

void Command(char* data) {
  if((data[0] == 'L') || (data[0] == 'l')) {
    AxisRead = strtol(data+1, NULL, 10);
    AxisRead = constrain(AxisRead, 0, 255);

    AxisData[0] = AxisRead;
  }
  
  if((data[0] == 'C') || (data[0] == 'c')) {
    AxisRead = strtol(data+1, NULL, 10);
    AxisRead = constrain(AxisRead, 0, 255);

    AxisData[1] = AxisRead;
  }
  
  if((data[0] == 'R') || (data[0] == 'r')) {
    AxisRead = strtol(data+1, NULL, 10);
    AxisRead = constrain(AxisRead, 0, 255);

    AxisData[2] = AxisRead;
  }
  
  if((data[0] == 'X') || (data[0] == 'x')) AxisControl = 'x';
  if((data[0] == 'Y') || (data[0] == 'y')) AxisControl = 'y';
  if((data[0] == 'Z') || (data[0] == 'z')) AxisControl = 'z';
  if((data[0] == 'S') || (data[0] == 's')) AxisControl = 0;
}

void Move(){
  if((AxisControl == 'x') || (AxisControl == 'y') || (AxisControl == 'z')) {
    if(AxisControl == 'x') Motor_FULLUP();
    if(AxisControl == 'y') Motor_FULLDW();
    if(AxisControl == 'z') Motor_RESET();
  }else {
    if(AxisData[0] > map(Encoder_Data[0], Motor_Min, Motor_Max, 0, 255)) Motor_UP(0);
    if(AxisData[0] < map(Encoder_Data[0], Motor_Min, Motor_Max, 0, 255)) Motor_DW(0);
    if(AxisData[0] == map(Encoder_Data[0], Motor_Min, Motor_Max, 0, 255)) Motor_ST(0);
    
    if(AxisData[1] > map(Encoder_Data[1], Motor_Min, Motor_Max, 0, 255)) Motor_UP(1);
    if(AxisData[1] < map(Encoder_Data[1], Motor_Min, Motor_Max, 0, 255)) Motor_DW(1);
    if(AxisData[1] == map(Encoder_Data[1], Motor_Min, Motor_Max, 0, 255)) Motor_ST(1);
  
    if(AxisData[2] > map(Encoder_Data[2], Motor_Min, Motor_Max, 0, 255)) Motor_UP(2);
    if(AxisData[2] < map(Encoder_Data[2], Motor_Min, Motor_Max, 0, 255)) Motor_DW(2);
    if(AxisData[2] == map(Encoder_Data[2], Motor_Min, Motor_Max, 0, 255)) Motor_ST(2);
  }
}

