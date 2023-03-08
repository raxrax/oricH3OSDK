/**
 * h3.h library
 * rax@2020
 * This library emulates a graphical mode into LORES characters. Screen size: 60x64 px
 **/

#ifndef __H3H__
#define __H3H__

#define MAX_X 60
#define MAX_Y 64

#define MAX_CHARS_PER_X 10
#define MAX_CHARS_PER_Y 8

extern void h3ShowCanvas(unsigned char x, unsigned char y);
extern void h3Cls();
extern void h3SetFB(unsigned char fb);
extern void h3SetPattern(unsigned char p);
extern void h3Curset(unsigned char x, unsigned char y);
extern void h3Save();
extern void h3Restore();
extern void h3Char(unsigned char x, unsigned char y, unsigned char c);
extern void h3String(unsigned char x, unsigned char y, char *str);
extern void h3Circle(int xm, int ym, int r);
extern void h3Draw(int x0, int y0, int x1, int y1);

#endif