#include <IRremote.h>

const int LIGHTS_PIN = 6;
const int POT_PIN = A0;
const int RECV_PIN = 11;

#define MAX_IR_VAL 3772834333
#define MIN_IR_VAL 3772797613
#define DEC_IR_VAL_1 3772781293
#define DEC_IR_VAL_2 3772805773
#define INC_IR_VAL_1 3772818013
#define INC_IR_VAL_2 3772779253

int brightness = 0;
int potVal = 0;
int initialPotVal = 0;

IRrecv irrecv(RECV_PIN);
decode_results results;

void handleIR() {
  if (irrecv.decode(&results)) {

    if (results.value == MAX_IR_VAL) {
      while (brightness < 255) {
        brightness++;
        setBrightness(brightness);
        delay(8);
      }
    }

    if (results.value == MIN_IR_VAL) {
      while (brightness > 0) {
        brightness--;
        setBrightness(brightness);
        delay(8);
      }
    }

    if (results.value == DEC_IR_VAL_1 || results.value == DEC_IR_VAL_2 ) {
      brightness = constrain(brightness + 5, 0, 255);
    }

    if (results.value == INC_IR_VAL_1 || results.value == INC_IR_VAL_2 ) {
      brightness = constrain(brightness - 5, 0, 255);
    }

    irrecv.resume();
  }
}

void handlePot() {
  int currentPotVal = getPotVal();
  // First conditions takes care of potentiometer fluctuations
  // Second condition checks if the pot is touched so it doesnt assing a value if the system is just turned on
  if ((currentPotVal < potVal - 3 || currentPotVal > potVal + 3) && initialPotVal != currentPotVal) {
    brightness = currentPotVal;
    if (brightness < 5) {
      brightness = 0;
    } else if (brightness > 250) {
      brightness = 255;
    }
    potVal = currentPotVal;
    initialPotVal = 12345;
  }
}

int getPotVal() {
  return map(analogRead(POT_PIN), 0, 1023, 0, 255);
}

void setBrightness(int brightnessToSet) {
  analogWrite(LIGHTS_PIN, brightnessToSet);
}

void setup()
{
  irrecv.enableIRIn();
  pinMode(LIGHTS_PIN, OUTPUT);
  pinMode(POT_PIN, INPUT);
  analogWrite(LIGHTS_PIN, brightness);
  initialPotVal = getPotVal();
}

void loop() {
  handleIR();
  handlePot();
  setBrightness(brightness);
}

