//
// Created by Clément.
//

#ifndef TP2_IMAGE2DWRITER_HPP
#define TP2_IMAGE2DWRITER_HPP

#include <iostream>
#include <string>
#include "Color.hpp"
#include "Image2D.hpp"

template<typename TValue> class Image2DWriter {
public:
    typedef TValue Value;
    typedef Image2D<Value> Image;

    static bool write(Image &img, std::ostream &output, bool ascii) {
        std::cerr << "[Image2DWriter<TValue>::write] NOT IMPLEMENTED." << std::endl;
        return false;
    }
};

template<> class Image2DWriter<unsigned char> {
public:
    typedef unsigned char Value;
    typedef Image2D<Value> Image;

    static bool write(Image &img, std::ostream &output, bool ascii) {
        if (ascii) {
            output << "P2\n";
            output << "#Crée par Clément\n";
            output << img.w() << " " << img.h() << "\n";
            output << "255\n";

            std::ostream_iterator<int> out_it(output, " ");
            std::copy(img.begin(), img.end(), out_it);
        } else {
            output << "P5\n";
            output << "#Crée par Clément\n";
            output << img.w() << " " << img.h() << "\n";
            output << "255\n";

            std::ostream_iterator<unsigned char> out_it(output);
            std::copy(img.begin(), img.end(), out_it);
        }

        return true;
    }
};

template<> class Image2DWriter<Color> {
public:
    typedef Color Value;
    typedef Image2D<Value> Image;
    typedef Image::ConstIterator ConstIterator;

    static bool write(Image &img, std::ostream &output, bool ascii) {
        output << "P6" << std::endl;
        output << "# Crée par Clément" << std::endl;
        output << img.w() << " " << img.h() << std::endl;
        output << "255" << std::endl;

        const Image &cimg = img;

        for (ConstIterator it = cimg.begin(), itE = cimg.end(); it != itE; ++it) {
            Color c = *it;

            output << c.red << c.green << c.blue;
        }

        return true;
    }
};


#endif //TP2_IMAGE2DWRITER_HPP
