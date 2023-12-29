int disRight;
int disLeft;
int disBack;
int disFront;

int motorF1 = 11;
int motorF2 = 10;

int motorB1 = 13;
int motorB2 = 12;

int sensorFtrig = 2;
int sensorFecho = 3;

int sensorBtrig = 4;
int sensorBecho = 5;

int sensorRtrig = 6;
int sensorRecho = 7;

int sensorLtrig = 8;
int sensorLecho = 9;


void setup(){

  Serial.begin(9600);

  //Sensors
  pinMode(sensorFtrig,OUTPUT);
  pinMode(sensorBtrig,OUTPUT);
  pinMode(sensorRtrig,OUTPUT);
  pinMode(sensorLtrig,OUTPUT);

  pinMode(sensorFecho,INPUT);
  pinMode(sensorBecho,INPUT);
  pinMode(sensorRecho,INPUT);
  pinMode(sensorLecho,INPUT);

  //motor
  pinMode(motorF1,OUTPUT);
  pinMode(motorF2,OUTPUT);
  pinMode(motorB1,OUTPUT);
  pinMode(motorB2,OUTPUT);

  //extra VCCs and GRNGs
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);

  digitalWrite(A0,HIGH);
  digitalWrite(A1,LOW);  //pair 1 = A0 vcc, A1 grnd
  digitalWrite(A2,HIGH);
  digitalWrite(A3,LOW);  //pair 2 = A2 vcc, A3 grnd

}

void loop(){

  disFront = measure(sensorFtrig,sensorFecho);
  if(disFront <= 20){
    Stop();
    disBack = measure(sensorBtrig,sensorBecho);
    if(disBack >= 30){
      while(disFront <= 50 && disBack >= 10){
        disBack = measure(sensorBtrig,sensorBecho);
        disFront = measure(sensorFtrig,sensorFecho);
        goBackward();
      }
      goForward();
      if(disLeft > disRight){
        turnLeft();
      }else{
        turnRight();
      }
      delay(250);
    } 
  }else{
    disRight = measure(sensorRtrig,sensorRecho);
    disLeft = measure(sensorLtrig,sensorLecho);
    if(disLeft <= 20 || disRight <= 20){
      if(disLeft > disRight){
        turnLeft();
      }else{
        turnRight();
      }
    }
    else{
      rest(motorF1,motorF2);
    }
    goForward();
  }
  
}

void rest(int a,int b){
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
}

int measure(int trig,int echo){
  digitalWrite(trig,LOW);
  digitalWrite(trig,HIGH);
  delay(10);
  digitalWrite(trig,LOW);
  long Time = pulseIn(echo,HIGH);
  int dis = Time*0.034/2;
  return dis;
}

void turnRight(){
  digitalWrite(motorF1,LOW);
  digitalWrite(motorF2,HIGH);
}

void turnLeft(){
  digitalWrite(motorF1,HIGH);
  digitalWrite(motorF2,LOW);
}

void goForward(){
  digitalWrite(motorB1,HIGH);
  digitalWrite(motorB2,LOW);
}

void goBackward(){
  digitalWrite(motorB1,LOW);
  digitalWrite(motorB2,HIGH);
}

void Stop(){
  digitalWrite(motorF1,LOW);
  digitalWrite(motorF2,LOW);
  digitalWrite(motorB1,LOW);
  digitalWrite(motorB2,LOW);
}
