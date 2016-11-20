#include <IRremote.h>

const int LIGHTS_PIN = 5;
const int DOWN_BNT_PIN = 6;
const int UP_BNT_PIN = 7;
const int RECV_PIN = 11;

int brightness = 0;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  irrecv.enableIRIn();
  pinMode(LIGHTS_PIN, OUTPUT);
  pinMode(DOWN_BNT_PIN, INPUT_PULLUP);
  pinMode(UP_BNT_PIN, INPUT_PULLUP);
  analogWrite(LIGHTS_PIN, brightness);
}

void loop() {

  if (irrecv.decode(&results)) {
    if (results.value == 3772834333) {
      brightness = 255;
    }

    if (results.value == 3772797613) {
      brightness = 0;
    }

    if (results.value == 3772781293 && brightness < 255) {
      brightness += 51;
    }

    if (results.value == 3772818013 && brightness > 0) {
      brightness -= 51;
    }

    irrecv.resume();
  }

  if (digitalRead(UP_BNT_PIN) == 0 && brightness < 255 ) {
    brightness += 51;
  }

  if (digitalRead(DOWN_BNT_PIN) == 0 && brightness > 0 ) {
    brightness -= 51;
  }

  analogWrite(LIGHTS_PIN, brightness);
  delay(125);
}

//3772834333  <-- start
//3772797613  <-- stop
//3772781293  <-- increase
//3772818013  <-- decrease
