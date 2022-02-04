#include "../base.hpp"

template<typename T>
vector<T> reversed(vector<T> A) {
    reverse(ALL(A));
    return A;
}
