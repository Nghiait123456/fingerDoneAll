/*
 * AddNewId.cpp
 *
 *  Created on: Jun 7, 2018
 *      Author: user
 */
#include "Arduino.h"
#include "fingerprint_data.h"
#include "SoftwareSerial.h"
#include  "userconfig.h"


uint8_t AddNewId ( uint8_t maxSizeId, dataSave &data)
{

  deviceRunTime.addnewId = 1;
  uint8_t id = 1;
  uint8_t location ;
  // find id add
  for( uint8_t i=0; i < maxSizeId; i++ )
      {
        // fmReadsCES(,idUsed[i],temp,data);
        fmReadsCES(dataSave,idUsed[i],id,data);
         if(id==0xFF)
         {
            location =i+1;
            break;
         }
      }
  //  flash full
  if (id == 1)
  {
    splnPM ("addnewid(fail);");
    deviceRunTime.beep = 0;
    deviceRunTime.secondScan = 0;
    deviceRunTime.addnewId = 0;
    // in ra
    return 3;
  }
  else
  {

    uint8_t p = create_Template (location, NULL); // them 1 id moi thanh cong tra ve 0 va 512bye id
  # if(DEBUG12==1)
    printlnUint32(p,5,'p');
  #endif
    if (p == 9)
    {
      deviceRunTime.beep = 0;
      deviceRunTime.secondScan = 0;
      deviceRunTime.addnewId = 2;
      uint8_t idValue=1;
      fmWritesCES(dataSave,idUsed[location-1],idValue,data);

      //update tong id
      spln("addnewid(ok);");

      return 2; // id doi thanh cong
    }

  }
  return 4;
}



