CC=g++
DLIBS=-lwiringPi
epd:main.o epd2in7.o imagedata.o epdif.o font8.o font12.o font16.o font20.o font24.o epdpaint.o
	$(CC) -Wall -o epd main.o epd2in7.o imagedata.o epdif.o font8.o font12.o font16.o font20.o font24.o epdpaint.o $(DLIBS)
imagedata.o:imagedata.cpp imagedata.h 
	$(CC) -Wall -c imagedata.cpp $(DLIBS)
epd2in7.o:epd2in7.cpp epd2in7.h
	$(CC) -Wall -c epd2in7.cpp $(DLIBS)
epdif.o:epdif.cpp epdif.h
	$(CC) -Wall -c epdif.cpp $(DLIBS)
font8.o:fonts.h font8.cpp
	$(CC) -Wall -c font8.cpp
font12.o:fonts.h font12.cpp
	$(CC) -Wall -c font12.cpp
font16.o:fonts.h font16.cpp
	$(CC) -Wall -c font16.cpp
font20.o:fonts.h font20.cpp
	$(CC) -Wall -c font20.cpp
font24.o:fonts.h font24.cpp
	$(CC) -Wall -c font24.cpp
epdpaint.o:epdpaint.cpp epdpaint.h
	$(CC) -Wall -c epdpaint.cpp $(DLIBS)
main.o:main.cpp epd2in7.h imagedata.h epdpaint.h
	$(CC) -Wall -c main.cpp $(DLIBS)
clean:
	rm imagedata.o main.o epd2in7.o epdif.o font8.o font12.o font16.o font20.o font24.o epdpaint.o epd

