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

    typedef ColorImage2D::Iterator ColorIterator;

    if (argc < 3) {
        std::cerr << "Commande : save-green-channel <input.ppm> <output.pgm>" << std::endl;

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

    typedef Image2D<unsigned char> GrayLevelImage2D;

    typedef Image2DWriter<unsigned char> GrayLevelImage2DWriter;

    typedef GrayLevelImage2D::Iterator GrayLevelIterator;

    GrayLevelImage2D img2(img.w(), img.h());

    typedef ColorImage2D::GenericConstIterator <ColorGreenAccessor> ColorGreenConstIterator;

    const ColorImage2D &cimg = img;

    ColorGreenConstIterator itGreen = cimg.begin<ColorGreenAccessor>();

    for (GrayLevelIterator it = img2.begin(), itE = img2.end();
         it != itE; ++it) {
        *it = *itGreen;
        ++itGreen;
    }

    //-----

    std::ofstream output(argv[2]);

    bool ok2 = GrayLevelImage2DWriter::write(img2, output, false);

    if (!ok2) {
        std::cerr << "Une erreur s'est produite lors de l'écriture du fichier !" << std::endl;

        return 1;
    }

    output.close();

    return 0;
}