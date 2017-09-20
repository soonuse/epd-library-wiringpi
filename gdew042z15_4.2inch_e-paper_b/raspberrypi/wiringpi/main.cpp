/**
 *  @filename   :   main.cpp
 *  @brief      :   4.2inch e-paper display (B) demo
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     August 15 2017
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
#include <stdio.h>
#include "epd4in2b.h"
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
    unsigned char* frame_red = (unsigned char*)malloc(epd.width * epd.height / 8);

    Paint paint_black(frame_black, epd.width, epd.height);
    Paint paint_red(frame_red, epd.width, epd.height);
    paint_black.Clear(UNCOLORED);
    paint_red.Clear(UNCOLORED);

    /* Draw something to the frame buffer */
    /* For simplicity, the arguments are explicit numerical coordinates */
    paint_black.DrawRectangle(20, 80, 180, 280, COLORED);
    paint_black.DrawLine(20, 80, 180, 280, COLORED);
    paint_black.DrawLine(180, 80, 20, 280, COLORED);
    paint_red.DrawFilledRectangle(200, 80, 360, 280, COLORED);
    paint_red.DrawCircle(300, 160, 60, UNCOLORED);
    paint_red.DrawFilledCircle(90, 210, 30, COLORED);

    /* Write strings to the buffer */
    paint_red.DrawFilledRectangle(0, 6, 400, 30, COLORED);
    paint_red.DrawStringAt(100, 10, "Hello world!", &Font24, UNCOLORED);
    paint_black.DrawStringAt(100, 40, "e-Paper Demo", &Font24, COLORED);
   
    /* Display the frame_buffer */
    epd.DisplayFrame(frame_black, frame_red);

    /* Display the image buffer */
    epd.DisplayFrame(IMAGE_BLACK, IMAGE_RED);

    epd.Sleep();
    return 0;
}

