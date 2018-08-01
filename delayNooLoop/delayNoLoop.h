/*
 * delayNoLoop.h
 *
 *  Created on: Jun 30, 2018
 *      Author: user
 */

#ifndef DELAYNOOLOOP_DELAYNOLOOP_H_
#define DELAYNOOLOOP_DELAYNOLOOP_H_

uint8_t delayNoLoop (uint32_t timeDelay, uint32_t timeStart);

#endif /* DELAYNOOLOOP_DELAYNOLOOP_H_ */

/*
 if( delayChangeID == 0 )
 {
 delayChangeID = millis();
 }
 if( delayNoLoop(5000,delayChangeID) && delayChangeID != 0 )
 {
 delayChangeID = 0;
 spln("da ket thuc delay 5 s--------------------------------------------");
 delay(3000);
 }

 spln("ngoai ham delay 5s ");*/
