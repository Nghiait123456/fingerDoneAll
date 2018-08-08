/*
 * fingerprint_data.cpp
 *
 *  Created on: Apr 5, 2018
 *      Author: user
 */
#include "Arduino.h"
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include "userconfig.h"



SoftwareSerial fingerSerial (10, 11);
Adafruit_Fingerprint finger = Adafruit_Fingerprint (&fingerSerial);

void endFinger ()
{
  fingerSerial.end ();
}
uint16_t fingerTemplatecount (void)
{
  finger.getTemplateCount ();
  uint16_t p = finger.templateCount;
  return p;
}

void listenFinger (void)
{
  fingerSerial.listen ();
}
void finger_Config (uint32_t baudrate)
{
  finger.begin (baudrate);
}
/*void printHex(int num, int precision) {
 char tmp[16];
 char format[128];

 sprintf(format, "%%.%dX", precision);

 sprintf(tmp, format, num);
 Serial.print(tmp);
 }*/

/*
uint8_t readnumber (uint32_t timeout_ms)
{
  uint8_t num = 0;
  uint32_t timer = millis ();
  while (num == 0)
  {
    while (!Serial.available ())
    {
      if (millis () - timer > timeout_ms)
        break;
    }
    num = Serial.parseInt ();
  }
  return num;
}
*/

//============================kiem tra password==========================

bool fingerVerifyPassword (void)
{
  if (finger.verifyPassword () == 1)
  {
    return 1;
  }
  else
    return 0;
}
#if (usePassWordFg == 1)
//================changer password===============
uint8_t changePassword (uint32_t Password)
{
  if (finger.verifyPassword () == 0)
    return 1;
  uint8_t p = finger.setPassword (Password);
  if (p != FINGERPRINT_OK)
  {
    return 1;
  }
  else
    return 0;
}
#endif
//=========================ham tao mau van tay moi =====================
/*uint8_t create_Template(uint8_t id,uint8_t *tempBuff,uint32_t timeout_ms)
 {  // tao van tay ok thi tra ve 0 va mau van tay
 uint8_t p = 1;
 uint32_t  timer=millis();
 // if((millis()-timer)>timeout_ms){return 1; }   // time out
 while (p != FINGERPRINT_OK) {// phat hien duoc van tay
 p = finger.getImage();
 if((millis()-timer)>timeout_ms){return 1;}// khong co thi sau mot thoi gian thoat  --> time out
 }
 p = finger.image2Tz(1);
 if( p != FINGERPRINT_OK){ return 2; }      //  save buffer 1 erro
 delay(2000);
 //====================== lay mau lan 2====================
 p = 1;
 // timer=millis(); // lay mau lan 2
 while (p != FINGERPRINT_OK) {
 p = finger.getImage();
 if((millis()-timer)>timeout_ms){return 1; }   //  time out
 }
 p = finger.image2Tz(2);
 if ( p != FINGERPRINT_OK){return 4;}  // save buffer 2 error

 p = finger.createModel(); // ghep 2 lan lay mau thanh 1 file tempalate
 if (p != FINGERPRINT_OK) {return 5;} // loi khong ghep duoc anh

 p = finger.storeModel(id);
 if (p == FINGERPRINT_PACKETRECIEVEERR) {return 6;  }  // loi duong truyen
 else if (p == FINGERPRINT_BADLOCATION) {return 7;} // loi truyen vi tri id
 else if (p == FINGERPRINT_FLASHERR) {return 8;}    // loi lu id vao flash

 p = finger.loadModel(id);
 if(p!= FINGERPRINT_OK){ return 9;}

 p = finger.getModel();
 if(p != FINGERPRINT_OK)return 10;
 uint8_t bytesReceived[534]; // 2 data packets
 memset(bytesReceived, 0xff, 534);
 uint32_t starttime = millis();
 int i = 0;
 while (i < 534 && (millis() - starttime) < timeout_ms) {
 if (fingerSerial.available()) {
 bytesReceived[i++] = fingerSerial.read();
 }
 }
 if(i<534){return 11;} // time out
 memset(tempBuff, 0xff, 512);
 int uindx = 0;
 for( uindx= 0; i < 256 ; i++ )  // bo di 9 byte from truyen
 {
 i= uindx+9;
 tempBuff[uindx] = bytesReceived[i];
 }
 for(uindx=256;  uindx < 512; uindx++ )  //541 = 9+256+11+256 +2
 {   i=uindx+20;
 tempBuff[uindx] = bytesReceived[i];
 }
 return 9; // create id ok
 }*/

//VERSION CU
/*uint8_t create_Template (uint8_t id, uint8_t *tempBuff, uint32_t timeout_ms)
 {  // tao van tay ok thi tra ve 0 va mau van tay
 uint8_t p = 1;
 uint8_t count = 0;

 if (finger.getImage () == FINGERPRINT_OK)
 {  // phat hien duoc van tay
 count = 1;
 }
 if (count != 1)
 return 0;
 p = finger.image2Tz (1);

 if (p != FINGERPRINT_OK)
 {
 return 1;
 }      //  save buffer 1 erro

 //  if(count != 2 ) return 2;
 //====================== lay mau lan 2====================
 if (finger.getImage () == FINGERPRINT_OK)
 {
 count = 3;
 }   //  time out

 if (count != 3)
 return 3;

 if (finger.image2Tz (2) != FINGERPRINT_OK)
 {
 return 4;
 }  // save buffer 2 error

 // ghep 2 lan lay mau thanh 1 file tempalate
 if (finger.createModel () != FINGERPRINT_OK)
 {
 return 5;
 } // loi khong ghep duoc anh

 p = finger.storeModel (id);
 if( p != FINGERPRINT_OK)  return 6;
 if (finger.storeModel (id) == FINGERPRINT_PACKETRECIEVEERR)
 {
 return 6;
 }  // loi duong truyen
 else if (p == FINGERPRINT_BADLOCATION)
 {
 return 7;
 } // loi truyen vi tri id
 else if (p == FINGERPRINT_FLASHERR)
 {
 return 8;
 }    // loi lu id vao flash

 return 9; // create id ok
 }*/

//VERSION MOI, VERSION CU OKIE BEN TREN
uint8_t create_Template (uint8_t id, uint8_t *tempBuff)
{  // tao van tay ok thi tra ve 0 va mau van tay
  uint8_t p = 1;
  uint8_t count = 0;
  // beep == 0 : da dat tay, beep ==1 ; da nhac tay
// to do
#if( DEBUG13 ==1)
 // printlnUint32(beep,5,'b');
  splnPM("nguoi dung hay nhac tay ra sau do dat lai ");
#endif

  // splnPM("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

  // printInt32NoPad(deviceRunTime.secondScan);
   if (deviceRunTime.secondScan == 2)
    {
      putHandOnFg2()
      ;
    }
  if (deviceRunTime.beep == 0  && deviceRunTime.secondScan == 0   )
    putHandOutFg()
    ;
  // if( beep==1) putHandOnFg();
  if (deviceRunTime.secondScan == 0 && finger.getImage () == FINGERPRINT_NOFINGER)
  {
  //  splnPM("dat tay lan 1");
    deviceRunTime.beep = 1; // da nhac tay
    if (deviceRunTime.beep == 1)
      putHandOnFg()
      ;
#if(DEBUG13==1)
    splnPM("lay mau lan 1 ");
#endif
    for (int j = 0; j < 5; j++)
    {
      if (count != 1)
      {
        if (finger.getImage () == FINGERPRINT_OK)
        {
          count = 1;
          deviceRunTime.beep = 0;
        }   //  time out
      }
      else if (count == 1)
        break;
    }

    if (count != 1)
      return 1;
    p = finger.image2Tz (1);

    if (p != FINGERPRINT_OK)
    {
      return 2;
    }      //  save buffer 1 erro
#if DEBUG13 ==1
    splnPM("hoan tat lay  mau lan 1 ");
#endif
    deviceRunTime.secondScan = 1;

    if (deviceRunTime.secondScan != 1)
        return 3;
  }

  //=====================================================================

  //yeu cau nhap tay lan thu hai va chi get imaget moi khi da nhap tay
#if DEBUG13 == 1
  splnPM("cho nguoi dung nhac tay len ");
#endif

  if (deviceRunTime.beep == 0 )
  {
    putHandOutFg();
    ;
  }

  if (finger.getImage () == FINGERPRINT_NOFINGER)
  {
    deviceRunTime.beep = 1;
    deviceRunTime.secondScan = 2;
  }
//  splnPM("khong nhac t t khoi 2");
  if (deviceRunTime.secondScan != 2)
    return 4;
  if (deviceRunTime.secondScan == 2)
  {
   // splnPM("dat tay lan 2");

    putHandOnFg2()
    ;
  }
#if DEBUG13 ==1
  splnPM("vao lay mau lan 2 ");
#endif
  //====================== lay mau lan 2===================================
  // thu lay mau lan 2  toi da 5 lan
  for (int j = 0; j < 12; j++)
  {

    if (count != 3)
    {
      if (finger.getImage () == FINGERPRINT_OK)
      {
        deviceRunTime.secondScan = 0;
        deviceRunTime.beep = 0;
        count = 3;
      }   //  time out
    }
    else if (count == 3)
      break;
  }

  if (count != 3)
  {
#if DEBUG13 ==1
    splnPM("lay mau lan 2 fail  ");
#endif
    return 5;
  }
#if DEBUG13 ==1
  splnPM(" lay mau lan 2  okie ");
#endif
  if (finger.image2Tz (2) != FINGERPRINT_OK)
  {
    return 6;
  }  // save buffer 2 error

  // ghep 2 lan lay mau thanh 1 file tempalate
  if (finger.createModel () != FINGERPRINT_OK)
  {
    return 7;
  } // loi khong ghep duoc anh

  p = finger.storeModel (id);
  if (p != FINGERPRINT_OK)
  {
    return 8;
  }

  deviceRunTime.beep = 0;
  deviceRunTime.secondScan = 0;
  OK();
  ;
#if (DEBUG13 == 1 )
  splnPM("return9");
#endif
  return 9; // create id ok
}
//=================================ham load hinh anh template hoặc từ bộ đệm ===============
/*uint8_t Finger_readTemplate(uint16_t id,uint8_t *fingerTemplate,uint32_t timeout_ms)
 {
 uint8_t p = finger.loadModel(id);
 if(p!= FINGERPRINT_OK){ return 1;}
 p = finger.getModel();
 if(p != FINGERPRINT_OK)return 2;

 // one data packet is 267 bytes. in one data packet, 11 bytes are 'usesless' :D 9 byte form truyen va 2 byte check sum
 // packet =256
 uint8_t bytesReceived[534]; // 2 data packets
 memset(bytesReceived, 0xff, 534);

 uint32_t starttime = millis();
 int i = 0;
 while (i < 534 && (millis() - starttime) < timeout_ms){
 // while ( (millis() - starttime) < timeout_ms){
 if (fingerSerial.available()) {
 bytesReceived[i++] = fingerSerial.read();
 }
 }

 //Serial.print(i);
 if(i<534){return 3;}
 memset(fingerTemplate, 0xff, 512);

 for( i = 9; i < 265 ; i++ )   // package length =128
 {
 fingerTemplate[i-9] = bytesReceived[i];
 }
 for ( i= 276; i < 532; i++ )
 {
 fingerTemplate[i-20] = bytesReceived[i];
 }

 // filtering only the data packets
 int uindx = 9;
 i=0;
 while (i < 556) {
 while (i < uindx) ++i;
 uindx += 256;
 while (i < uindx) {
 //fingerTemplate[index++] = bytesReceived[index];
 fingerTemplate[i++] = bytesReceived[i];
 }
 uindx += 2;
 while (i < uindx) ++i;
 uindx = i + 9;
 }


 return 0;
 }*/

//================================== ham doc template=========================
uint8_t Finger_readImageBuffer (uint8_t *id, uint8_t *imageBuffer, uint32_t timeout_ms)
{ // doc van tay
//  Serial.print(F("2*id=")); Serial.println(*id);
// deteced finger tra ve 0 con lại tra ve so loi. Khop voi id nao trhi tra ve so id do neu khong tra ve 0
  uint8_t p = 10;
  p = finger.getImage (); // detech van tay
  if (p != FINGERPRINT_OK)
    return 1; // khong doc dc van tay

  p = finger.image2Tz ();  // lu vao charbuffer
  if (p != FINGERPRINT_OK)
    return 2; // ghi khong thanh cong

  p = finger.fingerFastSearch ();
  if (p == FINGERPRINT_OK)
  {
    *id = (uint8_t) finger.fingerID;
    return 3;
  }  // search tra ve so id neu khong đúng tra ve 0
  else
  {
    *id = 0;
    return 4;
  }   // khong trung if nao

  /* p = finger.getModel();  //lech up
   if(p!=FINGERPRINT_OK) return 3;

   // Serial.write("b3");
   uint8_t bytesReceived[534];
   memset(bytesReceived, 0xff, 534);  //zero out template buffer

   int index=0;
   uint32_t starttime = millis();
   while ((index<534)&&(millis() - starttime) < timeout_ms)
   {
   if (fingerSerial.available())
   {
   bytesReceived[index++] = fingerSerial.read();
   }
   }

   if(index<534) return 4;
   memset(imageBuffer, 0xff, 256);
   int uindx = 0;
   for(uindx = 0; uindx < 256 ; uindx++ ) // package length =128
   {
   index = uindx +9;
   imageBuffer[uindx] =  bytesReceived[index];
   }*/
  return 0;
}

//===================================== ham delete template====================
uint8_t delete_Template (uint8_t id)
{
  uint8_t p = -1;
  p = finger.deleteModel (id);
  if (p != FINGERPRINT_OK)
  {
    return 1;
  }
  else
    return 0;
}
//======================== hàm empty template(xóa toàn bộ template)====================
uint8_t Finger_emptytemplate (void)
{
  uint8_t p = finger.emptyDatabase ();
  return p;

}

///======================= download vào buffchar ===================

/*uint8_t Finger_DownloadImager (uint8_t *imageBuffer, uint32_t timeout_ms)
 {
 uint8_t buffer[12];
 uint8_t data[] = { 0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x04, 0x09, 0x01, 0x00, 0x0F };

 fingerSerial.write (data, sizeof(data));
 int index = 0;
 uint32_t starttime = millis ();
 while ((index < 12) && ((millis () - starttime) < timeout_ms))
 {
 if (fingerSerial.available ())
 {
 buffer[index++] = (uint8_t) fingerSerial.read ();
 }
 }
 //return 0;
 if (buffer[9] > 0)
 {
 return 1;
 }
 for (index = 0; index < 256; index++)
 {
 fingerSerial.write (imageBuffer[index]);
 }
 uint8_t p = finger.fingerFastSearch ();
 if (p != FINGERPRINT_OK)
 {
 return 3;
 }
 return 0;
 }*/
//====================================================
/*
 uint8_t Finger_upload(int *checkSerial(void),int *readSearial(void),uint32_t timeout_ms)
 {   uint8_t buffer[12];
 uint8_t imageBuffer[256];
 uint8_t p= finger.getImage();
 if (p!= FINGERPRINT_OK) return 1;
 fingerSerial.write(0xEF);
 fingerSerial.write(0x01);
 fingerSerial.write(0xFF);
 fingerSerial.write(0xFF);
 fingerSerial.write(0xFF);
 fingerSerial.write(0xFF);
 fingerSerial.write(0x01);
 uint16_t k=0x0003;
 fingerSerial.write((uint8_t)(k>>8));
 fingerSerial.write((uint8_t)(k & 0xFF));
 fingerSerial.write(0x0A);
 k=0x000E;
 fingerSerial.write((uint8_t)(k>>8));
 fingerSerial.write((uint8_t)(k & 0xFF));
 delay(1);
 int index=0;
 uint32_t starttime = millis();
 while ((index < 12) && ((millis() - starttime) < timeout_ms))
 {
 if (checkSerial())
 {
 buffer[index++] = readSearial();
 }
 }
 if (buffer[9]>0) return 2;
 memset(imageBuffer, 0xff, 256);  //zero out template buffer
 index=0;
 starttime = millis();
 while ((index < 256) && ((millis() - starttime) < timeout_ms))
 {
 if (checkSerial())
 {
 imageBuffer[index++] = readSearial();
 }
 }
 for (int i = 0; i < 256; ++i) {
 Serial.print("0x");
 printHex(imageBuffer[i], 2);
 //Templatefinger[i]= fingerTemplate[i];
 Serial.print(", ");
 }


 return 0;
 }

 uint8_t Finger_readsyspara(uint8_t *buffer, uint32_t timeout_ms)
 {
 uint8_t data[12] = {0xEF, 0x01, 0xFF,0xFF,0xFF,0xFF, 0x01, 0x00, 0x03, 0x0F, 0x00, 0x13  };
 fingerSerial.write(data,12);
 uint32_t starttime = millis();
 int index=0;
 while( index<28 && ((millis() - starttime) < timeout_ms))
 {
 if(fingerSerial.available())
 {
 buffer[index++] = fingerSerial.read();
 }

 }if(index<28)return 0;
 else return 1;

 }

 */

//============================chuong trinh setup thong so he thong =======================




uint8_t fingerReadSystemParameter ( uint8_t *buffer, uint32_t timeout_ms, uint8_t &sercurity) //pranum =4 5 6
{

   uint16_t value;
     for (int i = 0; i < sizeof(buffer); i++)
     {
       buffer[i] = 0;
     }
     //uint8_t data[] = { 0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01 }; // dung mang buffer de luu
     buffer[0] = 0xEF;
     buffer[1] = 0x01;
     buffer[2] = 0xFF;
     buffer[3] = 0xFF;
     buffer[4] = 0xFF;
     buffer[5] = 0xFF;
     buffer[6] = 0x01;
     fingerSerial.write (buffer, 7);

     value = 0x03;
     fingerSerial.write (value >> 8);
     fingerSerial.write (value & 0xFF);
     fingerSerial.write (0x0F);

     uint16_t sum = 0x01 + 0x03 + 0x0F;
     fingerSerial.write (sum >> 8);
     fingerSerial.write (sum & 0xFF);
     ////////////////////////////////////////////////////////////////////////////////////////////////////////
     for (int i = 0; i < sizeof(buffer); i++)
     {
       buffer[i] = 0;
     }
     uint8_t index = 0;
     uint32_t starttime = millis ();
     while (index < 28 && ((millis () - starttime) < timeout_ms))
     {
       if (fingerSerial.available ())
       {
         buffer[index++] = fingerSerial.read ();
       }
     }
     if (index < 28)
       return 1;
     else
     {
       if (buffer[0] != 0xEF)
         return 2;
       if (buffer[1] != 0x01)
         return 3;
       if (buffer[2] != 0xFF)
         return 4;
       if (buffer[3] != 0xFF)
         return 5;
       if (buffer[4] != 0xFF)
         return 6;
       if (buffer[5] != 0xFF)
         return 7;
       if (buffer[6] != 0x07)
         return 8;
       if (buffer[7] != 0x00)
         return 9;
       if (((uint8_t) buffer[8] != 19))
         return 10;
       if (buffer[9] != 0x00)
         return 11;
     }
     value = 0;
     for (int i = 6; i < 26; i++)
     {
       value += (uint8_t) buffer[i];
     }
     if (       value != (  ( ((uint16_t) buffer[26])*256 + (uint8_t) buffer[27] )  )         )     return 12;
     sercurity = uint8_t(buffer[17]);
     return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 uint8_t fingerSetsyspara (uint8_t paranum, uint8_t content,  uint8_t *buffer, uint32_t timeout_ms)
 {
   uint16_t value;
   for (int i = 0; i < sizeof(buffer); i++)
   {
     buffer[i] = 0;
   }
   //uint8_t data[] = { 0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01 }; // dung mang buffer de luu
   buffer[0] = 0xEF;
   buffer[1] = 0x01;
   buffer[2] = 0xFF;
   buffer[3] = 0xFF;
   buffer[4] = 0xFF;
   buffer[5] = 0xFF;
   buffer[6] = 0x01;
   fingerSerial.write (buffer, 7);

   value = 0x05;
   fingerSerial.write (value >> 8);
   fingerSerial.write (value & 0xFF);
   fingerSerial.write (0x0E);

   fingerSerial.write (paranum);
   fingerSerial.write (content);

   uint16_t sum = 0x01 + 0x05 + 0x0E + (uint8_t) paranum + (uint8_t) content;
   fingerSerial.write (sum >> 8);
   fingerSerial.write (sum & 0xFF);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////
   for (int i = 0; i < sizeof(buffer); i++)
   {
     buffer[i] = 0;
   }
   uint8_t index = 0;
   uint32_t starttime = millis ();
   while (index < 12 && ((millis () - starttime) < timeout_ms))
   {
     if (fingerSerial.available ())
     {
       buffer[index++] = fingerSerial.read ();
     }
   }
   if (index < 12)
     return 1;
   else
   {
     if (buffer[0] != 0xEF)
       return 2;
     if (buffer[1] != 0x01)
       return 3;
     if (buffer[2] != 0xFF)
       return 4;
     if (buffer[3] != 0xFF)
       return 5;
     if (buffer[4] != 0xFF)
       return 6;
     if (buffer[5] != 0xFF)
       return 7;
     if (buffer[6] != 0x07)
       return 8;
     if (buffer[7] != 0x00)
       return 9;
     if (buffer[8] != 0x03)
       return 10;
     if (buffer[9] != 0x00)
       return 11;
   }
   value = 0;
   for (int i = 6; i < 10; i++)
   {
     value += (uint8_t) buffer[i];
   }
   if (value != ((uint8_t) buffer[10] * 256 + (uint8_t) buffer[11]))
     return 12;
   return 0;

 }

