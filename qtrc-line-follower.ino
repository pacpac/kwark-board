// Line Follower with QTR-1RC from Polulu
// This example is designed for use with eight QTR-1RC sensor
// Use Potentiometer to set Kp in the P-controller

#include <QTRSensors.h>

#define M_SF_PIN  2
#define M_DIS_PIN 3

#define M1_PWM_PIN 9
#define M2_PWM_PIN 10
#define M1_DIR_PIN 12
#define M2_DIR_PIN 13

#define K_POT_PIN  A0

#define NUM_SENSORS   8                      // number of sensors used
#define TIMEOUT       10000                  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   QTR_NO_EMITTER_PIN     // emitter is controlled by digital pin 2

// sensors 0 through 7 are connected to digital pins 3 through 10, respectively
QTRSensorsRC qtrrc((unsigned char[]) {1,2,11,4,5,6,7,8}, NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];


void setup()
{
  pinMode(M_DIS_PIN, OUTPUT);
  pinMode(M1_PWM_PIN, OUTPUT);
  pinMode(M2_PWM_PIN, OUTPUT);
  pinMode(M1_DIR_PIN, OUTPUT);
  pinMode(M2_DIR_PIN, OUTPUT);
  delay(100);
  digitalWrite(M_DIS_PIN, 1);

  delay(500);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 100; i++)  // make the calibration take about 10 seconds
  {
    qtrrc.calibrate();       // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
}


void loop()
{
  float K = map(analogRead(K_POT_PIN),0, 1023, 0.0, 10.0);

  int err = K * (3500 - position);
  
  digitalWrite(M1_DIR_PIN, 1);
  analogWrite(M1_PWM_PIN,  constrain(map(err, -2000, 2000, 255, 0),0 ,255));
  digitalWrite(M2_DIR_PIN, 0);
  analogWrite(M2_PWM_PIN, constrain(map(err, -2000, 2000, 0, 255),0 ,255));

  Serial.print(position);
  Serial.print('\t');
  Serial.print(err);
  Serial.println();
  delay(10);
}
