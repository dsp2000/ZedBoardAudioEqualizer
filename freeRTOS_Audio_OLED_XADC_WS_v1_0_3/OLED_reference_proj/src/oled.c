/* Credits to : http://embeddedcentric.com/customized-hardware-design-and-integration/ */

//#include "OLEDBuffer.h"
#include "ZedboardOLED.h"

/* Also refer to "\freeRTOS_Audio_OLED_XADC_bsp\ps7_cortexa9_0\libsrc\ZedboardOLED_v1_0"
 * for more options on writing to the OLED - Line or a character
 */
int main(void){

print_message("Hello",0);
//print_message("World",2);
//print_message("How cool is this",3);
//OLEDUpdateSelectedFrequencyBand(4);
//	clear_OLED();
//	OLEDClearBuffer();
while (1);

return 0;
}
