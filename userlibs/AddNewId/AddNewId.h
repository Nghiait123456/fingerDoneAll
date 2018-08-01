/*
 * AddNewId.h
 *
 *  Created on: Jun 7, 2018
 *      Author: user
 */

#ifndef ADDNEWID_ADDNEWID_H_
#define ADDNEWID_ADDNEWID_H_
#include "userconfig.h"


#if (testAddID ==1)
uint8_t AddNewId (uint8_t ID_firstly, uint8_t Max_size_id, csshocksize eepromLocationStatSave);
#else
uint8_t AddNewId (uint8_t ID_firstly, uint8_t Max_size_id, csshocksize eepromLocationStatSave);
#endif
#endif /* ADDNEWID_ADDNEWID_H_ */
