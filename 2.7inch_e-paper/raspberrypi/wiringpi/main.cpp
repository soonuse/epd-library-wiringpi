/**
 *  @filename   :   main.cpp
 *  @brief      :   2.7inch e-paper display demo
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
#include "epd2in7.h"
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

    unsigned char* frame_buffer = (unsigned char*)malloc(epd.width / 8 * epd.height);

    Paint paint(frame_buffer, epd.width, epd.height);
    paint.Clear(UNCOLORED);

    /* Draw something to the frame_buffer */
    /* For simplicity, the arguments are explicit numerical coordinates */
    paint.SetRotate(ROTATE_0);
    paint.DrawStringAt(4, 50, "e-Paper Demo", &Font20, COLORED);
    paint.DrawRectangle(10, 130, 50, 180, COLORED);
    paint.DrawLine(10, 130, 50, 180, COLORED);
    paint.DrawLine(50, 130, 10, 180, COLORED);
    paint.DrawCircle(120, 150, 30, COLORED);
    paint.DrawFilledRectangle(10, 200, 50, 250, COLORED);
    paint.DrawFilledRectangle(0, 76, 176, 96, COLORED);
    paint.DrawFilledCircle(120, 220, 30, COLORED);
    paint.DrawStringAt(18, 80, "Hello world!", &Font16, UNCOLORED);
    
    /* Display the frame_buffer */
    epd.DisplayFrame(paint.GetImage());

    /* Display the image buffer */
    epd.DisplayFrame(IMAGE_DATA);
    return 0;
}

