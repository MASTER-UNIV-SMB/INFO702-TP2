//
// Created by Clément.
//

#ifndef TP2_IMAGE2DREADER_HPP
#define TP2_IMAGE2DREADER_HPP

#include <iostream>
#include <string>
#include "Color.hpp"
#include "Image2D.hpp"
#include <ctype.h>
#include <cstdlib>

template<typename TValue> class Image2DReader {
public:
    typedef TValue Value;
    typedef Image2D<Value> Image;

    static bool read(Image &img, std::istream &input) {
        std::cerr << "[Image2DReader<TValue>::read] NOT IMPLEMENTED." << std::endl;
        return false;
    }
};

template<> class Image2DReader<unsigned char> {
public:
    typedef unsigned char Value;

    typedef Image2D<Value> Image;
    typedef Image::Iterator Iterator;

    static bool read(Image &img, std::istream &input) {
        if (!input.good()) {
            std::cerr << "Une erreur s'est produite !";

            return false;
        }

        std::string str;
        std::string type;

        std::getline(input, str);

        type = str;

        std::getline(input, str);

        while (str.c_str()[0] == '#') {
            std::getline(input, str);
        }

        int w, h;
        std::istringstream istr(str);
        istr >> w >> h;

        std::getline(input, str);

        img.w(w);
        img.h(h);
        img.data().resize(w * h);
        std::cout << "type " << type << std::endl;
        std::cout << "width " << w << std::endl;
        std::cout << "height " << h << std::endl;

        if (type == "P2") {
            input >> std::skipws;

            for (Iterator it = img.begin(), itE = img.end(); it != itE; ++it) {
                int g;
                input >> g;
                *it = g;
            }
        } else {
            input >> std::noskipws;

            for (Iterator it = img.begin(), itE = img.end(); it != itE; ++it) {
                unsigned char g;
                input >> g;
                *it = g;
            }
        }

        return true;
    }
};

template<> class Image2DReader<Color> {
public:
    typedef Color Value;

    typedef Image2D<Value> Image;

    typedef Image::Iterator Iterator;

    typedef unsigned char Byte;

    static bool read(Image &img, std::istream &input) {
        if (!input.good()) {
            std::cerr << "Une erreur s'est produite !";

            return false;
        }

        std::string str;
        std::string type;

        std::getline(input, str);

        type = str;

        std::getline(input, str);

        while (str.c_str()[0] == '#') {
            std::getline(input, str);
        }

        int w, h;
        std::istringstream istr(str);
        istr >> w >> h;

        std::getline(input, str);

        img.w(w);
        img.h(h);
        img.data().resize(w * h);
        std::cout << "type " << type << std::endl;
        std::cout << "width " << w << std::endl;
        std::cout << "height " << h << std::endl;

        input >> std::noskipws;

        int cpt = 0;
        int size = w * h;

        for (Iterator it = img.begin(), itE = img.end(); it != itE; ++it) {
            Byte red, blue, green;

            input >> red;
            input >> green;
            input >> blue;

            cpt++;

            *it = Color(red, green, blue);
        }

        return true;
    }
};

#endif //TP2_IMAGE2DREADER_HPP