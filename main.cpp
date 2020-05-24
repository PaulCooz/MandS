#include "qimage.h"
#include <complex>
#include <iostream>

using namespace std;

long double Lr, Li, Rr, Ri, PixelsPerDistance;
int Pow, hmp;

void HowMuchHasPassed(int r)
{
    if (r % 10 == 0 && r != hmp)
    {
        hmp = r;
        cout << hmp << "%" << endl;
    }
}

void MakeImage()
{
    const int MaxW = (Rr - Lr) * PixelsPerDistance + 2,
              MaxH = (Ri - Li) * PixelsPerDistance + 2;
    QImage img(MaxW, MaxH, QImage::Format_RGB32);

    const long double OnePercent = (Rr - Lr) / 100.0;
    hmp = -1;

    long double IncR = 0.8 / PixelsPerDistance,
                IncI = 0.8 / PixelsPerDistance;
    for(long double r = Lr; r < Rr; r += IncR)
    {
        for(long double i = Li; i < Ri; i += IncI)
        {
            complex<long double> c(r, i), z(0, 0);

            int cr = 0, cg = 0, cb = 0;
            for(int it = 0; it < 255; it++)
            {
                if (it % 3 == 0) cr = it;                               // Set color
                else if (it % 3 == 1) cg = it;
                else if (it % 3 == 2) cb = it;

                z = pow(z, Pow) + c;

                if (abs(z) > 2) break;
            }

            int x = r * PixelsPerDistance;                              // Set x
            x -= Lr * PixelsPerDistance;                                // 0 <= x <= MaxW

            int y = i * PixelsPerDistance;                              // Set y
            y -= Li * PixelsPerDistance;                                // 0 <= y <= MaxH

            img.setPixel(x, y, qRgb(4 * cr, 4 * cg, 4 * cb));           // Set a color pixel
        }

        HowMuchHasPassed((r - Lr) / OnePercent);                        // Output hmp
    }

    img.save("MandelbrotSet.png", "PNG");                               // Make new image
}


int main()
{
    cout << "Input min real" << endl;
    cin >> Lr;
    cout << "Input max real" << endl;
    cin >> Rr;

    cout << "Input min imag" << endl;
    cin >> Li;
    cout << "Input max imag" << endl;
    cin >> Ri;

    cout << "Input power" << endl;
    cin >> Pow;

    cout << "Number of pixels" << endl;
    cin >> PixelsPerDistance;
    PixelsPerDistance /= max((Rr - Lr), (Ri - Li));

    MakeImage();
}
