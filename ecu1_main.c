#include<xc.h>
#include "adc.h"
#include "can.h"
#include "ecu_sensor.h"
#include "msd_id.h"
#include "uart.h"
#include <string.h>

#define _XTAL_FREQ 20000000

static const char *gears[8] = {"NG", "G1", "G2", "G3", "G4", "G5", "G6", "GR"};

void my_itoa(unsigned int speed, unsigned char res[])
{
    int i = 0, j = 0;
    unsigned char temp[10];

    if (speed == 0)
    {
        res[0] = '0';
        res[1] = '\0';
        return;
    }

    while (speed > 0)
    {
        temp[i++] = (speed % 10) + '0';
        speed = speed / 10;
    }

    for (j = 0; j < i; j++)
    {
        res[j] = temp[i - j - 1];
    }

    res[i] = '\0';
}

void init_config()
{
    init_adc();
    init_can();
    init_digital_keypad();
    init_uart();
}

int main()
{
    init_config();

    unsigned int speed;
    unsigned char gear;
    unsigned char str[4];
    str[0]='4';
     str[1]='4';
      str[2]='\0';
    

    while (1)
    {
        // Get speed
        speed = get_speed();

        // Get gear
        gear = get_gear_pos();

        // Safety check for gear
        if (gear > 7)
        {
            gear = 0; // Default to Neutral Gear
        }

        // Convert speed to string
        my_itoa(speed, str);

        // UART Display 
        puts("Speed: ");
        puts(str);
        puts("  Gear: ");
        puts(gears[gear]);
        puts("\r\n");
        can_transmit(SPEED_MSG_ID, str, 2);
         __delay_ms(100); 
        can_transmit(GEAR_MSG_ID, gears[gear], 2);

        __delay_ms(100);  // safer delay
          

    }
}