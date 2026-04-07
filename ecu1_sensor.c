#include<xc.h>
#include "ecu_sensor.h"
#include "adc.h"
#include "can.h"
#include "msd_id.h"
#include "uart.h"
#define _XTAL_FREQ 20000000
#include "digital_keypad.h"

uint16_t get_speed()
{
    // Implement the speed function
        unsigned int new_val;
        new_val= (read_adc(CHANNEL4)*99)/1023;
        return new_val;   
  }

unsigned char get_gear_pos()
{
    // Implement the gear function
         static unsigned char indx=0;
        unsigned int key=read_digital_keypad(STATE_CHANGE);
        if(key==SWITCH1)
        {
            indx=(indx+1)%8;
        }
        else if(key==SWITCH2)
        {
            if(indx<=0) indx=0;
            else indx--;
        }
        return indx;

}