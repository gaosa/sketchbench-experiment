#ifndef CMM_H
#define CMM_H

#include "Cm.h"
#include "Params.h"
#include <algorithm>

template<class Hash>
class Cmm: public Cm<Hash> {
private:
    using Cm<Hash>::k;
    using Cm<Hash>::l;
    using Cm<Hash>::h;
    using Cm<Hash>::w;
    using Cm<Hash>::data;
    int tot = 0;
    int t[Params::MaxHashNum];
public:
    const std::string Name = "cmm";
    Cmm(int _k, int _l, int _w): Cm<Hash>(_k, _l, _w) {}
    void Insert(const char* str, const int len) {
        Cm<Hash>::Insert(str, len);
        ++tot;
    }
    int Query(const char* str, const int len) {
        for (int i = 0; i < k; ++i) {
            t[i] = data[i][h[i].Run(str, len) % l];
            t[i] -= (tot - t[i]) / (l - 1);
        }
        std::sort(t, t+k);
        int res = (t[k>>1] + t[(k-1)>>1])>>1;
        return res < 0 ? 0 : res < ((1<<w)-1) ? res : ((1<<w)-1);
    }
};
#endif