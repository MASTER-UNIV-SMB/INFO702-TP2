//
// Created by Clément.
//

#include "Histogramme.hpp"

void Histogramme::init(GrayLevelImage2D &img) {
    int size = img.w() * img.h();

    std::cout << size << std::endl;

    for (int i = 0; i < 256; ++i) {
        int cpt = 0;

        for (Iterator it = img.begin(), itE = img.end(); it != itE; ++it) {
            if ((int) *it == i) {
                cpt++;
            }
        }

        double prop = (double) cpt / (double) size;

        histo[i] = prop;

        double propc = 0;

        for (int j = 0; j < i; ++j) {
            propc += histo[j];
        }

        histoc[i] = propc;
    }

}

int Histogramme::egalisation(int j) const {
    return 255 * histoc[j];
}
