/**
 *  @filename   :   epd2in13b.cpp
 *  @brief      :   Implements for Dual-color e-paper library
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     August 10 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdlib.h>
#include "epd2in13b.h"
#include "epdif.h"

Epd::~Epd() {
};

Epd::Epd() {
    reset_pin = RST_PIN;
    dc_pin = DC_PIN;
    cs_pin = CS_PIN;
    busy_pin = BUSY_PIN;
    width = EPD_WIDTH;
    height = EPD_HEIGHT;
};

int Epd::Init(void) {
    /* this calls the peripheral hardware interface, see epdif */
    if (IfInit() != 0) {
        return -1;
    }
    /* EPD hardware init start */
    Reset();
    SendCommand(BOOSTER_SOFT_START);
    SendData(0x17);
    SendData(0x17);
    SendData(0x17);
    SendCommand(POWER_ON);
    WaitUntilIdle();
    SendCommand(PANEL_SETTING);
    SendData(0x8F);
    SendCommand(VCOM_AND_DATA_INTERVAL_SETTING);
    SendData(0x37);
    SendCommand(RESOLUTION_SETTING);
    SendData(0x68);     // width: 104
    SendData(0x00);
    SendData(0xD4);     // height: 212
    /* EPD hardware init end */
    return 0;
}

/**
 *  @brief: basic function for sending commands
 */
void Epd::SendCommand(unsigned char command) {
    DigitalWrite(dc_pin, LOW);
    SpiTransfer(command);
}

/**
 *  @brief: basic function for sending data
 */
void Epd::SendData(unsigned char data) {
    DigitalWrite(dc_pin, HIGH);
    SpiTransfer(data);
}

/**
 *  @brief: Wait until the busy_pin goes HIGH
 */
void Epd::WaitUntilIdle(void) {
    while(DigitalRead(busy_pin) == 0) {      //0: busy, 1: idle
        DelayMs(100);
    }
}

/**
 *  @brief: module reset.
 *          often used to awaken the module in deep sleep,
 *          see Epd::Sleep();
 */
void Epd::Reset(void) {
    DigitalWrite(reset_pin, LOW);            //module reset    
    DelayMs(200);
    DigitalWrite(reset_pin, HIGH);
    DelayMs(200);    
}

/**
 *  @brief: display the frame buffers
 */
void Epd::DisplayFrame(const unsigned char* frame_buffer_black, const unsigned char* frame_buffer_red) {
    if (frame_buffer_black != NULL) {
        SendCommand(DATA_START_TRANSMISSION_1);
        DelayMs(2);
        for (int i = 0; i < this->width * this->height / 8; i++) {
            SendData(frame_buffer_black[i]);
        }
        DelayMs(2);
    }
    if (frame_buffer_red != NULL) {
        SendCommand(DATA_START_TRANSMISSION_2);
        DelayMs(2);
        for (int i = 0; i < this->width * this->height / 8; i++) {
            SendData(frame_buffer_red[i]);
        }
        DelayMs(2);
    }
    SendCommand(DISPLAY_REFRESH);
    WaitUntilIdle();
}

/**
 *  @brief: After this command is transmitted, the chip would enter the 
 *          deep-sleep mode to save power. 
 *          The deep sleep mode would return to standby by hardware reset. 
 *          The only one parameter is a check code, the command would be
 *          executed if check code = 0xA5. 
 *          You can use Epd::Init() to awaken
 */
void Epd::Sleep() {
    SendCommand(POWER_OFF);
    WaitUntilIdle();
    SendCommand(DEEP_SLEEP);
    SendData(0xA5);     // check code
}

/* END OF FILE */


