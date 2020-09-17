 #include "SevenSegmentTM1637.h"
 const byte PIN_CLK = 9;   // define CLK pin (any digital pin)
const byte PIN_DIO = 8;
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#define santctrl 4
long duration;
int distance;
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
int pmptime=1000;
long previousMillis;
long previousMillis1;
int ledState=0;

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
void sanitiser() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; 
 // Serial.print("Distance: ");
  Serial.print(distance);
 // Serial.println(" cm");
  if (distance < 5) {
    millitmr();
}  
}

 void mills1(){
  unsigned long currentMillis1 = millis();
if (currentMillis1 - previousMillis1 >= pmptime) {
    previousMillis1 = currentMillis1;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(santctrl, ledState);
  }
}

void loop(){
  step2();
  step1();
  millitmr();  
//sanitiser();
mills1();
 }
