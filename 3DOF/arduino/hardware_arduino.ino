#define M1_U 22
#define M2_U 28
#define M3_U 36

#define M1_D 27
#define M2_D 12
#define M3_D 37

unsigned long pwm_value1 = 0;
unsigned long pwm_value2 = 0;

int way = 0;
int i = 0;
int j = 0;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(A12, INPUT);
  pinMode(A13, INPUT);

  pinMode(M1_U, OUTPUT);
  pinMode(M1_D, OUTPUT);
  pinMode(M2_U, OUTPUT);
  pinMode(M2_D, OUTPUT);
  pinMode(M3_U, OUTPUT);
  pinMode(M3_D, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available() > 0) {
    char Read = Serial.read();
  
    if(Read == 'a') {
      Serial.println("Motor L Up");
      digitalWrite(M1_U, HIGH);
      digitalWrite(M1_D, LOW);
    }
    if(Read == 'b') {
      Serial.println("Motor L Stop");
      digitalWrite(M1_U, LOW);
      digitalWrite(M1_D, LOW);
    }
    if(Read == 'c') {
      Serial.println("Motor L Down");
      digitalWrite(M1_U, LOW);
      digitalWrite(M1_D, HIGH);
    }

    if(Read == 'd') {
      Serial.println("Motor R Up");
      digitalWrite(M2_U, HIGH);
      digitalWrite(M2_D, LOW);
    }
    
    if(Read == 'e') {
      Serial.println("Motor R Stop");
      digitalWrite(M2_U, LOW);
      digitalWrite(M2_D, LOW);
    }
    
    if(Read == 'f') {
      Serial.println("Motor R Down");
      digitalWrite(M2_U, LOW);
      digitalWrite(M2_D, HIGH);
    }

    if(Read == 'g') {
      Serial.println("Motor C Up");
      digitalWrite(M3_U, HIGH);
      digitalWrite(M3_D, LOW);
    }
    if(Read == 'h') {
      Serial.println("Motor C Stop");
      digitalWrite(M3_U, LOW);
      digitalWrite(M3_D, LOW);
    }
    if(Read == 'i') {
      Serial.println("Motor C Down");
      digitalWrite(M3_U, LOW);
      digitalWrite(M3_D, HIGH);
    }

    if(Read == 's') {
      Serial.println("Motor Stop");
      digitalWrite(M1_U, LOW), digitalWrite(M1_D, LOW);
      digitalWrite(M2_U, LOW), digitalWrite(M2_D, LOW);
      digitalWrite(M3_U, LOW), digitalWrite(M3_D, LOW);
    }

    if(Read == 'x') {
      Serial.flush();
      i=0;
      j=0;
    }
  }
  delay(1);
  Serial.flush();

  Analog_TEST();

}

void PWM_TEST(void) {
  pwm_value1 = pulseIn(2, HIGH);
  pwm_value2 = pulseIn(3, HIGH);

  Serial.print("1 : ");
  Serial.print(pwm_value1);
  Serial.print("\t\t");
  Serial.print("2 : ");
  Serial.println(pwm_value2);  
}

void Analog_TEST(void) {    
  int ARead1 = analogRead(A12);
  int ARead2 = analogRead(A13);

  if(ARead1 > 900) i++;
  if(ARead2 > 900) j++; 

  Serial.print("Hall A : ");
  Serial.print(ARead1);
  Serial.print("\t | ");
  Serial.print("Hall B : ");
  Serial.print(ARead2);
  Serial.print("\t | ");
  Serial.print("Pulse A HIGH : ");
  Serial.print(i);
  Serial.print("\t | ");
  Serial.print("Pulse B HIGH : ");
  Serial.println(j);
}

