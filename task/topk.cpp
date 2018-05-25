#include "../sketch/all.h"
#include "../utils/Hash.h"
#include "../utils/Data.h"

#include <unordered_map>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
struct Node {
    string s;
    int v;
    Node* next;
    Node(const string _s):s(_s),v(1),next(NULL){}
};

class Cache {
private:
    const int capacity;
    unordered_map<string, Node*> hash;
    Node* head = NULL;
public:
    Cache(int _capacity): capacity(_capacity) {}
    vector<pair<string, int> > Topk() {
        vector<pair<string, int> > res;
        auto t = head;
        while (t) {
            res.push_back(make_pair(t->s, t->v));
        }
        reverse(res.begin(), res.end());
        return res;
    }
    bool Insert(const string& str) {
        auto it1 = hash.find(str);
        if (it1 != hash.end()) {
            auto it2 = it1->second;
            ++it2->v;
            for (auto i = it2, j = it2->next; j && j->v < i->v; i = j, j = j->next) {
                swap(i->s, j->s);
                swap(i->v, j->v);
                swap(hash[i->s], hash[j->s]);
            }
            return true;
        }
        if (hash.size() < capacity) {
            auto t = new Node(str);
            t->next = head;
            head = t;
            hash[str] = head;
            return true;
        }
        return false;
    }
    bool Replace(string& str, int& v) {
        if (v > head->v) {
            hash[str] = head;
            hash.erase(head->s);
            swap(str, head->s);
            swap(v, head->v);
            return true;
        }
        return false;
    }
};*/

template<class Sketch>
void task(char* filename, int k) {
    auto sk = Sketch(3, (1<<24)/(3*24), 24);
    Data dat;
    dat.Open(filename);
    char str[5];
    unordered_map<string, int> cache;
    unordered_map<string, int> real;
    unordered_map<string, int> str2int;
    while (dat.Next(str)) {
        string s(str, 4);
        ++real[s];
        if (!str2int.count(s)) str2int[s] = str2int.size();
        if (cache.count(s)) ++ cache[s];
        else if (cache.size() < k) ++cache[s];
        else {
            int v = sk.Query(str, 4) + 1;
            int sm = ~(1<<31);
            string ss;
            for (const auto& p: cache) {
                if (p.second < sm) {
                    sm = p.second;
                    ss = p.first;
                }
            }
            if (sm >= v) {
                sk.Insert(str, 4);
            } else {
                cache.erase(ss);
                cache[s] = v;
                sk.Insert(ss.c_str(), 4);
            }
        }
    }
    vector<pair<string, int> > res1;
    for (const auto& p: cache) {
        res1.push_back(p);
    }
    sort(res1.begin(), res1.end(), [](const pair<string, int>& p1, const pair<string, int>& p2) {
        return p1.second > p2.second;
    });
    for (auto p: res1) {
        cout << str2int[p.first] << " " << p.second << endl;
    }
    cout << endl;
    vector<pair<string, int> > res2;
    for (const auto& p: real) res2.push_back(p);
    sort(res2.begin(), res2.end(), [](const pair<string, int>& p1, const pair<string, int>& p2) {
        return p1.second > p2.second;
    });
    for (int i = 0; i < k; ++i) {
        cout << str2int[res2[i].first] << " " << res2[i].second << endl;
    }
}

int main(int argc, char* argv[]) {
    string sk = argv[1];
    int k = atoi(argv[2]);
    char filename[] = "/home/wanghao/liuqianhui/SketchBench/formatted00.dat";
    if (sk == "a") task<A<Hash> >(filename, k);
    else if (sk == "c") task<C<Hash> >(filename, k);
    else if (sk == "cu") task<Cu<Hash> >(filename, k);
    else if (sk == "cm") task<Cm<Hash> >(filename, k);
    else if (sk == "cmm") task<Cmm<Hash> >(filename, k);
    else if (sk == "cmm2") task<Cmm2<Hash> >(filename, k);
    else if (sk == "csm") task<Csm<Hash> >(filename, k);
    else if (sk == "lcu") task<Lcu<Hash> >(filename, k);
    else if (sk == "sbf") task<Sbf<Hash> >(filename, k);
    return 0;
}