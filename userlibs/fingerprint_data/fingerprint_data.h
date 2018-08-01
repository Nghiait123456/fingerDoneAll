/*
 * fingerprint_data.h
 *
 *  Created on: Apr 5, 2018
 *      Author: user
 */

#ifndef FINGERPRINT_DATA_H_
#define FINGERPRINT_DATA_H_

uint16_t fingerTemplatecount (void);
void finger_Config (uint32_t baudrate);
#if (usePassWordFg == 1)
bool Finger_verifyPassword (void);
uint8_t changePassword (uint32_t Password);
#endif
//int getFingerprint(void );
uint8_t Finger_readsyspara (uint8_t *buffer, uint32_t timeout_ms);

uint8_t readnumber (uint32_t timeout_ms);
uint8_t create_Template (uint8_t id, uint8_t *tempBuff);
//int Finger_checkSerial(void);
//int Finger_readSerial(void);
//void printHex (int num, int precision);
uint8_t delete_Template (uint8_t id);
uint8_t Finger_readTemplate (uint16_t id, uint8_t *fingerTemplate, uint32_t timeout_ms);
uint8_t Finger_readImageBuffer (uint8_t *id, uint8_t *imageBuffer, uint32_t timeout_ms);
uint8_t delete_Template (uint8_t id); // xoa id so bao nhieu
uint8_t Finger_emptytemplate (void); // xoa tat ca id
//uint8_t Finger_DownloadImager (uint8_t *imageBuffer, uint32_t timeout_ms);
uint8_t fingerReadSystemParameter (uint8_t *buffer, uint32_t timeout_ms, uint8_t &sercurity);
uint8_t fingerSetsyspara (uint8_t paranum, uint8_t content,  uint8_t *buffer, uint32_t timeout_ms);//pranum =4 5 6
void endFinger ();
void listenFinger ();
bool fingerVerifyPassword (void);



#endif /* FINGERPRINT_DATA_H_ */
