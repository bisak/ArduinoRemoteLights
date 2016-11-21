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
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(LIGHTS_PIN, OUTPUT);
  pinMode(DOWN_BNT_PIN, INPUT_PULLUP);
  pinMode(UP_BNT_PIN, INPUT_PULLUP);
  analogWrite(LIGHTS_PIN, brightness);
}

void loop() {

  if (irrecv.decode(&results)) {
    //Used so serial light blinks when data is received
    Serial.println(results.value);
    irrecv.resume();
    if (results.value == 3772834333) {
      brightness = 255;
    }

    if (results.value == 3772797613) {
      brightness = 0;
    }

    //Added additional values for the same button
    if ((results.value == 3772781293 || results.value == 3772805773) && brightness < 255) {
      brightness += 51;
    }

    //Added additional values for the same button
    if ((results.value == 3772818013 || results.value == 3772779253) && brightness > 0) {
      brightness -= 51;
    }
  }

  if (digitalRead(UP_BNT_PIN) == 0 && brightness < 255 ) {
    if (brightness > 127) {
      brightness += 10;
    } else {
      brightness += 5;
    }
  }

  if (digitalRead(DOWN_BNT_PIN) == 0 && brightness > 0 ) {
    if (brightness > 127) {
      brightness -= 10;
    } else {
      brightness -= 5;
    }
  }

  if (brightness > 255) {
    brightness = 255;
  }
  if (brightness < 0) {
    brightness = 0;
  }
  analogWrite(LIGHTS_PIN, brightness);
  delay(50);
}

//3772834333  <-- start
//3772797613  <-- stop
//3772781293 AND 3772805773 <-- increase
//3772818013 AND 3772779253  <-- decrease
