#define Motor_L 0
#define Motor_M 1
#define Motor_R 2

#define Buffer_Size 48

#define Motor_Min 0
#define Motor_Max 80
#define delay_time 20

#define Axis_Min 0
#define Axis_Max 255

int Motor_CW[3] = {22,28,36};
int Motor_CCW[3] = {27,12,37};
int Encoder[3] = {2,3,18};
int Tone = 50;

volatile int Encoder_Data[3] = {0,0,0};
volatile int Encoder_Save[3] = {0,0,0};

int Motor_work[3] = {0,0,0};
int Motor_way[3] = {0,0,0};

int AxisRead = 0;
int AxisData[3] = {0,0,0};
char AxisControl = 0;

char buffers[Buffer_Size];
String stringWrite ="";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(2400);
  Serial.flush();

  Serial.println("contacted.");
  
  delay(100);

  for(char i=0; i<3; i++) {
    pinMode(Motor_CW[i], OUTPUT);
    pinMode(Motor_CCW[i], OUTPUT);
    pinMode(Encoder[i], INPUT);
  }

  Serial.println("settings.");

  Motor_START();

  Serial.println("start.");
  Serial.flush();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Motor_work[Motor_L] == 1) Motor_Encoder(Motor_L);
  if(Motor_work[Motor_M] == 1) Motor_Encoder(Motor_M);
  if(Motor_work[Motor_R] == 1) Motor_Encoder(Motor_R);
  
  while(Serial.available()) {
    int index = 0;
    int numChar = Serial.available();

    if(numChar > Buffer_Size) numChar = Buffer_Size;
    while(numChar--) buffers[index++] = Serial.read();

    splitString(buffers);
  }

  Move();
  String_println();
  delay(delay_time);
}

