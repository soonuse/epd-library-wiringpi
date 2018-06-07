/**
 *  @filename   :   main.cpp
 *  @brief      :   1.54inch e-paper display (C) demo
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     July 24 2017
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

#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include "epd1in54c.h"
#include "imagedata.h"
#include "epdpaint.h"

#define COLORED      1
#define UNCOLORED    0

int main(void)
{
    Epd epd;
    if (epd.Init() != 0) {
        printf("e-Paper init failed\n");
        return -1;
    }

    unsigned char* frame_black = (unsigned char*)malloc(epd.width * epd.height / 8);
    unsigned char* frame_yellow = (unsigned char*)malloc(epd.width * epd.height / 8);

    Paint paint_black(frame_black, epd.width, epd.height);
    Paint paint_yellow(frame_yellow, epd.width, epd.height);
    paint_black.Clear(UNCOLORED);
    paint_yellow.Clear(UNCOLORED);

    /* Draw something to the frame buffer */
    /* For simplicity, the arguments are explicit numerical coordinates */
    paint_black.DrawRectangle(10, 60, 50, 110, COLORED);
    paint_black.DrawLine(10, 60, 50, 110, COLORED);
    paint_black.DrawLine(50, 60, 10, 110, COLORED);
    paint_black.DrawCircle(120, 80, 30, COLORED);
//    paint_yellow.DrawFilledRectangle(10, 130, 50, 180, COLORED);
    paint_yellow.DrawFilledRectangle(0, 6, 152, 26, COLORED);
//    paint_yellow.DrawFilledCircle(120, 150, 30, COLORED);

    /*Write strings to the buffer */
    paint_black.DrawStringAt(10, 30, "e-Paper Demo", &Font16, COLORED);
    paint_yellow.DrawStringAt(18, 10, "Hello world!", &Font16, UNCOLORED);
   
    /* Display the frame buffer */
    epd.DisplayFrame(frame_black, frame_yellow);
    
    delay(2000);
    /* Display the image buffer */
    epd.DisplayFrame(IMAGE_BLACK, IMAGE_YELLOW);
    return 0;
}

