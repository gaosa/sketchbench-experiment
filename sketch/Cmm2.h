#ifndef CMM2_H
#define CMM2_H

#include "Cu.h"
#include "Params.h"
#include <algorithm>

template<class Hash>
class Cmm2: public Cu<Hash> {
private:
    using Cu<Hash>::k;
    using Cu<Hash>::l;
    using Cu<Hash>::h;
    using Cu<Hash>::w;
    using Cu<Hash>::data;
    int tot = 0;
    int t[Params::MaxHashNum];
public:
    Cmm2(int _k, int _l, int _w): Cu<Hash>(_k, _l, _w) {}
    void Insert(const char* str, const int len) {
        Cu<Hash>::Insert(str, len);
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