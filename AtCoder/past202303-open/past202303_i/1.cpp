/*
・きっちり自力AC！
・組み合わせ全列挙、ソート
・各自、手札と山札から作れる組み合わせを全探索して、
　枚数、文字、人番号で適切なソートをやればOK。
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
    ll N;
    cin >> N;
    string X;
    cin >> X;

    auto make = [](string X, string S) -> pll {
        vector<char> A(ALL(X)), B(ALL(S));
        vector<pll> vec;
        for (auto comb1 : combinations(A, 3)) {
            for (auto comb2 : combinations(B, 2)) {
                vector<pll> cur;
                map<char, ll> C;
                rep(i, 3) {
                    C[comb1[i]]++;
                }
                rep(i, 2) {
                    C[comb2[i]]++;
                }
                for (auto [k, v] : C) {
                    cur.eb(max(-v, -5LL), k - 'A');
                }
                sort(ALL(cur));
                vec.eb(cur[0]);
            }
        }
        sort(ALL(vec));
        return vec[0];
    };
    vector<array<ll, 3>> vec;
    rep(i, N) {
        string S;
        cin >> S;
        auto [a, b] = make(X, S);
        vec.pb({a, b, i});
    }
    sort(ALL(vec));
    ll ans = vec[0][2] + 1;
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
