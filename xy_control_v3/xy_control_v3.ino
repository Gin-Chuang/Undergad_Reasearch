  
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


int turnBack = 0;
int   Y_to_end = 0;

int row_num = 5;
int row_length = 300;
int col_num = 10;
int col_length = 100;

int back = 0;

 
AccelStepper stepper1(1,xstepPin,xdirPin);//建立步进电机对象
AccelStepper stepper2(1,ystepPin,ydirPin);//建立步进电机对象

void setup() {
  Serial.begin(9600);
  pinMode(xstepPin,OUTPUT);     
  pinMode(xdirPin,OUTPUT);      
  pinMode(xenablePin,OUTPUT);  
  digitalWrite(xenablePin,LOW);   
 
  stepper1.setMaxSpeed(1400.0);      
  stepper1.setAcceleration(3000.0);  
  stepper2.setMaxSpeed(1400.0);      
  stepper2.setAcceleration(3000.0);  

 // stepper1.moveTo(position_0);

  
}

void Signal(){
  Serial.print(x);
  Serial.print(y);
  Serial.print(t);
  
}

void step1run(int a){
  stepper1.moveTo(row_length*a);
  stepper1.runToPosition();
  delay(100);
}

void step2run(int num){
  stepper2.moveTo(num);
  stepper2.runToPosition();
  delay(1000);
}

void Y_motor(int c){
  stepper2.setCurrentPosition(0);
  Serial.println( stepper2.currentPosition() );

  stepper2.moveTo(300);
  stepper2.runToPosition();
  delay(1000);
  stepper2.moveTo(600);
  stepper2.runToPosition();
  delay(1000);
  stepper2.moveTo(900);
  stepper2.runToPosition();
  delay(1000);
  Serial.println( stepper2.currentPosition() );
  stepper2.moveTo(1200);
  stepper2.runToPosition();
  Serial.println( stepper2.currentPosition() );
  delay(1000);
  stepper2.moveTo(0);
  stepper2.runToPosition();
  Serial.println( stepper2.currentPosition() );
  delay(1000);
//  for( int i = 1; i < row_num + 1; i++){
//    step2run(row_length*i);
//    Serial.println(back);
//    Serial.println( stepper2.currentPosition() );
//  }

}


 
void loop(){
   
  for(int i = 1; i < (5); i++){
    step1run(i);
    Y_motor(i*10);   
  }
  step1run(0);
  delay(1000000);
//  step1run(0);
//  step2run(1500);
//  step2run(0);

//    stepper1.moveTo(300);
//    stepper1.runToPosition();
//    Y_motor(10);

} 
