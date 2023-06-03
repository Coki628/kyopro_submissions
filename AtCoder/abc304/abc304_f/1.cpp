/*
・自力ならず。。
・約数系包除
・途中まで書いて、重複あるじゃんダメじゃん、って詰んでた。
　TLで約数包除のキーワードを得たら話が見えて通せた。
　Eも詰まってて浅くしか考察できなかったとはいえ、ダメだったな。。
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
    string S;
    cin >> S;

    auto divs = divisors(N);
    sort(ALL(divs));
    ll M = divs.size();
    vector<mint> res(N + 1);
    rep(i, M - 1) {
        ll n = divs[i];
        vector<ll> ok(n, 1);
        rep(j, N) {
            if (S[j] == '.') {
                ok[j % n] = 0;
            }
        }
        ll d = N / n;
        res[d] = mint(2).pow(sum(ok));
        rep(j, d + d, N + 1, d) {
            res[d] -= res[j];
        }
    }
    mint ans = sum(res);
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
