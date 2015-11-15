#include <MsTimer2.h>

#define Motor_L 0
#define Motor_M 1
#define Motor_R 2

#define Serial_delay 250
#define Encoder_delay 10

#define Min 0
#define Axis_Max 255
#define Motor_Max 100

#define Motor_L_Revision 0
#define Motor_R_Revision 0
#define Motor_M_Revision 0

#define Motor_L_way 1
#define Motor_R_way 1
#define Motor_M_way 1

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
int Axis_Data[3] = {0,0,0};

int BUTTON_Count = 0;

String visaRead = "";

void Encoder() {
  if(Motor_work[Motor_L] == 1) Motor_Encoder(Motor_L);
  if(Motor_work[Motor_R] == 1) Motor_Encoder(Motor_R);
  if(Motor_work[Motor_M] == 1) Motor_Encoder(Motor_M);

  Motor_WORK();
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
  Serial.flush(); 

  MsTimer2::set(20, Encoder);
  MsTimer2::start();

} 

void loop() {
  if(digitalRead(BUTTON) == LOW) {
    Serial.println("RESET BUTTON IN");
    Serial.println(BUTTON_Count); 
    BUTTON_Count ++;
  }else BUTTON_Count = 0;

  if(BUTTON_Count > 10) {
    tone(TONE, 777);
    delay(100);
    Motor_START();
  }
  
  if (Serial.available() > 0) {
    //visaRead = Serial.readString();
    visaRead = Serial.readStringUntil('n');

    Serial.println(visaRead);

    if(visaRead != "") {
      if((visaRead == "U") || (visaRead == "u") || (visaRead == "D") || (visaRead == "d") || (visaRead == "S") || (visaRead == "s") || (visaRead == "X") || (visaRead == "x")) {
        //Serial.println("Command WORK");
      }else stringMotorAxis();
    }
    //Serial.println("\n\n");
  }
  //SerialShow();
  
  Serial.flush();
  delay(Serial_delay);
}

