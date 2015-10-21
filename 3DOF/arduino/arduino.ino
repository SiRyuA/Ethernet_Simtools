 int Motor_CW[3] = {22,28,36};
int Motor_CCW[3] = {27,12,37};
int Encoder[3] = {2,3,18};

volatile int Encoder_Data[3] = {0,0,0};
volatile int Encoder_Save[3] = {0,0,0};

int Motor_work[3] = {0,0,0};
int Motor_way[3] = {0,0,0};

int Motor_Min = 0;
int Motor_Max = 0;

int Only_Arduino = 0;

char buffers[9];

void setup() {
  // put your setup code here, to run once:
  for(char i=0; i<3; i++) {
    pinMode(Motor_CW[i], OUTPUT);
    pinMode(Motor_CCW[i], OUTPUT);
    pinMode(Encoder[i], INPUT);
  }

  Serial.begin(9600);
  Serial.println("START");

  Motor_Min = 0;
  Motor_Max = 300;

  Only_Arduino = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Motor_work[0] == 1) Motor_Encoder(0);
  if(Motor_work[1] == 1) Motor_Encoder(1);
  if(Motor_work[2] == 1) Motor_Encoder(2);
  
  while(Serial.available()) {
    int index = 0;
    int numChar = Serial.available();

    if(numChar > 8) numChar = 8;
    while(numChar--) buffers[index++] = Serial.read();

    splitString(buffers);
  }
  delay(20);

  if(Only_Arduino == 0) {
    Serial.print("L");
    Serial.print(map(Encoder_Data[0],Motor_Min,Motor_Max,0,255));
    Serial.print("C");
    Serial.print(map(Encoder_Data[1],Motor_Min,Motor_Max,0,255));
    Serial.print("R");
    Serial.print(map(Encoder_Data[2],Motor_Min,Motor_Max,0,255));
    
    Serial.println("");
  }
}

void splitString(char* data) {
  if(Only_Arduino == 1) {
    Serial.print("Data read : ");
    Serial.println(data);
  }
  char* parameter;
  parameter = strtok(data, ","); // "," 기준 데이터 값 잘라내기
  while(parameter != NULL) { // 아닐경우 다시 ","기준 재기
    Move(parameter);
    parameter = strtok (NULL, ",");
  }
  
  //버퍼 초기화
  for(int x = 0; x < 9; x++) {
    buffers[x] = '\0';
  }
  Serial.flush();
}

void Move(char* data) {
  if(data[0] == 'a') Motor_UP(0);
  if(data[0] == 'b') Motor_ST(0);
  if(data[0] == 'c') Motor_DW(0);

  if(data[0] == 'd') Motor_UP(1);
  if(data[0] == 'e') Motor_ST(1);
  if(data[0] == 'f') Motor_DW(1);

  if(data[0] == 'g') Motor_UP(2);
  if(data[0] == 'h') Motor_ST(2);
  if(data[0] == 'i') Motor_DW(2);

  if(data[0] == 'y') Motor_FULLUP();
  if(data[0] == 'x') Motor_FULLDOWN();
  if(data[0] == 'r') Motor_RESET();
}
