/*
 * checkEeprom.cpp
 *
 *  Created on: Jul 19, 2018
 *      Author: user
 */
#include <Arduino.h>
#include "userconfig.h"

uint8_t handlingErrorData (uint8_t * listIdFail , uint8_t &sumIdFail )
{
  if (eeread (locationStartIdEeprom) >= eeread (locationEndIdEeprom))
  {
    return 1; // thong bao loi va treo chuong trinh lai
  }
  if (checkEeprom (eeread (locationStartIdEeprom), (eeread (locationStartIdEeprom) + 127 - 1), listIdFail))
  {
    return 2; // thoong bao loi va treo chuong tirnh lai vi vung nho k su dung ma cung bi loi
  }
  copyEepromToEeprom (eeread (locationStartIdEeprom), eeread (locationStartIdEeprom) + 127 - 1, NULL, NULL, eeread (
  locationStartIdEeprom + 127));
  uint8_t sumIdFailLocal = checkEeprom ((csshocksize)eeread (locationStartIdEeprom),(csshocksize) (eeread (locationStartIdEeprom) + 127 - 1),listIdFail);
  if (sumIdFailLocal == 0)
  {
    return 3; // thong bao loi va chet chuong trinh vi loi o day la loi he thong
  }
  if( sumIdFailLocal > 10 )
  {
    return 4; //  thong bao loi va chet chuong trinh vi so vung nho bi hong qua nhieu
  }
  else
  {
    fixIdFail(eeread (locationStartIdEeprom), eeread (locationStartIdEeprom) + 127 - 1,listIdFail,sumIdFailLocal);
    sumIdFail=sumIdFailLocal;
    return 0;
  }
}

uint8_t fixIdFail (csshocksize idStartFix, csshocksize idEndFix, uint8_t *listIdFail, uint8_t sumIdFail)
{
  if (sumIdFail == 0)
    return 0;
  for (uint8_t fix = 0; fix < sumIdFail; fix++)
  {
    eewrite ((csshocksize) (idStartFix + listIdFail[fix]), 0xFF);
  }
  return 1;
}
uint8_t checkEeprom (csshocksize idStart, csshocksize idEnd, uint8_t *dataError)
{
   uint8_t  sum = 0;
  memset (dataError, 0xFF, sizeof(dataError));
  for (csshocksize i = idStart; i <= idEnd; i++)
  {
    eewrite (i, 0xAA);
    if ((uint8_t) eeread (i) != 0xAA)
    {
      dataError[sum] = i - idStart;
      sum++;
    }
  }
  return sum;
}
// 2th copy: copy mot vung nho lien tuc
// copy 1 vung nho khong lien tuc do 1 vung nho lien tuc bi hong 1 so cho
csshocksize copyEepromToEeprom (csshocksize idStartCopy, csshocksize idEndCopy, uint8_t * listIdFail, uint8_t sumIdfail,
                                csshocksize idStartPate)
{
  uint16_t sum = 0;
  if (idStartCopy >= idEndCopy)
    return 0;
  if (idStartCopy <= idStartPate && idStartPate <= idEndCopy)
    return 0;
  if( listIdFail == 0 )
  {
    csshocksize copy = idStartCopy;
    csshocksize pate = idStartCopy;
    while( copy <= idEndCopy)
    {
      eewrite(pate,eeread(copy));
      pate++;
      copy++;
    }
    return pate;
  }
  else (listIdFail != 0)
  {
    csshocksize copy = idStartCopy;
    csshocksize pate = idStartCopy;
    while (copy <= idEndCopy)
    {
      uint8_t check = 0;
      for (uint8_t i = 0; i < sumIdfail; i++)
      {
        if (copy == (idStartCopy + listIdFail[i]))
          check = 1;
      }
      if (check == 1)
      {
        copy++;
      }
      else if (check == 0)
      {
        eewrite (pate, eeread (copy));
        copy++;
        pate++;
      }
    }
    return pate;
  }
  return 0;
}
