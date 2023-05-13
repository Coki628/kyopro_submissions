/*
・自力AC！
・集計しといてatcoderな文字かどうかで場合分け。
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
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    string S, T;
    cin >> S >> T;
    ll N = S.size();

    auto C1 = Counter(S);
    auto C2 = Counter(T);
    ll M = 26;
    map<char, ll> need1, need2;
    for (auto c : ascii_lowercase) {
        if (C1[c] < C2[c]) {
            need1[c] = C2[c] - C1[c];
        } else if (C1[c] > C2[c]) {
            need2[c] = C1[c] - C2[c];
        }
    }
    string atcoder = "atcoder";
    for (auto c : ascii_lowercase) {
        if (need1[c]) {
            if (count(ALL(atcoder), c)) {
                if (C1['@'] >= need1[c]) {
                    C1['@'] -= need1[c];
                } else {
                    No();
                    return;
                }
            } else {
                No();
                return;
            }
        } else if (need2[c]) {
            if (count(ALL(atcoder), c)) {
                if (C2['@'] >= need2[c]) {
                    C2['@'] -= need2[c];
                } else {
                    No();
                    return;
                }
            } else {
                No();
                return;
            }
        }
    }
    Yes();
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
