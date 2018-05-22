#include "../sketch/all.h"
#include "../utils/Hash.h"
#include "../utils/Data.h"

#include <unordered_map>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

// in this step, sketch and data are already inited
// return pair: freqs and time
template<class Sketch>
pair<vector<pair<int, int> >, vector<long long> >
run(Sketch& sk, Data& dat, int strByte = 4) {
    dat.Reset();
    char* str = new char[strByte];
    unordered_map<string, int> m;
    vector<long long> timesNano;
    auto begin = chrono::high_resolution_clock::now();
    while (dat.Next(str)) {
        sk.Insert(str, strByte);
    }
    auto end = chrono::high_resolution_clock::now();
    timesNano.push_back(chrono::duration_cast<chrono::nanoseconds>(end - begin).count());
    int cnt = 0;
    dat.Reset();
    while (dat.Next(str)) {
        ++cnt;
        ++m[string(str, strByte)];
    }
    timesNano.push_back(cnt);
    vector<pair<int, int> > res;
    int useless = 0;
    begin = chrono::high_resolution_clock::now();
    for (const auto& p: m) {
        useless += sk.Query(p.first.c_str(), strByte);
    }
    cout << useless << endl;
    end = chrono::high_resolution_clock::now();
    timesNano.push_back(chrono::duration_cast<chrono::nanoseconds>(end - begin).count());
    timesNano.push_back(m.size());
    for (const auto& p: m) {
        res.push_back(make_pair(p.second, sk.Query(p.first.c_str(), strByte)));
    }
    delete [] str;
    return make_pair(res, timesNano);
}

void save(const pair<vector<pair<int, int> >, vector<long long> >& result, const string& freqpath, const string& thrupath) {
    ofstream f;
    f.open(freqpath);
    for (const auto& p: result.first) {
        f << p.first << "\t" << p.second << endl;
    }
    f.close();
    f.open(thrupath);
    for (const auto& n: result.second) {
        f << n << endl;
    }
    f.close();
}

inline string genpath(string task, string dat, string sk, int k, int l, int w) {
    return "result/" + task + 
           "/" + dat + "/" + sk + 
           "/" + to_string(k) + "_" + 
           to_string(l) + "_" + to_string(w) + 
           ".txt";
}

template<class Sketch>
void init_run_save(const string& filepath, const string& filename, int k, int mem, int w = 24) {
    Sketch sk(k, mem/(k*w), w);
    Data dat;
    dat.Open(filepath.c_str());
    save(
        run(sk, dat),
        genpath("freq", filename, sk.Name, k, mem, w),
        genpath("thru", filename, sk.Name, k, mem, w)
    );
}

// wrapper for init_run_save
void sk_init_run_save(const string& sk, const string& filepath, const string& filename, int k, int mem, int w = 24) {
    if (sk == "a") { init_run_save<A<Hash> >(filepath, filename, k, mem, w);}
    else if (sk == "c") { init_run_save<C<Hash> >(filepath, filename, k, mem, w);}
    else if (sk == "cu") { init_run_save<Cu<Hash> >(filepath, filename, k, mem, w);}
    else if (sk == "cm") { init_run_save<Cm<Hash> >(filepath, filename, k, mem, w);}
    else if (sk == "cmm") { init_run_save<Cmm<Hash> >(filepath, filename, k, mem, w);}
    else if (sk == "cmm2") { init_run_save<Cmm2<Hash> >(filepath, filename, k, mem, w);}
    else if (sk == "lcu") { init_run_save<Lcu<Hash> >(filepath, filename, k, mem, w);}
    else if (sk == "csm") { init_run_save<Csm<Hash> >(filepath, filename, k, mem, w);}
    else if (sk == "sbf") { init_run_save<Sbf<Hash> >(filepath, filename, k, mem, w);}
    else { cout << "wrong sketch name" << endl; }
}

int main(int argc, char* argv[]) {
    
    const string sk = argv[1];
    const char* filepath = argv[2];
    const char* filename = argv[3];

    for (int k = 2, cnt = 0; k <= 9; ++k) {
        for (int mem = (1<<22); mem <= (1<<25); mem += (1<<22)) {
            sk_init_run_save(sk, filepath, filename, k, mem);
            cout << ++cnt << " " << 64 << endl;
        }
    }
    
    return 0;
}