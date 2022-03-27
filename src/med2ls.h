#include "genesis.h"

#ifndef MED2LS_H
#define MED2LS_H

void MED2ls_Return();
void MED2ls_RetWacthDog();
u16 med2ls_usb_rd_ready();
u16 med2ls_usb_wr_ready();
u8 med2ls_usb_read();
u8 med2ls_usb_write(u8 data);

#endif // MED2LS_H
