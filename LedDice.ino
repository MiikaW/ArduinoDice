/*
   Led matrix dice
   Made by Miika Wirtanen
*/

/*  Led matrix pins
    11      9
    12  10  8
    6       7
*/

#include <Bounce2.h>
#define BUTTON_PIN 2

int led[7] = {6, 12, 11, 10, 9, 8, 7}; // Leds
int resultAnim[6][7] = {0, 0, 0, 1, 0, 0, 0,
                   0, 0, 1, 0, 0, 0, 1,
                   0, 0, 1, 1, 0, 0, 1,
                   1, 0, 1, 0, 1, 0, 1,
                   1, 0, 1, 1, 1, 0, 1,
                   1, 1, 1, 0, 1, 1, 1
                  }; // Results

int startingAnim[3][7] = {0, 0, 1, 0, 1, 0, 0,
                        0, 1, 0, 1, 0, 1, 0,
                        1, 0, 0, 0, 0, 0, 1
                       }; // Starting animation

int rollingAnim[6][7] = {1, 0, 0, 0, 0, 0, 0,
                      0, 1, 0, 0, 0, 0, 0,
                      0, 0, 1, 0, 0, 0, 0,
                      0, 0, 0, 0, 1, 0, 0,
                      0, 0, 0, 0, 0, 1, 0,
                      0, 0, 0, 0, 0, 0, 1
                     }; // Rolling animation

int randNumber;

Bounce mainBtn = Bounce();

void setup() {
  Serial.begin(9600);
  Serial.println("Dice - Hold button down to start");
  randomSeed(analogRead(0)); // Generates truly random numbers --> pin 0 cannot be connected

  mainBtn.attach(BUTTON_PIN, INPUT_PULLUP);
  mainBtn.interval(25);

  for (int i = 0; i < 7; i++) {
    pinMode(led[i], OUTPUT);
  }
  ledanimate(3, 7, "startingAnim"); // Starting animation

}

void loop() {
  mainBtn.update();

  if ( mainBtn.fell() ) { // Button goes from HIGH --> LOW
    rolldice();
  } else if ( mainBtn.rose() ) { // Button goes from LOW --> HIGH
    Serial.println();
    Serial.print("Shaking");
  } else if (mainBtn.read() ) {
    ledanimate(7, 7, "resultAnim"); // Show result
    Serial.print(".");
    delay(100);
  }
}

// Result
void rolldice() {
  Serial.print("Rolling");
  delay(10);
  for (int i = 0; i < 10; i++) {
    Serial.print(".");
    delay(100);
  }
  randNumber = 0;
  randNumber = random(1, 7);
  Serial.print(randNumber); // Print random number
  ledanimate(6, 7, "rollingAnim"); // Rolling
  for (int i = 0; i < 7; i++) {
    digitalWrite(led[i], resultAnim[randNumber - 1][i]);
  }
}

// Led Animation
void ledanimate(int row, int column, int animation) {
  for (int y = 0; y < row; y++) {
    for (int i = 0; i < column; i++) {
      if (animation == "resultAnim") {
        digitalWrite(led[i], resultAnim[y][i]);
      } else if (animation == "startingAnim") {
        digitalWrite(led[i], startingAnim[y][i]);
      } else if (animation == "rollingAnim") {
        digitalWrite(led[i], rollingAnim[y][i]);
      }
    }
    delay(50);
  }
  for (int i = 0; i < 7; i++) {
    digitalWrite(led[i], 0);
  }
}
