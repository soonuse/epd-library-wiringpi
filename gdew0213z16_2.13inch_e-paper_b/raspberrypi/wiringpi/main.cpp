/**
 *  @filename   :   main.cpp
 *  @brief      :   2.13inch e-paper display (B) demo
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
#include "epd2in13b.h"
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
    paint_black.SetRotate(ROTATE_0);
    paint_red.SetRotate(ROTATE_0);
    paint_black.DrawRectangle(10, 60, 50, 100, COLORED);
    paint_black.DrawLine(10, 60, 50, 100, COLORED);
    paint_black.DrawLine(50, 60, 10, 100, COLORED);
    paint_black.DrawCircle(80, 80, 15, COLORED);
    paint_red.DrawFilledRectangle(10, 120, 50, 180, COLORED);
    paint_red.DrawFilledRectangle(0, 6, 128, 26, COLORED);
    paint_red.DrawFilledCircle(80, 150, 15, COLORED);

    /*Write strings to the buffer */
    paint_black.DrawStringAt(4, 30, "e-Paper Demo", &Font12, COLORED);
    paint_red.DrawStringAt(6, 10, "Hello world!", &Font12, UNCOLORED);
   
    /* Display the frame_buffer */
    epd.DisplayFrame(frame_black, frame_red);

    /* Display the image buffer */
    epd.DisplayFrame(IMAGE_BLACK, IMAGE_RED);

    epd.Sleep();
    return 0;
}

