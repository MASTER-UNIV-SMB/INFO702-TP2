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

    if (argc < 2) {
        std::cerr << "Commande: save-channels <input.ppm>" << std::endl;

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
    GrayLevelImage2D img3(img.w(), img.h());
    GrayLevelImage2D img4(img.w(), img.h());

    typedef ColorImage2D::GenericConstIterator <ColorBlueAccessor> ColorBlueConstIterator;

    const ColorImage2D &cimg = img;

    ColorBlueConstIterator itBlue = cimg.begin<ColorBlueAccessor>();

    for (GrayLevelIterator it = img3.begin(), itE = img3.end();
         it != itE; ++it) {
        *it = *itBlue;
        ++itBlue;
    }

    std::ofstream output("papillon_blue.ppm");

    bool ok2 = GrayLevelImage2DWriter::write(img3, output, false);

    if (!ok2) {
        std::cerr << "Une erreur s'est produite lors de l'écriture du fichier !" << std::endl;

        return 1;
    }

    output.close();

    typedef ColorImage2D::GenericConstIterator <ColorGreenAccessor> ColorGreenConstIterator;

    ColorGreenConstIterator itGreen = cimg.begin<ColorGreenAccessor>();

    for (GrayLevelIterator it = img2.begin(), itE = img2.end();
         it != itE; ++it) {
        *it = *itGreen;
        ++itGreen;
    }

    std::ofstream output2("papillon_vert.ppm");

    ok2 = GrayLevelImage2DWriter::write(img2, output2, false);

    if (!ok2) {
        std::cerr << "Une erreur s'est produite lors de l'écriture du fichier !" << std::endl;

        return 1;
    }

    output.close();

    typedef ColorImage2D::GenericConstIterator <ColorRedAccessor> ColorRedConstIterator;

    ColorRedConstIterator itRed = cimg.begin<ColorRedAccessor>();

    for (GrayLevelIterator it = img4.begin(), itE = img4.end();
         it != itE; ++it) {
        *it = *itRed;
        ++itRed;
    }

    std::ofstream output3("papillon_red.ppm");

    ok2 = GrayLevelImage2DWriter::write(img4, output3, false);

    if (!ok2) {
        std::cerr << "Une erreur s'est produite lors de l'écriture du fichier !" << std::endl;

        return 1;
    }

    output.close();

    return 0;
}
