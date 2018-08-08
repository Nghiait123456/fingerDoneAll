/*
 * readAndCompareFinger.cpp
 *
 *  Created on: Apr 12, 2018
 *      Author: user
 */
#define __MAIN_C__
#include "Arduino.h"
#include "fingerprint_data.h"
#include "SoftwareSerial.h"
#include "readAndCompareFinger.h"
#include "changeIdFInger.h"
#include "gpsDataNew.h"
#include <SoftwareSerial.h>
#include "ClearID.h"
#include "ListIdUsed.h"
#include "AddNewId.h"
#include  "userconfig.h"
//dataSeveinVmc

////////////////////////////////////////////////////////////////////////////////////////////////////////////
DeviceStatusRunTime deviceRunTime;
DeviceConfigStore deviceConfig;
dataSave dataSaveInEf VMC;
/*unsigned char addnewId = 0;
 unsigned long timeProvince;
 char datasend_encoder[6];
 char input_uart[50];

 unsigned long x = 0;
 unsigned long y = 0;


 unsigned char changeId = 0;
 unsigned char getId = 0;

 unsigned char callAddIdFromApp = 0;
 unsigned char callChangeIdFromApp = 0;
 unsigned char callGetIdFromApp = 0;

 unsigned char secondScan = 0;
 unsigned char beep = 0;

 volatile unsigned char numberIdChange = 0;
 volatile unsigned char sttGetGps = 0;
 volatile unsigned char sumIdUsed = 0;
 unsigned long delayTest = 0;

 volatile unsigned char timeGps = 0;*/
char datasend_encoder[6];
char input_uart[50];
//csshocksize StartSaveEflat;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void beepMutil (uint32_t freq, uint32_t duration, uint32_t space, uint16_t times)
{
  while (times--)
  {
    sysbeep (7, freq, duration);
    delay (duration + space);
  }
}

void putHandOnFg (void)
{
  beepMutil (1000, 150, 150, 2);
}
void putHandOnFg2 (void)
{
  beepMutil (1000, 150, 150, 4);
}
void putHandOutFg (void)
{
  beepMutil (1000, 10, 10, 15);
}
void OK (void)
{
  beepMutil (1000, 3000, 0, 1);
}
void timeOut (void)
{
  beepMutil (1000, 200, 200, 6);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
ucsstype getGpsFromEeprom (void)
{

  if (getarg (0) > 0)
  {
# if( DEBUG12 ==1)
    splnPM(" truyen sai so tham so ");
# endif
    return 0;
  }
  uint8_t longGpsLocal = 0xFF;
  fmReadsCES(dataSave, longGps, longGpsLocal, dataSaveInEf);
  if (longGpsLocal != 0xFF)
  {
    spPM("getgps(ok,");
    for (uint8_t i = 0; i < longGpsLocal; i++)
    {
      printInt32NoPad (dataSaveInEf.gpsData[i]);

    }
    splnPM(");");

    spPM("distanceTimeRead(");
    printInt32NoPad ((uint32_t) (millis () - deviceRunTime.disTanceTimeReadGps));
    splnPM(");");
    return 1;
  }
  else
  {
    splnPM("getgps(fail);");
  }
  return 0;
}
/* if (fmRead ((csshocksize) StartSaveEflat-longGpsData) != 0xFF)
 {

 //check data
 spPM("getgps(ok,");

 for (csshocksize i = (csshocksize) (StartSaveEflat - locationStartSaveGpsData);
 i < (csshocksize) (      (csshocksize)( StartSaveEflat - locationStartSaveGpsData) +  (csshocksize) (fmRead ((csshocksize) StartSaveEflat-longGpsData ) -25) )  ; i++)
 {

 spb(fmRead(i));
 }


 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 for (csshocksize i = (csshocksize) (      (csshocksize)( StartSaveEflat - locationStartSaveGpsData) +  (csshocksize) (fmRead ((csshocksize) StartSaveEflat-longGpsData ) -25) )  ;
 i < (csshocksize) (     (csshocksize)( StartSaveEflat -locationStartSaveGpsData)+ (csshocksize) fmRead((StartSaveEflat-longGpsData ) )    ); i++)
 {

 spb(fmRead(i));
 }

 splnPM(");");

 // send time
 spPM("distanceTimeRead(");
 printInt32NoPad((uint32_t) ( millis()-deviceRunTime.disTanceTimeReadGps )   );
 splnPM(");");
 return 1;
 }
 else
 {
 splnPM ("getgps(fail);");
 }
 return 0;
 }*/

ucsstype changeID (void)
{
  if (deviceRunTime.addnewId != 0 || deviceRunTime.getId != 0)
    return 0;
  if (!getarg (0))
  {
#if( DEBUG12 ==1 )
    splnPM ("khong co tham so dc truyen ");
#endif
    return 0;
  }
  if (getarg (0) > 1)
  {
#if( DEBUG12 ==1 )
    splnPM ("truyen sai so tham so ");
#endif
    return 0;
  }
  if (isstringarg (1))
  {
#if( DEBUG12 ==1 )
    spln ("tham so khong phai dang so ");
#endif
    return 2;
  }

  finger_Config (57600);
  deviceRunTime.callChangeIdFromApp = 1;
  deviceRunTime.numberIdChange = getarg (1);
  if (0 >= getarg (1) || getarg (1) > 127)
    return 2;
  // uint8_t x = changeIdFinger ( getarg (1), (csshocksize) (StartSaveEflat - locationStartIdEeprom) );
  uint8_t x = changeIdFinger (getarg (1), dataSaveInEf);
  if (x == 2)
    return 1;
  return 0;
}

ucsstype clearID123 (void)
{

  if (deviceRunTime.addnewId != 0 || deviceRunTime.getId != 0 || deviceRunTime.changeId != 0)
    {
    return 1;
    }
  if (!getarg (0))
  {
#if( DEBUG12 ==1 )
    spln ("khong co tham so dc truyen ");
#endif
    return 2;
  }
  if (getarg (0) > 1)
  {
#if( DEBUG12 ==1 )
    spln ("truyen sai so tham so ");
#endif

    return 3;
  }
  if (isstringarg (1))
  {
#if( DEBUG12 ==1 )
    spln ("tham so khong phai dang so ");
#endif
    return 4;
  }

  finger_Config (57600);
  if (0 >= getarg (1) || getarg (1) > 127)
  {
  return 5;
  }
  uint8_t x = ClearId (getarg (1), dataSaveInEf);
  if (x == 5)
  {
    return 6;
  }
  return 0;
}
ucsstype listID (void)
{
  if (getarg (0) > 0)
  {
#if( DEBUG12 ==1 )
    splnPM ("truyen sai so tham so ");
#endif
    return 1;
  }

  finger_Config (57600);
//  ListIdUsed (1, 127, (csshocksize) (StartSaveEflat - locationStartIdEeprom) );
  ListIdUsed (127, dataSaveInEf);
  return 0;
}

ucsstype addID (void)
{
  if (getarg (0) > 0)
  {
#if( DEBUG12 ==1 )
    splnPM ("truyen sai so tham so ");
#endif
    return 0;
  }

  if (deviceRunTime.changeId != 0 || deviceRunTime.getId != 0)
    return 0;
  deviceRunTime.callAddIdFromApp = 1;
  finger_Config (57600);
  // uint8_t x = AddNewId (1, 127, (csshocksize) (StartSaveEflat - locationStartIdEeprom));
  uint8_t x = AddNewId (127, dataSaveInEf);
  if (x == 2)
    return 1;
  return 0;
}

ucsstype getFG (void)
{
  putHandOnFg ();
  if (getarg (0) > 0)
  {
#if (DEBUG12 ==1 )
    splnPM ("truyen sai so tham so ");
#endif
    return 0;
  }
  if (deviceRunTime.addnewId != 0 || deviceRunTime.changeId != 0)
    return 0;
  deviceRunTime.callGetIdFromApp = 1;
  finger_Config (57600);
  uint8_t x = readAndCompaeFinger ();
  if (x == 2)
    return 1;
  return 0;
}

ucsstype getScr (void)
{
  uint8_t security;
  finger_Config (57600);
  if (fingerReadSystemParameter ((uint8_t *) input_uart, 150, security) == 0)
  {
    memset (input_uart, 0, sizeof(input_uart));
    strcat (input_uart, "fgreadscr(\"ok\",");
    datasend_encoder[0] = 0;
    sprintf (datasend_encoder, "%d", security);
    strcat (input_uart, datasend_encoder);
    strcat (input_uart, ");");
    spln (input_uart);
  }
  else
  {
    splnPM("fgreadscr(fail);");
  }
  return 0;
}

ucsstype setScr (void)
{
  if (!getarg (0))
  {
    return 1;
  }
  if (getarg (0) > 1)
  {
    return 2;
  }
  if (isstringarg (1))
  {
    return 3;
  }
  finger_Config (57600);
  if ((uint8_t) getarg (1) > 5 || (uint8_t) getarg (1) < 1)
    return 4;
  if (fingerSetsyspara (5, (uint8_t) getarg (1), (uint8_t *) input_uart, 150) == 0)
  {
    splnPM("fgsetscr(ok);");
  }
  else
  {
    splnPM("fgsetscr(fail);");
  }
  return 0;
}

void gpsRead ()
{
 // if (fmRead ((csshocksize) StartSaveEflat - longGpsData) == 0xFF);
    if(fmGetCES(dataSave,longGps,dataSaveInEf) == 0xFF)
  {
#if( DEBUG121 ==1 )
    splnPM ("van chua doc dc gps ");
#endif
    // uint8_t l = getGpsData_softWareSerial (deviceRunTime.sttGetGps,(csshocksize) StartSaveEflat - locationStartSaveGpsData);
    uint8_t l = getGpsData_softWareSerial (deviceRunTime.sttGetGps, dataSaveInEf);
    if (l >= 2)
    {
      deviceRunTime.sttGetGps = 0;
    }
  }
  else
  {
    // spln("da doc duoc gps ");
    static unsigned long gps2 = millis ();
    if (deviceRunTime.timeGps == 0)
    {
#if(DEBUG121 == 1)
      spln ("da dat lai bo dem time ----------- ");
#endif
      gps2 = millis ();
      deviceRunTime.timeGps = 1;
    }
    if ((millis () - gps2) < 2000)
    {
      // spln("nho hon 2000");
    //  uint8_t l = getGpsData_softWareSerial (deviceRunTime.sttGetGps,(csshocksize) StartSaveEflat - locationStartSaveGpsData);
      uint8_t l = getGpsData_softWareSerial (deviceRunTime.sttGetGps, dataSaveInEf);
      //  printlnUint32 (l, 5, 'l');
      if (l >= 2)
      {
        deviceRunTime.sttGetGps = 0;
      }
    }
    else if ((millis () - gps2) > 20000)
    {
      deviceRunTime.timeGps = 0;
      gps2 = millis ();
#if(DEBUG121 ==1)
      spln ("da reset bo dem time --------- ");
#endif
    }
  }
}
#if(DEBUG12 ==1)
void printHex (int num, int precision)
{
  char tmp[16];
  char format[30];

  sprintf (format, "%%.%dX", precision);

  sprintf (tmp, format, num);
  sp (tmp);
}
#endif

volatile uint16_t x = 1;

void sbashInit (void)
{

//  while(1);
  initCSShock (115200);
  config_GPSneo (9600);
  finger_Config (57600);
  if (!fingerVerifyPassword ())
  {
    splnPM("finger error ");
    debug;
  }

  addCSShockFunction ("gpsget", (csshock_func) getGpsFromEeprom);
  addCSShockFunction ("fgchange", (csshock_func) changeID);
  addCSShockFunction ("fgclear", (csshock_func) clearID123);
  addCSShockFunction ("fglist", (csshock_func) listID);
  addCSShockFunction ("fgaddnew", (csshock_func) addID);
  addCSShockFunction ("fgget", (csshock_func) getFG);
  addCSShockFunction ("fgscrget", (csshock_func) getScr);
  addCSShockFunction ("fgscrset", (csshock_func) setScr);
  SHOW_DEFINE_UINT(dataSaveInEf.gpsData);
  SHOW_DEFINE_UINT(dataSaveInEf.idUsed);
  SHOW_DEFINE_UINT(&dataSaveInEf.longGps);

  // fmWritesCES(dataSave,idUsed[0],value,dataSaveInEf);
}

void dataInit (void)
{

  memset (&deviceConfig, 0, sizeof(deviceConfig));
  memset (&deviceRunTime, 0, sizeof(deviceRunTime));

}
void setup ()
{
  initCSShock (115200);

  sbashInit ();
  dataInit ();

 /* StartSaveEflat = fmGetUserStartAddress ();
  spPM("Start Save ef=");
  printInt32NoPad (StartSaveEflat);*/
 // fmWrite ((csshocksize) StartSaveEflat - longGpsData, 0XFF);
  uint8_t value =0xFF;
  fmWritesCES(dataSave,longGps,value,dataSaveInEf);
}

// The loop function is called in an endless loop
void loop ()
{

  static unsigned long addidTimeout = millis ();
  static unsigned long changeidTimeout = millis ();
  static unsigned long getIdFgTimeout = millis ();

///////////////////////////////////////////////////////////////////////////////////////

//  p012 = micros ();

  if (deviceRunTime.changeId == 0 && deviceRunTime.getId == 0)
  {
    // co callAddIDFromApp : de update time out 1 lan duy nhat
    if (deviceRunTime.callAddIdFromApp == 1 && deviceRunTime.addnewId == 1)
    {
      addidTimeout = millis () + 35000;
      deviceRunTime.callAddIdFromApp = 0;
    }
    if (millis () < addidTimeout && deviceRunTime.addnewId == 1)
    {

      finger_Config (57600);
      //  AddNewId (1, 127, (csshocksize) (StartSaveEflat - locationStartIdEeprom));
      AddNewId (127, dataSaveInEf);
    }
    else if (deviceRunTime.addnewId == 2)
    {
      deviceRunTime.addnewId = 0;
      deviceRunTime.beep = 0;
      deviceRunTime.secondScan = 0;
    }
    else if (millis () > addidTimeout)
    {
      deviceRunTime.beep = 0;
      deviceRunTime.secondScan = 0;
      if (deviceRunTime.addnewId == 1)
      {
        splnPM("addnewid(fail);");
        deviceRunTime.addnewId = 0;
        timeOut ();
      }
    }
  }
//////////////////////////////////////////////////////////////////////////////////////
  if (deviceRunTime.addnewId == 0 && deviceRunTime.getId == 0)
  {
    if (deviceRunTime.callChangeIdFromApp == 1 && deviceRunTime.changeId == 1)
    {
      changeidTimeout = millis () + 35000;
      deviceRunTime.callChangeIdFromApp = 0;
    }
    if (millis () < changeidTimeout && deviceRunTime.changeId == 1)
    {
      finger_Config (57600);
      //  changeIdFinger (deviceRunTime.numberIdChange, (csshocksize) (StartSaveEflat - locationStartIdEeprom));
      changeIdFinger (deviceRunTime.numberIdChange, dataSaveInEf);
    }
    else if (deviceRunTime.changeId == 2)
    {
      deviceRunTime.changeId = 0;
      deviceRunTime.beep = 0;
      deviceRunTime.secondScan = 0;
    }
    else if (millis () > changeidTimeout)
    {

      deviceRunTime.beep = 0;
      deviceRunTime.secondScan = 0;
      if (deviceRunTime.changeId == 1)
      {
        splnPM("changeid(fail);");
        deviceRunTime.changeId = 0;
        timeOut ();
      }
    }
  }
//////////////////////////////////////////////////////////////////////////////////////////
  if (deviceRunTime.changeId == 0 && deviceRunTime.addnewId == 0)
  {
    if (deviceRunTime.callGetIdFromApp == 1 && deviceRunTime.getId == 1)
    {
      getIdFgTimeout = millis () + 10000;
      deviceRunTime.callGetIdFromApp = 0;
    }
    if (millis () < getIdFgTimeout && deviceRunTime.getId == 1)
    {
      finger_Config (57600);
      readAndCompaeFinger ();
    }
    else if (deviceRunTime.getId == 2)
    {
      deviceRunTime.getId = 0;
      getIdFgTimeout = millis ();
    }
    else if (millis () > getIdFgTimeout)
    {
      if (deviceRunTime.getId == 1)
      {
        splnPM("getid(fail);");
        deviceRunTime.getId = 0;
        timeOut ();
      }
    }
  }
//////////////////////////////////////////////////////////////////////////////////////////////


  gpsRead ();

  runCSShock ();
  //
}

