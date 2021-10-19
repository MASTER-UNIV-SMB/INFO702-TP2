//
// Created by Clément.
//

#include <cmath>
#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Image2DReader.hpp"
#include "Image2DWriter.hpp"
#include "Accessor.hpp"

int main(int argc, char **argv) {
    typedef Image2D<Color> ColorImage2D;

    typedef Image2DReader<Color> ColorImage2DReader;
    typedef Image2DWriter<Color> ColorImage2DWriter;

    typedef ColorImage2D::Iterator ColorIterator;

    if (argc < 3) {
        std::cerr << "Commande : cathodic-screen <input.ppm> <output.ppm>" << std::endl;

        return 0;
    }

    ColorImage2D img;

    std::ifstream input(argv[1]);

    bool ok = ColorImage2DReader::read(img, input);

    if (!ok) {
        std::cerr << "Erreur lors de la lecture du fichier !" << std::endl;

        return 1;
    }

    input.close();

    typedef ColorImage2D::GenericIterator <ColorRedAccessor> ColorRedConstIterator;
    typedef ColorImage2D::GenericIterator <ColorGreenAccessor> ColorGreenConstIterator;
    typedef ColorImage2D::GenericIterator <ColorBlueAccessor> ColorBlueConstIterator;

    ColorRedConstIterator itRed = img.begin<ColorRedAccessor>();
    ColorGreenConstIterator itGreen = img.begin<ColorGreenAccessor>();
    ColorBlueConstIterator itBlue = img.begin<ColorBlueAccessor>();

    int x = 0;

    for (ColorIterator it = img.begin(), itE = img.end(); it != itE; ++it) {
        switch (x % 3) {
            case 0:
                *itGreen = *itBlue = 0;
                break;
            case 1:
                *itRed = *itBlue = 0;
                break;
            case 2:
                *itRed = *itGreen = 0;
                break;
        }

        ++itRed;
        ++itGreen;
        ++itBlue;

        x = (x + 1) % img.w();
    }

    std::ofstream output2(argv[2]);

    bool ok2 = ColorImage2DWriter::write(img, output2, false);

    if (!ok2) {
        std::cerr << "Une erreur s'est produite lors de l'écriture du fichier !" << std::endl;

        return 1;
    }

    output2.close();
}
