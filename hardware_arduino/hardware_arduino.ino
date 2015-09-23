#define M1_U 22
#define M2_U 28
#define M3_U 36

#define M1_D 27
#define M2_D 12
#define M3_D 37

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

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
      Serial.println("M S");
      digitalWrite(M1_U, LOW), digitalWrite(M1_D, LOW);
      digitalWrite(M2_U, LOW), digitalWrite(M2_D, LOW);
      digitalWrite(M3_U, LOW), digitalWrite(M3_D, LOW);
    }

    if(Read == 'x') {
      Serial.flush();
    }
  }
  delay(50);
  Serial.flush();
}
