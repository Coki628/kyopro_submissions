#include "../../template.hpp"

template<typename T>
vector<T> sorted(vector<T> A, bool reverse=false) {
    sort(ALL(A));
    if (reverse) std::reverse(ALL(A));
    return A;
}
