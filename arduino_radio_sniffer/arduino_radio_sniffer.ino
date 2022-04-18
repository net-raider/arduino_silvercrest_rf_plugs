#define LISTEN_CMD 'l'
#define RECEIVER_PIN 3

static uint32_t STOP_SYM = 'z';
static uint32_t interrupt_pin = 0;
static uint32_t timing = 0;
static uint32_t last_time = 0;

void listen_rf(void);
void handleInterrupt(void);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  interrupt_pin = digitalPinToInterrupt(RECEIVER_PIN);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() == 0) {}
  char cmd = Serial.read();
  switch (cmd) {
    case LISTEN_CMD:
      listen_rf();
      break;
    default:
      Serial.print("wut?");
      break;
  }
}

void listen_rf(void) {
  attachInterrupt(interrupt_pin, handleInterrupt, CHANGE);
  delay(3000);
  detachInterrupt(interrupt_pin);
  Serial.write((byte *)&STOP_SYM, 4);
}


void handleInterrupt(void) {
  const long time = micros();
  timing = time - last_time;
  Serial.write((byte *)&timing, 4);
  last_time = time;
}
