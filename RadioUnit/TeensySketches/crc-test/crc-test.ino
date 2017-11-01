#define UInt16 uint16_t

    static constexpr int POLY = 0x8005;
    static constexpr int BITF = 0x8000;


UInt16 crc(char* buffer,int len)
{
  int count = len;
  int i, j;
  UInt16 tmp, val; // 16 Bit
  UInt16 ptr = 0;

  Serial.print(buffer[ptr], HEX);
  Serial.print(buffer[ptr+1], HEX);
  tmp = static_cast<short>(buffer[ptr] << 8 | (buffer[ptr+1] & 0xFF));
        ptr++;
        ptr++;
  
  if (count > 2)
  {
    for (i = count / 2; i > 0; i--) // only even counts !!! and more than 4
    {
      if (i > 1)
      {
        Serial.print(buffer[ptr], HEX);
        Serial.print(buffer[ptr+1], HEX);
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
  Serial.println();
  return (tmp & 0xFFFF);
}

 

void setup()
{
  Serial.begin(9600);
  while(!Serial);
  delay(1000);
  
char test_data[] = {static_cast<char>(0x53), static_cast<char>(0x00), static_cast<char>(0x05), static_cast<char>(0x01), static_cast<char>(0x0F), static_cast<char>(0xB5), static_cast<char>(0x00), static_cast<char>(0x00), static_cast<char>(0x1E), static_cast<char>(0x08)};
for(int i=0;i<10;i++){
  Serial.print(test_data[i], HEX);
  Serial.print(" ");
}
Serial.println();
// 53 0 5 1 F B5 0 0 1E 8 0 0 80 0 0 should give CRC 2C12
Serial.println();
Serial.print(crc(test_data,10), 16);
Serial.println(" should be 2C12");

char test2[]={211,13,0,44,0,11,223,119,39,14,141,39,0,11,112};
Serial.println();
Serial.print(crc(test2,15), 16);
Serial.println(" should be BE71");
}
void loop()
{

}

