// Metronome
// by Kara Ngamsopee

#include <analogWrite.h>

//the numbers of the LED pins
const int RGB = 27;
const int LED = 33;
const int POT = A1;
const int onButton = A3;

bool currentlyOn = false;

int POTval = 0;
int bpm = 500;

long interval = 180000; //3 minutes
long previousMillis = 0;

void setup() {
  Serial.begin(9600);

  pinMode(POT, INPUT);
  pinMode(onButton, INPUT);

  pinMode(RGB, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop() {

  unsigned long currentMillis = millis();

  int buttonState = digitalRead(onButton);

  if ((buttonState == 1) && (currentlyOn == false)) {
    previousMillis = currentMillis;
    currentlyOn = true; //turns on when button is pushed
  }

  if (currentMillis - previousMillis > interval) {
    currentlyOn = false; //turns off after 3 minutes
  }

  if (currentlyOn == true) {
    POTval = analogRead(POT);

    bpm = map(POTval, 0, 4095, 20, 240); //min bpm 20 and max bpm 240
    Serial.print("\t bpm: ");
    Serial.println(bpm);

    analogWrite(RGB, 255);
    delay(6000 / bpm);
    analogWrite(RGB, 0);
    delay(54000 / bpm);

    analogWrite(LED, 255);
    delay(6000 / bpm);
    analogWrite(LED, 0);
    delay(54000 / bpm);

  }


}
