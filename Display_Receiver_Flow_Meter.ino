#include <SPI.h>        //SPI.h must be included as DMD is written by SPI (the IDE complains otherwise)
#include <DMD.h>        //
#include <TimerOne.h>   //
#include "SystemFont5x7.h"
#include "ComicSansMS18.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(4, 3); // RX, TX

//Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);
int fx, rumus; int hasil_baca_1, hasil_baca, kalibrasi_ulang, kalibrasi_ulang_2;
int kunci, tampung;
void ScanDMD()
{
  dmd.scanDisplayBySPI();
}

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;

void setup(void)
{

  //initialize TimerOne's interrupt/CPU usage used to scan and refresh the display
  Timer1.initialize( 3000 );           //period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker.
  Timer1.attachInterrupt( ScanDMD );   //attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()

  //clear/init the DMD pixels held in RAM
  dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)
  Serial.begin(9600);
  mySerial.begin(9600);
}

/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
  --------------------------------------------------------------------------------------*/
char pesanDisplay[10];

void loop(void) {


  int sensor = mySerial.parseInt();
  dtostrf(sensor, 2, 1, pesanDisplay);
  dmd.selectFont(ComicSansMS18);

  dmd.drawString( 0, -1, pesanDisplay, 3, GRAPHICS_NORMAL );




  delay(300);
  dmd.clearScreen( true );
  dmd.drawString( 0, -1, pesanDisplay, 3, GRAPHICS_NORMAL );
  
}
