#ifndef LCU_H
#define LCU_H

#include "Cu.h"
#include "Params.h"

template<class Hash>
class Lcu: public Cu<Hash> {
private:
    using Cu<Hash>::k;
    using Cu<Hash>::l;
    using Cu<Hash>::h;
    using Cu<Hash>::data;
    int idx = 1, sz = 0;
public:
    const std::string Name = "lcu";
    Lcu(int _k, int _l, int _w): Cu<Hash>(_k, _l, _w) {}
    void Insert(const char* str, const int len) {
        ++sz;
        Cu<Hash>::Insert(str, len);
        if (sz != k * l) return;
        sz = 0;
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < l; ++j) {
                if (data[i][j] > 0 && data[i][j] <= idx) {
                    --data[i][j];
                }
            }
        }
        ++idx;
    }
};
#endif