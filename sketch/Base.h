#ifndef BASE_H
#define BASE_H

#include "Params.h"
#include <string>

template<class Hash>
class Base {
protected:
    int *data[Params::MaxHashNum];
    Hash h[Params::MaxHashNum];
public:
    const int k, l, w; // hash num, counter per array, bit per counter
    const std::string Name = "base";
    Base(int _k, int _l, int _w): k(_k), l(_l), w(_w) {
        // alloc memory and init
        for (int i = 0; i < k; ++i) {
            data[i] = new int [l];
            for (int j = 0; j < l; ++j) {
                data[i][j] = 0;
            }
            h[i].SetSeed(1000 + i);
        }
    }
    ~Base() {
        for (int i = 0; i < k; ++i) {
            delete [] data[i];
        }
    }
    virtual void Insert(const char* str, const int len) = 0;
    virtual int Query(const char* str, const int len) = 0;
};
#endif