// schranke

#define M_SF_PIN  2
#define M_DIS_PIN 3

#define M1_PWM_PIN 9
#define M2_PWM_PIN 10
#define M1_DIR_PIN 12
#define M2_DIR_PIN 13

int pushButton1 = 2;
int pushButton2 = 5;
int photoSensor = 4;
int mDir = 12;
int mPwm = 9;

int state = 0;


void setup() {
  Serial.begin(9600);

  // make the pushbutton's pin an input:
  pinMode(pushButton1, INPUT_PULLUP);
  pinMode(pushButton2, INPUT_PULLUP);
  pinMode(photoSensor, INPUT_PULLUP);

  pinMode(mPwm, OUTPUT); // M1 Speed
  pinMode(mDir, OUTPUT); // M1 Direction
  pinMode(M_DIS_PIN, OUTPUT);
  digitalWrite(M_DIS_PIN, 1);
}

void openBar() {
  digitalWrite(mDir, 0);
  analogWrite(mPwm, 255);    
  while(digitalRead(pushButton1) != 0);
  analogWrite(mPwm, 0);    
}

void closeBar() {
  digitalWrite(mDir, 1);
  analogWrite(mPwm, 255);    
  while(digitalRead(pushButton2)!=0);
  analogWrite(mPwm, 0);      
}

void loop() {
  while(digitalRead(photoSensor) == 0);
  openBar();
  delay(3000);
  closeBar();
}
