#define UInt16 uint16_t

const int POLY = 0x8005;
const int BITF = 0x8000;


UInt16 calculate_crc(char* buffer,int len)
{
  int count = len;
  int i, j;
  UInt16 tmp, val; // 16 Bit
  UInt16 ptr = 0;

  tmp = static_cast<short>(buffer[ptr] << 8 | (buffer[ptr+1] & 0xFF));
        ptr++;
        ptr++;
  
  if (count > 2)
  {
    for (i = count / 2; i > 0; i--) // only even counts !!! and more than 4
    {
      if (i > 1)
      {
        val = static_cast<int>(buffer[ptr] << 8 | (buffer[ptr+1] & 0xFF));
        ptr++;
        ptr++;
      }
      else
      {
        if (count % 2 == 1)
        {
          val = buffer[count - 1] << 8;
        }
        else
        {
          val = 0; // last value with 0   // last 16 bit value
        }
      }
  
      for (j = 0; j < 16; j++)
      {
      if ((tmp & BITF) != 0)
      {
        tmp <<= 1;
  
        if ((val & BITF) != 0)
        {
        tmp++; // rotate carry
        }
        tmp ^= POLY;
      }
      else
      {
        tmp <<= 1;
  
        if ((val & BITF) != 0)
        {
        tmp++; // rotate carry
        }
      }
      val <<= 1;
      }
    }
  }
  return (tmp & 0xFFFF);
}

 

void setup()
{
  Serial.begin(9600);
  Serial2.begin(19200);
  while(!Serial);
    delay(1000);

  char test2[]={211,13,0,44,0,11,223,119,39,14,141,39,0,11,112};
  Serial.println();
  Serial.print(calculate_crc(test2,15), 16);
  Serial.println(" should be BE71");
}

int k=0;
const char ff=255;
const char stx=2;
const char etx=3;

union crc_union{
  uint16_t myVar;
  uint8_t myByte[2];
};

crc_union crc;


void loop()
{
  //FF STX 
  //D3 LEN CN1 CN0 SN3 SN2 SN1 SN0 TD TH TL TSS MEM2 MEM1 MEM0 CRC1 CRC0    
  //ETX
  char punch[]={211,13,0,44,0,11,0,119,0,14,141,39,0,11,112};
  punch[7]=k; //Increment SN0 each punch
  punch[9]=k; //Increment TH each punch
  punch[14]=k*8; //Increment MEM0 by 8 each punch. TODO: increment MEM1 when MEM0 overflows
  crc.myVar=calculate_crc(punch,15);
  Serial.print(255,HEX);
  Serial.print(2,HEX);
  for(int i=0;i<15;i++) Serial.print(punch[i],HEX);
  Serial.print(crc.myByte[0],HEX);
  Serial.print(crc.myByte[1],HEX);
  Serial.println(3,HEX);
  
  Serial2.write(ff);
  Serial2.write(stx);
  Serial2.write(punch,15);
  Serial2.write(crc.myByte,2);
  Serial2.write(etx);
  //TODO: implement support for CTS flow control (Tinymesh will set CTS=High when its receive buffer is full).  
  delay(300);
  if(k>=255)
    k=0;
  k++;
}

