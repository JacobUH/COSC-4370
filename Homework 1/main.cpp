#include <iostream>
#include "BMP.h"
#include <cmath>
using namespace std;

// Set pixel color in BMP
void writeEllipse(int x, int y, int xc, int yc, BMP &bmpNew)
{
    bmpNew.set_pixel(x + xc, y + yc, 255, 255, 255, 0);
    bmpNew.set_pixel(xc - x, y + yc, 255, 255, 255, 0); // Mirrored in the second quadrant
    bmpNew.set_pixel(x + xc, yc - y, 255, 255, 255, 0); // Mirrored in the third quadrant
    bmpNew.set_pixel(xc - x, yc - y, 255, 255, 255, 0); // Mirrored in the fourth quadrant
}

// Midpoint ellipse drawing algorithm
void midpointEllipse(int a, int b, BMP &bmpNew)
{
    int x = 0;
    int y = b;
    float xc = 0;
    float yc = 2 * a * a * b;
    float decisionParameter = b * b - a * a * b + 0.25 * a * a;

    // Region 1
    while (xc < yc)
    {
        writeEllipse(x, y, a, b, bmpNew);
        x++;
        xc += 2 * b * b;

        if (decisionParameter < 0)
        {
            decisionParameter += b * b * (2 * x + 3);
        }
        else
        {
            y--;
            yc -= 2 * a * a;
            decisionParameter += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
        }
    }

    // Region 2
    decisionParameter = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;

    while (y >= 0)
    {
        writeEllipse(x, y, a, b, bmpNew);
        y--;
        yc -= 2 * a * a;

        if (decisionParameter < 0)
        {
            x++;
            xc += 2 * b * b;
            decisionParameter += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
        }
        else
        {
            decisionParameter += a * a * (-2 * y + 3);
        }
    }
}

void midpointCircleArc(int a, int b, struct BMP &bmp)
{
    int radius = b;

    int x = 0;
    int y = radius;
    int d = 1 - radius;
    int deltaE = 3;
    int deltaSE = -2 * radius + 5;

    while (y > x)
    {
        if (d < 0)
        { // select E
            d += deltaE;
            deltaE += 2;
            deltaSE += 2;
        }
        else
        {
            d += deltaSE; // select SE
            deltaE += 2;
            deltaSE += 4;
            y--;
        }
        x++;
        bmp.set_pixel(a + x, b + y, 0, 0, 255, 0);
        bmp.set_pixel(a + y, b + x, 0, 0, 255, 0);
        bmp.set_pixel(a + x, b - y, 0, 0, 255, 0);
        bmp.set_pixel(a + y, b - x, 0, 0, 255, 0);
    }
}

int main()
{
    int a = 200;
    int b = 100;
    BMP bmpNew(a * 2 + 1, b * 2 + 1, false);
    bmpNew.fill_region(0, 0, a, b, 0, 0, 0, 0);

    midpointEllipse(a, b, bmpNew);
    midpointCircleArc(a, b, bmpNew);
    bmpNew.write("output.bmp");

    return 0;
}
