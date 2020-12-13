/* Copyright (c) 2010-2011 mbed.org, MIT License
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or
* substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef __LCD_DISCO_L476VG_H
#define __LCD_DISCO_L476VG_H

#ifdef TARGET_DISCO_L476VG

#include "mbed.h"
#include "stm32l476g_discovery_glass_lcd.h"

/*
 Class to drive the LCD Glass display (GH08172T device)
 present on DISCO_L476VG board.

 Usage:
 
#include "mbed.h"
#include "LCD_DISCO_L476VG.h"

LCD_DISCO_L476VG lcd;

int main()
{
    uint32_t temp = 0;
    uint8_t stemp[7] = {0};
 
    lcd.Clear();
    lcd.DisplayString((uint8_t *)"Hello");
 
    while(1)
    {
        sprintf((char *)stemp, "val=%d", temp);
        lcd.DisplayString(stemp);
        lcd.BarLevelConfig((uint8_t)temp);
        temp++;
        if (temp > 4) temp = 0;
        wait(1);
    }
}
*/
class LCD_DISCO_L476VG
{
public:
    //! Constructor
    LCD_DISCO_L476VG();

    //! Destructor
    ~LCD_DISCO_L476VG();

    /**
      * @brief  Initialize the LCD GLASS relative GPIO port IOs and LCD peripheral.
      * @retval None
      */
    void Init(void);

    /**
      * @brief  DeInitialize the LCD GLASS relative GPIO port IOs and LCD peripheral.
      * @retval None
      */
    void DeInit(void);
    
    /**
      * @brief  Configure the LCD Blink mode and Blink frequency.
      * @param  BlinkMode: specifies the LCD blink mode.
      *   This parameter can be one of the following values:
      *     @arg LCD_BLINKMODE_OFF:           Blink disabled
      *     @arg LCD_BLINKMODE_SEG0_COM0:     Blink enabled on SEG[0], COM[0] (1 pixel)
      *     @arg LCD_BLINKMODE_SEG0_ALLCOM:   Blink enabled on SEG[0], all COM (up to 8 
      *                                       pixels according to the programmed duty)
      *     @arg LCD_BLINKMODE_ALLSEG_ALLCOM: Blink enabled on all SEG and all COM 
      *                                       (all pixels)
      * @param  BlinkFrequency: specifies the LCD blink frequency.
      *     @arg LCD_BLINKFREQUENCY_DIV8:    The Blink frequency = fLcd/8
      *     @arg LCD_BLINKFREQUENCY_DIV16:   The Blink frequency = fLcd/16
      *     @arg LCD_BLINKFREQUENCY_DIV32:   The Blink frequency = fLcd/32
      *     @arg LCD_BLINKFREQUENCY_DIV64:   The Blink frequency = fLcd/64 
      *     @arg LCD_BLINKFREQUENCY_DIV128:  The Blink frequency = fLcd/128
      *     @arg LCD_BLINKFREQUENCY_DIV256:  The Blink frequency = fLcd/256
      *     @arg LCD_BLINKFREQUENCY_DIV512:  The Blink frequency = fLcd/512
      *     @arg LCD_BLINKFREQUENCY_DIV1024: The Blink frequency = fLcd/1024
      * @retval None
      */
    void BlinkConfig(uint32_t BlinkMode, uint32_t BlinkFrequency);
    
    /**
      * @brief  Configure the LCD contrast.
      * @param  Contrast: specifies the LCD contrast value.
      *   This parameter can be one of the following values:
      *     @arg LCD_CONTRASTLEVEL_0: Maximum Voltage = 2.60V
      *     @arg LCD_CONTRASTLEVEL_1: Maximum Voltage = 2.73V
      *     @arg LCD_CONTRASTLEVEL_2: Maximum Voltage = 2.86V
      *     @arg LCD_CONTRASTLEVEL_3: Maximum Voltage = 2.99V
      *     @arg LCD_CONTRASTLEVEL_4: Maximum Voltage = 3.12V
      *     @arg LCD_CONTRASTLEVEL_5: Maximum Voltage = 3.25V
      *     @arg LCD_CONTRASTLEVEL_6: Maximum Voltage = 3.38V
      *     @arg LCD_CONTRASTLEVEL_7: Maximum Voltage = 3.51V
      * @retval None
      */
    void Contrast(uint32_t Contrast);
    
    /**
      * @brief  Write a character in the LCD RAM buffer.
      * @param  ch: The character to display.
      * @param  Point: A point to add in front of char.
      *          This parameter can be one of the following values:  
      *              @arg POINT_OFF: No point to add in front of char.
      *              @arg POINT_ON: Add a point in front of char.
      * @param  Colon: Flag indicating if a colon character has to be added in front 
      *                     of displayed character.
      *          This parameter can be one of the following values:
      *              @arg DOUBLEPOINT_OFF: No colon to add in back of char.
      *              @arg DOUBLEPOINT_ON: Add an colon in back of char.
      * @param  Position: Position in the LCD of the character to write.
      *                   This parameter can be any value in range [1:6].
      * @retval None
      * @note   Required preconditions: The LCD should be cleared before to start the
      *         write operation.
      */
    void DisplayChar(uint8_t* ch, Point_Typedef Point, DoublePoint_Typedef Column, DigitPosition_Typedef Position);
    
    /**
      * @brief  Write a character string in the LCD RAM buffer.
      * @param  ptr: Pointer to string to display on the LCD Glass.
      * @retval None
      */
    void DisplayString(uint8_t* ptr);
    
    /**
      * @brief  Write a character string with decimal point in the LCD RAM buffer.
      * @param  ptr: Pointer to string to display on the LCD Glass.
      * @retval None
      * @note Required preconditions: Char is ASCCI value "ORed" with decimal point or Colon flag
      */
    void DisplayStrDeci(uint16_t* ptr);
    
    /**
      * @brief  Display a string in scrolling mode
      * @param  ptr: Pointer to string to display on the LCD Glass.
      * @param  nScroll: Specifies how many time the message will be scrolled
      * @param  ScrollSpeed : Specifies the speed of the scroll, low value gives
      *         higher speed 
      * @retval None
      * @note   Required preconditions: The LCD should be cleared before to start the
      *         write operation.
      */
    void ScrollSentence(uint8_t* ptr, uint16_t nScroll, uint16_t ScrollSpeed);
    
    /**
      * @brief Display one or several bar in LCD frame buffer.
      * @param BarId: specifies the LCD GLASS Bar to display
      *     This parameter can be one of the following values:
      *     @arg BAR0: LCD GLASS Bar 0
      *     @arg BAR0: LCD GLASS Bar 1
      *     @arg BAR0: LCD GLASS Bar 2
      *     @arg BAR0: LCD GLASS Bar 3
      * @retval None
      */
    void DisplayBar(uint32_t BarId);
    
    /**
      * @brief Clear one or several bar in LCD frame buffer. 
      * @param BarId: specifies the LCD GLASS Bar to display
      *     This parameter can be combination of one of the following values:
      *     @arg LCD_BAR_0: LCD GLASS Bar 0
      *     @arg LCD_BAR_1: LCD GLASS Bar 1
      *     @arg LCD_BAR_2: LCD GLASS Bar 2
      *     @arg LCD_BAR_3: LCD GLASS Bar 3
      * @retval None
      */
    void ClearBar(uint32_t BarId);
    
    /**
      * @brief Configure the bar level on LCD by writing bar value in LCD frame buffer.
      * @param BarLevel: specifies the LCD GLASS Battery Level.
      *     This parameter can be one of the following values:
      *     @arg BATTERYLEVEL_OFF: LCD GLASS Battery Empty
      *     @arg BATTERYLEVEL_1_4: LCD GLASS Battery 1/4 Full
      *     @arg BATTERYLEVEL_1_2: LCD GLASS Battery 1/2 Full
      *     @arg BATTERYLEVEL_3_4: LCD GLASS Battery 3/4 Full
      *     @arg BATTERYLEVEL_FULL: LCD GLASS Battery Full
      * @retval None
      */
    void BarLevelConfig(uint8_t BarLevel);
    
    /**
      * @brief  Clear the whole LCD RAM buffer.
      * @retval None
      */
    void Clear(void);

private:

};

#else
#error "This class must be used with DISCO_L476VG board only."
#endif // TARGET_DISCO_L476VG

#endif
