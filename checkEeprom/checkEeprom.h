/*
 * checkEeprom.h
 *
 *  Created on: Jul 19, 2018
 *      Author: user
 */

#ifndef CHECKEEPROM_CHECKEEPROM_H_
#define CHECKEEPROM_CHECKEEPROM_H_
uint8_t checkEeprom( csshocksize idStart , csshocksize idEnd, uint8_t *dataError );
csshocksize copyEepromToEeprom(csshocksize idStartCopy, csshocksize idEndCopy, uint8_t * listIdFail,uint8_t sumIdfail, csshocksize idStartPate );
uint8_t fixIdFail (csshocksize idStartFix, csshocksize idEndFix, uint8_t *listIdFail, uint8_t sumIdFail);
uint8_t handlingErrorData (uint8_t * listIdFail, uint8_t sumIdFail);



#endif /* CHECKEEPROM_CHECKEEPROM_H_ */
