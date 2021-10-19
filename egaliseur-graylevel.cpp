//
// Created by Clément.
//

#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Image2DWriter.hpp"
#include "Image2DReader.hpp"
#include "Histogramme.hpp"
#include "Accessor.hpp"

int main(int argc, char **argv) {
    typedef unsigned char GrayLevel;

    typedef Image2D<GrayLevel> GrayLevelImage2D;
    typedef Image2D<unsigned char> GrayLevelImage2D;

    typedef GrayLevelImage2D::Iterator Iterator;
    typedef GrayLevelImage2D::ConstIterator ConstIterator;
    typedef GrayLevelImage2D::Iterator GrayLevelIterator;

    if (argc < 3) {
        std::cerr << "Commande : egaliseur-graylevel <input.pgm> <output.pgm>" << std::endl;
        return 0;
    }

    GrayLevelImage2D img2;

    std::ifstream input(argv[1]);

    bool ok = Image2DReader<GrayLevel>::read(img2, input);

    if (!ok) {
        std::cerr << "Erreur lors de la lecture du fichier !" << std::endl;

        return 1;
    }

    input.close();

    std::cout << "L'import a été réussi !" << std::endl;

    Histogramme H;
    H.init(img2.begin(), img2.end());

    for (GrayLevelImage2D::Iterator it = img2.begin(), itE = img2.end(); it != itE; ++it) {
        *it = (unsigned char) H.egalisation((int) *it);
    }

    std::ofstream output(argv[2]);

    bool ok2 = Image2DWriter<GrayLevel>::write(img2, output, false);

    if (!ok2) {
        std::cerr << "Une erreur s'est produite lors de l'écriture du fichier !" << std::endl;

        return 1;
    }

    output.close();

    return 0;
}


