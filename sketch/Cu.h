#ifndef CU_H
#define CU_H

#include "Base.h"
#include "Params.h"

#include <iostream>

template<class Hash>
class Cu: public Base<Hash> {
protected:
    using Base<Hash>::k;
    using Base<Hash>::l;
    using Base<Hash>::h;
    using Base<Hash>::w;
    using Base<Hash>::data;
    unsigned int t[Params::MaxHashNum];
public:
    const std::string Name = "cu";
    Cu(int _k, int _l, int _w): Base<Hash>(_k, _l, _w) {}
    void Insert(const char* str, const int len) {
        for (int i = 0; i < k; ++i) {
            t[i] = h[i].Run(str, len) % l;
        }
        int sm = data[0][t[0]];
        for (int i = 1; i < k; ++i) {
            int tt = data[i][t[i]];
            sm = sm < tt ? sm : tt; 
        }
        for (int i = 0; i < k; ++i) {
            data[i][t[i]] += (data[i][t[i]] == sm);
        }
    }
    int Query(const char* str, const int len) {
        int sm = data[0][h[0].Run(str, len) % l];
        for (int i = 1; i < k; ++i) {
            int tt = data[i][h[i].Run(str, len) % l];
            sm = sm < tt ? sm : tt;
        }
        return sm > ((1<<w)-1) ? ((1<<w)-1) : sm;
    }
};
#endif