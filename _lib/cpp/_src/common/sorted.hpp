#include "../base.hpp"

template<typename T>
vector<T> sorted(vector<T> A, bool reverse=false) {
    sort(ALL(A));
    if (reverse) std::reverse(ALL(A));
    return A;
}

string sorted(string S, bool reverse=false) {
    sort(ALL(S));
    if (reverse) std::reverse(ALL(S));
    return S;
}
