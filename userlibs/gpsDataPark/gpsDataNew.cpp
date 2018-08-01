/*
 * gpsDataNew.cpp
 *
 *  Created on: May 16, 2018
 *      Author: user
 */
#include "Arduino.h"
#include <SoftwareSerial.h>
SoftwareSerial GPSNeo (12, 13);
#include "userconfig.h"

void endGPS ()
{
  GPSNeo.end ();
}
bool checkGPS ()
{
  if (GPSNeo.available ())
    return true;
  return false;
}
void config_GPSneo (uint16_t baude)
{

  GPSNeo.begin (baude);
}

void listenGPS ()
{
  GPSNeo.listen ();
}

/*
 uint8_t getData_softWareSerial( char *Latitude, char *Longitude, char *Height, char *Time , uint8_t Status)
 {

 static unsigned char  count =0;
 static unsigned char  countLatitude =0;
 static unsigned char  countLongitude =0;
 static unsigned char  countHeight =0;
 static unsigned char  countTime =0;
 static unsigned long  startTimeOut = millis() + 2000 ;
 char value ;
 if(Status == 0 )
 {
 sttGetGps = 1;
 // spln("reset thong so ");
 count = 0;
 countLatitude =0;
 countLongitude =0;
 countHeight =0;
 countTime =0;
 startTimeOut = millis() + 2000;
 }

 //*length=0;

 GPSNeo.listen();
 if(GPSNeo.available() )
 {
 value  = GPSNeo.read();
 spln("value=");
 spb(value);
 // printlnInteger(count,5,'c');

 if(count == 0  && value == '$') count = 1;
 else  if(count == 1  && value == 'G') count = 2;
 else  if(count == 2  && value == 'P') count = 3;
 else  if(count == 3  && value == 'G') count = 4;
 else  if(count == 4  && value == 'G') count = 5;
 else  if(count == 5  && value == 'A') count = 6;
 else  if( count == 6 && value == ',') count = 7;

 // read TIME
 else if( count == 7  && value != ',')
 {
 Time[countTime] = value;
 countTime++;
 }
 else if( count == 7 && value == ',' )
 {
 count = 8 ;
 Time[countTime] = 0;
 }

 ///////////////////////////////////////////////////////////////////
 // read Latitude
 else if( count == 8 && value != ',' )
 {
 Latitude[countLatitude] = value ;
 countLatitude ++;
 }
 else if( count == 8  && value == ',' )
 {
 count =  9;
 }
 // read N or S
 else if( count == 9  && value != ',' )
 {
 Latitude[countLatitude] = value ;
 countLatitude ++;
 }
 else if( count == 9 && value == ',' )
 {
 Latitude[countLatitude]= 0;
 count = 10 ;
 }
 //////////////////////////////////////////////////////////////////////

 // read Longitude
 else if( count == 10   && value != ',' )
 {
 Longitude[countLongitude] = value ;
 countLongitude ++;
 }
 else if( count == 10 && value == ',' )
 {
 count = 11;
 }
 // read w or e
 else if( count ==11 && value != ',' )
 {
 Longitude[countLongitude] = value ;
 countLongitude ++;
 }
 else if( count == 11 && value == ',' )
 {
 Longitude[countLongitude] = 0;
 count = 12;
 }
 /////////////////////////////////////////////////////////////////////////

 // read Heigh
 else if( count == 12 && value == ',' )
 {
 count = 13 ;
 }
 else if( count == 13 && value == ',' )
 {
 count = 14;
 }
 else if( count == 14 && value == ',' )
 {
 count =15 ;
 }
 else if( count == 15 & value != ',' )
 {
 Height[countHeight]= value ;
 countHeight ++ ;
 }
 else if( count ==15 & value == ','  )
 {
 Height[countHeight] = 0;
 count = 16;
 }


 /////////////////////////////////////////////////////////////////////////////

 // finished read gps
 else if( count == 16 )
 {
 return 1 ;
 }


 }
 if ( millis() > startTimeOut )
 {
 return 2 ;
 }
 return 0;
 }
 */

/*uint8_t getGpsData_softWareSerial(  uint8_t Status, uint16_t gpsDataLocationTemporary  )
 {

 static unsigned char  count =0;
 static unsigned char  countData =0;
 static unsigned long  startTimeOut = millis() + 2000 ;
 char value ;
 if(Status == 0 )
 {
 sttGetGps = 1;
 // spln("reset thong so ");
 count = 0;
 countData = 0;
 startTimeOut = millis() + 2000;
 }

 //*length=0;

 GPSNeo.listen();
 if(GPSNeo.available() )
 {
 value  = GPSNeo.read();


 if(count == 0  && value == '$') count = 1;
 else if(count == 0  && value != '$') count = 0;
 else  if(count == 1  && value == 'G') count = 2;
 else  if(count == 1  && value != 'G') count = 0;
 else  if(count == 2  && value == 'P') count = 3;
 else  if(count == 2  && value != 'P') count = 0;
 else  if(count == 3  && value == 'G') count = 4;
 else  if(count == 3  && value != 'G') count = 0;
 else  if(count == 4  && value == 'G') count = 5;
 else  if(count == 4  && value != 'G') count = 0;
 else  if(count == 5  && value == 'A') count = 6;
 else  if(count == 5  && value != 'A') count = 0;
 else  if( count == 6 && value == ',') count = 7;
 else  if( count == 6 && value != ',') count = 0;

 // read TIME
 else if( count == 7  && value != ',')
 {
 fmWrite((countData+gpsDataLocationTemporary),value);
 countData++;

 }
 else if( count == 7 && value == ',' )
 {
 count = 8 ;
 fmWrite((countData+gpsDataLocationTemporary),value);
 countData++;
 }

 ///////////////////////////////////////////////////////////////////
 // read Latitude
 else if( count == 8 && value != ',' )
 {
 fmWrite((countData+gpsDataLocationTemporary),value);
 countData++;
 }
 else if( count == 8  && value == ',' )
 {
 count =  9;
 }
 // read N or S
 else if( count == 9  && value != ',' )
 {
 if( (value != 'N') && ( value != 'S') )
 {
 count = 0;
 countData = 0;
 return 1; // error data

 }
 fmWrite((countData+gpsDataLocationTemporary),value);
 countData++;
 }
 else if( count == 9 && value == ',' )
 {
 count = 10 ;
 fmWrite((countData+gpsDataLocationTemporary),value);
 countData++;
 }
 //////////////////////////////////////////////////////////////////////

 // read Longitude
 else if( count == 10   && value != ',' )
 {
 fmWrite((countData+gpsDataLocationTemporary),value);
 countData++;
 }
 else if( count == 10 && value == ',' )
 {
 count = 11;

 }
 // read w or e
 else if( count ==11 && value != ',' )
 {

 if( (value != 'W') && ( value != 'E') )
 {
 count = 0;
 countData = 0;
 return 1; // error data
 }
 fmWrite((countData+gpsDataLocationTemporary),value);
 countData++;
 }
 else if( count == 11 && value == ',' )
 {
 count = 12;
 fmWrite((countData+gpsDataLocationTemporary),value);
 countData++;
 }
 /////////////////////////////////////////////////////////////////////////

 // read Heigh
 else if( count == 12 && value == ',' )
 {
 count = 13 ;
 }
 else if( count == 13 && value == ',' )
 {
 count = 14;
 }
 else if( count == 14 && value == ',' )
 {
 count =15 ;
 }
 else if( count == 15 & value != ',' )
 {
 fmWrite((countData+gpsDataLocationTemporary),value);
 countData++;
 }
 else if( count ==15 & value == ','  )
 {
 count = 16;

 }
 else if( count ==16  & value == 'M'  )
 {
 count = 17 ;
 }

 else if( count ==16  & value != 'M'  )
 {
 count = 0 ;
 countData = 0;
 }


 /////////////////////////////////////////////////////////////////////////////

 // finished read gps
 else if( count == 17 )
 {
 if( countData  > 2)
 {

 printInteger(countData,5,'(');
 speol();
 fmWrite(longGpsData,countData);
 countData = 0 ;
 // save to eeprom
 return  countData ;
 }
 }


 }
 if ( millis() > startTimeOut )
 {
 return 2 ;
 }
 return 0;
 }*/

uint8_t getGpsData_softWareSerial (uint8_t Status, uint16_t gpsDataLocationTemporary)
{

  static unsigned char count = 0;
  static unsigned char testNum = 0;
  static unsigned char countData = 0;
  static unsigned long startTimeOut = millis () + 2000;

  char value;
  if (Status == 0)
  {
    deviceRunTime.sttGetGps = 1;
    count = 0;
    countData = 0;
    startTimeOut = millis () + 2000;
    testNum = 0;
  }

//*length=0;

  GPSNeo.listen ();
  if (GPSNeo.available ())
  {
    value = GPSNeo.read ();
    if ((value == 13) || (value == 10))
    {
      count = 0;
      countData = 0;
      testNum = 0;
      return 0;
    }

    else if ((count == 0) && (value == '$'))
      count = 1;
    else if ((count == 0) && (value != '$'))
      count = 0;
    else if ((count == 1) && (value == 'G'))
      count = 2;
    else if ((count == 1) && (value != 'G'))
      count = 0;
    else if ((count == 2) && (value == 'P'))
      count = 3;
    else if ((count == 2) && (value != 'P'))
      count = 0;
    else if ((count == 3) && (value == 'G'))
      count = 4;
    else if ((count == 3) && (value != 'G'))
      count = 0;
    else if ((count == 4) && (value == 'G'))
      count = 5;
    else if ((count == 4) && (value != 'G'))
      count = 0;
    else if ((count == 5) && (value == 'A'))
      count = 6;
    else if ((count == 5) && (value != 'A'))
      count = 0;
    else if ((count == 6) && (value == ','))
    {
      count = 7;
      //  x++;
    }
    else if ((count == 6) && (value != ','))
      count = 0;

    // read TIME
    else if ((count == 7) && (value != ','))
    {
      fmWrite ((countData + gpsDataLocationTemporary), value);
      countData++;
      testNum = 1;

    }
    else if ((count == 7) && (value == ',') && (testNum == 1))
    {
      count = 8;
      fmWrite ((countData + gpsDataLocationTemporary), value);
      countData++;
      testNum = 0;
    }

    ///////////////////////////////////////////////////////////////////
    // read Latitude
    else if ((count == 8) && (value != ','))
    {
      fmWrite ((countData + gpsDataLocationTemporary), value);
      countData++;
      testNum = 1;
    }
    else if ((count == 8) && (value == ',') && (testNum == 1))
    {
      count = 9;
      testNum = 0;
    }
    // read N or S
    else if ((count == 9) && (value != ','))
    {
      if ((value != 'N') && (value != 'S'))
      {
        count = 0;
        countData = 0;
        return 1; // error data

      }
      fmWrite ((countData + gpsDataLocationTemporary), value);
      countData++;
      testNum = 1;
    }
    else if ((count == 9) && (value == ',') && (testNum == 1))
    {
      count = 10;
      fmWrite ((countData + gpsDataLocationTemporary), value);
      countData++;
      testNum = 0;
    }
    //////////////////////////////////////////////////////////////////////

    // read Longitude
    else if ((count == 10) && (value != ','))
    {
      fmWrite ((countData + gpsDataLocationTemporary), value);
      countData++;
      testNum = 1;
    }
    else if ((count == 10) && (value == ',') && (testNum == 1))
    {
      count = 11;
      testNum = 0;
    }
    // read w or e
    else if ((count == 11) && (value != ','))
    {

      if ((value != 'W') && (value != 'E'))
      {
        count = 0;
        countData = 0;
        return 3; // error data
      }
      fmWrite ((countData + gpsDataLocationTemporary), value);
      countData++;
      testNum = 1;
    }
    else if ((count == 11) && (value == ',') && (testNum == 1))
    {
      count = 12;
      testNum = 0;
      fmWrite ((countData + gpsDataLocationTemporary), value);
      countData++;

    }
    /////////////////////////////////////////////////////////////////////////

    // read Heigh
    else if (count == 12 && value == ',')
    {
      count = 13;
    }
    else if (count == 13 && value == ',')
    {
      count = 14;
    }
    else if (count == 14 && value == ',')
    {
      count = 15;
    }
    else if (count == 15 && value != ',')
    {
      fmWrite ((countData + gpsDataLocationTemporary), value);
      countData++;
      testNum = 1;
    }
    else if ((count == 15) && (value == ',') && (testNum == 1))
    {
      count = 16;
      testNum = 0;

    }
    else if ((count == 16) && (value == 'M'))
    {

      count = 17;
    }

    else if ((count == 16) && (value != 'M'))
    {
      count = 0;
      countData = 0;
    }

    /////////////////////////////////////////////////////////////////////////////

    // finished read gps
    else if (count == 17)
    {
      if (countData > 6 && countData < 255)
      {
        fmWrite ((csshocksize) StartSaveEflat - longGpsData, countData);
#if( DEBUG121 ==1 )
        sp ("gps thanh cong roi,countdata= ");
        printInt32NoPad (countData);
#endif

        countData = 0;
        count = 0;

        // save to eeprom
        deviceRunTime.disTanceTimeReadGps = millis();
        return countData;
      }
      count = 0;
      countData = 0;
      return 0;
    }

  }
  if (millis () > startTimeOut)
  {
    return 2;
  }

  return 0;
}

/*
 uint8_t getGpsData_softWareSerial (uint8_t Status, uint16_t gpsDataLocationTemporary)
 {

 static unsigned char count = 0;
 static unsigned char testNum = 0;
 static unsigned char countData = 0;
 static unsigned long startTimeOut = millis () + 2000;
 char value;
 if (Status == 0)
 {
 sttGetGps = 1;
 // spln("reset thong so ");
 count = 0;
 countData = 0;
 startTimeOut = millis () + 2000;
 testNum = 0;
 }

 //*length=0;

 GPSNeo.listen ();
 if (GPSNeo.available ())
 {
 value = GPSNeo.read ();
 if ((value == 13) || (value == 10))
 {
 //     spln("reset thong so ");
 count = 0;
 countData = 0;
 testNum = 0;
 return 0;
 }

 else if ((count == 0) && (value == '$'))
 count = 1;
 else if ((count == 0) && (value != '$'))
 count = 0;
 else if ((count == 1) && (value == 'G'))
 count = 2;
 else if ((count == 1) && (value != 'G'))
 count = 0;
 else if ((count == 2) && (value == 'P'))
 count = 3;
 else if ((count == 2) && (value != 'P'))
 count = 0;
 else if ((count == 3) && (value == 'G'))
 count = 4;
 else if ((count == 3) && (value != 'G'))
 count = 0;
 else if ((count == 4) && (value == 'G'))
 count = 5;
 else if ((count == 4) && (value != 'G'))
 count = 0;
 else if ((count == 5) && (value == 'A'))
 count = 6;
 else if ((count == 5) && (value != 'A'))
 count = 0;
 else if ((count == 6) && (value == ','))
 {
 count = 7;
 x++;
 }


 }
 if (millis () > startTimeOut)
 {
 return 2;
 }
 return 0;
 }
 */

/*
 uint8_t get_GPSdata (char *input, char *Latitude, char *Longitude, char *Height, char *Time)
 {
 // get time
 char *location;
 location = strstr (input, "A,");
 if (*(location + 2) != ',' && location != 0)
 {
 location = location + 2;
 while (*location != ',')
 {
 *Time = *location;
 Time++;
 location++;
 }
 *Time = 0;
 }

 // get east
 location = strstr (input, ",N,");
 if (location != 0)
 {
 location--;
 while (*location != ',')
 {
 location--;
 }
 location++;

 while (*location != ',')
 {
 *Latitude = *location;
 Latitude++;
 location++;
 }
 *Latitude = 'N';
 Latitude++;
 *Latitude = 0;

 }
 else
 {
 location = strstr (input, ",S,");
 if (location != 0)
 {
 location--;
 while (*location != ',')
 {
 location--;
 }
 location++;

 while (*location != ',')
 {
 *Latitude = *location;
 Latitude++;
 location++;
 }
 *Latitude = 'S';
 Latitude++;
 *Latitude = 0;

 }
 }

 // get West

 location = strstr (input, ",W,");
 if (location != 0)
 {
 location--;
 while (*location != ',')
 {
 location--;
 }
 location++;
 while (*location != ',')
 {
 *Longitude = *location;
 Longitude++;
 location++;
 }
 *Longitude = 'W';
 Longitude++;
 *Longitude = 0;

 }
 else
 {
 location = strstr (input, ",E,");
 if (location != 0)
 {
 location--;
 while (*location != ',')
 {
 location--;
 }
 location++;
 while (*location != ',')
 {
 *Longitude = *location;
 Longitude++;
 location++;
 }
 *Longitude = 'E';
 Longitude++;
 *Longitude = 0;

 }
 }

 // get altitude
 location = strstr (input, ",M,");
 if (location != 0)
 {
 location--;
 while (*location != ',')
 {
 location--;
 }
 location++;
 while (*location != ',')
 {
 *Height = *location;
 Height++;
 location++;
 }
 *Height = 0;

 }

 }
 */

