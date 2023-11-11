/*
・自力AC！
・mapでシミュした。
　でもTL見てたらみんなスタックでやっててそれはそうになった。。
　しかもmapでやるにしても、判定Cのやつ1つだけでいいよね？
　まじで頭ついてなかったなー…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
// #define CAST_MINT_TO_LL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    string S;
    cin >> S;
    ll N = S.size();

    map<ll, char> mp;
    rep(i, N) {
        mp[i] = S[i];
    }
    auto itr1 = mp.begin();
    while (itr1 != mp.end()) {
        bool removed = false;
        auto [k1, v1] = *itr1;
        if (v1 == 'C' and itr1 != mp.begin()) {
            auto itr2 = prev(itr1);
            if (itr2 != mp.begin()) {
                auto itr3 = prev(itr2);
                auto [k2, v2] = *itr2;
                auto [k3, v3] = *itr3;
                string s = {v3, v2, v1};
                if (s == "ABC") {
                    mp.erase(itr1);
                    mp.erase(itr2);
                    itr1 = mp.erase(itr3);
                    removed = true;
                }
            }
        }
        if (v1 == 'B' and itr1 != mp.begin() and next(itr1) != mp.end()) {
            auto itr2 = prev(itr1);
            auto itr3 = next(itr1);
            auto [k2, v2] = *itr2;
            auto [k3, v3] = *itr3;
            string s = {v2, v1, v3};
            if (s == "ABC") {
                mp.erase(itr1);
                mp.erase(itr2);
                itr1 = mp.erase(itr3);
                removed = true;
            }
        }
        if (v1 == 'A' and next(itr1) != mp.end()) {
            auto itr2 = next(itr1);
            if (next(itr2) != mp.end()) {
                auto itr3 = next(itr2);
                auto [k2, v2] = *itr2;
                auto [k3, v3] = *itr3;
                string s = {v1, v2, v3};
                if (s == "ABC") {
                    mp.erase(itr1);
                    mp.erase(itr2);
                    itr1 = mp.erase(itr3);
                    removed = true;
                }
            }
        }
        if (not removed) {
            itr1++;
        }
    }
    string ans;
    for (auto [k, v] : mp) {
        ans += v;
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
