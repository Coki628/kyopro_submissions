// 階乗(modなし)
template<typename T>
T factorial(T x) {
    T res = 1;
    for (T i=1; i<=x; i++) res *= i;
    return res;
}
