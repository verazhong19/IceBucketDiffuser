#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Pin assignments for mister, pump, and buttons
#define mistButtonPin 4
#define neoPixelButtonPin 7
#define misterPin 2
#define pumpPin 3
#define LED_PIN 6

// Number of NeoPixels
#define LED_COUNT 16

// Initialize NeoPixel strip
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Variables for button states and device states
bool lastMisterButtonState = HIGH;
bool lastNeoPixelButtonState = HIGH;
bool misterPumpIsOn = false;
bool neoPixelsIsOn = false;

void setup() {
  pinMode(mistButtonPin, INPUT_PULLUP);
  pinMode(neoPixelButtonPin, INPUT_PULLUP);
  pinMode(misterPin, OUTPUT);
  pinMode(pumpPin, OUTPUT);

  digitalWrite(misterPin, LOW);
  digitalWrite(pumpPin, LOW);

  strip.begin();
  strip.show();
  strip.setBrightness(255);
}

void loop() {
  bool currentMisterButtonState = digitalRead(mistButtonPin);
  bool currentNeoPixelButtonState = digitalRead(neoPixelButtonPin);

  // Check for mister and pump button press
  if (lastMisterButtonState == HIGH && currentMisterButtonState == LOW) {
    misterPumpIsOn = !misterPumpIsOn;
    digitalWrite(misterPin, misterPumpIsOn ? HIGH : LOW);
    digitalWrite(pumpPin, misterPumpIsOn ? HIGH : LOW);
    delay(50);
  }

  // Check for NeoPixel button press
  if (lastNeoPixelButtonState == HIGH && currentNeoPixelButtonState == LOW) {
    neoPixelsIsOn = !neoPixelsIsOn;

    if (neoPixelsIsOn) {
      runLedAnimations();
    } else {
      strip.clear();
      strip.show();
    }

    delay(50);
  }
  // Set last button state for the next loop iteration
  lastMisterButtonState = currentMisterButtonState;
  lastNeoPixelButtonState = currentNeoPixelButtonState;
}

//Run Neopixel Animation
void runLedAnimations() {
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
}

