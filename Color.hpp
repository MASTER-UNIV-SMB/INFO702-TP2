//
// Created by Clément.
//

#ifndef TP2_COLOR_HPP
#define TP2_COLOR_HPP

#include <vector>
#include <iostream>
#include <exception>
#include <iterator>
#include <string>
#include <fstream>
#include <sstream>

struct Color {
    typedef unsigned char Byte;

    Byte red, green, blue;

    Color() {}

    Color(Byte _red, Byte _green, Byte _blue) : red(_red), green(_green), blue(_blue) {}

    float r() const { return ((float) red) / 255.0; }
    float g() const { return ((float) green) / 255.0; }
    float b() const { return ((float) blue) / 255.0; }

    enum Channel {
        Red, Green, Blue
    };

    Channel argmax() const {
        if (red >= green) return red >= blue ? Red : Blue;
        else return green >= blue ? Green : Blue;
    }

    float max() const { return std::max(std::max(r(), g()), b()); }

    float min() const { return std::min(std::min(r(), g()), b()); }

    void getHSV(int &h, float &s, float &v) const {
        if (max() == min()) h = 0;
        else {
            switch (argmax()) {
                case Red:
                    h = ((int) (60.0 * (g() - b()) / (max() - min()) + 360.0)) % 360;
                    break;
                case Green:
                    h = ((int) (60.0 * (b() - r()) / (max() - min()) + 120.0));
                    break;
                case Blue:
                    h = ((int) (60.0 * (r() - g()) / (max() - min()) + 240.0));
                    break;
            }
        }

        s = max() == 0.0 ? 0.0 : 1.0 - min() / max();

        v = max();
    }

    void setHSV(int h, float s, float v) {
        if (1.0 < v) {
            std::cout << "Une erreur s'est produite !" << std::endl;
        }

        int ti = (h / 60) % 6;

        float f = (h / 60.0f) - ti;
        float l = v * (1 - s);
        float m = v * (1 - f * s);
        float n = v * (1 - (1 - f) * s);

        v *= 255.0;
        m *= 255.0;
        n *= 255.0;
        l *= 255.0;

        switch (ti) {
            case 0:
                red = (Byte) v;
                green = (Byte) n;
                blue = (Byte) l;
                break;
            case 1:
                red = (Byte) m;
                green = (Byte) v;
                blue = (Byte) l;
                break;
            case 2:
                red = (Byte) l;
                green = (Byte) v;
                blue = (Byte) n;
                break;
            case 3:
                red = (Byte) l;
                green = (Byte) m;
                blue = (Byte) v;
                break;
            case 4:
                red = (Byte) n;
                green = (Byte) l;
                blue = (Byte) v;
                break;
            case 5:
                red = (Byte) v;
                green = (Byte) l;
                blue = (Byte) m;
                break;
            default :
                std::cout << "Une erreur s'est produite !" << std::endl;
                break;
        }
    }
};


#endif
