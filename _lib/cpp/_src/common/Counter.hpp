#include "../macros.hpp"

template<typename T>
map<T, ll> Counter(const vector<T> &A) {
    map<T, ll> res;
    for (T a : A) {
        res[a]++;
    }
    return res;
}

template<typename T>
vector<ll> Counter(const vector<T> &A, int mx) {

    vector<ll> res(mx+1);
    for (T a : A) {
        res[a]++;
    }
    return res;
}

map<char, ll> Counter(const string &S) {
    map<char, ll> res;
    for (char c : S) {
        res[c]++;
    }
    return res;
}
