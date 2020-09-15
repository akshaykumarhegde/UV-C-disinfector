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
long previousMillis;
void setup() {
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
    
        Serial.println(count); 
        }
    //delay(50);
  }
  lastButtonState2 = buttonState2;
   if(count == 1){
        count1 = 30000;}

     if(count == 2){
        count1 = 60000;}
        
     if(count == 3){
        count1 = 90000;}
        
      if(count == 4){
        count = 1;
     
        }
}


void millitmr(){
  if(state == 1){
    if(ctrl == 0){
      Serial.println("led on");
         previousMillis = millis();
         ctrl++;
    } 
         unsigned long currentMillis = millis();
         if(currentMillis - previousMillis > count1){
         Serial.println("led off");
         delay(50);
         state++;
  }
  }
}
 
void loop(){
  step2();
  step1();
  millitmr();
  }
