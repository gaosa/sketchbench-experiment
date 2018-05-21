#ifndef SBF_H
#define SBF_H

#include "Params.h"

template<class Hash>
class Sbf {
private:
    const int k, l, w;
    int* data;
    Hash h[Params::MaxHashNum];
public:
    Sbf(int _k, int _l, int _w): k(_k), l(_l), w(_w) {
        data = new int[k*l];
        for (int i = 0; i < k; ++i) h[i].SetSeed(1000+i);
    }
    ~Sbf() { delete [] data; }
    void Insert(const char* str, const int len) {
        for (int i = 0; i < k; ++i) {
            ++data[h[i].Run(str, len) % (k*l)];
        }
    }
    int Query(const char* str, const int len) {
        int sm = data[h[0].Run(str, len) % (k*l)];
        for (int i = 0; i < k; ++i) {
            int t = data[h[i].Run(str, len) % (k*l)];
            sm = sm < t ? sm : t;
        }
        return sm > ((1<<w)-1) ? ((1<<w)-1) : sm;
    }
};
#endif