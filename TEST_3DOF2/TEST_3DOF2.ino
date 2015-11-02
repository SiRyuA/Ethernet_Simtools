#define Motor_L 0
#define Motor_M 1
#define Motor_R 2

#define delay_time 20

#define Min 0
#define Axis_Max 255
#define Motor_Max 100

int Motor_CW[3] = {22,28,36}; 
int Motor_CCW[3] = {27,12,37}; 
int Encoder[3] = {2,3,18}; 
int Tone = 50;

volatile int Encoder_Data[3] = {0,0,0};
volatile int Encoder_Save[3] = {0,0,0};

int Motor_work[3] = {0,0,0};
int Motor_way[3] = {0,0,0};
int Axis_Data[3] = {0,0,0};

String visaRead = "";

void setup() {
  Serial.begin(9600);
  Serial.flush();

  Serial.println("contacted.");

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
  if(Motor_work[Motor_L] == 1) Motor_Encoder(Motor_L);
  if(Motor_work[Motor_M] == 1) Motor_Encoder(Motor_M);
  if(Motor_work[Motor_R] == 1) Motor_Encoder(Motor_R);
  
  while (Serial.available() > 0) {
    //visaRead = Serial.readString();
    visaRead = Serial.readStringUntil(';');

    Serial.println(visaRead);

    if(visaRead != "") {
      if((visaRead == "U") || (visaRead == "u") || (visaRead == "D") || (visaRead == "d") || (visaRead == "S") || (visaRead == "s") || (visaRead == "X") || (visaRead == "x")) {
        if((visaRead == "U") || (visaRead == "u")) Motor_FULLUP();
        if((visaRead == "D") || (visaRead == "d")) Motor_FULLDW();
        if((visaRead == "S") || (visaRead == "s")) Motor_START();
        if((visaRead == "X") || (visaRead == "x")) Motor_RST();
      }else stringMotorAxis();
    }
    Serial.println("\n\n");
  }
  Motor_WORK();
  
  visaRead = "";
  Serial.flush();
  delay(delay_time);
}

