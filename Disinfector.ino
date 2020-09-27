#include "SevenSegmentTM1637.h"
const byte PIN_CLK = 9;   // define CLK pin (any digital pin)
const byte PIN_DIO = 8;
#define santctrl 4
int buttonState1 = 0;
int buttonState2 = 0;
int lastButtonState1 = 0;    
int lastButtonState2 = 0;
int buttonPin1 =6;
int buttonPin2=7;
int count = 1;
long count1;
int state;
int ctrl;
int preval;
long previousMillis;
int rst =5;
int r=11;
int g=10;

SevenSegmentTM1637    display(PIN_CLK, PIN_DIO);

const int  IRbuttonPin3 = 2; 
const int  IRpump = 3; 
//int buttonPushCounter3 = 0;   // counter for the number of button presses
int IRbuttonState3 = 0;         // current state of the button
int IRlastButtonState3 = 0;     // previous state of the button
int IRsense;
long IRinterval = 1000;
int IRsanictrl;
unsigned long IRpreviousMillis = 0; 


void setup() {
      display.begin();
  digitalWrite(rst, HIGH);
  Serial.print("oning"); 
  pinMode(LED_BUILTIN, OUTPUT );
  pinMode(A0, OUTPUT);
  pinMode(rst, OUTPUT);
      pinMode(r, OUTPUT );
  digitalWrite(r, HIGH);
        pinMode(g, OUTPUT );
  digitalWrite(g, HIGH);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  // initialize the button pin as a input:
  pinMode(IRbuttonPin3, INPUT);
  pinMode(IRpump,OUTPUT); 
   digitalWrite(g, LOW);
  // initialize the LED as an output:
  // initialize serial communication:
  Serial.begin(9600);
}


void contro() {
  IRbuttonState3 = digitalRead(IRbuttonPin3);
  if (IRbuttonState3 != IRlastButtonState3) {
    if (IRbuttonState3 == HIGH) {
      Serial.println("on");
       digitalWrite(IRpump, LOW);
    } else {
      Serial.println("off");
      IRsanictrl=0;
  }
  IRlastButtonState3 = IRbuttonState3;
}
}

void loop(){
  contro();
    mode();
  select();
  millitmr();
   if(IRsanictrl == 0){
      Serial.println("led on");
      digitalWrite(IRpump, HIGH);
        IRsanictrl++;}
        unsigned long IRcurrentMillis = millis();
        if(IRcurrentMillis - IRpreviousMillis > IRinterval) {
       IRpreviousMillis = IRcurrentMillis;
       digitalWrite(IRpump, LOW); 
    }
 }
void millitmr(){
  if(state == 1){
    if(ctrl == 0){
      Serial.println("led on");
       digitalWrite(LED_BUILTIN, HIGH);
         digitalWrite(r, LOW); 
         previousMillis = millis();
         ctrl++;
    } 
         unsigned long currentMillis = millis();
         if(currentMillis - previousMillis > count1){
         Serial.println("led off");
          digitalWrite(LED_BUILTIN, LOW);
          digitalWrite(g, HIGH); 
          display.print(" ov"); 
         //delay(50);
         state=0;
        
  }
  }
}
void mode() {
  buttonState2 = digitalRead(buttonPin2);
  if (buttonState2 != lastButtonState2) {
    if (buttonState2 == HIGH) {
      //Serial.println("step2off");
    } 
    else {
      Serial.println("step2on");
       count++;
         //Serial.println(count);
         
        }
    delay(50);
  }
  lastButtonState2 = buttonState2;
   if(count == 1){
        count1 = 120000;
           preval=2;}
          if(count == 2){
        count1 = 300000;
           preval=5;}
        if(count == 3){
        count1 = 480000;
           preval=8;}
        if(count == 4){
        count = 1;}
        display.print(preval);
        //display.clear();
        //Serial.println(count); 
}
void select() {
  buttonState1 = digitalRead(buttonPin1);
  if (buttonState1 != lastButtonState1) {
    if (buttonState1 == HIGH) {
     // Serial.println("step1off");
       state++;
      if(state == 2){
        state = 0;
        }
    }
    else {
      Serial.println("step10n");
     
       digitalWrite(rst, LOW);
    }
    delay(50);
  }
  lastButtonState1 = buttonState1;
}
