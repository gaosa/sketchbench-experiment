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
    for (auto p: m) {
        int real = p.second;
        int guess = sk.Query(p.first.c_str(), 4);
        int ae = real - guess;
        ae = ae < 0 ? -ae : ae;
        aae += ae;
    }
    cout << (double)aae / m.size() << endl;
}

int main() {
    Cu<Hash> a(4, 65536, 16);
    Data dat;
    dat.Open("/Users/GSA/Desktop/local/sketchbench-DatasetAnalyzer/dataset/kosarak.dat", 4);
    task(a, dat);
}