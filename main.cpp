#include "mbed.h"
#include "LCD_DISCO_L476VG.h"

// initialize inputs and outputs
DigitalIn battery_0(PB_3); // external switch battery    charge level bit 0
DigitalIn battery_1(PB_6); // external switch battery    charge level bit 1
DigitalIn battery_2(PB_7); // external switch battery    charge level bit 2
DigitalIn battery_3(PA_1); // joystick left and external switch battery charge level bit 3
InterruptIn ac_avail(PA_2); // joystick right and external switch    1 if AC power is available
DigitalIn solar(PA_3); // joystick up and external switch    1 if solar panels currently charging battery
DigitalIn wind(PA_5); // joystick down and external switch    1 if wind turbine currently charging battery
InterruptIn switch_power(PA_0); // joystick center    manually switches power source and enables manual mode
DigitalOut ac_on(PB_2); // on board LED    switches AC power to the house on
DigitalOut dc_on(PE_8); // on board LED    switches DC power to the house on
DigitalOut to_grid(PD_0); // external LED  sell power back to Dominion

// peak times during winter are 6am-9am and 5pm-8pm   
int peak_start = 1607205600; // 5pm december 5
int peak_end = 1607216400;  //8pm december 5
int peak_start_m = 1607252400; // 6 am december 6
int peak_end_m = 1607263200; // 9 am december 6
int hr24 = 86400; // 24 hours in seconds
bool manual = false; // track whether in manual mode

//strings to display
// start with six spaces so no overlap
uint8_t battery[] = "      Battery Power";
uint8_t ac[] = "      DOMINION ENERGY";
uint8_t manstr[] = "      MANUAL MODE";
uint8_t ac_drop[] = "      LOST AC";
uint8_t autostr[] = "      AUTO MODE";
uint8_t sellstr[] = "      SELLING POWER";
uint16_t nscroll = 1;
uint16_t nspeed = 300;
LCD_DISCO_L476VG lcd;

void ac_lost() {
    // lose ac power
    dc_on = 1;
    ac_on = 0; 
    lcd.LCD_DISCO_L476VG::Clear();
    lcd.LCD_DISCO_L476VG::ScrollSentence(ac_drop, nscroll, nspeed);
    lcd.LCD_DISCO_L476VG::Clear();
    lcd.LCD_DISCO_L476VG::ScrollSentence(battery, nscroll, nspeed);
    lcd.LCD_DISCO_L476VG::Clear();
    }

void manmode() {
    if(!manual) { // if not already in manual mode before the button was pressed
        if(dc_on) {
            ac_on = 1;
            dc_on = 0;
            lcd.LCD_DISCO_L476VG::Clear();
            lcd.LCD_DISCO_L476VG::ScrollSentence(ac, nscroll, nspeed);
        } else {
            dc_on = 1;
            ac_on = 0;
            lcd.LCD_DISCO_L476VG::Clear();
            lcd.LCD_DISCO_L476VG::ScrollSentence(battery, nscroll, nspeed);
        }
        lcd.LCD_DISCO_L476VG::Clear();
        lcd.LCD_DISCO_L476VG::ScrollSentence(manstr, nscroll, nspeed); // display manual when entering
        
    } else {
        lcd.LCD_DISCO_L476VG::Clear();
        lcd.LCD_DISCO_L476VG::ScrollSentence(autostr, nscroll, nspeed); // display auto when exiting manual
        lcd.LCD_DISCO_L476VG::Clear();
    }
    manual = !manual; // switch manual on or off
}

// main() runs in its own thread in the OS
int main()
{
    // enable interrupts
    ac_avail.fall(&ac_lost);
    switch_power.rise(&manmode);
    
    if(ac_avail){ // initialize to AC power if ac is avialable
        ac_on = 1; 
        dc_on = 0;
    } else { // else DC
        ac_on = 0;
        dc_on = 1;
    }
    
    
    set_time(1607205300); // 4:55pm local on december 5th

    
    while (true) {
        time_t seconds = time(NULL);
        if(!(ac_on || dc_on)) { // In case both were turned off set to ac
            ac_on = 1;
            dc_on = 0;
        }
        if(manual){ // display if in manual mode
            lcd.LCD_DISCO_L476VG::Clear();
            lcd.LCD_DISCO_L476VG::ScrollSentence(manstr, nscroll, nspeed);
        }
        if(ac_on) {
            lcd.LCD_DISCO_L476VG::Clear();
            lcd.LCD_DISCO_L476VG::ScrollSentence(ac, nscroll, nspeed);
            lcd.LCD_DISCO_L476VG::Clear();
            
            dc_on = 0; // turn off dc if both are on
            to_grid = 0; // charge battery rather than feed grid while on ac
            
            if(!manual){ // if in auto mode
                if(battery_3 && battery_2 && battery_1 && battery_0) { // battery full need to use
                dc_on = 1;
                ac_on = 0;  
                lcd.LCD_DISCO_L476VG::Clear();
                lcd.LCD_DISCO_L476VG::ScrollSentence(battery, 1, 400);
                lcd.LCD_DISCO_L476VG::Clear();              
                }
                      
                if(((seconds - peak_start) % hr24) < ((peak_end - peak_start) % hr24) || ((seconds - peak_start_m) % hr24) < ((peak_end_m - peak_start_m) % hr24)) { // if during peak hours
                    if(battery_3 || ((solar || wind) && battery_2 && battery_1 && battery_0)){ // make sure battery is sufficently charged or solar/wind charging battery
                        dc_on = 1;
                        ac_on = 0;
                        lcd.LCD_DISCO_L476VG::Clear();
                        lcd.LCD_DISCO_L476VG::ScrollSentence(battery, 1, 400);
                        lcd.LCD_DISCO_L476VG::Clear();
                    }
                }                
            }

            
        } else if(dc_on) {
            lcd.LCD_DISCO_L476VG::Clear();
            lcd.LCD_DISCO_L476VG::ScrollSentence(battery, 1, 400);
            lcd.LCD_DISCO_L476VG::Clear();
            
            ac_on = 0; // in case both are on
            if(!manual) {
                if(ac_avail && !battery_3 && !((solar || wind) && battery_2 && battery_1 && battery_0)) { // if battery depleted
                    ac_on = 1;
                    dc_on = 0;
                    lcd.LCD_DISCO_L476VG::Clear();
                    lcd.LCD_DISCO_L476VG::ScrollSentence(ac, nscroll, nspeed);
                    lcd.LCD_DISCO_L476VG::Clear();
                }
                if(ac_avail && ((seconds - peak_start) % hr24) > ((peak_end - peak_start) % hr24) && ((seconds - peak_start_m) % hr24) > ((peak_end_m - peak_start_m) % hr24)) { // ac is available and outside peak time
                    if((!battery_1 && !battery_0) || !battery_2) { // only if battery is below 80%
                        ac_on = 1;
                        dc_on = 0;
                        lcd.LCD_DISCO_L476VG::Clear();
                        lcd.LCD_DISCO_L476VG::ScrollSentence(ac, nscroll, nspeed);
                         lcd.LCD_DISCO_L476VG::Clear();
                    }
                }
            }
            if (ac_avail && (solar || wind) && battery_3 && battery_2 && battery_1) { // battery at least 93% and charging while on battery
                to_grid = 1;                               // sell excess power back
                lcd.LCD_DISCO_L476VG::Clear();
                lcd.LCD_DISCO_L476VG::ScrollSentence(sellstr, nscroll, nspeed);
                lcd.LCD_DISCO_L476VG::Clear();
            } else {
                to_grid = 0;        // stop selling power and charge battery
            }
        } 
        ThisThread::sleep_for(300s); // sleep for 5 minutes then check again
    }
}

