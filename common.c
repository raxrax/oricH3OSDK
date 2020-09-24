
#define MAX_STARS 10

unsigned char starsX[MAX_STARS];
unsigned char starsY[MAX_STARS];
unsigned char starsS[MAX_STARS];

void initStars()
{
    unsigned char i;

    h3SetFB(2);
    for (i = 0; i < MAX_STARS; ++i)
    {
        starsX[i] = rand() % MAX_X;
        starsY[i] = rand() % MAX_Y;
        starsS[i] = rand() % 2 + 1;
        h3Curset(starsX[i], starsY[i]);
    }
}

void moveStars()
{
    unsigned char i;
    for (i = 0; i < MAX_STARS; ++i)
    {
        h3Curset(starsX[i], starsY[i]);

        starsX[i] -= starsS[i];

        if (starsX[i] > 200)
        {
            starsX[i] = MAX_X;
            starsY[i] = rand() % MAX_Y;
            starsS[i] = rand() % 3 + 1;
        }

        h3Curset(starsX[i], starsY[i]);
    }
}

void stars()
{
    initStars();
    while (key()==0)
    {
        moveStars();
        // h3Char(30,55,'^');
    }
}

void rain()
{
    unsigned char i,r,x;
    unsigned int loop;

    h3SetFB(1);
    h3Cls();
    for(i=10;i<48;i+=7){
        for(r=1;r<6;++r){
            h3Circle(i,10,r);
        }
    }

    h3SetPattern(85);
    for(i=7;i<50;i+=3){
        h3Draw(i,12,i+6,55);
    }

    i=0;
    for(loop=0;loop<3000;++loop){

        if (loop % 500 == 0)
        {
            h3SetPattern(rand()%255);
            h3Draw(0,57-i,59,57-i++);
        }

        if(rand()%255==180){
            h3SetPattern(255);
            h3SetFB(2);
            x = rand()%35;
            h3Draw(x+6,15,x,50);
            h3Draw(x+6,15,x,50);
        }

    }

    key();

}