#include "Arduino.h"

const int ledPin = 13;      // The number of the LED pin
const int ctsPin = 14;		// Clear to send from TM

#define usbSerial Serial	// USB cable to PC (and TM-CCT)
#define tmSerial Serial2	// Serial TX/RX connected to TM

//The setup function is called once at startup of the sketch
void setup() {
	pinMode(ledPin, OUTPUT);
	pinMode(ctsPin, INPUT);

	usbSerial.begin(19200);
	tmSerial.begin(19200);

	usbSerial.println("Waiting for TM-CCT to connect");
}

// The loop function is called in an endless loop
void loop() {
	// If a character is available from the USB and TM is ready to receive, copy the char to TM
	if (usbSerial.available() && digitalRead(ctsPin) == LOW) {
		tmSerial.write(usbSerial.read());
	}

	// If TM has returned a character, copy it to the USB port
	if (tmSerial.available()) {
	    usbSerial.write(tmSerial.read());
	}
}
