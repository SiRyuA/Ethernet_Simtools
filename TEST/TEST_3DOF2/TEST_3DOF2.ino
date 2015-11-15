#include <MsTimer2.h>

#define Motor_L 0
#define Motor_M 1
#define Motor_R 2

#define Serial_delay 500
#define Encoder_delay 5

#define Min 0
#define Axis_Max 255
#define Motor_Max 70

#define TONE 50
#define BUTTON 51

int Motor_CW[3] = {22,28,36}; 
int Motor_CCW[3] = {27,12,37}; 
int EncoderA[3] = {2,3,4}; 
int EncoderB[3] = {18,8,10};

int Encoder_Data[3] = {0,0,0};
int EncoderA_Temp[3] = {0,0,0};
int EncoderB_Temp[3] = {0,0,0};

int Motor_work[3] = {0,0,0};
int Motor_way[3] = {0,0,0};
int Axis_Temp[3] = {0,0,0};
int Axis_Data[3] = {0,0,0};
int Axis_Move[3] = {0,0,0};

int BUTTON_Count = 0;
int WORK_Locker = 0;

unsigned long previousMillis = 0; 
const long interval = 500;

String visaRead = "";

void Encoder() {
  if(Motor_work[Motor_L] == 1) Motor_Encoder(Motor_L);
  if(Motor_work[Motor_R] == 1) Motor_Encoder(Motor_R);
  if(Motor_work[Motor_M] == 1) Motor_Encoder(Motor_M);

  if((visaRead == "U") || (visaRead == "u") || (visaRead == "D") || (visaRead == "d") || (visaRead == "S") || (visaRead == "s") || (visaRead == "X") || (visaRead == "x")) {
    if((visaRead == "U") || (visaRead == "u")) Motor_FULLUP();
    if((visaRead == "D") || (visaRead == "d")) Motor_FULLDW();
    if((visaRead == "S") || (visaRead == "s")) Motor_START();
    if((visaRead == "X") || (visaRead == "x")) Motor_RST();
  }else {
    if(WORK_Locker == 0) Motor_WORK();
  }
}

void setup() {
  Serial.begin(9600);
  Serial.flush();

  Serial.println("contacted.");

  for(char i=0; i<3; i++) { 
   pinMode(Motor_CW[i], OUTPUT); 
   pinMode(Motor_CCW[i], OUTPUT); 
   pinMode(EncoderA[i], INPUT);
   pinMode(EncoderB[i], INPUT); 
  }
  pinMode(TONE, OUTPUT);
  pinMode(BUTTON, INPUT);

  Serial.println("settings."); 
  Motor_START(); 
 
  Serial.println("start."); 
} 

void loop() {
  if(digitalRead(BUTTON) == LOW) {
    //Serial.println("RESET BUTTON IN");
    //Serial.println(BUTTON_Count); 
    BUTTON_Count ++;
    tone(TONE, 777);
  }else {
    BUTTON_Count = 0;
    noTone(TONE);
  }

  if(BUTTON_Count > 2) {
    noTone(TONE);
    Motor_START();
  }
  
  if(Motor_work[Motor_L] == 1) Motor_Encoder(Motor_L);
  if(Motor_work[Motor_R] == 1) Motor_Encoder(Motor_R);
  if(Motor_work[Motor_M] == 1) Motor_Encoder(Motor_M);

  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (Serial.available() > 0) {
      //visaRead = Serial.readString();
      visaRead = Serial.readStringUntil(';');
    
      //Serial.println(visaRead);
    }
  }
  
  if(visaRead != "") {
    if((visaRead == "U") || (visaRead == "u") || (visaRead == "D") || (visaRead == "d") || (visaRead == "S") || (visaRead == "s") || (visaRead == "X") || (visaRead == "x")) {
    }else stringMotorAxis();
  }
 
  SerialShow();
  
  Serial.flush();
  delay(Serial_delay);
}

