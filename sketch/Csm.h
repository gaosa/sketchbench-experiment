#ifndef CSM_H
#define CSM_H

#include "Base.h"
#include "Params.h"
#include "stdlib.h"

template<class Hash>
class Csm: public Base<Hash> {
protected:
    using Base<Hash>::k;
    using Base<Hash>::l;
    using Base<Hash>::h;
    using Base<Hash>::w;
    using Base<Hash>::data;
    int acc = 0, ave = 0;
public:
    Csm(int _k, int _l, int _w): Base<Hash>(_k, _l, _w) {}
    void Insert(const char* str, const int len) {
        int i = rand() % k;
        ++data[i][h[i].Run(str, len) % l];
        acc = (acc == l - 1) ? 0 : acc + 1;
        ave += (acc == 0);
    }
    int Query(const char* str, const int len) {
        int res = -ave;
        for (int i = 0; i < k; ++i) {
            res += data[i][h[i].Run(str, len) % l];
        }
        return res < 0 ? 0 : res < ((1<<w)-1) ? res : ((1<<w)-1);
    }
};
#endif