long randNumber;
#include <Servo.h> // 서보 라이브러리 사용

Servo myservo1; // myservo 라는 이름의 서보 선언
Servo myservo2;
Servo myservo3;

int trig = 13; //초음파센서의 trig핀을 아두이노 13번 핀 연결
int echo = 12; //초음파센서의 echo핀을 아두이노 12번 핀 연결

int count = 0;
int oldcount = 0;
void setup() {
  Serial.begin(9600);
  myservo1.attach(2);
  myservo2.attach(3);
  myservo3.attach(4);
  randomSeed(analogRead(0));
  pinMode(trig, OUTPUT); // 13번핀 OUTPUT 설정
  pinMode(echo, INPUT);  // 12번핀 INPUT 설정
  myservo1.write(90);
  delay(500);
  myservo2.write(90);
  delay(500);
  myservo3.write(90);
  delay(1000);
  myservo1.write(0);
  delay(500);
  myservo2.write(0);
  delay(500);
  myservo3.write(0); 
  delay(500);
  Serial.println("ready for start");
}

void loop() {
  ///////////////초음파 센서 인식/////////////
  long duration, distance;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration / 58; // cm 환산
  Serial.println(distance);
  //////////////////////////////////////////
  
  if (distance <= 10) count = 1;
  else count = 0;
  
  if (count == 1 && oldcount == 0){
    
    randNumber = random(1, 4);
    Serial.println(randNumber);
    
    if (randNumber == 1) {  //가위
      myservo1.write(90);
      myservo2.write(0);
      myservo3.write(0);
      delay(2000);
    } else if (randNumber == 2){  //바위
      myservo1.write(0);
      myservo2.write(90);
      myservo3.write(0);
      delay(2000);
    } else if (randNumber == 3){  //보
      myservo1.write(0);
      myservo2.write(0);
      myservo3.write(90);
      delay(2000);
    }
  } else if (count == 0 && oldcount == 1) {
    myservo1.write(0);
    myservo2.write(0);
    myservo3.write(0);
  }
  oldcount = count;
}
