#include "../macros.hpp"

string bin(ll x) {
    string res;
    while (x) {
        if (x & 1) {
            res += '1';
        } else {
            res += '0';
        }
        x >>= 1;
    }
    reverse(ALL(res));
    if (res == "") res += '0';
    return res;
}
