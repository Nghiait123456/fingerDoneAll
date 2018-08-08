/*
 * ClearID.cpp
 *
 *  Created on: Jun 4, 2018
 *      Author: user
 */

/*
 * changeIDFinger.cpp
 *
 *  Created on: Apr 12, 2018
 *      Author: user
 */
#include "Arduino.h"
#include "fingerprint_data.h"
#include "SoftwareSerial.h"
#include "userconfig.h"

uint8_t ClearId (uint8_t id, dataSave &data)
{
  uint8_t p = delete_Template (id);

  if (p == 0)
  {
    uint8_t value =0xFF;
   fmWritesCES(dataSave,idUsed[id-1],value,data);
    splnPM ("clearid(ok);");
    // in ra
    return 0; // clear ID ok
  }
  else
  {
    splnPM ("clearid(fail);");
  }

  return 5;
}

