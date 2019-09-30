
/*
DEFINE THESE:
int analogread() <-- read analog data and return it
void delay_ms(int a) <-- delay a miliseconds
char dataPort <-- port to send number to 7 seg
char selectPort <-- port to cathod pins of 7 segs.
*/

static const char digitCodeMap[] = {
  //     GFEDCBA  Segments      7-segment map:
  0B00111111, // 0   "0"          AAA
  0B00000110, // 1   "1"         F   B
  0B01011011, // 2   "2"         F   B
  0B01001111, // 3   "3"          GGG
  0B01100110, // 4   "4"         E   C
  0B01101101, // 5   "5"         E   C
  0B01111101, // 6   "6"          DDD   Dp
  0B00000111, // 7   "7"
  0B01111111, // 8   "8"
  0B01101111, // 9   "9"
};

mainFunction()
{
    int a;
    int b[5];

    while(1)
    {
        a = analogRead();
        convert7seg(a, b);
        show7seg(b);
        delay_ms(10);

    }
}

void convert7seg(int a, char b[5])
{
    double f = analogToCelecius(a);
    long int g = (int) f * 1000;
    int c;
    for(int i = 4; i >= 0; i--)
    {
        c = g % 10;
        b[i] = digitCodeMap[c];
        g /= 10;
    }
}

void show7seg(char b[5])
{
    for(int i = 0; i < 4; i++)
    {
        dataPort = b[i];
        selectPort = (1 << i) ^ (0 - 1);
        delay_ms(1);
    }
}
