#include <Keypad.h>

#include <Adafruit_BusIO_Register.h> //OLED DİSPLAY İÇİN GEREKLİ OLAN KÜTÜPHANELERİN EKLENMESİ
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>
#include <SPI.h> 
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

const unsigned char PROGMEM logo128x32 [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF8, 0x00, 0x00, 0x0F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x03, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x07, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x01, 0xF0, 0x00, 0x3F, 0xFE, 0x1F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x21, 0x86,
0xFF, 0xFF, 0x00, 0x0F, 0x00, 0x07, 0xE0, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x00, 0xDA, 0x4B,
0xC0, 0x01, 0x80, 0x3C, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 0xDA, 0x4B,
0xC0, 0x01, 0x80, 0xF0, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0xDA, 0x4B,
0xC0, 0x01, 0x83, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0xDA, 0x4B,
0xC0, 0x01, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0xDE, 0x7B,
0x40, 0x01, 0x8E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xC0, 0x00, 0xC0, 0x03,
0x60, 0x01, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x60, 0x03,
0x30, 0x03, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x38, 0x0E,
0x1C, 0x1C, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x06, 0x60,
0x02, 0x30, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x06, 0x60,
0x02, 0x20, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x06, 0x60,
0x02, 0x20, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x06, 0x60,
0x02, 0x20, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x06, 0x60,
0x06, 0x20, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x00, 0x04, 0x20,
0x06, 0x30, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x04, 0x20,
0x06, 0x30, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x0C, 0x30,
0x04, 0x10, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x0C, 0x30,
0x04, 0x10, 0x01, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xE0, 0x00, 0x00, 0x08, 0x10,
0x0C, 0x18, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x08, 0x10,
0x0C, 0x18, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x00, 0x30, 0x00, 0x0C, 0x30,
0x06, 0x38, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0xFC, 0x00, 0x01, 0xE0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x07, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xF0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};





#define GET_LOW_BYTE(A) (uint8_t)((A)) //Serial bus servo komutları koda eklendi.
#define GET_HIGH_BYTE(A) (uint8_t)((A) >> 8)
#define BYTE_TO_HW(A, B) ((((uint16_t)(A)) << 8) | (uint8_t)(B))

#define LOBOT_SERVO_FRAME_HEADER         0x55
#define LOBOT_SERVO_MOVE_TIME_WRITE      1
#define LOBOT_SERVO_MOVE_TIME_READ       2
#define LOBOT_SERVO_MOVE_TIME_WAIT_WRITE 7
#define LOBOT_SERVO_MOVE_TIME_WAIT_READ  8
#define LOBOT_SERVO_MOVE_START           11
#define LOBOT_SERVO_MOVE_STOP            12
#define LOBOT_SERVO_ID_WRITE             13
#define LOBOT_SERVO_ID_READ              14
#define LOBOT_SERVO_ANGLE_OFFSET_ADJUST  17
#define LOBOT_SERVO_ANGLE_OFFSET_WRITE   18
#define LOBOT_SERVO_ANGLE_OFFSET_READ    19
#define LOBOT_SERVO_ANGLE_LIMIT_WRITE    20
#define LOBOT_SERVO_ANGLE_LIMIT_READ     21
#define LOBOT_SERVO_VIN_LIMIT_WRITE      22
#define LOBOT_SERVO_VIN_LIMIT_READ       23
#define LOBOT_SERVO_TEMP_MAX_LIMIT_WRITE 24
#define LOBOT_SERVO_TEMP_MAX_LIMIT_READ  25
#define LOBOT_SERVO_TEMP_READ            26
#define LOBOT_SERVO_VIN_READ             27
#define LOBOT_SERVO_POS_READ             28
#define LOBOT_SERVO_OR_MOTOR_MODE_WRITE  29
#define LOBOT_SERVO_OR_MOTOR_MODE_READ   30
#define LOBOT_SERVO_LOAD_OR_UNLOAD_WRITE 31
#define LOBOT_SERVO_LOAD_OR_UNLOAD_READ  32
#define LOBOT_SERVO_LED_CTRL_WRITE       33
#define LOBOT_SERVO_LED_CTRL_READ        34
#define LOBOT_SERVO_LED_ERROR_WRITE      35
#define LOBOT_SERVO_LED_ERROR_READ       36

#define LOBOT_DEBUG 1  

byte LobotCheckSum(byte buf[])
{
  byte i;
  uint16_t temp = 0;
  for (i = 2; i < buf[3] + 2; i++) {
    temp += buf[i];
  }
  temp = ~temp;
  i = (byte)temp;
  return i;
}

void LobotSerialServoMove(HardwareSerial &SerialX, uint8_t id, int16_t position, uint16_t time)
{
  byte buf[10];
  if(position < 0)
      position = 0;
  if(position > 1000)
      position = 1000;
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 7;
  buf[4] = LOBOT_SERVO_MOVE_TIME_WRITE;
  buf[5] = GET_LOW_BYTE(position);
  buf[6] = GET_HIGH_BYTE(position);
  buf[7] = GET_LOW_BYTE(time);
  buf[8] = GET_HIGH_BYTE(time);
  buf[9] = LobotCheckSum(buf);
  SerialX.write(buf, 10);
}

void LobotSerialServoStopMove(HardwareSerial &SerialX, uint8_t id)
{
  byte buf[6];
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 3;
  buf[4] = LOBOT_SERVO_MOVE_STOP;
  buf[5] = LobotCheckSum(buf);
  SerialX.write(buf, 6);
}

void LobotSerialServoSetID(HardwareSerial &SerialX, uint8_t oldID, uint8_t newID)
{
  byte buf[7];
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = oldID;
  buf[3] = 4;
  buf[4] = LOBOT_SERVO_ID_WRITE;
  buf[5] = newID;
  buf[6] = LobotCheckSum(buf);
  SerialX.write(buf, 7);
  
#ifdef LOBOT_DEBUG
  Serial.println("LOBOT SERVO ID WRITE");
  int debug_value_i = 0;
  for (debug_value_i = 0; debug_value_i < buf[3] + 3; debug_value_i++)
  {
    Serial.print(buf[debug_value_i], HEX);
    Serial.print(":");
  }
    Serial.println(" ");
#endif

}

void LobotSerialServoSetMode(HardwareSerial &SerialX, uint8_t id, uint8_t Mode, int16_t Speed)
{
  byte buf[10];

  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 7;
  buf[4] = LOBOT_SERVO_OR_MOTOR_MODE_WRITE;
  buf[5] = Mode;
  buf[6] = 0;
  buf[7] = GET_LOW_BYTE((uint16_t)Speed);
  buf[8] = GET_HIGH_BYTE((uint16_t)Speed);
  buf[9] = LobotCheckSum(buf);

#ifdef LOBOT_DEBUG
  Serial.println("LOBOT SERVO Set Mode");
  int debug_value_i = 0;
  for (debug_value_i = 0; debug_value_i < buf[3] + 3; debug_value_i++)
  {
    Serial.print(buf[debug_value_i], HEX);
    Serial.print(":");
  }
  Serial.println(" ");
#endif

  SerialX.write(buf, 10);
}
void LobotSerialServoLoad(HardwareSerial &SerialX, uint8_t id)
{
  byte buf[7];
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 4;
  buf[4] = LOBOT_SERVO_LOAD_OR_UNLOAD_WRITE;
  buf[5] = 1;
  buf[6] = LobotCheckSum(buf);
  
  SerialX.write(buf, 7);
  
#ifdef LOBOT_DEBUG
  Serial.println("LOBOT SERVO LOAD WRITE");
  int debug_value_i = 0;
  for (debug_value_i = 0; debug_value_i < buf[3] + 3; debug_value_i++)
  {
    Serial.print(buf[debug_value_i], HEX);
    Serial.print(":");
  }
  Serial.println(" ");
#endif

}

void LobotSerialServoUnload(HardwareSerial &SerialX, uint8_t id)
{
  byte buf[7];
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 4;
  buf[4] = LOBOT_SERVO_LOAD_OR_UNLOAD_WRITE;
  buf[5] = 0;
  buf[6] = LobotCheckSum(buf);
  
  SerialX.write(buf, 7);
  
#ifdef LOBOT_DEBUG
  Serial.println("LOBOT SERVO LOAD WRITE");
  int debug_value_i = 0;
  for (debug_value_i = 0; debug_value_i < buf[3] + 3; debug_value_i++)
  {
    Serial.print(buf[debug_value_i], HEX);
    Serial.print(":");
  }
  Serial.println(" ");
#endif
}


int LobotSerialServoReceiveHandle(HardwareSerial &SerialX, byte *ret)
{
  bool frameStarted = false;
  bool receiveFinished = false;
  byte frameCount = 0;
  byte dataCount = 0;
  byte dataLength = 2;
  byte rxBuf;
  byte recvBuf[32];
  byte i;

  while (SerialX.available()) {
    rxBuf = SerialX.read();
    delayMicroseconds(100);
    if (!frameStarted) {
      if (rxBuf == LOBOT_SERVO_FRAME_HEADER) {
        frameCount++;
        if (frameCount == 2) {
          frameCount = 0;
          frameStarted = true;
          dataCount = 1;
        }
      }
      else {
        frameStarted = false;
        dataCount = 0;
        frameCount = 0;
      }
    }
    if (frameStarted) {
      recvBuf[dataCount] = (uint8_t)rxBuf;
      if (dataCount == 3) {
        dataLength = recvBuf[dataCount];
        if (dataLength < 3 || dataCount > 7) {
          dataLength = 2;
          frameStarted = false;
        }
      }
      dataCount++;
      if (dataCount == dataLength + 3) {
        
#ifdef LOBOT_DEBUG
        //Serial.print("RECEIVE DATA:");
        for (i = 0; i < dataCount; i++) {
          //Serial.print(recvBuf[i], HEX);
          //Serial.print(":");
        }
        //Serial.println(" ");
#endif

        if (LobotCheckSum(recvBuf) == recvBuf[dataCount - 1]) {
          
#ifdef LOBOT_DEBUG
          //Serial.println("Check SUM OK!!");
          //Serial.println("");
#endif

          frameStarted = false;
          memcpy(ret, recvBuf + 4, dataLength);
          return 1;
        }
        return -1;
      }
    }
  }
}


int LobotSerialServoReadPosition(HardwareSerial &SerialX, uint8_t id)
{
  int count = 10000;
  int ret;
  byte buf[6];

  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 3;
  buf[4] = LOBOT_SERVO_POS_READ;
  buf[5] = LobotCheckSum(buf);

#ifdef LOBOT_DEBUG
  Serial.println("LOBOT SERVO Pos READ");
  int debug_value_i = 0;
  for (debug_value_i = 0; debug_value_i < buf[3] + 3; debug_value_i++)
  {
   Serial.print(buf[debug_value_i], HEX);
   Serial.print(":"); 
  }
  Serial.println(" ");
#endif

  while (SerialX.available())
    SerialX.read();

  SerialX.write(buf, 6);

  while (!SerialX.available()) {
    count -= 1;
    if (count < 0)
      return -1;
  }

  if (LobotSerialServoReceiveHandle(SerialX, buf) > 0)
    ret = BYTE_TO_HW(buf[2], buf[1]);
  else
    ret = -1;

#ifdef LOBOT_DEBUG
  //Serial.println(ret);
#endif
  return ret;
}
int LobotSerialServoReadVin(HardwareSerial &SerialX, uint8_t id)
{
  int count = 10000;
  int ret;
  byte buf[6];

  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 3;
  buf[4] = LOBOT_SERVO_VIN_READ;
  buf[5] = LobotCheckSum(buf);

#ifdef LOBOT_DEBUG
  Serial.println("LOBOT SERVO VIN READ");
  int debug_value_i = 0;
  for (debug_value_i = 0; debug_value_i < buf[3] + 3; debug_value_i++)
  {
    Serial.print(buf[debug_value_i], HEX);
    Serial.print(":");
  }
  Serial.println(" ");
#endif

  while (SerialX.available())
    SerialX.read();

  SerialX.write(buf, 6);

  while (!SerialX.available()) {
    count -= 1;
    if (count < 0)
      return -2048;
  }

  if (LobotSerialServoReceiveHandle(SerialX, buf) > 0)
    ret = (int16_t)BYTE_TO_HW(buf[2], buf[1]);
  else
    ret = -2048;

#ifdef LOBOT_DEBUG
  Serial.println(ret);
#endif
  return ret;
}

const byte satir = 4; //Keypad satır ve sütün tanımı yapıldı.
const byte sutun = 4;
char tus_takimi[satir][sutun]= {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
  };
  byte satir_pinleri[satir] = {13,12,11,10}; //Satır ve sütün dizileri oluşturuldu.
  byte sutun_pinleri[sutun] = {9,8,7,6};

Keypad tus_takimi1 = Keypad(makeKeymap(tus_takimi),satir_pinleri, sutun_pinleri, satir, sutun);


#define ID1 1 //Servo motorların tanımlaması yapıldı.
#define ID2 2
#define ID3 3
#define ID4 4
#define ID5 5
#define ID6 6
  

void setup() {
  display.clearDisplay();
  display.display();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Wire.begin();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(15,10);
  display.clearDisplay();
  display.println("MERHABA!");
  display.display();
  Serial.begin(115200);
  delay(5000);
  
  static int konum1,konum2,konum3,konum4,konum5,konum6; //Okuyacağımız konum bilgilerini saklanacağı değişkenler atandı.
  static int sure1=0,sure2=0,sure3=0,sure4=0,sure5=0,sure6=0; //Motorların hareketlerini tamamlaması için gerekli süreyi tutmak adına gerekli değişkenler oluşturuldu.
  static int konum[6]={konum1,konum2,konum3,konum4,konum5,konum6} ;
  static int sure[6]={sure1,sure2,sure3,sure4,sure5,sure6};
}

int x=0; //Oled displayin x ve y tanımlaması yapıldı.
int y=0;

void loop() {
  display.clearDisplay();
  display.drawBitmap(x, y, logo128x32, 128, 32, 1);
  display.display();
  static int konum1,konum2,konum3,konum4,konum5,konum6;
  static int sure1,sure2,sure3,sure4,sure5,sure6;
  static int sure11,sure22,sure33,sure44,sure55,sure66;
  static int konum[6]={konum1,konum2,konum3,konum4,konum5,konum6} ;
  static int sure[6]={sure1,sure2,sure3,sure4,sure5,sure6};
  static int newsure[6]={sure11,sure22,sure33,sure44,sure55,sure66};
  char tus =tus_takimi1.getKey();
 
 if(tus){
   if(tus=='A'){
    LobotSerialServoMove(Serial,ID2,390,2600);//Cihazdan okunan konumlara göre uygun poziyson atandı ve 'A' tuşuna başlangıç konumuna hazır hale getirme görevi atandı
    LobotSerialServoLoad(Serial,ID3);
    delay(500);
    LobotSerialServoMove(Serial,ID3,473,2000);
    delay(3000);
    LobotSerialServoMove(Serial,ID1,652,1600);
    LobotSerialServoMove(Serial,ID4,95,580);
    LobotSerialServoMove(Serial,ID5,561,1000);
    LobotSerialServoMove(Serial,ID6,320,500);
    }
  
  if(tus=='B'){
   LobotSerialServoUnload(Serial,ID1);//Unload komutu motorlardaki torku boşa düşürerek öğrenme moduna hazır hale getirildi.
   LobotSerialServoUnload(Serial,ID2);
   LobotSerialServoUnload(Serial,ID3);
   LobotSerialServoUnload(Serial,ID4);
   LobotSerialServoUnload(Serial,ID5);
   LobotSerialServoUnload(Serial,ID6);
   display.setTextSize(1);
   display.setTextColor(WHITE);
   display.setCursor(0,0);
   display.clearDisplay();
   display.println("Kasigi kendinize\ngore ayarlayiniz.\nArdindan 'C' tusuna\nbasiniz.");
   display.display();
   delay(10000);
  }

if(tus=='C'){
    konum[0]=LobotSerialServoReadPosition(Serial,ID1);//Motorların öğrenme modu yapabilmesi için pozisyon bilgisi okuma gerçekleştirildi.
    konum[1]=LobotSerialServoReadPosition(Serial,ID2);
    konum[2]=LobotSerialServoReadPosition(Serial,ID3);
    konum[3]=LobotSerialServoReadPosition(Serial,ID4);
    konum[4]=LobotSerialServoReadPosition(Serial,ID5);
    konum[5]=LobotSerialServoReadPosition(Serial,ID6);
    }


    
  if(tus=='1'){
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.clearDisplay();
    display.println("1. tabagin servisi\nyapiliyor...");
    display.display();
    //ID1
      if(konum[0]>=652){            //Bilinen konumdan okunan konum arasındaki farkı alıp ve bunu belirli bir katsayı ile çarparak süre ataması yaptık.Bu geliştirilen hesaplama bize öğrenme modunda her hareketin stabilize olmasını sağladı.
        sure[0]= (652-konum[0])*-10;
        LobotSerialServoMove(Serial,ID1,652,sure[0]);
      }else{
        sure[0] = (652-konum[0])*10;
        LobotSerialServoMove(Serial,ID1,652,sure[0]);
        }
    
  //ID2   
    if(konum[1]>=392){  //if döngüsü içindeki yazı bizim daha önceki okuduğumuz koordinatlardaki bilgilerdir.Bu bilgiler eşliğinde hareket sağlanmaktadır.
        sure[1]=(392-konum[1])*-17;
        LobotSerialServoMove(Serial,ID2,392,sure[1]);
      }else{
          sure[1]=(392-konum[1])*17;
          LobotSerialServoMove(Serial,ID2,392,sure[1]);
        }
     
  //ID3 
    if(konum[2]>=505){
        sure[2]=(505-konum[2])*-10;
        LobotSerialServoMove(Serial,ID3,505,sure[2]);
      }else{
          sure[2]=(505-konum[2])*10;
          LobotSerialServoMove(Serial,ID3,505,sure[2]);
        }
    
  //ID4
    if(konum[3]>=50){
        sure[3]=(50-konum[3])*-10;
        LobotSerialServoMove(Serial,ID4,50,sure[3]);
      }else{
          sure[3]=(50-konum[3])*10;
          LobotSerialServoMove(Serial,ID4,50,sure[3]);
        }
     
  //ID5
    if(konum[4]>=561){
        sure[4]=(561-konum[4])*-10;
        LobotSerialServoMove(Serial,ID5,561,sure[4]);
      }else{
          sure[4]=(561-konum[4])*10;
          LobotSerialServoMove(Serial,ID5,561,sure[4]);
        }
    //ID6
    if(konum[5]>=320){
        sure[5]=(320-konum[5])*10;
        LobotSerialServoMove(Serial,ID6,320,sure[5]);
    }else{
          sure[5]=(320-konum[5])*10;
          LobotSerialServoMove(Serial,ID6,320,sure[5]);
      }
  delay(5000);
  //Tabak hizalama
  LobotSerialServoMove(Serial,ID1,625,200);//Tabak hizalama harketi bizim robot kolu tabaktan yemek almak için uygun konuma getirip okudğumuz konum eşliğinde gerçekleştirilmiştir.
  delay(200);
  LobotSerialServoMove(Serial,ID5,586,200);
  LobotSerialServoMove(Serial,ID6,634,1500);
  delay(1500);
  LobotSerialServoMove(Serial,ID2,373,400);
  LobotSerialServoMove(Serial,ID3,270,1500);
  LobotSerialServoMove(Serial,ID4,260,1300);

  
 delay(4000);

 //Kaşığı doldurma başlangıç
  LobotSerialServoMove(Serial,ID3,203,800);//Bu pozisyonda kaşık tabağın içindeki ilk hareketini yapar.
  LobotSerialServoMove(Serial,ID4,378,1000);
  LobotSerialServoMove(Serial,ID6,445,1000);
  LobotSerialServoMove(Serial,ID2,413,200);
  LobotSerialServoMove(Serial,ID1,629,200);
  LobotSerialServoMove(Serial,ID5,586,300);
  delay(2000);
  //Kaşığı tamamen doldurma 
  LobotSerialServoMove(Serial,ID6,300,1000);//Kaşığı doldurmak için yeterli olan hareketi yapan motorlar için uygun konum bilgileri ve süreleri belirlenmiştir.
  LobotSerialServoMove(Serial,ID5,542,400);
  LobotSerialServoMove(Serial,ID1,667,400);
  delay(2000);
  //Kaşığı sıyırma
  LobotSerialServoMove(Serial,ID1,710,800);//Kaşık doldurulduktan sonra tabağın içindeki sıyırma bölümünde kaşık üstündeki fazla yemeği alır ve servis ısrasındaki dökülme aza indirilir. 
  delay(1500);
  LobotSerialServoMove(Serial,ID3,395,2000);
  LobotSerialServoMove(Serial,ID4,200,2000);
  delay(5000);

  
  
    //ID1
      if(konum[0]>=710){                  //Tabaktan yemek alındıktan sonra kullanıcının belirlediği konuma gitmek için tekrardan konum farkından yararlanarak süre hesaplaması yapıldı.Bu sayede bütün motorlar stabilize şekilde hareketi tamamladı.
        newsure[0]= (710-konum[0])*-10;   //Robot kolun kaşığı dökmeden taşıyabilmesi için bazı düzenlemeler yapıldı bunlar araya gecikme ekleme ve bütün motorlara çalışma sırası verildi ilkden sona doğru değil karışık sıralamayla en uygun düzen belirlendi.
        LobotSerialServoMove(Serial,ID1,konum[0],newsure[0]);
      }else{
          newsure[0] = (710-konum[0])*10;
          LobotSerialServoMove(Serial,ID1,konum[0],newsure[0]);
        }

           //ID5
    if(konum[4]>=574){
        newsure[4]=(574-konum[4])*-10;
        LobotSerialServoMove(Serial,ID5,konum[4],newsure[4]);
      }else{
          newsure[4]=(574-konum[4])*10;
          LobotSerialServoMove(Serial,ID5,konum[4],newsure[4]);
        }
       
  delay(2000);
  //ID2   
    if(konum[1]>=423){
        newsure[1]=(423-konum[1])*-20;
        LobotSerialServoMove(Serial,ID2,konum[1]-10,newsure[1]);
      }else{
          newsure[1]=(423-konum[1])*20;
          LobotSerialServoMove(Serial,ID2,konum[1]-10,newsure[1]);
        }
        //ID6
    if(konum[5]>=300){
        newsure[5]=(300-konum[5])*5;
        LobotSerialServoMove(Serial,ID6,konum[5],200);
    }else{
          newsure[5]=(300-konum[5])*5;
          LobotSerialServoMove(Serial,ID6,konum[5],200);
      }
    //ID3 
    if(konum[2]>=395){
        newsure[2]=(395-konum[2])*-4;
        LobotSerialServoMove(Serial,ID3,konum[2],newsure[2]);
      }else{
          newsure[2]=(395-konum[2])*4;
          LobotSerialServoMove(Serial,ID3,konum[2],newsure[2]);
        }
  //ID4
    if(konum[3]>=200){
        newsure[3]=(200-konum[3])*-10;
        LobotSerialServoMove(Serial,ID4,konum[3],newsure[3]);
      }else{
          newsure[3]=(200-konum[3])*10;
          LobotSerialServoMove(Serial,ID4,konum[3],newsure[3]);
        }
      
  } 
  
    
 if(tus=='2'){  //tus1 için yapılan bütün teknikler tus2 içinde yapıldı tek fark 2.tabağın konumundan kaynaklandı mantık ve algoritma  olarak aynı çalışıyorlar.
    display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.clearDisplay();
  display.println("2. tabagin servisi\nyapiliyor...");
  display.display();
      //2.Tabak başlangıç konumu ID 1-6 arası.
      //ID1
      if(konum[0]>=407){
        sure[0]= (407-konum[0])*-10;
        LobotSerialServoMove(Serial,ID1,407,sure[0]);
      }else{
          sure[0] = (407-konum[0])*10;
          LobotSerialServoMove(Serial,ID1,407,sure[0]);
        }
    
  //ID2   
    if(konum[1]>=395){
        sure[1]=(395-konum[1])*-17;
        LobotSerialServoMove(Serial,ID2,395,sure[1]);
      }else{
          sure[1]=(395-konum[1])*17;
          LobotSerialServoMove(Serial,ID2,395,sure[1]);
        }
     
  //ID3 
    if(konum[2]>=485){
        sure[2]=(485-konum[2])*-10;
        LobotSerialServoMove(Serial,ID3,485,sure[2]);
      }else{
          sure[2]=(485-konum[2])*10;
          LobotSerialServoMove(Serial,ID3,485,sure[2]);
        }
    
  //ID4
    if(konum[3]>=120){
        sure[3]=(120-konum[3])*-10;
        LobotSerialServoMove(Serial,ID4,120,sure[3]);
      }else{
          sure[3]=(120-konum[3])*10;
          LobotSerialServoMove(Serial,ID4,120,sure[3]);
        }
     
  //ID5
    if(konum[4]>=770){
        sure[4]=(770-konum[4])*-10;
        LobotSerialServoMove(Serial,ID5,770,sure[4]);
      }else{
          sure[4]=(770-konum[4])*10;
          LobotSerialServoMove(Serial,ID5,770,sure[4]);
        }
    //ID6
    if(konum[5]>=320){
        sure[5]=(320-konum[5])*10;
        LobotSerialServoMove(Serial,ID6,320,sure[5]);
    }else{
          sure[5]=(320-konum[5])*10;
          LobotSerialServoMove(Serial,ID6,320,sure[5]);
      }
  delay(3000);
  //Tabak hizalama
  LobotSerialServoMove(Serial,ID1,400,100);
  delay(200);
  LobotSerialServoMove(Serial,ID5,805,400);
  LobotSerialServoMove(Serial,ID6,600,1500);
  delay(1500);
  LobotSerialServoMove(Serial,ID2,420,1000);
  LobotSerialServoMove(Serial,ID3,360,1500);
  LobotSerialServoMove(Serial,ID4,238,1300);
  delay(4000);
 
 
 //Kaşığı doldurma başlangıç
  LobotSerialServoMove(Serial,ID3,272,1000);
  LobotSerialServoMove(Serial,ID4,344,1000);
  LobotSerialServoMove(Serial,ID6,408,1000);
  LobotSerialServoMove(Serial,ID2,450,300);
  delay(2000);

  //Kaşığı tamamen doldurma 
  LobotSerialServoMove(Serial,ID6,293,700);
  LobotSerialServoMove(Serial,ID5,765,400);
  LobotSerialServoMove(Serial,ID4,393,400);
  LobotSerialServoMove(Serial,ID3,257,300);
  LobotSerialServoMove(Serial,ID1,418,150);

  delay(3000);
  LobotSerialServoMove(Serial,ID1,490,500);
  LobotSerialServoMove(Serial,ID5,693,800);
  delay(1500);
  LobotSerialServoMove(Serial,ID3,463,2000);
  LobotSerialServoMove(Serial,ID4,176,2000);
  delay(5000);

  //ID1
   if(konum[0]>=488){
      newsure[0]= (488-konum[0])*-5;
      LobotSerialServoMove(Serial,ID1,konum[0],newsure[0]);
   }else{
        newsure[0] = (488-konum[0])*5;
        LobotSerialServoMove(Serial,ID1,konum[0],newsure[0]);
        }

    //ID5
    if(konum[4]>=694){
        newsure[4]=(694-konum[4])*-10;
        LobotSerialServoMove(Serial,ID5,konum[4],newsure[4]);
      }else{
          newsure[4]=(694-konum[4])*10;
          LobotSerialServoMove(Serial,ID5,konum[4],newsure[4]);
        }
  delay(2000);
  //ID2   
    if(konum[1]>=450){
        newsure[1]=(450-konum[1])*-20;
        LobotSerialServoMove(Serial,ID2,konum[1]-10,newsure[1]);
      }else{
          newsure[1]=(450-konum[1])*15;
          LobotSerialServoMove(Serial,ID2,konum[1]-10,newsure[1]);
        }
        //ID6
    if(konum[5]>=293){
        newsure[5]=(293-konum[5])*5;
        LobotSerialServoMove(Serial,ID6,konum[5],200);
    }else{
          newsure[5]=(293-konum[5])*5;
          LobotSerialServoMove(Serial,ID6,konum[5],200);
      }
  //ID3 
    if(konum[2]>=448){
        newsure[2]=(448-konum[2])*-6;
        LobotSerialServoMove(Serial,ID3,konum[2],newsure[2]);
      }else{
          newsure[2]=(448-konum[2])*6;
          LobotSerialServoMove(Serial,ID3,konum[2],newsure[2]);
        }
    
  //ID4
    if(konum[3]>=176){
        newsure[3]=(176-konum[3])*-10;
        LobotSerialServoMove(Serial,ID4,konum[3],newsure[3]);
      }else{
          newsure[3]=(176-konum[3])*10;
          LobotSerialServoMove(Serial,ID4,konum[3],newsure[3]);
        }
      
      }
            
       if(tus=='*'){ //Load modu servo motora tork verme durumudur '*' tuşuna basıldığında bütün motorlar kitli hale getirilir.
        LobotSerialServoLoad(Serial,ID1);
        LobotSerialServoLoad(Serial,ID2);
        LobotSerialServoLoad(Serial,ID3);
        LobotSerialServoLoad(Serial,ID4);
        LobotSerialServoLoad(Serial,ID5);
        LobotSerialServoLoad(Serial,ID6);
        }
    
  }}
