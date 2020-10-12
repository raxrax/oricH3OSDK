/**
 * h3.h library
 * rax@2020
 * This library emulates a graphical mode into LORES characters. Screen size: 60x64 px
 **/

#ifndef __H3H__
#define __H3H__

#define abs(x) (((x) < 0) ? -(x) : (x))

#define MAX_X 60
#define MAX_Y 64

#define MAX_CHARS_PER_X 10
#define MAX_CHARS_PER_Y 8

unsigned h3Buffer[80 * 8];
unsigned char h3fb = 1;
unsigned char h3pattern = 255;

unsigned int h3MapX[MAX_X] = {47360U, 47360U, 47360U, 47360U, 47360U, 47360U, 47424U, 47424U, 47424U, 47424U, 47424U, 47424U, 47488U, 47488U, 47488U, 47488U, 47488U, 47488U, 47552U, 47552U, 47552U, 47552U, 47552U, 47552U, 47616U, 47616U, 47616U, 47616U, 47616U, 47616U, 47680U, 47680U, 47680U, 47680U, 47680U, 47680U, 47744U, 47744U, 47744U, 47744U, 47744U, 47744U, 47808U, 47808U, 47808U, 47808U, 47808U, 47808U, 47872U, 47872U, 47872U, 47872U, 47872U, 47872U, 47936U, 47936U, 47936U, 47936U, 47936U, 47936U};

unsigned char CHARSET[] = {
    0, 0, 0, 0, 0, 0,
    16, 16, 16, 0, 16, 0,
    40, 40, 0, 0, 0, 0,
    40, 56, 40, 56, 40, 0,
    24, 48, 16, 24, 48, 0,
    40, 8, 16, 32, 40, 0,
    16, 40, 16, 40, 24, 0,
    16, 16, 0, 0, 0, 0,
    16, 32, 32, 32, 16, 0,
    16, 8, 8, 8, 16, 0,
    40, 16, 56, 16, 40, 0,
    0, 16, 56, 16, 0, 0,
    0, 0, 0, 0, 16, 32,
    0, 0, 56, 0, 0, 0,
    0, 0, 0, 0, 16, 0,
    8, 8, 16, 32, 32, 0,
    56, 40, 40, 40, 56, 0,
    16, 16, 16, 16, 16, 0,
    56, 8, 56, 32, 56, 0,
    56, 8, 56, 8, 56, 0,
    40, 40, 56, 8, 8, 0,
    56, 32, 56, 8, 56, 0,
    56, 32, 56, 40, 56, 0,
    56, 8, 8, 8, 8, 0,
    56, 40, 56, 40, 56, 0,
    56, 40, 56, 8, 56, 0,
    0, 16, 0, 16, 0, 0,
    0, 16, 0, 16, 32, 0,
    8, 16, 32, 16, 8, 0,
    0, 56, 0, 56, 0, 0,
    32, 16, 8, 16, 32, 0,
    48, 8, 16, 0, 16, 0,
    56, 40, 40, 32, 56, 0,
    16, 40, 56, 40, 40, 0,
    56, 40, 48, 40, 56, 0,
    24, 32, 32, 32, 24, 0,
    48, 40, 40, 40, 48, 0,
    56, 32, 48, 32, 56, 0,
    56, 32, 48, 32, 32, 0,
    24, 32, 40, 40, 24, 0,
    40, 40, 56, 40, 40, 0,
    56, 16, 16, 16, 56, 0,
    8, 8, 8, 8, 48, 0,
    40, 40, 48, 40, 40, 0,
    32, 32, 32, 32, 56, 0,
    40, 56, 40, 40, 40, 0,
    56, 40, 40, 40, 40, 0,
    24, 40, 40, 40, 48, 0,
    56, 40, 56, 32, 32, 0,
    56, 40, 40, 40, 56, 16,
    56, 40, 48, 40, 40, 0,
    24, 32, 16, 8, 48, 0,
    56, 16, 16, 16, 16, 0,
    40, 40, 40, 40, 56, 0,
    40, 40, 40, 56, 16, 0,
    40, 40, 40, 56, 40, 0,
    40, 40, 16, 40, 40, 0,
    40, 40, 56, 16, 16, 0,
    56, 8, 16, 32, 56, 0,
    24, 16, 16, 16, 24, 0,
    32, 32, 16, 8, 8, 0,
    24, 8, 8, 8, 24, 0,
    16, 40, 40, 0, 0, 0,
    0, 0, 0, 0, 0, 60,
    16, 32, 16, 0, 0, 0,
    0, 24, 40, 40, 24, 0,
    32, 48, 40, 40, 48, 0,
    0, 24, 32, 32, 24, 0,
    8, 24, 40, 40, 24, 0,
    0, 24, 40, 48, 24, 0,
    8, 16, 56, 16, 16, 0,
    0, 24, 40, 56, 8, 48,
    32, 48, 40, 40, 40, 0,
    16, 0, 16, 16, 16, 0,
    16, 0, 16, 16, 16, 48,
    32, 40, 48, 40, 40, 0,
    48, 16, 16, 16, 16, 0,
    0, 40, 56, 40, 40, 0,
    0, 48, 40, 40, 40, 0,
    0, 24, 40, 40, 48, 0,
    0, 48, 40, 40, 48, 32,
    0, 24, 40, 40, 24, 8,
    0, 40, 48, 32, 32, 0,
    0, 56, 32, 24, 56, 0,
    16, 56, 16, 16, 8, 0,
    0, 40, 40, 40, 24, 0,
    0, 40, 40, 56, 16, 0,
    0, 40, 40, 56, 40, 0,
    0, 40, 16, 40, 40, 0,
    0, 40, 40, 56, 8, 56,
    0, 56, 8, 48, 56, 0,
    8, 16, 48, 16, 8, 0,
    16, 16, 16, 16, 16, 0,
    32, 16, 24, 16, 32, 0,
    40, 20, 40, 20, 40, 20,
    60, 60, 60, 60, 60, 60};

void h3ShowCanvas(unsigned char x, unsigned char y)
{
    unsigned char chr = 32;
    unsigned int addr = 0xbb80 + x + y * 40;

    //set lores mode
    for (y = 0; y < 8; ++y)
    {
        poke(addr - 1 + y * 40, 9);
        poke(addr + y * 40 + MAX_CHARS_PER_X, 8);
    }

    //print chars
    for (x = 0; x < 10; ++x)
    {
        for (y = 0; y < 8; ++y)
        {
            poke(addr + x + y * 40, chr++);
        }
    }
}

void h3Cls()
{
    memset(0xb900, 0, 80 * 8);
}

void h3SetFB(unsigned char fb)
{
    h3fb = fb;
}

void h3SetPattern(unsigned char p)
{
    h3pattern = p;
}

void h3Curset(unsigned char x, unsigned char y)
{
    unsigned char offsetX = 5 - x % 6;
    unsigned int addr = h3MapX[x] + y;

    switch (h3fb)
    {
    case 0:
        poke(addr, peek(addr) & ~(1 << offsetX));
        break;

    case 1:
        poke(addr, peek(addr) | 1 << offsetX);
        break;

    case 2:
        poke(addr, peek(addr) ^ 1 << offsetX);
        break;
    }
}

void h3Save()
{
    memcpy(h3Buffer, (void *)0xb900, 8 * 80);
}

void h3Restore()
{
    memcpy((void *)0xb900, h3Buffer, 8 * 80);
}

void h3Char(unsigned char x, unsigned char y, unsigned char c)
{
    unsigned int addr = (unsigned int)CHARSET + (c - 32) * 6;
    unsigned char l;

    for (l = 0; l < 6; ++l)
    {
        c = peek(addr++);

        if (c & 32)
        {
            h3Curset(x, y + l);
        }
        if (c & 16)
        {
            h3Curset(x + 1, y + l);
        }
        if (c & 8)
        {
            h3Curset(x + 2, y + l);
        }
    }
}

void h3String(unsigned char x, unsigned char y, char *str)
{
    unsigned char i, c, l = strlen(str), startX = x;

    for (i = 0; i < l; ++i)
    {
        c = str[i];

        if (c == 10 || x > MAX_X - 3)
        {
            x = startX;
            y = y + 6;
            if (c == 10)
            {
                continue;
            }
        }

        h3Char(x, y, c);
        x += 4;
    }
}

void h3Circle(int xm, int ym, int r)
{
    unsigned char patternCounter = 0;
    int x = -r, y = 0, err = 2 - 2 * r;
    do
    {
        //set point
        if (h3pattern & (1 << patternCounter))
        {
            h3Curset(xm - x, ym + y);
            h3Curset(xm - y, ym - x);
            h3Curset(xm + x, ym - y);
            h3Curset(xm + y, ym + x);
        }

        //counter
        if (++patternCounter == 8)
        {
            patternCounter = 0;
        }

        r = err;
        if (r > x)
        {
            err += ++x * 2 + 1;
        }
        if (r <= y)
        {
            err += ++y * 2 + 1;
        }
    } while (x < 0);
}

void h3Draw(int x0, int y0, int x1, int y1)
{
    unsigned char patternCounter = 0;
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    for (;;)
    {

        //set point
        if (h3pattern & (1 << patternCounter))
        {
            h3Curset(x0, y0);
        }

        //counter
        if (++patternCounter == 8)
        {
            patternCounter = 0;
        }

        if (x0 == x1 && y0 == y1)
        {
            break;
        }

        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

#endif