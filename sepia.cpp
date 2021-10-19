//
// Created by Clément.
//

#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Color.hpp"
#include "Image2DWriter.hpp"
#include "Accessor.hpp"
#include "Histogramme.hpp"
#include "Image2DReader.hpp"

int main(int argc, char **argv) {
    typedef unsigned char Byte;

    typedef Image2D<Color> ColorImage2D;
    typedef Image2D<Byte> GrayLevelImage2D;

    typedef ColorImage2D::Iterator Iterator;
    typedef ColorImage2D::ConstIterator ConstIterator;

    typedef GrayLevelImage2D::Iterator GrayLevelIterator;

    if (argc < 3) {
        std::cerr << "Commande : sepia <input.pgm> <output.pgm>" << std::endl;

        return 0;
    }

    ColorImage2D img;

    std::ifstream input(argv[1]);

    bool ok = Image2DReader<Color>::read(img, input);

    if (!ok) {
        std::cerr << "Erreur lors de la lecture du fichier !" << std::endl;
        return 1;
    }

    input.close();

    for (ColorImage2D::GenericIterator <ColorValueAccessor> it = img.begin<ColorValueAccessor>(), itE = img.end<ColorValueAccessor>(); it != itE; ++it) {
        Color c = (*it).arg;

        double red = (c.red * .393) + (c.green * .769) + (c.blue * .189);
        red = std::min(255.0, red);
        red = std::max(0.0, red);

        double green = (c.red * .349) + (c.green * .686) + (c.blue * .168);
        green = std::min(255.0, green);
        green = std::max(0.0, green);

        double blue = (c.red * .272) + (c.green * .534) + (c.blue * .131);
        blue = std::min(255.0, blue);
        blue = std::max(0.0, blue);

        (*it).arg = Color((Byte) red, (Byte) green, (Byte) blue);
    }

    std::ofstream output(argv[2]);

    bool ok2 = Image2DWriter<Color>::write(img, output, false);

    if (!ok2) {
        std::cerr << "Une erreur s'est produite lors de l'écriture du fichier !" << std::endl;

        return 1;
    }

    output.close();

    return 0;
}

