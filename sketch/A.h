#ifndef A_H
#define A_H

#include "Cm.h"
#include "Params.h"
#include "string.h"

template<class Hash>
class A: public Cm<Hash> {
protected:
    char *filter;
    int *oldcnt, *newcnt;
    int sz = 0;
    int lookup(const char* str, const int len) {
        for (int i = 0; i < sz; ++i) {
            if (!memcmp(filter+i*Params::MaxStrByte, str, len)) {
                return i;
            }
        }
        return -1;
    }
    int minpos() {
        int res = 0, sm = newcnt[0];
        for (int i = 1; i < sz; ++i) {
            if (newcnt[i] < sm) {
                sm = newcnt[i];
                res = i;
            }
        }
        return res;
    }
public:
    A(int _k, int _l, int _w): Cm<Hash>(_k, _l, _w) {
        filter = new char [Params::MaxStrByte * Params::FilterSize];
        oldcnt = new int [Params::FilterSize];
        newcnt = new int [Params::FilterSize];
    }
    ~A() {
        delete [] filter;
        delete [] oldcnt;
        delete [] newcnt;
    }
    void Insert(const char* str, const int len) {
        int p = lookup(str, len);
        if (p != -1) {
            ++newcnt[p];
            return;
        }
        if (sz < Params::FilterSize) {
            memcpy(filter+Params::MaxStrByte*sz, str, len);
            newcnt[sz] = 1;
            oldcnt[sz] = 0;
            ++sz;
            return;
        }
        Cm<Hash>::Insert(str, len);
        int v = Cm<Hash>::Query(str, len);
        p = minpos();
        if (v > newcnt[p]) {
            if (newcnt[p] > oldcnt[p]) {
                for (int i = 0; i < newcnt[p] - oldcnt[p]; ++i) {
                    Cm<Hash>::Insert(filter+p*Params::MaxStrByte, len);
                }
            }
            memcpy(filter+p*Params::MaxStrByte, str, len);
            newcnt[p] = v;
            oldcnt[p] = v;
        }
    }
    int Query(const char* str, const int len) {
        int p = lookup(str, len);
        if (p != -1) {
            return newcnt[p];
        }
        return Cm<Hash>::Query(str, len);
    }
};
#endif