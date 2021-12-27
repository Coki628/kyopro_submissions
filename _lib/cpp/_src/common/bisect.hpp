#include "../../template.hpp"

template<typename T>
int bisect_left(const vector<T> &A, T val, int lo=0) {
    return lower_bound(A.begin()+lo, A.end(), val) - A.begin();
}

template<typename T>
int bisect_right(const vector<T> &A, T val, int lo=0) {
    return upper_bound(A.begin()+lo, A.end(), val) - A.begin();
}
