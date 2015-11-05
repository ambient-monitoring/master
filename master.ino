#include <VirtualWire.h>

const int led_pin = 13;
const int receive_pin = 12;

void setup()
{
  Serial.begin(9600);

  vw_set_rx_pin(receive_pin);
  vw_setup(2000);	 // Bits per sec

  vw_rx_start();       // Start the receiver PLL running
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  // Non-blocking
  if (vw_get_message(buf, &buflen)) {
    digitalWrite(led_pin, HIGH); // Flash a light to show received good message

    char msg[buflen];

    for (int i = 0; i < buflen; i++) {
      msg[i] = buf[i];
    }

    msg[buflen] = '\0';

    Serial.println(msg);
  
    digitalWrite(led_pin, LOW);
  }
}
