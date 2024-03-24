
#include <Servo.h>


#define MAX_LIGHT 900

Servo duck_motor1,duck_motor2,duck_motor3,dog;
int pos = 0;
int ran=0;
const int duck_LDR1 = A0;
const int duck_LDR2 = A2;
const int duck_LDR3 = A4;




void up(Servo);
void down(Servo);
void start(int);

void setup() {
Serial.begin(9600);
duck_motor1.attach(3);
duck_motor2.attach(6);
duck_motor3.attach(9);
dog.attach(11);


pinMode(duck_LDR1, INPUT);
pinMode(duck_LDR2, INPUT);
pinMode(duck_LDR3, INPUT);

duck_motor1.write(120);
duck_motor1.write(120);
duck_motor1.write(120);
dog.write(120);

ran=random(1,4);
start(ran);

}

void loop() {

int ldrStatus_1 = analogRead(duck_LDR1);
int ldrStatus_2 = analogRead(duck_LDR2);
int ldrStatus_3 = analogRead(duck_LDR3);



  
      if(ldrStatus_1>MAX_LIGHT){

    Serial.println("ok");
        
        down(duck_motor1);

        up(dog);
        delay(1000);
        down(dog);
        

ran=random(1,4);
start(ran);
        
        }
      
  if(ldrStatus_2>MAX_LIGHT){
       Serial.println("ok");
        down(duck_motor2);

         up(dog);
        delay(1000);
        down(dog);

        

ran=random(1,4);
start(ran);
        }
      
       if(ldrStatus_3>MAX_LIGHT){
        Serial.println("ok");
        down(duck_motor3);
         up(dog);
        delay(1000);
        down(dog);

        

ran=random(1,4);
start(ran);

      
        } 


    
        
  
}



void start(int s){

switch(s){
  case 1:
  up(duck_motor1);
  break;

  case 2:
  up(duck_motor2);
  break;

  case 3:
  up(duck_motor3);
  break;


  
}

  
}




void down(Servo s){

  for (pos = 0; pos <= 120; pos += 1) { 
   
    s.write(pos);              
    delay(15);                       
  }

}


void up(Servo s){

  for (pos = 120; pos >= 0; pos -= 1) { 
    s.write(pos);              
    delay(15);                       

}
}
