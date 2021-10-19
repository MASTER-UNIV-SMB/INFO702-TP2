//
// Created by Clément.
//

#ifndef TP2_IMAGE2D_HPP
#define TP2_IMAGE2D_HPP

#include <vector>
#include <iostream>
#include <exception>
#include <iterator>
#include <string>
#include <fstream>
#include <sstream>

template<typename TValue> class Image2D {
public:
    typedef Image2D<TValue> Self;
    typedef TValue Value;
    typedef std::vector<Value> Container;

    Image2D() : m_data(0), m_width(0), m_height(0) {}

    Image2D(int w, int h, Value g = Value()) : m_data(w * h, g), m_width(w), m_height(h) {}

    struct Iterator : public Container::iterator {
        Iterator(Self &image, int x, int y) : Container::iterator(image.m_data.begin() + image.index(x, y)) {}
    };

    struct ConstIterator : public Container::const_iterator {
        ConstIterator(const Self &image, int x, int y) : Container::const_iterator(image.m_data.begin() + image.index(x, y)) {}
    };

    Iterator begin() { return start(0, 0); }

    Iterator end() { return start(0, h()); }

    Iterator start(int x, int y) { return Iterator(*this, x, y); }

    ConstIterator begin() const { return start(0, 0); }

    ConstIterator end() const { return start(0, h()); }

    ConstIterator start(int x, int y) const { return ConstIterator(*this, x, y); }

    template<typename TAccessor> struct GenericConstIterator : public Container::const_iterator {
        typedef TAccessor Accessor;
        typedef typename Accessor::Argument ImageValue;
        typedef typename Accessor::Value Value;
        typedef typename Accessor::Reference Reference;
        GenericConstIterator(const Image2D<ImageValue> &image, int x, int y) : Container::const_iterator(image.m_data.begin() + image.index(x, y)) {};

        Value operator*() const { return Accessor::access(Container::const_iterator::operator*()); }
    };

    template<typename Accessor> GenericConstIterator<Accessor> start(int x = 0, int y = 0) const {
        return GenericConstIterator<Accessor>(*this, x, y);
    }

    template<typename Accessor> GenericConstIterator<Accessor> end(int x = 0, int y = 0) const { return start<Accessor>(w(), h()); }

    template<typename Accessor> GenericConstIterator<Accessor> begin(int x = 0, int y = 0) const { return start<Accessor>(0, 0); }

    template<typename TAccessor>
    struct GenericIterator : public Container::iterator {
        typedef TAccessor Accessor;

        typedef typename Accessor::Argument ImageValue;
        typedef typename Accessor::Value Value;
        typedef typename Accessor::Reference Reference;

        GenericIterator(Image2D<ImageValue> &image, int x, int y) : Container::iterator(image.m_data.begin() + image.index(x, y)) {};

        Value operator*() const { return Accessor::access(Container::const_iterator::operator*()); }

        Reference operator*() { return Accessor::access(Container::iterator::operator*()); }
    };

    template<typename Accessor>
    GenericIterator<Accessor> start(int x = 0, int y = 0) { return GenericIterator<Accessor>(*this, x, y); }

    template<typename Accessor>
    GenericIterator<Accessor> end(int x = 0, int y = 0) { return start<Accessor>(w(), h()); }

    template<typename Accessor>
    GenericIterator<Accessor> begin(int x = 0, int y = 0) { return GenericIterator<Accessor>(*this, 0, 0); }

    void fill(Value g);

    int w() const { return m_width; }
    int h() const { return m_height; }

    void w(int w) { m_width = w; }
    void h(int h) { m_height = h; }

    Value at(int i, int j) const {
        return m_data[Image2D::index(i, j)];
    }

    Value &at(int i, int j) {
        return m_data.at(Image2D::index(i, j));
    }

    Container &data() { return m_data; }

private:
    Container m_data;
    int m_width;
    int m_height;

    int index(int i, int j) const {
        return j * this->m_width + i;
    }
};

#endif //TP2_IMAGE2D_HPP
