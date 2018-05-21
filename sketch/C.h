#ifndef C_H
#define C_H

#include "Base.h"
#include "Params.h"
#include <algorithm>

template<class Hash>
class C: public Base<Hash> {
protected:
    using Base<Hash>::k;
    using Base<Hash>::l;
    using Base<Hash>::h;
    using Base<Hash>::w;
    using Base<Hash>::data;
    Hash g[Params::MaxHashNum];
    unsigned int t[Params::MaxHashNum];
public:
    C(int _k, int _l, int _w): Base<Hash>(_k, _l, _w) {
        for (int i = 0; i < k; ++i) {
            g[i].SetSeed(1000 + k + i);
        }
    }
    void Insert(const char* str, const int len) {
        for (int i = 0; i < k; ++i) {
            data[i][h[i].Run(str, len) % l] += ((g[i].Run(str, len) & 1) ? 1 : -1);
        }
    }
    int Query(const char* str, const int len) {
        for (int i = 0; i < k; ++i) {
            t[i] = data[i][h[i].Run(str, len) % l];
            t[i] = (g[i].Run(str, len) & 1) ? t[i] : -t[i];
        }
        std::sort(t, t+k);
        int res = (t[k>>1] + t[(k-1)>>1])>>1;
        return res < 0 ? 0 : res < ((1<<(w-1))-1) ? res : ((1<<(w-1))-1);
    }
};
#endif