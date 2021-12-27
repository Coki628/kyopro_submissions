#include "../macros.hpp"
#include "../common/toint.hpp"

// N進数文字列Sを10進数に
ll ntod(string S, ll n) {
    ll res = 0, k = 1;
    reverse(ALL(S));
    for (char &c : S) {
        res += k*toint(c);
        k *= n;
    }
    return res;
}
