 
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
const int position_0 = moveSteps;
const int position_1 = 2*moveSteps;
const int position_2 = 3*moveSteps;
const int position_3 = 4*moveSteps;
const int position_4 = 5*moveSteps;
int turnBack = 0;

int   Y_to_end = 0;
 
AccelStepper stepper1(1,xstepPin,xdirPin);//建立步进电机对象
AccelStepper stepper2(1,ystepPin,ydirPin);//建立步进电机对象

void setup() {
  Serial.begin(9600);
  pinMode(xstepPin,OUTPUT);     
  pinMode(xdirPin,OUTPUT);      
  pinMode(xenablePin,OUTPUT);  
  digitalWrite(xenablePin,LOW);   
 
  stepper1.setMaxSpeed(300.0);      
  stepper1.setAcceleration(1800.0);  
  stepper2.setMaxSpeed(400.0);      
  stepper2.setAcceleration(1800.0);  

 // stepper1.moveTo(position_0);

  
}


void step1run(){
    while(stepper1.distanceToGo()!= 0){  
      stepper1.run(); 
    }   
}

void step2run(){
    while(stepper2.distanceToGo()!= 0){  
      stepper2.run(); 
      Serial.println(stepper2.targetPosition());
      Serial.println(stepper2.distanceToGo());
      delay(50);
    }   
}

void Y_motor(int num){
  Y_to_end = 0;
  while( Y_to_end == 0 ){
       if ( stepper2.currentPosition() == 0 ){ 
            stepper2.moveTo(position_0);
            step2run();        
            Serial.println(num + 1);
            delay(15000);
      } else if ( stepper2.currentPosition() == position_0  ){   
            stepper2.moveTo(position_1); 
            step2run(); 
            Serial.println(num + 2);
            delay(15000);            
      } else if ( stepper2.currentPosition() == position_1  ){   
            stepper2.moveTo(position_2); 
            step2run(); 
            Serial.println(num + 3);   
            delay(15000);  
      } else if ( stepper2.currentPosition() == position_2  ){    
            stepper2.moveTo(position_3);
            step2run();
            Serial.println(num + 4);
            delay(15000);             
      } else if ( stepper2.currentPosition() == position_3  ){  
            stepper2.moveTo(0);
            step2run();
            Serial.println(num + 5);
            delay(15000); 
            Y_to_end = 1; // Go through once            
      }  
 }
}


 
void loop(){

    if ( stepper1.currentPosition() == 0 ){ 
        Y_motor(10);
        stepper1.moveTo(position_0);
        step1run();
        Serial.println("cam");
        delay(15000);
  } else if ( stepper1.currentPosition() == position_0  ){   
        Y_motor(20);
        stepper1.moveTo(position_1); 
        step1run(); 
        Serial.println("cam");
        delay(15000);            
  } else if ( stepper1.currentPosition() == position_1  ){   
        Y_motor(30);
        stepper1.moveTo(position_2); 
        step1run(); 
        Serial.println("cam");   
        delay(15000);  
  } else if ( stepper1.currentPosition() == position_2  ){    
        Y_motor(40);
        stepper1.moveTo(position_3);
        step1run();         
        Serial.println("cam");
        delay(15000);             
  } else if ( stepper1.currentPosition() == position_3  ){ 
        Y_motor(50);
        stepper1.moveTo(0); 
        step1run();   
        delay(15000);
        Serial.println("cam");         
  }                          
  // 1号电机运行 stepper2.run();   // 1号电机运行

}
