#include <Servo.h>
#include <timer.h>

Servo servo_4;

timer t1(100);
timer t2(100);
timer t3(1200);

int bu_pin = 6;
int rd_pin = 5;
int led_val = HIGH;
bool schakelaarHf= false;

void setup()
{
  pinMode(10, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(bu_pin, OUTPUT);
  pinMode(rd_pin, OUTPUT);
  servo_4.attach(4);

  Serial.begin(9600);
}


void loop(){
  if(digitalRead(10) == HIGH) {
    led_active();

    if(schakelaarHf== false){
      t3.start();
      schakelaarHf= true;
    }
    
    Serial.println(t3.status());
    
    if(t3.get() == true){
      servo_4.write(30);
    }
  }

  if (digitalRead(16) == HIGH) {
    schakelaarHf= false;
    led_rest();
    servo_4.write(90);
  }

}

void led_rest(){
  digitalWrite(bu_pin, HIGH);

  //Wait until t1 his time runs out
  if(t1.get() == true){
    led_val = !led_val;
    digitalWrite(rd_pin, !led_val);

    //Change the timer time depending on the led state 
    if(led_val == HIGH){
      t1.set(1500);
    }else{
      t1.set(100);
    }
  }
}

void led_active(){
 if(t2.get() == true){
    led_val = !led_val;
    digitalWrite(bu_pin, !led_val);
    digitalWrite(rd_pin, led_val);
  }
}



