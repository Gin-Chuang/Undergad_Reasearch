
#include <AccelStepper.h>  //本示例程序使用AccelStepper库


// A4988连接Arduino引脚号
const int xdirPin = 5;     // 方向控制引脚
const int xstepPin = 2;    // 步进控制引脚
const int xenablePin = 8;  // 使能控制引脚
const int ydirPin = 6;     // 方向控制引脚
const int ystepPin = 3;    // 步进控制引脚
const int yenablePin = 10;  // 使能控制引脚

const int WormboxSize = 4;
const int moveSteps = 300;    //运行步数

String cmd;
int row_num = 5;
int row_length = 2776;
// row len = 3.5cm = 2824
// 1000 = 20cm
// 10000 = 
int col_num = 5;
int col_length = 2776;
//col len = 3.5cm
int gap = 3995;

int back = 0;


AccelStepper stepper1(1, xstepPin, xdirPin); //建立步进电机对象
AccelStepper stepper2(1, ystepPin, ydirPin); //建立步进电机对象

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  pinMode(xstepPin, OUTPUT);
  pinMode(xdirPin, OUTPUT);
  pinMode(xenablePin, OUTPUT);
  digitalWrite(xenablePin, LOW);

  stepper1.setMaxSpeed(3400.0);
  stepper1.setAcceleration(9000.0);
  stepper2.setMaxSpeed(3400.0);
  stepper2.setAcceleration(9000.0);
  // 1400,4000 not too bad
  // stepper1.moveTo(position_0);
  
}


void step1run(int target_position) {
  stepper1.moveTo(target_position);
  stepper1.runToPosition();
  delay(1000);
}

void step2run(int target_position) {
  stepper2.moveTo(target_position);
  stepper2.runToPosition();
  delay(1000);
  //wait and take a photo
}

void Photo(int x , int y , char z) {
  Serial.print(x);
  Serial.print(y);
  Serial.print(z);
  delay(1000);
}

void Y_motor() {
//  跑一個column
  stepper1.setCurrentPosition(0);
  for (int i = 1; i < 5; i++) {
    step1run(i * row_length);
    delay(1000);
  }
  step1run(4 * row_length + 3995);
  delay(1000);
  
  for (int i = 5; i < 9; i++) {
    step1run(i * row_length + 3995);
    delay(1000);
  }

//  Photo(3, row_num , 'p');
  step1run(0);
  delay(1000);
}

void zero(){
     //while pin signal != 0
     //run
     delay(1000);
}


int X_target_position = 0;
int Y_target_position = 0;

void loop() {

  
  if (Serial.available()) {
    Serial.println("serial available");
    cmd = Serial.readString();
    
    if(cmd=="d"){
      Serial.println("left");
      X_target_position += row_length;
      stepper1.moveTo(X_target_position);
    }
    else if(cmd == "a"){
      Serial.println("left");
      X_target_position = 0;
      stepper1.moveTo(0);
    }
    else if(cmd == "s"){
      Serial.println("down");
      Y_target_position += col_length;
      stepper2.moveTo(Y_target_position);
    }
     else if(cmd == "w"){
      Serial.println("up");
      Y_target_position = 0;
      stepper2.moveTo(0);
    }
     else if(cmd == "rightgap"){
      Serial.println("rightgap");
      X_target_position += gap;
      stepper1.moveTo(X_target_position);
    }
     else if(cmd == "downgap"){
      Serial.println("downgap");
      Y_target_position += gap;
      stepper2.moveTo(Y_target_position);
    }
     else if(cmd == "z"){
      Serial.println("zero");
      stepper1.setCurrentPosition(0);
      stepper2.setCurrentPosition(0);
    }
  }
  
//  stepper2.setCurrentPosition(0);
//  for (int i = 1; i < 5; i++) {
//    Y_motor(3);
//    step2run(i * col_length);
//  }
//  Y_motor(3);
//  step2run(4 * col_length + 3995);
//  for (int i = 5; i < 9; i++) {
//    Y_motor(3);
//    step2run(i * col_length + 3995);
//  }
//  Y_motor(3); 
//  Photo(2, row_num , 'p');
//  step2run(0);
//  delay(1000);

}
