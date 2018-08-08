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

uint8_t ListIdUsed ( int MaxSizeId, dataSave &data)
{

  uint16_t sum = fingerTemplatecount ();
  if (sum == 0)
  {
    splnPM ("listid();");
    return 0;
  }
  else
  {
    sp("listid(");
    uint8_t sumCount =0;
    uint8_t temp =0;
    for( uint8_t i=0; i < MaxSizeId; i++ )
    {
      temp=0;

      // fmReadsCES(,idUsed[i],temp,data);
      fmReadsCES(data,idUsed[i],temp,data);
       if(temp==1)
       {
         printInt32NoPad(i+1);
         sumCount++;
         if( sum != sumCount)
         spPM(",");
         if(sumCount %  20  == 0 && sumCount != 0  )
         {
           speol();
         }
         if( sumCount == sum ) break;
       }
    }
    spln(");");
   return 1;
  }
}
