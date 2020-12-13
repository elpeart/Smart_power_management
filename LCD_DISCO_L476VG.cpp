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

#include "LCD_DISCO_L476VG.h"

// Constructor
LCD_DISCO_L476VG::LCD_DISCO_L476VG()
{
    BSP_LCD_GLASS_Init();
}

// Destructor
LCD_DISCO_L476VG::~LCD_DISCO_L476VG()
{
    BSP_LCD_GLASS_DeInit();
}

//=================================================================================================================
// Public methods
//=================================================================================================================

void LCD_DISCO_L476VG::Init(void)
{
    BSP_LCD_GLASS_Init();
}

void LCD_DISCO_L476VG::DeInit(void)
{
    BSP_LCD_GLASS_DeInit();
}

void LCD_DISCO_L476VG::BlinkConfig(uint32_t BlinkMode, uint32_t BlinkFrequency)
{
    BSP_LCD_GLASS_BlinkConfig(BlinkMode, BlinkFrequency);
}

void LCD_DISCO_L476VG::Contrast(uint32_t Contrast)
{
    BSP_LCD_GLASS_Contrast(Contrast);
}

void LCD_DISCO_L476VG::DisplayChar(uint8_t* ch, Point_Typedef Point, DoublePoint_Typedef Column, DigitPosition_Typedef Position)
{
    BSP_LCD_GLASS_DisplayChar(ch, Point, Column, Position);
}

void LCD_DISCO_L476VG::DisplayString(uint8_t* ptr)
{
    BSP_LCD_GLASS_DisplayString(ptr);
}

void LCD_DISCO_L476VG::DisplayStrDeci(uint16_t* ptr)
{
    BSP_LCD_GLASS_DisplayStrDeci(ptr);
}

void LCD_DISCO_L476VG::ScrollSentence(uint8_t* ptr, uint16_t nScroll, uint16_t ScrollSpeed)
{
    BSP_LCD_GLASS_ScrollSentence(ptr, nScroll, ScrollSpeed);
}

void LCD_DISCO_L476VG::DisplayBar(uint32_t BarId)
{
    BSP_LCD_GLASS_DisplayBar(BarId);
}

void LCD_DISCO_L476VG::ClearBar(uint32_t BarId)
{
    BSP_LCD_GLASS_ClearBar(BarId);
}

void LCD_DISCO_L476VG::BarLevelConfig(uint8_t BarLevel)
{
    BSP_LCD_GLASS_BarLevelConfig(BarLevel);
}

void LCD_DISCO_L476VG::Clear(void)
{
    BSP_LCD_GLASS_Clear();
}

//=================================================================================================================
// Private methods
//=================================================================================================================
