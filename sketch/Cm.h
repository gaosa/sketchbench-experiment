#ifndef CM_H
#define CM_H

#include "Cu.h"
#include "Params.h"

template<class Hash>
class Cm: public Cu<Hash> {
private:
    using Cu<Hash>::k;
    using Cu<Hash>::l;
    using Cu<Hash>::h;
    using Cu<Hash>::data;
public:
    Cm(int _k, int _l, int _w): Cu<Hash>(_k, _l, _w) {}
    void Insert(const char* str, const int len) {
        for (int i = 0; i < k; ++i) {
            ++data[i][h[i].Run(str, len) % l];
        }
    }
};
#endif