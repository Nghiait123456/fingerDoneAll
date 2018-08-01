/*
 * delayNoLoop.cpp
 *
 *  Created on: Jun 30, 2018
 *      Author: user
 */
#include "Arduino.h"

uint8_t delayNoLoop (uint32_t timeDelay, uint32_t timeStart)
{
  if (millis () > (timeDelay + timeStart))
    return 1;
  return 0;
}

