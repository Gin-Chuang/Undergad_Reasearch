tㄟ  
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


int row_num = 5;
int row_length = 100;

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
void Photo(int x , int y ,char z){
  Serial.print(x);
  Serial.print(y);
  Serial.print(z);
  delay(1000);
}

void Y_motor(int c){
  stepper2.setCurrentPosition(0);
  for( int i = 1; i < row_num + 1; i++){
    Photo(c, i, 'p');
    step2run(row_length*i);
  }
  Photo(c, row_num + 1, 'p');
  step2run(0);
}


 
void loop(){
   
  for(int i = 1; i < (5); i++){
    step1run(i);
    Y_motor(i*10);   
  }
  step1run(0);
  delay(1000000);

}
