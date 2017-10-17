/*
  Multple Serial test

 Receives from the main serial port, sends to the others.
 Receives from serial port 1, sends to the main serial (Serial 0).

 */
int led = 13;
int sw_cts = 23;

void setup() {
  // initialize both serial ports:
  Serial.begin(19200);
  Serial2.begin(19200);
  pinMode(sw_cts, INPUT);
  pinMode(led, OUTPUT);     
}

void loop() {
   for (int i=10; i <= 20; i++){
      digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
      Serial.println(i);
      Serial.print(" ");
      do{
        while(digitalRead(sw_cts)==HIGH){delay(10);} //make sure cts is low before we attempt to send packet
        Serial2.print("<<-<<-<<-");
        Serial2.print(i);
        Serial2.print("->>->>->>");
      } while(digitalRead(sw_cts)==HIGH);  //resend whole packet if CTS went high during tranmission
      
      delay(1); //make sure led is on at least a small moment so it can be seen
      digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
//      delay(random(2000));
      delay(50);
   }
   delay(2000);
}
