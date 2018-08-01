/*
 * userconfig.h
 *
 *  Created on: Jul 3, 2018
 *      Author: user
 */

#ifndef USERCONFIG_H_
#define USERCONFIG_H_

#define DEBUG12  0

#define DEBUG13     0
#define DEBUG121  0
#define usePassWordFg 0
#define USER_DISABLE_MULTITYPE_SUPPORT 1
#include </home/user/workspace/NoPCShare/IotTeam/IoTHeartLibs/Arduino/avr/atmega328_tiny/csshock.h>

typedef struct
{
    union
    {
        struct
        {
            uint8_t ISRUNNING :1;
            uint8_t NEED_UPDATE_OLED :1;
        } b;
        uint8_t array[1];
    };
    uint32_t lastStartupTime = 0;
    unsigned char addnewId = 0;
    unsigned long timeProvince;


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

    volatile unsigned char timeGps = 0;
    volatile unsigned long disTanceTimeReadGps =0;
} DeviceStatusRunTime;

typedef struct
{
    union
    {
        struct
        {
            uint16_t ENABLE_AUTO_SLEEP_MODE : 1 ;

        } b;
        uint8_t array[1];
    };


} DeviceConfigStore;

extern DeviceStatusRunTime deviceRunTime;
extern DeviceConfigStore deviceConfig;
extern csshocksize StartSaveEflat;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







// vij tri luu id trong eeprom la id + locationStartEepromID

/*extern unsigned char addnewId;
extern unsigned char changeId;
extern unsigned char getId;

extern unsigned char callAddIdFromApp;
extern unsigned char callChangeIdFromApp;
extern unsigned char callGetIdFromApp;
extern unsigned char callClearIdFromApp;

extern unsigned long delayTest;


extern char input_uart[50];

extern unsigned long x;
extern unsigned long y;

extern volatile unsigned char timeGps;

extern volatile unsigned char numberIdChange;
extern volatile unsigned char sttGetGps;

extern unsigned char secondScan ;
extern unsigned char beep ;*/
extern char datasend_encoder[6];
extern char input_uart[50];




extern void beepMutil (uint32_t freq, uint32_t duration, uint32_t space, uint16_t times);
extern  void putHandOnFg(void);
extern  void putHandOutFg(void);
extern  void OK(void);
extern  void timeOut(void);
extern  void putHandOnFg2 (void);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define locationStartIdEeprom (127)
#define locationStartSaveGpsData  (127+60)
#define longGpsData  (127+60+1)
#define button 7
#define Newproduct ((127+1+1)+1)
#define debug   while(1) { runCSShock (); }
#define testAddID 0


#endif /* USERCONFIG_H_ */
