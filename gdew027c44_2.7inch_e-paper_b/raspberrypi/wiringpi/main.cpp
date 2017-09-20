/**
 *  @filename   :   main.cpp
 *  @brief      :   2.7inch e-paper display (B) demo
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     July 31 2017
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

#include <stdio.h>
#include <stdlib.h>
#include "epd2in7b.h"
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

    unsigned char* frame_buffer_black = (unsigned char*)malloc(epd.width / 8 * epd.height);
    unsigned char* frame_buffer_red = (unsigned char*)malloc(epd.width / 8 * epd.height);

    Paint paint_black(frame_buffer_black, epd.width, epd.height);
    Paint paint_red(frame_buffer_red, epd.width, epd.height);
    paint_black.Clear(UNCOLORED);
    paint_red.Clear(UNCOLORED);

    /* Draw something to the frame_buffer */
    /* For simplicity, the arguments are explicit numerical coordinates */
    paint_black.SetRotate(ROTATE_0);
    paint_red.SetRotate(ROTATE_0);
    paint_black.DrawStringAt(4, 50, "e-Paper Demo", &Font20, COLORED);
    paint_black.DrawRectangle(10, 130, 50, 180, COLORED);
    paint_black.DrawLine(10, 130, 50, 180, COLORED);
    paint_black.DrawLine(50, 130, 10, 180, COLORED);
    paint_black.DrawCircle(120, 150, 30, COLORED);
    paint_red.DrawFilledRectangle(10, 200, 50, 250, COLORED);
    paint_red.DrawFilledRectangle(0, 76, 176, 96, COLORED);
    paint_red.DrawFilledCircle(120, 220, 30, COLORED);
    paint_red.DrawStringAt(18, 80, "Hello world!", &Font16, UNCOLORED);
    
    /* Display the frame_buffer */
    epd.DisplayFrame(paint_black.GetImage(), paint_red.GetImage());

    /* Display the image buffer */
    epd.DisplayFrame(IMAGE_BLACK, IMAGE_RED);
    return 0;
}

