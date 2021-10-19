//
// Created by Clément.
//

#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Color.hpp"
#include "Image2DWriter.hpp"
#include "Image2DReader.hpp"
#include "Accessor.hpp"
#include "Histogramme.hpp"

int main(int argc, char **argv) {
    typedef Image2D<Color> ColorImage2D;
    typedef Image2D<unsigned char> GrayLevelImage2D;

    typedef ColorImage2D::Iterator Iterator;
    typedef ColorImage2D::ConstIterator ConstIterator;

    typedef GrayLevelImage2D::Iterator GrayLevelIterator;

    if (argc < 3) {
        std::cerr << "Commande : generate-histogramme <input.pgm> <output.pgm>" << std::endl;

        return 0;
    }

    ColorImage2D img2;

    std::ifstream input(argv[1]);

    bool ok = Image2DReader<Color>::read(img2, input);

    if (!ok) {
        std::cerr << "Erreur lors de la lecture du fichier !" << std::endl;

        return 1;
    }

    input.close();

    std::cout << "L'import a été réussi !" << std::endl;

    Histogramme H;

    GrayLevelImage2D img(512, 512);

    H.init(img2.begin<ColorValueAccessor>(),img2.end<ColorValueAccessor>());

    for (int i = 0; i < img.w(); i++) {
        for (int j = 0; j < img.h(); ++j) {
            if (img.h() - j > H.histo[i] * 100 * img.h()) {
                img.at(i, j) = 255;
            } else {
                img.at(i, j) = 0;
            }

            if (i > 255) {
                if (img.h() - j > H.histoc[i - 255] * img.h()) {
                    img.at(i, j) = 255;
                } else {
                    img.at(i, j) = 0;
                }
            }
        }
    }

    std::ofstream output(argv[2]);

    bool ok2 = Image2DWriter<unsigned char>::write(img, output, false);

    if (!ok2) {
        std::cerr << "Une erreur s'est produite lors de l'écriture du fichier !" << std::endl;

        return 1;
    }

    output.close();

    return 0;
}

