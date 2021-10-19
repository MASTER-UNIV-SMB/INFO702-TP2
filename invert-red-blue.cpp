//
// Created by Clément.
//

#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Color.hpp"
#include "Image2DWriter.hpp"
#include "Image2DReader.hpp"

int main(int argc, char **argv) {
    typedef unsigned char Byte;

    typedef Image2D<Color> ColorImage2D;

    typedef ColorImage2D::Iterator Iterator;
    typedef ColorImage2D::ConstIterator ConstIterator;

    if (argc < 3) {
        std::cerr << "Commande : invert-red-blue <input.pgm> <output.pgm>" << std::endl;

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

    std::cout << "L'import a été réussi !" << std::endl;

    for (Iterator it = img.begin(), itE = img.end(); it != itE; ++it) {
        Byte red = (*it).red;
        (*it).red = (*it).blue;
        (*it).blue = red;
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


