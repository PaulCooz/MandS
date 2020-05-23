#include "qimage.h"
#include <complex>
#include <iostream>

#define ll long long
#define ld long double

ld Li, Lj, Ri, Rj, stepR, stepI;
ll Pow;

void MakeImage()
{
    const ll MW = (Ri - Li) * stepR, MH = (Rj - Lj) * stepI;

    QImage img(MW, MH, QImage::Format_RGB32);
    ld IncI = (ld)1.0 / stepR,
       IncJ = (ld)1.0 / stepI;

    for(ld i = Li; i < Ri; i += IncI)
    {
        for(ld j = Lj; j < Rj; j += IncJ)
        {
            std::complex<ld> c(i, j), z(0, 0);

            unsigned char it = 0;
            for(it = 0; it < 255; it++)
            {
                z = pow(z, Pow) + c;

                if (z.real() * z.real() + z.imag() * z.imag() > 4) break;
            }

            ll x = abs(Li) * stepR + i * stepR,
               y = abs(Lj) * stepI + j * stepI;

            img.setPixel(x, y, qRgb(it, it, it));
        }
    }

    img.save("MandelbrotSet.png", "PNG");
}


int main()
{
    std::cout << "Input min real" << std::endl;
    std::cin >> Li;
    std::cout << "Input max real" << std::endl;
    std::cin >> Ri;

    std::cout << "Input min imag" << std::endl;
    std::cin >> Lj;
    std::cout << "Input max imag" << std::endl;
    std::cin >> Rj;

    std::cout << "Input min step R^-1" << std::endl;
    std::cin >> stepR;
    std::cout << "Input min step I^-1" << std::endl;
    std::cin >> stepI;

    std::cout << "Input power" << std::endl;
    std::cin >> Pow;

    MakeImage();
}
