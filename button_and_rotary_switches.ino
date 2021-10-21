/* 
 *  Keyboard Library documentation: https://github.com/arduino-libraries/Keyboard/blob/master/src/Keyboard.h
 *  HID-Project library documentation: https://github.com/NicoHood/HID/wiki/Consumer-API
*/
#include <HID-Project.h>

// Rotary Encoder Inputs
#define inputCLK A0
#define inputDT A1
#define inputSW A3

//Pin Layout
const int buttonPin = 3;
const int ledPinSW1 = 10;
const int ledPinSW2 = 16;
const int ledPinSW3 = 14;
const int ledPinSW4 = 15;
const int ledPinBT1 = 6;
const int ledPinBT2 = 7;
const int ledPinBT3 = 8;
const int ledPinBT4 = 9;
int buttonState;
int lastButtonState = LOW;
int currentStateCLK;
int previousStateCLK; 
int mode = 1;
int maxModes = 4;
int modeBTN = 1;
int maxBTNModes =2;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() { 
 
  pinMode (inputCLK,INPUT);
  pinMode (inputDT,INPUT);
  pinMode(inputSW, INPUT_PULLUP);
  pinMode(buttonPin, INPUT);
  pinMode(ledPinSW1, OUTPUT);
  pinMode(ledPinSW2, OUTPUT);
  pinMode(ledPinSW2, OUTPUT);
  pinMode(ledPinSW3, OUTPUT);
  pinMode(ledPinSW4, OUTPUT);
  pinMode(ledPinBT1, OUTPUT);
  pinMode(ledPinBT2, OUTPUT);
  pinMode(ledPinBT3, OUTPUT);
  pinMode(ledPinBT4, OUTPUT);
  

  // Setup Serial Monitor
  Serial.begin (9600);
  Consumer.begin();
  Keyboard.begin();

  // Read the initial state of inputCLK
  previousStateCLK = digitalRead(inputCLK);
} 
void changeBTMode() {
    modeBTN = (modeBTN % maxBTNModes) + 1;
}

void changeMode() {
    mode = (mode % maxModes) + 1;
}
void loop() { 
  int reading = digitalRead(buttonPin);

  
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      }
    }

  // Read the current state of inputCLK
  currentStateCLK = digitalRead(inputCLK);

  if (currentStateCLK != previousStateCLK){ 
    // If the inputDT state is different than the inputCLK state then 
    // the encoder is rotating counterclockwise
    if (digitalRead(inputDT) != currentStateCLK) { 
      rotateRight();
    } else {
      rotateLeft();
    }
  } 
  // Update previousStateCLK with the current state
  previousStateCLK = currentStateCLK;
  lastButtonState = reading;

  if (reading != buttonState){
    changeBTMode();
        delay(300);
  }
  if(!digitalRead(inputSW)) {
        changeMode();
            delay(300);
        }
  //Switch led modes
  if(mode==1){
    digitalWrite(ledPinSW1, HIGH);
    }
    else{
      digitalWrite(ledPinSW1, LOW);
      }
  if(mode==2){
    digitalWrite(ledPinSW2, HIGH);
    }
    else{
      digitalWrite(ledPinSW2, LOW);
      }
  if(mode==3){
    digitalWrite(ledPinSW3, HIGH);
    }
    else{
      digitalWrite(ledPinSW3, LOW);
      }
  if(mode==4){
    digitalWrite(ledPinSW4, HIGH);
    }
    else{
      digitalWrite(ledPinSW4, LOW);
      }


// Button led modes
  if(modeBTN==1){
    digitalWrite(ledPinBT1, HIGH);
    }
    else{
      digitalWrite(ledPinBT1, LOW);
      }
  if(modeBTN==2){
    digitalWrite(ledPinBT2, HIGH);
    }
    else{
      digitalWrite(ledPinBT2, LOW);
      }
  if(modeBTN==3){
    digitalWrite(ledPinBT3, HIGH);
    }
    else{
      digitalWrite(ledPinBT3, LOW);
      }
  if(modeBTN==4){
    digitalWrite(ledPinBT4, HIGH);
    }
    else{
      digitalWrite(ledPinBT4, LOW);
      }
}

void rotateRight() {
  switch(modeBTN){
    case 1:{
      switch(mode) {
        case 1:
          // Increase the volume.
          Consumer.write(MEDIA_VOLUME_UP);
          break;
        case 2: 
          //Cltr + TAB
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_TAB);
          Keyboard.releaseAll();
          break;
        case 3:
          // Lightroom, PowerPoint
          Keyboard.press(KEY_UP_ARROW);
          Keyboard.releaseAll();
          break;
        case 4:
          // Photoshop Brush size
          Keyboard.write('[');
          break;

          
      
      }
      break;
      
     case 2:{
      switch(mode) {
        case 1:
          // Increase the volume.
          Consumer.write(MEDIA_VOLUME_DOWN);
          break;
        case 2: 
          //Cltr + TAB
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_TAB);
          Keyboard.releaseAll();
          break;
        case 3:
          // Lightroom, PowerPoint
          Keyboard.press(KEY_RIGHT_ARROW);
          Keyboard.releaseAll();
          break;
        case 4:
          // Photoshop Brush size
          Keyboard.write('R');
          break;

          
      }
      break;
    }
  }
}
}

void rotateLeft() {
  switch(modeBTN){
    case 1:{
      switch(mode) {
        case 1:
          // Decrease the volume.
          Consumer.write(MEDIA_VOLUME_DOWN);
          break;
        case 2: 
          //Cltr + SHIFT + TAB
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press(KEY_TAB);
          Keyboard.releaseAll();
          break;
        case 3:
          // Lightroom, PowerPoint
          Keyboard.press(KEY_DOWN_ARROW);
          Keyboard.releaseAll();
          break;
        case 4:
          // Photoshop Brush size
          Keyboard.write(']');
          break;
  }
  break;

  case 2:{
      switch(mode) {
        case 1:
          // Decrease the volume.
          Consumer.write(MEDIA_VOLUME_UP);
          break;
        case 2: 
          //Cltr + SHIFT + TAB
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press(KEY_LEFT_SHIFT);
          Keyboard.press(KEY_TAB);
          Keyboard.releaseAll();
          break;
        case 3:
          // Lightroom, PowerPoint
          Keyboard.press(KEY_DOWN_ARROW);
          Keyboard.releaseAll();
          break;
        case 4:
          // Photoshop Brush size
          Keyboard.write('L');
          break;
  }
  break;
}
}
  }
}
