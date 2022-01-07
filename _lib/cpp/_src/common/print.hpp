#pragma once
#include "../macros.hpp"

void print() {
    cout << '\n';
}

template<typename T>
void print(T out) {
    cout << out << '\n';
}

template<typename T1, typename T2>
void print(const pair<T1, T2> &p) {
    cout << p.first << ' ' << p.second << '\n';
}

template<typename T1, typename T2, typename T3>
void print(const tuple<T1, T2, T3> &tp) {
    cout << get<0>(tp) << ' ' << get<1>(tp) << ' ' << get<2>(tp) << '\n';
}

template<typename T1, typename T2, typename T3, typename T4>
void print(const tuple<T1, T2, T3, T4> &tp) { 
    cout << get<0>(tp) << ' ' << get<1>(tp) << ' ' << get<2>(tp) << ' ' << get<3>(tp) << '\n';
}

template<typename T1, typename T2>
void print(const vector<pair<T1, T2>> &V) {
    for (auto& p : V) print(p);
}

template<typename T>
void print(const vector<T> &V) {
    rep(i, V.size()) {
        cout << V[i];
        if (i != V.size()-1) cout << ' ';
    }
    cout << '\n';
}

template<typename T, size_t SZ>
void print(const array<T, SZ> &arr) {
    rep(i, arr.size()) {
        cout << arr[i];
        if (i != arr.size()-1) cout << ' ';
    }
    cout << '\n';
}

template<typename T>
void print(const deque<T> &que) {
    vector<T> V(ALL(que));
    print(V);
}

template<typename T>
void print(const set<T> &se) {
    vector<T> V(ALL(se));
    print(V);
}

#define debug(x) (cout << #x << ": ", print(x));
