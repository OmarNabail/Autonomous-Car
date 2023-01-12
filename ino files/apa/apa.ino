#define enbA  7
#define enbB  2
#define IN1  6    //Right Motor (-)
#define IN2  5    //Right Motor (+)
#define IN3  4    //Left Motor (+)
#define IN4  3    //Right Motor (-)
int RightSpd = 130;
int LeftSpd = 130;
// back pin 
#define BacktrigPin  13
#define BackechoPin  12
long Backdisance;
long Backduration;
// backRight pin 
#define BackRighttrigPin  11
#define BackRightechoPin  10
long BackRightdisance;
long BackRightduration;
// front pin 
#define frontTrigPin  8
#define frontEchoPin  9
long frontdisance;
long frontduration;
boolean  start=true;
int const buzzPin = A5;
void setup(){
  Serial.begin(9600);
  pinMode(BacktrigPin, OUTPUT);
  pinMode(BackechoPin, INPUT);
  pinMode(BackRighttrigPin, OUTPUT);
  pinMode(BackRightechoPin, INPUT);
  pinMode(frontTrigPin, OUTPUT);
  pinMode(frontEchoPin, INPUT);
  pinMode(enbA, OUTPUT);
  pinMode(enbB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(buzzPin, OUTPUT);
}

void loop(){
   ultraBack();
  ultraRightBack();
  ultrafront();
if(start == 1){
   if(BackRightdisance>25&&frontdisance>25){   
    park();
   }else{
    
    forward();
  }  
  } 
    

}
void park(){
  //buzzerAleram();
  stopCar();
    delay(1000);
    forward();
    delay(900);
    backward();
    delay(700);
    left();
    delay(800);
    backward();
    delay(600);
    forward();
    delay(100);
    right();
    delay(850);
     forward();
    delay(150);
     stopCar();
      start=false;
      
  }
 
void ultraBack(){
   int Backduration, Backdisance;
  
  digitalWrite(BacktrigPin, HIGH); 
  delay(1);
  digitalWrite(BacktrigPin, LOW);
  
  Backduration = pulseIn(BackechoPin, HIGH);
  Backdisance = (Backduration/2) / 29.1; 
    if (Backdisance <= 10 && Backdisance >= 0) {
      // Buzz
      digitalWrite(buzzPin, HIGH);
    } else {
      // Don't buzz
      digitalWrite(buzzPin, LOW);
    }
}
void ultraRightBack(){
  digitalWrite(BackRighttrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(BackRighttrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(BackRighttrigPin, LOW);
  BackRightduration = pulseIn(BackRightechoPin, HIGH);
  BackRightdisance = BackRightduration*0.034/2; 
}
void ultrafront(){
  digitalWrite(frontTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(frontTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(frontTrigPin, LOW);
  frontduration = pulseIn(frontEchoPin, HIGH);
  frontdisance = frontduration*0.034/2; 
}
void forward(){
       analogWrite(enbA, RightSpd);
      analogWrite(enbB, LeftSpd);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
  }
  void backward(){
      analogWrite(enbA, RightSpd);
      analogWrite(enbB, LeftSpd);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
  }
  void left(){
    analogWrite(enbA, RightSpd);
      analogWrite(enbB, LeftSpd);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
  }
  void right(){
      analogWrite(enbA, RightSpd);
      analogWrite(enbB, LeftSpd);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
  }
    void stopCar(){
       analogWrite(enbA, 0);
      analogWrite(enbB, 0);
  }
