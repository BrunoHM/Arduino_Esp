#include "HID-Project.h"

const int pinLed = LED_BUILTIN;
const int btn1 = 2;
const int btn2 = 3;
const int btn3 = 4;
const int btn4 = 5;
const int btn5 = 6;
const int btn6 = 7;
const int btn7 = 8;
const int btn8 = 9;
const int btn9 = 10;

bool multimidiaMode = false;

char charLastKeyPress;
uint16_t uintLastKeyPress;
unsigned long firstTriggerKey;

void setup() {

  pinMode(pinLed, OUTPUT);
  
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(btn4, INPUT_PULLUP);
  pinMode(btn5, INPUT_PULLUP);
  pinMode(btn6, INPUT_PULLUP);
  pinMode(btn7, INPUT_PULLUP);
  pinMode(btn8, INPUT_PULLUP);
  pinMode(btn9, INPUT_PULLUP);

  Consumer.begin();
}

void pressKey(char charLetterToPress1, uint16_t uint16LetterToPress1, uint16_t uint16LetterToPress2){
  
  if(charLastKeyPress != charLetterToPress1 || uintLastKeyPress != uint16LetterToPress1 || firstTriggerKey+100 <= millis()){
    firstTriggerKey = millis();
    charLastKeyPress = charLetterToPress1;
    uintLastKeyPress = uint16LetterToPress1;

    if(charLetterToPress1 <> "" && uint16LetterToPress1 == 0 && !multimidiaMode){
      Keyboard.write(charLetterToPress1);
    }else if(charLetterToPress1 == "" && uint16LetterToPress1 > 0 && multimidiaMode){
      Consumer.write(MEDIA_PLAY_PAUSE);
    }else if(uint16LetterToPress2 > 0 && multimidiaMode){
      Keyboard.write(uint16LetterToPress2);
    }
    
    Keyboard.releaseAll();
  }
}


void loop() {

  if (!digitalRead(btn1)) {
    pressKey('z', 0, MEDIA_PLAY_PAUSE);
  }

  if (!digitalRead(btn2)) {    
    pressKey("", KEY_LEFT_SHIFT, MEDIA_NEXT);
  }

  if (!digitalRead(btn3)) {
    pressKey('q', 0, MEDIA_PREVIOUS);
  }

  if (!digitalRead(btn4)) {
    pressKey('a', 0, MEDIA_VOLUME_UP);
  }

  if (!digitalRead(btn5)) {
    pressKey('s', 0, MEDIA_VOLUME_DOWN);
  }

  if (!digitalRead(btn6)) {
    pressKey('d', 0, MEDIA_VOLUME_MUTE);
  }

  if (!digitalRead(btn7)) {
    pressKey((char) 32, 0, 0);
  }

  if (!digitalRead(btn8)) {
    pressKey('x', 0, 0);
  }

  if (!digitalRead(btn9)) {
    multimidiaMode = !multimidiaMode;
  }
  
}