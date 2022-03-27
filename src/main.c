#include <genesis.h>
#include "med2ls.h"

void Joy_Handler(u16 joy, u16 changed, u16 state)
{
    if ((joy == JOY_1) || (joy == JOY_2))
    {
        if (state & BUTTON_MODE)
        {
            MED2ls_Return(); // Exit. Those Return to EverDrive Main menu from here for example...
        }
    }
}

int main(bool hardReset)
{
    JOY_setEventHandler(&Joy_Handler);

    VDP_setScreenWidth320();
    VDP_setHInterrupt(0);
    VDP_setHilightShadow(0);
    VDP_setTextPalette(0);
    VDP_setPaletteColor(0, 0xCCCC99);
    VDP_drawText("Debuging Mega EverDrive 2 Tool", 5, 9);
    VDP_drawText("+ Softreturn to Main menu by inside cmd;", 0, 11);
    VDP_drawText("+ Automatic reset intime next load ROM;", 0, 12);
    VDP_drawText("+ Escape to Main menu by USB sequence.", 0, 13);

    VDP_drawText("Press 'Mode'-key to exit ...", 2, 15);
    VDP_drawText("... or send sequence over USB", 2, 16);

    while (TRUE)
    {
        MED2ls_RetWacthDog(); // Put this in main-loop for monitoring commands from USB

        // any code do here
        // ...

        // always call this method at the end of the frame
        SYS_doVBlankProcess();
    }

    return 0;
}
