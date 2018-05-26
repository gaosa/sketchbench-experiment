#include "../sketch/all.h"
#include "../utils/Hash.h"
#include "../utils/Data.h"

#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template<class Sketch>
pair<double, double> analyze(
    Sketch& sk1, 
    Sketch& sk2, 
    unordered_map<string, int>& m1,
    unordered_map<string, int>& m2,
    const int threshold
) {
    unordered_set<string> s1, s2;
    for (const auto& p: m1) {
        int v1 = sk1.Query(p.first.c_str(), 4);
        int v2 = sk2.Query(p.first.c_str(), 4);
        int r1 = p.second;
        int r2 = m2[p.first];
        if (abs(v1 - v2) >= threshold) s1.insert(p.first);
        if (abs(r1 - r2) >= threshold) s2.insert(p.first);
    }
    for (const auto& p: m2) {
        if (m1.count(p.first)) continue;
        int v1 = sk1.Query(p.first.c_str(), 4);
        int v2 = sk2.Query(p.first.c_str(), 4);
        if (abs(v1 - v2) >= threshold) s1.insert(p.first);
        if (p.second >= threshold) s2.insert(p.first);
    }
    int cnt = 0;
    for (const auto& s: s1) {
        cnt += s2.count(s);
    }
    return make_pair(cnt*1.0/s1.size(), cnt*1.0/s2.size());
}

template<class Sketch>
void run(const char* filename, int k, int mem) {
    Data dat;
    dat.Open(filename);
    const int unit = (dat.Size() >> 3) / k;  // each window
    const int threshold = unit * 4.0 / 10000.0;
    double recall = 0, precision = 0;
    for (int i = 0; i < k; ++i) {
        auto sk1 = Sketch(3, mem/(3*24), 24);
        auto sk2 = Sketch(3, mem/(3*24), 24);
        unordered_map<string, int> m1, m2;
        char str[5];
        int idx = 0;
        while (dat.Next(str)) {
            ++idx;
            sk1.Insert(str, 4);
            ++m1[string(str, 4)];
            if (idx == unit) break;
        }
        idx = 0;
        while (dat.Next(str)) {
            ++idx;
            sk2.Insert(str, 4);
            ++m2[string(str, 4)];
            if (idx == unit) break;
        }
        auto p = analyze(sk1, sk2, m1, m2, threshold);
        recall += p.second;
        precision += p.first;
    }
    cout << recall / k << " " << precision / k << endl;
}

int main(int argc, char* argv[]) {
    char* filename = argv[1];
    string sk = argv[2];
    const int k = 64;

    for (int mem = 1<<15; mem <= (1<<18); mem += 1<<15) {
        if (sk == "a") run<A<Hash> >(filename, 64, mem);
        else if (sk == "c") run<C<Hash> >(filename, 64, mem);
        else if (sk == "cm") run<Cm<Hash> >(filename, 64, mem);
        else if (sk == "cmm") run<Cmm<Hash> >(filename, 64, mem);
        else if (sk == "cmm2") run<Cmm2<Hash> >(filename, 64, mem);
        else if (sk == "cu") run<Cu<Hash> >(filename, 64, mem);
        else if (sk == "csm") run<Csm<Hash> >(filename, 64, mem);
        else if (sk == "lcu") run<Lcu<Hash> >(filename, 64, mem);
        else if (sk == "sbf") run<Sbf<Hash> >(filename, 64, mem);
    }
    return 0;
}