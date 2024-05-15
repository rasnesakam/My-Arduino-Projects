#define PIN_BUZZER    7
#define PIN_DS_ECHO   13
#define PIN_DS_TRGR   12
#define DIST_DIVIDER  (29 * 2)

void            ping();
unsigned int    calculateDistance(unsigned long);
void            buzzBuzzer(unsigned int delay);
unsigned int    setupDelayTime(unsigned int distance);

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_DS_ECHO, INPUT);
  pinMode(PIN_DS_TRGR, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  static unsigned int delayInMilis = 0;
  ping();
  unsigned long echoTimeMs = pulseIn(PIN_DS_ECHO, HIGH);
  unsigned int distance = calculateDistance(echoTimeMs);
  delayInMilis = setupDelayTime(distance);
  Serial.print("distance is:");
  Serial.print(distance);
  Serial.println();
  buzzBuzzer(delayInMilis);
  delay(delayInMilis != 0 ? delayInMilis : 100);
}

unsigned int setupDelayTime(unsigned int distance){
  if (distance <= 5)
    return 100;
  if (distance <= 10)
    return 250;
  else if (distance <= 15)
    return 500;
  else if (distance <= 20)
    return 1000;
  else
    return 0;
}

unsigned int calculateDistance(unsigned long echoTimeMs){
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  unsigned long distance = echoTimeMs / DIST_DIVIDER;
  return (unsigned int) distance;
}


void buzzBuzzer(unsigned int delayInMilis){
  if (delayInMilis == 0)
    return;
  digitalWrite(PIN_BUZZER, HIGH);
  delay(delayInMilis);
  digitalWrite(PIN_BUZZER, LOW);
}

void ping(){
  digitalWrite(PIN_DS_TRGR, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_DS_TRGR, LOW);
}