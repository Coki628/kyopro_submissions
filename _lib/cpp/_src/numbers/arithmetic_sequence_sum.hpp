// 等差数列の和：(初項a, 公差d, 項数n)
template<typename T>
T arithmetic_sequence_sum(T a, T d, T n) {
    return (a*2+(n-1)*d)*n/2;
}

// 等差数列の和：(初項l, 末項r, 項数n)
// template<typename T>
// T arithmetic_sequence_sum(T l, T r, T n) {
//     return (l+r)*n/2;
// }
