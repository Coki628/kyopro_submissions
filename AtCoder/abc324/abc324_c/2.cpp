/*
・なんとか自力AC。Cでこれは時間かけすぎた。
・ロリハで高速化してぶん殴る。
　あと、長さが違い過ぎるのを場合分けしておかないと、Tがでかすぎる時にやられる。
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

#include "string/RollingHash.hpp"

void solve() {
    ll N;
    cin >> N;
    string T;
    cin >> T;
    ll M = T.size();
    vector<string> S(N);
    cin >> S;

    RollingHash rh;
    auto check = [&rh](string S, string T) {
        ll n = S.size();
        ll m = T.size();
        if (n == m) {
            ll diff = 0;
            rep(i, n) {
                if (S[i] != T[i]) diff++;
            }
            if (diff <= 1) {
                return true;
            }
        } else {
            if (n > m) {
                swap(n, m);
                swap(S, T);
            }
            auto stable = rh.build(S);
            auto ttable = rh.build(T);
            auto shash = rh.query(stable, 0, n);
            rep(i, m) {
                auto t2hash = rh.combine(rh.query(ttable, 0, i), rh.query(ttable, i + 1, m), m - (i + 1));
                if (shash == t2hash) {
                    return true;
                }
            }
        }
        return false;
    };
    vector<ll> ans;
    rep(i, N) {
        ll n = S[i].size();
        if (abs(n - M) >= 2) {
            continue;
        }
        if (check(S[i], T)) {
            ans.eb(i);
        }
    }
    ans++;
    print(ans.size());
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
