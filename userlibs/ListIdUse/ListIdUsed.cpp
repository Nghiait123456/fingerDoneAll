/*
 * ListIdUsed.cpp
 *
 *  Created on: Jun 6, 2018
 *      Author: user
 */

/*
 * getGPSparck.cpp
 *
 *  Created on: May 14, 2018
 *      Author: user
 */

/*
 * getGPSPark.cpp
 *
 *  Created on: Apr 19, 2018
 *      Author: user
 */
#include "Arduino.h"
#include "fingerprint_data.h"
#include "readAndCompareFinger.h"
#include "userconfig.h"

/*
 uint8_t ListIdUsed( uint16_t eeprom_start, int MaxSizeId ,uint16_t eepromLocationStartSaveId )
 {
 int i=0;
 int l=5;
 uint16_t eeprom_start1= eeprom_start;
 int h=0;
 for( int t= 0; t < sizeof(input_uart); t++ )
 {
 input_uart[t]=0;
 }
 // convert h sang string
 datasend_encoder[0]=0;
 strcat(input_uart,"listid(");
 while( i <= eeprom_start + MaxSizeId )
 {
 for( int j = eeprom_start1 ; j < eeprom_start1 + l ; j++  )
 {
 i=j;
 if( j > eeprom_start + MaxSizeId ) break;
 datasend_encoder[0]=0;
 if( fmRead((j+eepromLocationStartSaveId)) == 1 )
 {
 sprintf(datasend_encoder,"%d", j );
 strcat(input_uart,datasend_encoder);
 strcat(input_uart,",");
 h++;
 if( h == 15 )
 {

 h=0;
 sp(input_uart);
 for( int t= 0; t < sizeof(input_uart); t++ )
 {
 input_uart[t]=0;
 }

 }
 }
 }
 eeprom_start1=eeprom_start1 +l;
 }
 // print h < 6
 if( h > 0 && h < 15 )
 {
 h=0;
 sp(input_uart);
 }
 // gui chuoi end
 for( int t= 0; t < sizeof(input_uart); t++ )
 {
 input_uart[t]=0;
 }
 strcat(input_uart,");");
 spln(input_uart);
 // in ra chuoi
 }

 */

uint8_t ListIdUsed (uint16_t eeprom_start, int MaxSizeId, uint16_t eepromLocationStartSaveId)
{

  uint16_t sum = fingerTemplatecount ();
  if (sum == 0)
  {
    splnPM ("listid();");
    return 0;
  }
  else
  {
    int i = 0;
    int l = 5;
    int sumid = 0;
    uint16_t eeprom_start1 = eeprom_start;
    int h = 0;
    memset (input_uart, 0, sizeof(input_uart));
    // convert h sang string
    datasend_encoder[0] = 0;
    strcat (input_uart, "listid(");
    while (i <= eeprom_start + MaxSizeId)
    {
      for (int j = eeprom_start1; j < eeprom_start1 + l; j++)
      {
        i = j;
        if (j > eeprom_start + MaxSizeId)
          break;
        datasend_encoder[0] = 0;

        if (fmRead ((j + eepromLocationStartSaveId)) == 1)
        {
          h++;
          sumid++;
          sprintf (datasend_encoder, "%d", j);
          strcat (input_uart, datasend_encoder);
          if (sumid < sum)
          {
            strcat (input_uart, ",");
          }
          else if (sumid >= sum)
            break;

          if (h == 15)
          {

            h = 0;
            sp (input_uart);
            memset (input_uart, 0, sizeof(input_uart));

          }
        }
      }
      eeprom_start1 = eeprom_start1 + l;
      if (sumid >= sum)
        break;
    }
    // print h < 6
    if (h > 0 && h < 15)
    {
      h = 0;
      sp (input_uart);
    }
    // gui chuoi end
    memset (input_uart, 0, sizeof(input_uart));
    strcat (input_uart, ");");
    spln (input_uart);
    // in ra chuoi
  }
  return 1;
}

