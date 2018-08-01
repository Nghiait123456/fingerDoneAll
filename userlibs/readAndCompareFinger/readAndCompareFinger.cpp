#include "Arduino.h"
#include "fingerprint_data.h"
#include "SoftwareSerial.h"
#include "userconfig.h"

uint8_t readAndCompaeFinger(void)
{
       unsigned char id ;
       deviceRunTime.getId = 1;

        uint8_t p= Finger_readImageBuffer(&id,NULL,0); // dung tra ve 0 sai, thi tra ve ma loi so id. khop voi id nao thi tra ve id day kop khop trhi id =0

#if DEBUG12 ==1
         printlnUint32(p,5,'p');
#endif
         if( p== 3   )
             {
               deviceRunTime.getId = 2;
               memset (input_uart, 0, sizeof(input_uart));
               strcat(input_uart,"getfg(\"ok\",");
               for( uint8_t i=0; i< sizeof(datasend_encoder); i++ )
               {
                 datasend_encoder[i]=0;
               }
               sprintf(datasend_encoder,"%d", id );
               strcat(input_uart,datasend_encoder);
               strcat(input_uart,")");
               spln(input_uart);
             // in ra
               OK();
              return 2; // id trung khop
             }

    return 3;
 }



