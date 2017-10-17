
//A normal sportident punch is 20 bytes. Example:
//255, 2, 211, 13, 0, 44, 0, 3, 171, 90, 37, 102, 247, 13, 0, 1, 192, 251, 107, 3
int led = 13;
int sw_cts = 23;

void setup() {
  Serial.begin(9600);
  Serial1.begin(38400);
  Serial1.setTimeout(500); //50 milliseconds
  //38400 baud means 3840 char/sec means 5 ms to send 20 characters
  //4800 baud means 480 char/sec means 42 ms to send 20 characters
  Serial2.begin(19200);
  pinMode(sw_cts, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led,HIGH);
  delay(2000);
  
  Serial.print("Control booted");
  Serial2.print("Control booted");
  digitalWrite(led,LOW);     
}

int maxSize=20; //normal sportident punch autosend packets are 20 bytes (in extended protocol mode)
int len=0;
boolean sent=true;
char inData[20]; // Allocate some space for the string

void loop()
{
  if (Serial1.available() > 0) 
  {
    digitalWrite(led,HIGH);
    len=Serial1.readBytes(inData,maxSize);
    Serial.print("new packet len=");
    Serial.println(len);
    sent=false;
  }else{
    Serial.print("n");
  }
  delay(100);
  if (!sent){  //todo: use a buffer of packets, not only one single packet
    sent=trySend(inData,len);
  }
}

boolean trySend(char data[], int len) {  //return true if packet was sent and CTS did not go high during transmission
  digitalWrite(led,HIGH);
  if(false and digitalRead(sw_cts)==HIGH){//make sure cts is low before we attempt to send packet
    Serial.print("c");
    return(false);
  } else {
    for (int i=0; i<len; i++) {
      Serial.print(data[i],BIN); 
      Serial.print(','); 
      Serial2.print(data[i]); //TODO: put into a buffer and send it with cts support
    }
  }
  digitalWrite(led,LOW);     
  return(digitalRead(sw_cts)==LOW); //Only return success if CTS was low before and after transmission
}

