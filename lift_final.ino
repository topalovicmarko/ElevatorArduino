int pinA = A0;
int pinB = A1;
int pinC = A2;
int pinD = A3;
int pinE = A4;
int pinF = A5;
int pinG = 2;
const int trigPin = 3;
const int echoPin = 4;
const int tasterPin1 = 5;
const int tasterPin2 = 6;
const int tasterPin3 = 7;
int in1 = 9;
int in2 = 10;
int in3 = 11;
int in4 = 12;
long duration;
int distance;
bool flag = false;

void setup() {
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(tasterPin1, INPUT);
  pinMode(tasterPin2, INPUT);
  pinMode(tasterPin3, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600); // Serial communication
}

void doleON() {
  digitalWrite(9, HIGH);
  digitalWrite(11, HIGH);
}
void doleOFF() {
  digitalWrite(9, LOW);
  digitalWrite(11, LOW);
}

void goreON() {
  digitalWrite(10, HIGH);
  digitalWrite(12, HIGH);
}
void goreOFF() {
  digitalWrite(10, LOW);
  digitalWrite(12, LOW);
}

void prizemlje() {
  // 0
  digitalWrite(pinA , 1);
  digitalWrite(pinB , 1);
  digitalWrite(pinC , 1);
  digitalWrite(pinD , 1);
  digitalWrite(pinE , 1);
  digitalWrite(pinF , 1);
  digitalWrite(pinG , 0);
}

void prvi_sprat() {
  // 1
  digitalWrite(pinA , 0);
  digitalWrite(pinB , 1);
  digitalWrite(pinC , 1);
  digitalWrite(pinD , 0);
  digitalWrite(pinE , 0);
  digitalWrite(pinF , 0);
  digitalWrite(pinG , 0);
}

void drugi_sprat() {
  // 2
  digitalWrite(pinA , 1);
  digitalWrite(pinB , 1);
  digitalWrite(pinC , 0);
  digitalWrite(pinD , 1);
  digitalWrite(pinE , 1);
  digitalWrite(pinF , 0);
  digitalWrite(pinG , 1);
}

void merenje_udaljenosti(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
}

void loop() {

  int tasterStatus1 = 0;
  int tasterStatus2 = 0;
  int tasterStatus3 = 0;

  tasterStatus1 = digitalRead(tasterPin1);
  tasterStatus2 = digitalRead(tasterPin2);
  tasterStatus3 = digitalRead(tasterPin3);

  merenje_udaljenosti();

 //goreON();
 //doleON();

  if (distance >=19) {
    prizemlje();
  }
  else if (distance == 10) {
    prvi_sprat();
  }
  else if (distance ==4) {
    drugi_sprat();
  }

  if(tasterStatus1==HIGH){
    if(distance < 20){
      delay(1000);
      goreOFF();
      flag = true;
      while(flag){
        doleON();
        merenje_udaljenosti();
        if(distance==10){
          prvi_sprat();
        }
        if(distance==20){
          doleOFF();
          prizemlje();
          flag=false;
        }
      }
    }
    else{
      goreOFF();
      doleOFF();
    }
  }

if(tasterStatus2==HIGH){
    if(distance < 10){
      delay(1000);
      goreOFF();
      flag = true;
      while(flag){
        merenje_udaljenosti();
        delay(500);
        doleON();
        if(distance==10){
          doleOFF();
          prvi_sprat();
          flag=false;
        }
      }
    }
    else if(distance>10){
      delay(1000);
      doleOFF();
      flag = true;
      while(flag){
        merenje_udaljenosti();
        delay(500);
        goreON();
        if(distance==10){
          goreOFF();
          prvi_sprat();
          flag=false;
        }
      }
    }
    else{
      goreOFF();
      doleOFF();
    }
  }

  if(tasterStatus3==HIGH){
    if(distance < 4){
      delay(1000);
      goreOFF();
      doleOFF();
    }
    else if(distance>4){
      delay(1000);
      doleOFF();
      flag = true;
      while(flag){
        goreON();
        merenje_udaljenosti();
        if(distance==10){
          prvi_sprat();
        }
        if(distance==4){
          drugi_sprat();
          goreOFF();
          flag=false;
        }
      }
    }
    else{
      goreOFF();
      doleOFF();
    }
  }

}
