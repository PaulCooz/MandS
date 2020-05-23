//#pragma GCC optimize("-Ofast")

#include <QImage>
#include <complex>
#include <iostream>

#define ld long double

ld Li, Lj, Ri, Rj, stepR, stepI;
int Pow;

void MakeImage()
{
    const int MW = (Ri - Li) * stepR, MH = (Rj - Lj) * stepI;

    unsigned char Map[MW][MH];
    ld IncI = (ld)1.0 / stepR, IncJ = (ld)1.0 / stepI;
    std::complex<ld> c, z;

    for(ld i = Li; i < Ri; i += IncI)
    {
        for(ld j = Lj; j < Rj; j += IncJ)
        {
            c.real(i);
            c.imag(j);

            z.real(0.0);
            z.imag(0.0);

            unsigned char it = 0;
            for(it = 0; it < 255; it++)
            {
                z = pow(z, Pow) + c;

                if (z.real() * z.real() + z.imag() * z.imag() > 4) break;
            }

            int x = abs(Li) * stepR + i * stepR,
                y = abs(Lj) * stepI + j * stepI;

            Map[x][y] = it;
        }
    }

    QImage img(MW, MH, QImage::Format_RGB32);
    for(int i = 0; i < MW; i++)
    {
        for(int j = 0; j < MH; j++)
        {
            img.setPixel(i, j, qRgb(Map[i][j], Map[i][j], Map[i][j]));
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

    std::cout << "\nReady!\a\n" << std::endl;
}
