#define BUFF_LEN 500
#define RADIO_PIN 3

static uint16_t msg_buff[BUFF_LEN];
int receive_message(void);
void send_radio(int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Init");
    pinMode(RADIO_PIN, OUTPUT);
}

void loop() {
  int msg_len = 0;
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    msg_len = receive_message();
    send_radio(msg_len);
  }
  delay(50);
}

int receive_message(void) {
  int i = 0;
  while (Serial.available()) {
    Serial.readBytes((uint8_t *)&msg_buff[i], 4);
    i++;
  }
  return i;
}


void send_radio(int msg_len) {
  uint8_t level = HIGH;
  for (int i = 0; i < msg_len; i++) {
    digitalWrite(RADIO_PIN, level);
    delayMicroseconds(msg_buff[i]);
    level = !level;
  }
  digitalWrite(RADIO_PIN, LOW);
}
