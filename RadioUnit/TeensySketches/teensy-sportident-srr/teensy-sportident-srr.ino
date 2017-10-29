/* Check for incoming Sportident punch packets on Serial1 from a Sportident SRR-OEM module.
 * Forward the punches on Serial2 to a Tinymesh radio module.
 * The sending waits if the CTS line is HIGH (should be connected to pin 23).
 * 
 */




//A normal sportident punch is 20 bytes. Example:
//255, 2, 211, 13, 0, 44, 0, 3, 171, 90, 37, 102, 247, 13, 0, 1, 192, 251, 107, 3
int led = 13;
int sw_cts = 23;

void setup() {
  Serial.begin(9600);
  Serial1.begin(38400);
  //Serial1.setTimeout(500); //50 milliseconds
  //38400 baud means 3840 char/sec means 5 ms to send 20 characters
  //4800 baud means 480 char/sec means 42 ms to send 20 characters
  Serial2.begin(19200);
  pinMode(sw_cts, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led,HIGH);
  delay(2000);
  
  Serial.println("Serial: Control booted");
  Serial2.println("Serial2: Control booted");
  digitalWrite(led,LOW);     
}

int maxSize=20; //normal sportident punch autosend packets are 20 bytes (in extended protocol mode)
int len=0;
int waitingBytes=0;
boolean sent=true;
char inData[20]; // Allocate some space for the string

void loop()
{
  waitingBytes=Serial1.available();
  Serial.println(waitingBytes);
  while(waitingBytes > 0) 
  {
    digitalWrite(led,digitalRead(sw_cts));     
    len=Serial1.readBytes(inData,maxSize);
    Serial.print("New packet len=");
    Serial.println(len);
    sent=false;
    while(!sent){  //todo: use a buffer of packets, not only one single packet
      sent=trySend(inData,len);
    }
    waitingBytes=Serial1.available();
  }
  Serial.print("z");
  delay(1000);
}

boolean trySend(char data[], int len) {  //return true if packet was sent and CTS did not go high during transmission
  digitalWrite(led,digitalRead(sw_cts));     
  if(digitalRead(sw_cts)==HIGH){
    //CTS is high = we are not allowed to send
    digitalWrite(led,HIGH);
    return(false);
  } else {
    //CTS is low = now we can send a packet
    for (int i=0; i<len; i++) {
      Serial.print(data[i],DEC); 
      Serial.print(','); 
      Serial2.print(data[i]); //TODO: put into a buffer and send it with cts support
    }
    Serial.println(".");
  }
  digitalWrite(led,digitalRead(sw_cts));     
  return(digitalRead(sw_cts)==LOW); //Only return success if CTS was low before and after transmission
}
