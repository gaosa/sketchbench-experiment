#include "../sketch/all.h"
#include "../utils/Hash.h"
#include "../utils/Data.h"

#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

template<class Sketch>
void task(Sketch& sk, Data& dat) {
    char str[4];
    unordered_map<string, int> m;
    while (dat.Next(str)) {
        sk.Insert(str, 4);
        ++m[string(str, 4)];
    }
    int aae = 0;
    for (const auto& p: m) {
        int real = p.second;
        int guess = sk.Query(p.first.c_str(), 4);
        int ae = real - guess;
        ae = ae < 0 ? -ae : ae;
        aae += ae;
    }
    cout << (double)aae / m.size() << endl;
}

int main() {
    Cu<Hash> cu(4, 65536, 16);
    Cm<Hash> cm(4, 65536, 16);
    A<Hash> a(4, 65536, 16);
    C<Hash> c(4, 65536, 16);
    Cmm<Hash> cmm(4, 65536, 16);
    Cmm2<Hash> cmm2(4, 65536, 16);
    Csm<Hash> csm(4, 65536, 16);
    Lcu<Hash> lcu(4, 65536, 16);
    Sbf<Hash> sbf(4, 65536, 16);
    Data dat;
    dat.Open("/Users/GSA/Desktop/local/sketchbench-DatasetAnalyzer/dataset/kosarak.dat", 4);
    task(cu, dat);
    dat.Reset();
    task(cm, dat);
    dat.Reset();
    task(a, dat);
    dat.Reset();
    task(c, dat);
    dat.Reset();
    task(cmm, dat);
    dat.Reset();
    task(cmm2, dat);
    dat.Reset();
    task(csm, dat);
    dat.Reset();
    task(lcu, dat);
    dat.Reset();
    task(sbf, dat);
}