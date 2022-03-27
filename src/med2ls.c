#include "med2ls.h"

#define REG_USB_BUFF *((volatile u16 *)0xA130E2) // usb buffer register
#define REG_USB_STAT *((volatile u16 *)0xA130E4) // usb status register

#define USB_WR_RDY 0x0002 // usb write ready bit
#define USB_RD_RDY 0x0004 // usb read ready bit

// magic data block in RAM reinitializing 68k CPU while being used as code
volatile u16 magic[] = {
    0x46FC, 0x2700, // move.w #0x2700, sr
    0x4E70,         // reset
    0x9BCD,         // sub.l a5, a5
    0x4E65,         // move.l a5, usp
    0x2E5D,         // move.l (a5)+, a7
    0x2A55,         // move.l (a5), a5
    0x4ED5          // jmp (a5)
};

void MED2ls_Return()
{
    goto *&magic;
}

void MED2ls_RetWacthDog()
{
    static u32 buff;

    if (!(~JOY_readJoypad(JOY_1) & (BUTTON_START | BUTTON_A | BUTTON_B | BUTTON_C))) // Start + A + B + C
    {
        MED2ls_Return();
    }

    if (med2ls_usb_rd_ready())
    {
        buff = buff << 8;
        buff = buff | med2ls_usb_read();

        if (buff == 0x20202A7E) // "  *~" - sequence from other PC-util, without answer
        {
            MED2ls_Return();
        }

        if (buff == 0x20202A54) // "  *T" - sequence from mega-usb util for port detect
        {
            while (med2ls_usb_wr_ready() == 0)
                ;
            med2ls_usb_write('k'); // correct answer ...
            MED2ls_Return();
        }
    }
}

u16 med2ls_usb_rd_ready()
{
    return REG_USB_STAT & USB_RD_RDY;
}

u16 med2ls_usb_wr_ready()
{
    return REG_USB_STAT & USB_WR_RDY;
}

u8 med2ls_usb_read()
{
    return REG_USB_BUFF;
}

u8 med2ls_usb_write(u8 data)
{
    return REG_USB_BUFF = data;
}
