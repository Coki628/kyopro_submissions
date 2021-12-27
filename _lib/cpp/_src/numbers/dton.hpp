#include "../macros.hpp"

// 10進数をN進数文字列に(負数対応版)
string dton(ll num, ll n, char base='0') {
    string res;
    while (abs(num) > 0) {
        ll m = num % abs(n);
        num -= m;
        res += base+m;
        num /= n;
    }
    reverse(ALL(res));
    if (res != "") {
        return res;
    } else {
        return res+base;
    }
}

// 旧版
// string dton(ll num, ll n) {
//     string res;
//     ll m;
//     while (num > 0) {
//         tie(num, m) = divmod(num, n);
//         res += tochar(m);
//     }
//     reverse(ALL(res));
//     if (res != "") {
//         return res;
//     } else {
//         return "0";
//     }
// }
