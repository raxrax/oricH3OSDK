#include <lib.h>


#include "h3.h"
#include "common.c"

unsigned char copyright[] = "rax@sofia2020";

unsigned char i, x, y;

void border()
{
   //    h3Draw(0, 0, 63, 0);
   //   // h3Draw(59, 0, 59, 63);
   //    h3Draw(0, 63, 59, 63);
   //   // h3Draw(0, 63, 0, 0);

   h3Line(0, 0, 5, 0);
   h3Line(0, 0, 0, 5);

   h3Line(54, 0, 59, 0);
   h3Line(59, 0, 59, 5);

   h3Line(59, 63, 59, 58);
   h3Line(59, 63, 54, 63);

   h3Line(0, 63, 0, 58);
   h3Line(0, 63, 5, 63);
}

void intro()
{
   h3Cls();
   border();
   h3String(5, 13, "Demo program");
   h3String(15, 33, "-= H3 =-");
   h3String(5, 50, "-Press a key-");
   stars();

   h3Cls();
   border();
   h3String(5, 3, "LIB: h3.h");
   h3Line(5, 10, 40, 10);
   // h3Draw(5, 11, 40, 11);
   h3String(5, 20, "This library\nemulates\ngraphic mode\n(60x64 px)\ninto lores\nchars");
   get();
}

void points()
{
   h3Cls();
   border();
   h3String(5, 5, "-= Test 1 =-");
   h3String(5, 20, "Random points");
   h3String(5, 50, "-Press a key-");
   get();

   for (i = 0; i < 255; ++i)
   {
      h3Curset(rand() % MAX_X, rand() % MAX_Y);
   }

   get();
}

void lines()
{
   h3SetFB(1);
   h3Cls();
   border();
   h3String(5, 5, "-= Test 2 =-");
   h3String(5, 20, "Random lines");
   h3String(5, 50, "-Press a key-");
   get();

   for (i = 0; i < 55; ++i)
   {
      h3Line(rand() % MAX_X, rand() % MAX_Y, rand() % MAX_X, rand() % MAX_Y);
   }

   get();
}

void circles()
{
   h3SetFB(1);
   h3Cls();
   border();
   h3String(5, 5, "-= Test 3 =-");
   h3String(15, 20, "Circles");

   h3String(5, 50, "-Press a key-");
   get();

   for (i = 0; i < 30; i += 3)
   {
      h3Circle(MAX_X / 2, MAX_Y / 2, i);
   }

   get();
}

void demoPattern(unsigned char p)
{
   h3SetPattern(p);
   h3Cls();
 
   for (i = 14; i < MAX_Y; i += 4)
   {
      h3Draw(0, i, 59, i);
   }
   get();
   h3Cls();
   for (i = 0; i < MAX_Y / 2; i += 4)
   {
      h3Circle(MAX_X / 2, MAX_Y / 2, i);
   }
   get();
}

void patternDemo()
{
   h3Cls();
   border();
   h3String(5, 5, "-= Test 4 =-");
   h3String(5, 14, "Pattern");
   h3String(5, 23, "This command\naffects:\ndraw() and\ncircle()");

   h3String(5, 50, "-Press a key-");
   get();
   demoPattern(85);
   demoPattern(204);
   demoPattern(4);
   h3SetPattern(255);
}

void rainDemo()
{
   h3Cls();
   border();
   h3String(5, 5, "-= Test 5 =-");
   h3String(20, 14, "Rain :)");

   h3String(5, 50, "-Press a key-");
   get();
   rain();
}

void commands()
{
   h3Cls();
   border();
   h3String(5, 2, "Commands:");
   h3String(5, 9, "h3Cls();");
   h3String(5, 9 + 6 * 1, "h3Curset();");
   h3String(5, 9 + 6 * 2, "h3Draw());");
   h3String(5, 9 + 6 * 3, "h3Circle();");
   h3String(5, 9 + 6 * 4, "h3Char();");
   h3String(5, 9 + 6 * 5, "h3String();");
   h3String(5, 9 + 6 * 6, "h3Save();");
   h3String(5, 9 + 6 * 7, "h3Restore();");
   h3String(5, 9 + 6 * 8, "-Press a key-");

   stars();

   h3Cls();
   border();
   h3String(5, 9, "h3SetFB();");
   h3String(5, 9 + 6 * 1, "h3SetPattern()");
   h3String(5, 9 + 6 * 2, "h3ShowCanvas()");
   h3String(5, 9 + 6 * 3, "");
   h3String(5, 9 + 6 * 4, "");
   h3String(5, 9 + 6 * 5, "");
   h3String(5, 9 + 6 * 6, "");
   h3String(5, 9 + 6 * 7, "");
   h3String(5, 9 + 6 * 8, "-Press a key-");

   stars();
}

void about()
{
   h3Cls();
   h3String(10, 25, "RAX @ 2020");

   h3String(5, 50, "-Press a key-");

   stars();
}

void main()
{
   cls();
   paper(0);
   ink(7);
   poke(0x26a, 10);

   for (i = 0; i < 98; i++)
   {
      printf("text mode   ");
   }

   h3Cls();

   h3ShowCanvas(5, 4);
   h3ShowCanvas(26, 4);
   h3ShowCanvas(5, 16);
   h3ShowCanvas(26, 16);

   h3Line(0, 0, 59, 63);
   h3Circle(MAX_X / 2, MAX_Y / 2, 25);
   for (i = 0; i < 10; i++)
      h3Line(0, 0, 59, 63);

   h3SetFB(1);

   intro();

   cls();
   h3Cls();
   h3ShowCanvas(5, 4);
   h3ShowCanvas(26, 4);
   h3ShowCanvas(5, 16);
   h3ShowCanvas(26, 16);


   points();
   lines();
   circles();
   patternDemo();
   rainDemo();
   commands();
   about();

   h3Cls();
   stars();

   h3Cls();
   cls();
}
