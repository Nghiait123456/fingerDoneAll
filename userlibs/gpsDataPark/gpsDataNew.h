/*
 * gpsDataNew.h
 *
 *  Created on: May 16, 2018
 *      Author: user
 */

#ifndef GPSDATAPARK_GPSDATANEW_H_
#define GPSDATAPARK_GPSDATANEW_H_

uint8_t getData_softWareSerial12( char *output,uint16_t *length, uint16_t timeout_ms );
uint8_t get_GPSdata(char *input,  char *x1, char *y, char *z, char *time);
uint8_t getGpsData_softWareSerial(  uint8_t Status, uint16_t gpsDataLocationTemporary  );
void config_GPSneo(uint16_t baude);
bool checkGPS();
void endGPS();
void listenGPS();
#endif /* GPSDATAPARK_GPSDATANEW_H_ */
