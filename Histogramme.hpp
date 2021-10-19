//
// Created by Clément.
//

#ifndef TP1_HISTOGRAMME_HPP
#define TP1_HISTOGRAMME_HPP

#include "Image2D.hpp"

class Histogramme {
public:
    typedef Image2D<unsigned char> GrayLevelImage2D;
    typedef GrayLevelImage2D::Iterator Iterator;

public:
    double histo[256];
    double histoc[256];
public:

    void init(GrayLevelImage2D &img) {
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

    int egalisation(int j) const {
        return 255 * histoc[j];
    }

    template<typename InputIterator> void init(InputIterator it, InputIterator itE) {
        int size = itE - it;

        for (int k = 0; k < 256; ++k) {
            histo[k] = 0;
        }

        for (; it != itE; ++it) {
            histo[(int) *it]++;
        }

        for (int i = 0; i < 256; ++i) {
            histo[i] = (double) histo[i] / double(size);

            double propc = 0;

            for (int j = 0; j < i; ++j) {
                propc += histo[j];
            }

            histoc[i] = propc;
        }
    }

};

#endif