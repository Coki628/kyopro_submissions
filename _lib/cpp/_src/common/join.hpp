#include "../macros.hpp"
#include "to_string.hpp"

template<typename T>
string join(const vector<T> &A, char separator=0) {
    int N = A.size();
    string res;
    rep(i, N) {
        res += tostr(A[i]);
        if (separator != 0 and i != N-1) res += separator;
    }
    return res;
}
