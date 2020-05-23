#include "qimage.h"
#include <complex>
#include <iostream>

#define ll long long
#define ld long double

using namespace std;

ld Lr, Li, Rr, Ri, steps;
ll Pow;

void MakeImage()
{
    const int MW = (Rr - Lr) * steps + 2,
              MH = (Ri - Li) * steps + 2;
    QImage img(MW, MH, QImage::Format_RGB32);
    
    ld IncR = 0.8 / steps,
       IncI = 0.8 / steps;
    for(ld r = Lr; r < Rr; r += IncR)
    {
        for(ld i = Li; i < Ri; i += IncI)
        {
            complex<ld> c(r, i), z(0, 0);

            int cr = 0, cg = 0, cb = 0;
            for(int it = 0; it < 255; it++)
            {
                if (it % 3 == 0) cr = it;
                else if (it % 3 == 1) cg = it;
                else if (it % 3 == 2) cb = it;

                z = pow(z, Pow) + c;

                if (abs(z) > 2) break;
            }

            ll x = abs(Lr) * steps + r * steps,
               y = abs(Li) * steps + i * steps;

            img.setPixel(x, y, qRgb(4*cr, 4*cg, 4*cb));
        }
    }

    img.save("MandelbrotSet.png", "PNG");
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

    steps = 500.0 / max((Rr - Lr), (Ri - Li));

    cout << "Input power" << endl;
    cin >> Pow;

    MakeImage();
}
