 #include "SevenSegmentTM1637.h"
 const byte PIN_CLK = 9;   // define CLK pin (any digital pin)
const byte PIN_DIO = 8;
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#define santctrl 4
int buttonState1 = 0;
int buttonState2 = 0;
int lastButtonState1 = 0;    
int lastButtonState2 = 0;
int buttonPin1 =6;
int buttonPin2=7;
int count = 1;
int count1;
int state;
int ctrl;
int preval;
long previousMillis;

SevenSegmentTM1637    display(PIN_CLK, PIN_DIO);
void setup() {
    display.begin();
  digitalWrite(A0, HIGH);
  Serial.print("oning"); 
  pinMode(LED_BUILTIN, OUTPUT );
  pinMode(A0, OUTPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  Serial.begin(9600);

}
void step1() {
  buttonState1 = digitalRead(buttonPin1);
  if (buttonState1 != lastButtonState1) {
    if (buttonState1 == HIGH) {
     // Serial.println("step1off");
     //state++;
    }
    else {
      Serial.println("step10n");
      state++;
      if(state == 2){
        state = 0;
        }
    }
    delay(50);
  }
  lastButtonState1 = buttonState1;
}
void step2() {
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
        count1 = 2000;
           preval=2;}

     if(count == 2){
        count1 = 5000;
           preval=5;}
        
     if(count == 3){
        count1 = 8000;
           preval=8;}
        
      if(count == 4){
        count = 1;
     
        }
        display.print(preval);
//        display.clear();
        //Serial.println(count); 
}


void millitmr(){
  if(state == 1){
    if(ctrl == 0){
      Serial.println("led on");
         previousMillis = millis();
         ctrl++;
    } 
         digitalWrite(LED_BUILTIN, HIGH); 
         unsigned long currentMillis = millis();
         if(currentMillis - previousMillis > count1){
         Serial.println("led off");
         digitalWrite(LED_BUILTIN, LOW);
         
         delay(50);
         state++;
          Serial.println("reboot");
          display.clear();
          display.print(" ov");
         digitalWrite(A0, LOW);
  }
  }
}
 
void loop(){
  step2();
  step1();
  millitmr();
  }
