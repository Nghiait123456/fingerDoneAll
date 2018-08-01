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

#if (testAddID==1)
uint8_t AddNewId (uint8_t ID_firstly, uint8_t Max_size_id, csshocksize eepromLocationStatSave)
{

  addnewId = 1;
  // find id add
  uint8_t i;

  i = ID_firstly + Max_size_id;

  while((i--) && fmRead (eepromLocationStatSave + Max_size_id - i));

  //  flash full
  if (i == 0xFF )
  {
    splnPM ("addnewid(fail);");
    // in ra
    return 3;
  }
  else
  {

    uint8_t p = create_Template (i, NULL); // them 1 id moi thanh cong tra ve 0 va 512bye id
  # if(DEBUG12==1)
    printlnUint32(p,5,'p');
  #endif
    if (p == 9)
    {
      beep = 0;
      secondScan = 0;
      addnewId = 2;
      fmWrite (i + eepromLocationStatSave, 1);
      //update tong id
      for (uint16_t j = 0; j < sizeof(input_uart); j++)
      {
        input_uart[j] = '\0';
      }
      memset (input_uart, 0, sizeof(input_uart));
      strcat (input_uart, "addnewid(\"ok\",");
      datasend_encoder[0] = 0;
      sprintf (datasend_encoder, "%d", i);
      strcat (input_uart, datasend_encoder);
      strcat (input_uart, ");");
      spln (input_uart);

      return 2; // id doi thanh cong
    }

  }
  return 4;
}
#else
uint8_t AddNewId (uint8_t ID_firstly, uint8_t Max_size_id, csshocksize eepromLocationStatSave)
{

  deviceRunTime.addnewId = 1;
  int id = -1;
  // find id add
  for (uint8_t i = ID_firstly; i < ID_firstly + Max_size_id; i++)
  {

    if (fmRead (i + eepromLocationStatSave) == 0xFF)
    {
      id = i;
      break;
    }
  }

  //  flash full
  if (id == -1)
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

    uint8_t p = create_Template (id, NULL); // them 1 id moi thanh cong tra ve 0 va 512bye id
  # if(DEBUG12==1)
    printlnUint32(p,5,'p');
  #endif
    if (p == 9)
    {
     deviceRunTime.beep = 0;
      deviceRunTime.secondScan = 0;
      deviceRunTime.addnewId = 2;

      fmWrite (id + eepromLocationStatSave, 1);
      //update tong id
      for (uint16_t j = 0; j < sizeof(input_uart); j++)
      {
        input_uart[j] = '\0';
      }
      memset (input_uart, 0, sizeof(input_uart));
      strcat (input_uart, "addnewid(\"ok\",");
      datasend_encoder[0] = 0;
      sprintf (datasend_encoder, "%d", id);
      strcat (input_uart, datasend_encoder);
      strcat (input_uart, ");");
      spln (input_uart);

      return 2; // id doi thanh cong
    }

  }
  return 4;
}
#endif


